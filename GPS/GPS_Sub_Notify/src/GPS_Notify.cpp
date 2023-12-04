#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include<csignal>
#endif

#include<iostream>
#include<condition_variable>
#include<thread>
#include<mutex>
#include<stdint.h>
#include<vsomeip/vsomeip.hpp>
#include<chrono>
#include "sample-ids.hpp"
#include "GPS_Data.hpp"
#include "serdes.hpp"






class GPS_Producer
{
private:
std::shared_ptr<vsomeip::application> app_;
bool use_tcp_;
bool is_registered_;
bool be_quite_;

std::mutex payload_mutex_;

std::thread notify;




public:



        GPS_Producer(bool _use_tcp):app_(vsomeip::runtime::get()->create_application()),
                                    use_tcp_(_use_tcp),
                                    notify(std::bind(&GPS_Producer::notify_GPS))
        {

        }




        bool init()
        {

            if(!app_->init())
            {
                std::cout<<" Couldn't initialize the application "<<std::endl;
                return false;
            }

            app_->register_state_handler(std::bind(&GPS_Producer::on_state,this,std::placeholders::_1));

            std::set<vsomeip::eventgroup_t> its_groups;

            its_groups.insert(EVENTGROUP_ID);

            app_->offer_event(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,EVENT_ID,its_groups,
            vsomeip::event_type_e::ET_FIELD);


            {
                std::lock_guard<std::mutex> its_lock(payload_mutex_);
            }



        }


        

        void on_state(vsomeip::state_type_e _state)
        {

            std::cout<<" Application "<<app_->get_name()<<" is "
                    <<(_state==vsomeip::state_type_e::ST_REGISTERED?" Registered ":" Deregistered")<<std::endl;
            if(_state==vsomeip::state_type_e::ST_REGISTERED ? " Registered ": " Deregistered")
            {

                if(!is_registered_)
                {
                    is_registered_=true;
                }
            }
            else
            {
                is_registered_=false;
            }

        }


        void start()
        {
            app_->start();
        }



        #ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING

        void stop()
        {

        }


        #endif


        void notify_GPS()
        {

        }









};