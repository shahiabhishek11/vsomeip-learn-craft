
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include <csignal>
#endif


#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#include <vsomeip/vsomeip.hpp>

#include "sample-ids.hpp"
#include "serdes.hpp"
#include "NewVehicleData.hpp"




class serviceSample
{
    public:
serviceSample(bool _use_static_routing) :
            app(vsomeip::runtime::get()->create_application()),
            is_registered_(false),
            use_static_routing_(_use_static_routing),
            blocked_(false),
            running_(true),
            offer_thread_(std::bind(&serviceSample::run, this)) {
    }

    bool init() {
        std::lock_guard<std::mutex> its_lock(mutex_);

        if (!app->init()) {
            std::cerr << "Couldn't initialize application" << std::endl;
            return false;
        }

        app->register_state_handler(
                std::bind(&serviceSample::onState, this,
                        std::placeholders::_1));
        

        app->register_message_handler(
                SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID,
                std::bind(&serviceSample::onMessage, this,
                        std::placeholders::_1));

        

        std::cout << "Static routing " << (use_static_routing_ ? "ON" : "OFF")
                  << std::endl;

        return true;
    }

    void start() {
        app->start();
    }

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
   
    void stop() {
        running_ = false;
        blocked_ = true;
        app->clear_all_handler();
        stopOffer();
        condition_.notify_one();
        offer_thread_.join();
        app->stop();
    }
#endif

    void offer() {
        app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
      
    }

    void stopOffer() {
        app->stop_offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
        
    }

    void onState(vsomeip::state_type_e _state) {
        std::cout << "Application " << app->get_name() << " is "
                << (_state == vsomeip::state_type_e::ST_REGISTERED ?
                        "registered." : "deregistered.")
                << std::endl;

        if (_state == vsomeip::state_type_e::ST_REGISTERED) {
            if (!is_registered_) {
                is_registered_ = true;
                blocked_ = true;
                condition_.notify_one();
            }
        } else {
            is_registered_ = false;
        }
    }

   

    void onMessage(const std::shared_ptr<vsomeip::message> &_request) {
       

        std::shared_ptr<vsomeip::message> its_response
            = vsomeip::runtime::get()->create_response(_request);

        std::shared_ptr<vsomeip::payload> its_payload
            = vsomeip::runtime::get()->create_payload();
        std::vector<vsomeip::byte_t> its_payload_data;

        //printing client id
        std::cout<<"Sending data to client "<<std::endl;

        fev::serdes<newVehicleData> sr;
        newVehicleData nvd;
        nvd.variable='N';
        nvd.MBC_perActEngTq=90.88;
        nvd.MBC_vWhlBasedVehSpd=89.0;
        nvd.MBC_perActEngTq=111;
        
        its_payload_data = sr.serialize(nvd);

        for(int i=0;i< its_payload_data.size(); i++)
        {
          //  std::cout<<i<<" "<<std::hex<<(int)its_payload_data.at(i)<<" - ";
        }

        its_payload->set_data(its_payload_data);
        its_response->set_payload(its_payload);

        app->send(its_response);
    }

    void run() {
        std::unique_lock<std::mutex> its_lock(mutex_);
        while (!blocked_)
            condition_.wait(its_lock);

        bool is_offer(true);

        if (use_static_routing_) {
            offer();
            while (running_);
        } else {
            while (running_) {
                if (is_offer)
                    offer();
                else
                    stopOffer();

                for (int i = 0; i < 10 && running_; i++)
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                is_offer = !is_offer;
            }
        }
    }

private:
    std::shared_ptr<vsomeip::application> app;
    bool is_registered_;
    bool use_static_routing_;

    std::mutex mutex_;
    std::condition_variable condition_;
    bool blocked_;
    bool running_;

    // blocked_ must be initialized before the thread is started.
    std::thread offer_thread_;
};






#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    serviceSample *its_sample_ptr(nullptr);
    void handle_signal(int _signal) {
        if (its_sample_ptr != nullptr &&
                (_signal == SIGINT || _signal == SIGTERM))
            its_sample_ptr->stop();
    }
#endif

int main(int argc, char **argv) {
    bool use_static_routing(false);

    std::string static_routing_enable("--static-routing");

    for (int i = 1; i < argc; i++) {
        if (static_routing_enable == argv[i]) {
            use_static_routing = true;
        }
    }

    serviceSample its_sample(use_static_routing);
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    its_sample_ptr = &its_sample;
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
#endif
    if (its_sample.init()) {
        its_sample.start();
        return 0;
    } else {
        return 1;
    }
}



  