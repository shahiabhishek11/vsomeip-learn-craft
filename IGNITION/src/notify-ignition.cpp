// Copyright i(C) 2014-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include <csignal>
#endif
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>

#include <vsomeip/vsomeip.hpp>
#include "sample-ids.hpp"








class service_sample 
{
    public:
            service_sample(bool _use_tcp, uint32_t _cycle) :
            app_(vsomeip::runtime::get()->create_application()),
            is_registered_(false),
            use_tcp_(_use_tcp),
            cycle_(_cycle),
            blocked_(false),
            running_(true),
            is_offered_(false),
            ign_value(0),
            offer_thread_(std::bind(&service_sample::run, this)),
            notify_thread_(std::bind(&service_sample::notify_ign, this))
            {

            }

    bool init() 
    {
        std::lock_guard<std::mutex> its_lock(mutex_);

        if (!app_->init()) {
            std::cerr << "Couldn't initialize application" << std::endl;
            return false;
        }
        app_->register_state_handler(
                std::bind(&service_sample::on_state, this,
                        std::placeholders::_1));
                          

	//NOTIFY IGNITION
        std::set<vsomeip::eventgroup_t> its_groups_ign;
        its_groups_ign.insert(IGN_EVENTGROUP_ID);
        app_->offer_event(
                IGN_SERVICE_ID,
                IGN_INSTANCE_ID,
                IGN_EVENT_ID,
                its_groups_ign,
                vsomeip::event_type_e::ET_EVENT, std::chrono::milliseconds::zero(),
                false, true, nullptr, vsomeip::reliability_type_e::RT_UNKNOWN);
        
  

        


        {
            std::lock_guard<std::mutex> its_lock(payload_mutex_);
            payload_ign = vsomeip::runtime::get()->create_payload();
           
        }
    
        blocked_ = true;
        condition_.notify_one();
        return true;
    }

    void start() 
    {
        app_->start();
    }

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    /*
     * Handle signal to shutdown
     */
    void stop() 
    {
        running_ = false;
        notify_condition_.notify_one();
       // notify_condition_newVehicle.notify_one();
        app_->clear_all_handler();
        stop_offer();
        offer_thread_.join();
        notify_thread_.join();
       // offer_thread_newVehicle.join();
       // notify_thread_newVehicle.join();
        app_->stop();
    }

#endif

    void offer() 
    {
        std::lock_guard<std::mutex> its_lock(notify_mutex_);
        app_->offer_service(IGN_SERVICE_ID, IGN_INSTANCE_ID,1,0);
    
        is_offered_ = true;
        notify_condition_.notify_one();
    }


    void stop_offer() {
        app_->stop_offer_service(IGN_SERVICE_ID, IGN_INSTANCE_ID,1,0);
        is_offered_ = false;
    }



    void on_state(vsomeip::state_type_e _state) {
        std::cout << "Application " << app_->get_name() << " is "
        << (_state == vsomeip::state_type_e::ST_REGISTERED ?
                "registered." : "deregistered.") << std::endl;

        if (_state == vsomeip::state_type_e::ST_REGISTERED) {
            if (!is_registered_) {
                is_registered_ = true;
            }
        } else {
            is_registered_ = false;
        }
    }

  

    void run() {
        std::unique_lock<std::mutex> its_lock(mutex_);
        while (!blocked_)
            condition_.wait(its_lock);

        bool is_offer(true);

        while (running_) {
            if (is_offer)
             {   
                offer();
               
             }else
                stop_offer();

            for (int i = 0; i < 10 && running_; i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

           
        }
    }

    void notify_ign() 
    {
	    std::cout<<"notify_ign called"<<std::endl;
	
         

        vsomeip::byte_t its_data[10];
        uint32_t its_size = 1;

        while (running_) {
            std::unique_lock<std::mutex> its_lock(notify_mutex_);
            while (!is_offered_ && running_)
                notify_condition_.wait(its_lock);
            while (is_offered_ && running_) {
                if (its_size == sizeof(its_data))
                    its_size = 1;

                for (uint32_t i = 0; i < its_size; ++i)
                {
                    if(i%2==0)
                    {
                            its_data[i] = 0;
                    }
                    else
                    {
                         its_data[i] = 1;
                    }
                }
                    

                {
                    std::lock_guard<std::mutex> its_lock(payload_mutex_);
                    payload_ign->set_data(its_data, its_size);

                   
                    app_->notify(IGN_SERVICE_ID, IGN_INSTANCE_ID,IGN_EVENT_ID, payload_ign);
                }

                its_size++;

                std::this_thread::sleep_for(std::chrono::milliseconds(cycle_));
            }
        }


    }


    
        
    private:
    std::shared_ptr<vsomeip::application> app_;
    bool is_registered_;
    bool use_tcp_;
    uint32_t cycle_;
   

    std::mutex mutex_;
    std::condition_variable condition_;
    bool blocked_;
    bool running_;
    int ign_value ;

    std::mutex notify_mutex_;
    std::condition_variable notify_condition_;
    bool is_offered_;

    std::mutex payload_mutex_;
    std::shared_ptr<vsomeip::payload> payload_ign;
    
    std::thread offer_thread_;
    std::thread notify_thread_;
    
};

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    service_sample *its_sample_ptr(nullptr);
    void handle_signal(int _signal) {
        if (its_sample_ptr != nullptr &&
                (_signal == SIGINT || _signal == SIGTERM))
            its_sample_ptr->stop();
    }
#endif



int main(int argc, char **argv) {
    
	
	bool use_tcp = false;
    uint32_t cycle = 1000; // default 1s
    
    //init_device();

    std::string tcp_enable("--tcp");
    std::string udp_enable("--udp");
    std::string cycle_arg("--cycle");

    for (int i = 1; i < argc; i++) {
        if (tcp_enable == argv[i]) {
            use_tcp = true;
            break;
        }
        if (udp_enable == argv[i]) {
            use_tcp = false;
            break;
        }

        if (cycle_arg == argv[i] && i + 1 < argc) {
            i++;
            std::stringstream converter;
            converter << argv[i];
            converter >> cycle;
        }
    }


    service_sample its_sample(use_tcp, cycle);
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
