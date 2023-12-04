// Copyright (C) 2014-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
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


class clientSample {
public:
    clientSample(bool _use_tcp, bool _be_quiet, uint32_t _cycle)
        : app(vsomeip::runtime::get()->create_application()),
          requestNVD(vsomeip::runtime::get()->create_request(_use_tcp)),
                 
          use_tcp_(_use_tcp),
          be_quiet_(_be_quiet),
          cycle_(_cycle),
          running_(true),
          blocked_(false),
          is_available_(false),
          sender_(std::bind(&clientSample::run, this)) {
    }

    bool init() {
        if (!app->init()) {
            std::cerr << "Couldn't initialize application" << std::endl;
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

        app->register_state_handler(
                std::bind(
                    &clientSample::onState,
                    this,
                    std::placeholders::_1));

        app->register_message_handler(
                SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, vsomeip::ANY_METHOD,
                std::bind(&clientSample::onMessage,
                          this,
                          std::placeholders::_1));

        requestNVD->set_service(SAMPLE_SERVICE_ID);
        requestNVD->set_instance(SAMPLE_INSTANCE_ID);
        requestNVD->set_method(SAMPLE_METHOD_ID);

        std::shared_ptr< vsomeip::payload > its_tpms_payload = vsomeip::runtime::get()->create_payload();
        std::vector< vsomeip::byte_t > its_tpms_payload_data;
        for (std::size_t i = 0; i < 10; ++i) its_tpms_payload_data.push_back(i % 256);
        its_tpms_payload->set_data(its_tpms_payload_data);
        requestNVD->set_payload(its_tpms_payload);


       

        app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID,
                std::bind(&clientSample::onAvailability,
                          this,
                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        
     

        return true;
    }

    void start() {
        app->start();
    }

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    /*
     * Handle signal to shutdown
     */
    void stop() {
        running_ = false;
        blocked_ = true;
        app->clear_all_handler();
        app->release_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
        
        condition_.notify_one();
        sender_.join();
        app->stop();  
    }
#endif

    void onState(vsomeip::state_type_e _state) {
        if (_state == vsomeip::state_type_e::ST_REGISTERED) {
            app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
            
        }
    }

    void onAvailability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
        std::cout << "Service ["
                << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
                << "] is "
                << (_is_available ? "available." : "NOT available.")
                << std::endl;

        if (SAMPLE_SERVICE_ID == _service && SAMPLE_INSTANCE_ID == _instance) {
            if (is_available_  && !_is_available) {
                is_available_ = false;
            } else if (_is_available && !is_available_) {
                is_available_ = true;
                send();
            }
        }

       
    }

   

    void onMessage(const std::shared_ptr< vsomeip::message > &_response) {
        std::cout << "Received a response from Service ["
               
                << std::endl;

        std::shared_ptr<vsomeip::payload> pl = _response->get_payload(); 
        vsomeip_v3::byte_t *rec_payload_data = pl->get_data();
        std::vector<vsomeip::byte_t> s;
        for(vsomeip_v3::length_t i=0;i<pl->get_length();i++)
        {
          //  std::cout<<std::hex<<(int)*(rec_payload_data+i)<<" - ";
            s.push_back(*(rec_payload_data+i));
        }
        std::cout<<"\ns data : ";
        for(vsomeip_v3::length_t i=0;i< s.size();i++)
        {
           // std::cout<<std::hex<<(int)s.at(i)<<" - ";
        }
        fev::serdes<newVehicleData> sr;
        newVehicleData nvd = sr.deserialize(s);
        std::cout<<" Varibale :- "<<nvd.variable<<std::endl;
        std::cout<<"nvd.MBC_perActEngTq="<<nvd.MBC_perActEngTq<<std::endl;
        std::cout<<"nvd.MBC_vWhlBasedVehSpd="<<nvd.MBC_vWhlBasedVehSpd<<std::endl;
        std::cout<<"nvd.MBC_perActEngTq="<<nvd.MBC_perActEngTq<<std::endl;
            

         if (is_available_)
            send();
    }

    void send() {
        if (!be_quiet_)
        {
            std::lock_guard< std::mutex > its_lock(mutex_);
            blocked_ = true;
            condition_.notify_one();
        }
    }

    void run() {
        while (running_) {
            {
                std::unique_lock<std::mutex> its_lock(mutex_);
                while (!blocked_) condition_.wait(its_lock);
                if (is_available_) {
                    app->send(requestNVD);
                    std::cout << "\nClient/Session ["
                            << std::setw(4) << std::setfill('0') << std::hex << requestNVD->get_client()
                            << "/"
                            << std::setw(4) << std::setfill('0') << std::hex << requestNVD->get_session()
                            << "] sent a request to Service ["
                            << std::setw(4) << std::setfill('0') << std::hex << requestNVD->get_service()
                            << "."
                            << std::setw(4) << std::setfill('0') << std::hex << requestNVD->get_instance()
                            << "]"
                            << std::endl;
                    blocked_ = false;
                }

                
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(cycle_));
        }
    }

private:
    std::shared_ptr< vsomeip::application > app;
    std::shared_ptr< vsomeip::message > requestNVD;
   


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
};

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    clientSample *its_sample_ptr(nullptr);
    void handle_signal(int _signal) {
        if (its_sample_ptr != nullptr &&
                (_signal == SIGINT || _signal == SIGTERM))
            its_sample_ptr->stop();
    }
#endif

int main(int argc, char **argv) {
    bool use_tcp = false;
    bool be_quiet = false;
    uint32_t cycle = 1000; // Default: 1s

    std::string tcp_enable("--tcp");
    std::string udp_enable("--udp");
    std::string quiet_enable("--quiet");
    std::string cycle_arg("--cycle");

    int i = 1;
    while (i < argc) {
        if (tcp_enable == argv[i]) {
            use_tcp = true;
        } else if (udp_enable == argv[i]) {
            use_tcp = false;
        } else if (quiet_enable == argv[i]) {
            be_quiet = true;
        } else if (cycle_arg == argv[i] && i+1 < argc) {
            i++;
            std::stringstream converter;
            converter << argv[i];
            converter >> cycle;
        }
        i++;
    }

    clientSample its_sample(use_tcp, be_quiet, cycle);
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
