

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include<csignal>
#endif

#include<iostream>
#include<vsomeip/vsomeip.hpp>
#include<chrono>
#include<condition_variable>
#include<sstream>
#include<stdint.h>
#include "serdes.hpp"
#include "sample-ids.hpp"
#include "GPS_Data.hpp"


class SubscribeSample
{
private:
std::shared_ptr<vsomeip::application> app_;
bool usetcp_;

public:



            SubscribeSample(bool _usetcp):app_(vsomeip::runtime::get()->create_application()),
                                          usetcp_(_usetcp)
            {

            }




            bool init()
            {

                    if(!app_->init())
                    {
                        std::cout<<" \n Couldn't initialize application "<<std::endl;
                        return false;

                    }

                    std::cout<<" Client setting [protocol = "
                            <<(usetcp_? " TCP ":" UDP ")
                            <<"]"
                            <<std::endl;


                    app_->register_state_handler(
                        std::bind(&SubscribeSample::on_state,this,std::placeholders::_1));

                    app_->register_message_handler(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,EVENT_ID,std::bind(&SubscribeSample::on_message,this,std::placeholders::_1));

                    app_->register_availability_handler(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,std::bind(&SubscribeSample::on_availability,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));


                    std::set<vsomeip::eventgroup_t> its_groups;
                    its_groups.insert(EVENTGROUP_ID);
                    app_->request_event(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,EVENT_ID,its_groups,vsomeip::event_type_e::ET_FIELD);

                    return true;

            }



            #ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
            
                    void stop()
                    {
                        app_->clear_all_handler();
                        app_->unsubscribe(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,EVENTGROUP_ID);
                        app_->release_event(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,EVENT_ID);
                        app_->release_service(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID);
                        app_->stop();
                    }
            #endif



            void on_availability(vsomeip::service_t _service,vsomeip::instance_t _instance,bool _is_available)
            {
                std::cout<<" Service  "<<(_is_available ? "available ":"Not available ")<<std::endl;


                if(!_is_available)
                {
                    app_->unsubscribe(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,EVENTGROUP_ID);
                }
            }




            void start()
            {
                app_->start();
            }



            void on_message(const std::shared_ptr<vsomeip::message> &_response)
            {

                std::shared_ptr<vsomeip::payload> its_payload =_response->get_payload();
                std::vector<vsomeip_v3::byte_t> its_vector_data;

                for(vsomeip_v3::length_t i=0;i<its_payload->get_length();i++)
                {
                    its_vector_data.push_back(its_payload->get_data()[i]);
                }


                struct GPS_Data gdata;
                serdes<GPS_Data>dser;
                gdata=dser.deserialize(its_vector_data);

                std::cout<<" Altitude = "<<gdata.param1<<" Latitude = "<<gdata.param2<<" Longtitude = "<<gdata.param3<<std::endl;

            }




            void on_state(vsomeip::state_type_e  _state)
            {
                if(_state == vsomeip::state_type_e::ST_REGISTERED)
                {
                    app_->request_service(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,1,0);
                }
            }


};





#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
SubscribeSample *sub_ptr(nullptr);

void handle_signal(int _signal)
{
        if(sub_ptr!=nullptr && (_signal==SIGINT || _signal == SIGTERM) )
        {
            sub_ptr->stop();

        }

}
#endif



        int main(int argc,char **argv)
        {
            bool use_tcp=false;

            std::string tcp_enable("--tcp");
            std::string udp_enable("--udp");

            int i=1;

            while(i<argc)
            {
                if(tcp_enable==argv[i])
                {
                    use_tcp=true;
                }
                else if(udp_enable==argv[i])
                {
                    use_tcp=false;
                }
                i++;
            }



            SubscribeSample  sub(use_tcp);

            #ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING

                sub_ptr=&sub;
                signal(SIGINT,handle_signal);
                signal(SIGTERM,handle_signal);
            #endif

            if(sub.init())
            {
                sub.start();
                return 0;
            }
            else
            {
                return 1;
            }





        }