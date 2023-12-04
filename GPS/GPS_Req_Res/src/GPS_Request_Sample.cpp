#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include<csignal>
#endif



#include <chrono>
#include <condition_variable>
#include <iostream>
#include <sstream>
#include <thread>
#include <vsomeip/vsomeip.hpp>
#include "../include/GPS_sample_ids.hpp"

class Request_Sample
{
private:
    std::shared_ptr<vsomeip::application> app_;
    std::shared_ptr<vsomeip::message> request_;
    bool use_tcp_;
    bool be_quiet_;
    uint32_t cycle_;
    vsomeip::session_t session_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool running_;
    bool blocked_;
    bool is_available_;
    std::thread sender_;

public:
    Request_Sample(bool _use_tcp, bool _be_quiet, uint32_t _cycle)
        : app_(vsomeip::runtime::get()->create_application()),
          request_(vsomeip::runtime::get()->create_request(_use_tcp)),
          use_tcp_(_use_tcp),
          be_quiet_(_be_quiet),
          cycle_(_cycle),
          running_(true),
          blocked_(false),
          is_available_(false),
          sender_(std::bind(&Request_Sample::run,this))
    {
    }

    bool init()
    {

        if(!app_->init())
        {
            std::cout<<" \n Couldn't initialize application "<<std::endl;
            return false;
        }


          std::cout << "Client settings [protocol="
                  << (use_tcp_ ? "TCP" : "UDP")
                  << ":quiet="
                  << (be_quiet_ ? "true" : "false")
                  << ":cycle="
                  << cycle_
                  << "]"
                  << std::endl;



        app_->register_state_handler( std::bind(
            &Request_Sample::on_state,
            this,
            std::placeholders::_1));

        app_->register_message_handler(
            vsomeip::ANY_SERVICE,INSTANCE_ID, vsomeip::ANY_METHOD,
            std::bind(&Request_Sample::on_message,
            this,
            std::placeholders::_1)); 


        request_->set_service(SERVICE_ID);
        request_->set_instance(INSTANCE_ID);
        request_->set_method(METHOD_ID);



        std::shared_ptr< vsomeip::payload > its_payload=vsomeip::runtime::get()->create_payload();
        std::vector< vsomeip::byte_t > its_payload_data;

        for(std::size_t i=0;i<10;i++)
        its_payload_data.push_back(i%256);
        its_payload->set_data(its_payload_data);
        request_->set_payload(its_payload);


        app_->register_availability_handler(SERVICE_ID,INSTANCE_ID,
                                    std::bind(&Request_Sample::on_availability,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));

        // app_->register_availability_handler(SERVICE_ID+1,INSTANCE_ID+1,
        //                             std::bind(&Request_Sample::on_availability,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
   
       return true;
    }





  void start()
    {
        app_->start();
    }


#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING


    void stop()
    {
        running_=false;
        blocked_=true;
        app_->clear_all_handler();
        app_->release_service(SERVICE_ID,INSTANCE_ID);
        condition_.notify_one();
        sender_.join();
        app_->stop();

    }

#endif








    void on_availability(vsomeip::service_t _service,vsomeip::instance_t _instance,bool _is_availabile)
    {
            std::cout<<" Service [ "
                    <<(is_available_ ? "available ": "NOT available")<<std::endl;


            if(SERVICE_ID == _service  && INSTANCE_ID == _instance )
            {
                if(is_available_  && !_is_availabile )
                    is_available_=false;
                else if(_is_availabile && !is_available_)
                {
                    is_available_=true;
                    send();
                }
            }



    }




    void on_message(const std::shared_ptr< vsomeip::message> &_response)
    {
        std::cout<<" \n Received a response from a Service ";
        if(is_available_)
        send();

    }


    void run()
    {

        while( running_){
        {
            std::unique_lock<std::mutex> its_lock(mutex_);

            while(!blocked_)
            condition_.wait(its_lock);

            if(is_available_)
            {
                app_->send(request_);
                std::cout<<" Client Session ....";
                blocked_=false;
            }

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(cycle_));
        }
    }


    void send()
    {
        if(!be_quiet_)
        {
            std::lock_guard< std::mutex > its_lock(mutex_);
            blocked_=true;
            condition_.notify_one(); 
        }
    }


    void on_state(vsomeip::state_type_e _state)
    {
            if(_state == vsomeip::state_type_e::ST_REGISTERED)
            {
                app_->request_service(SERVICE_ID,INSTANCE_ID);
            }
    }

  

};


#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING

    Request_Sample *rq_ptr(nullptr);

    void handle_signal(int _signal)
    {
        if(rq_ptr != nullptr && (_signal==SIGINT || _signal == SIGTERM))
        rq_ptr->stop();
    }

#endif







int main()
{

    bool use_tcp = false;
    bool be_quiet = false;
    uint32_t cycle = 1000;

    Request_Sample rq(use_tcp, be_quiet, cycle);

    #ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING

        rq_ptr=&rq;
        signal(SIGINT,handle_signal);
        signal(SIGTERM,handle_signal);

    #endif

    if (rq.init())
    {
        rq.start();
        return 0;
    }
    else
    {
        return 1;
    }
}