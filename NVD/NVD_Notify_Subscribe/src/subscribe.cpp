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
#include <stdint.h>
#include "../include/serdes.hpp"
#include <vsomeip/vsomeip.hpp>
#include "../include/sample-ids.hpp"
#include "declaration.hpp"

extern int count = 0;
class Subscriber
{
public:
    std::set<vsomeip::eventgroup_t> its_groups;

    Subscriber(bool _use_tcp) : app_(vsomeip::runtime::get()->create_application()), use_tcp_(_use_tcp)
    {
    }

    bool init()
    {
        if (!app_->init())
        {
            std::cerr << "Couldn't initialize application" << std::endl;
            return false;
        }
        std::cout << "Client settings [protocol="
                  << (use_tcp_ ? "TCP" : "UDP")
                  << "]"
                  << std::endl;

        app_->register_state_handler(
            std::bind(&Subscriber::on_state, this,
                      std::placeholders::_1));

        app_->register_message_handler(
            SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, EVENT_ID,
            std::bind(&Subscriber::on_message, this,
                      std::placeholders::_1));

        app_->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID,
                                            std::bind(&Subscriber::on_availability,
                                                      this,
                                                      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        std::set<vsomeip::eventgroup_t> its_groups;
        its_groups.insert(EVENTGROUP_ID);
        app_->request_event(
            SAMPLE_SERVICE_ID,
            SAMPLE_INSTANCE_ID,
            EVENT_ID,
            its_groups,
            vsomeip::event_type_e::ET_FIELD);

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
        app_->clear_all_handler();
        app_->unsubscribe(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, EVENTGROUP_ID);
        app_->release_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, EVENT_ID);
        app_->release_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
        app_->stop();
    }
#endif

    void on_state(vsomeip::state_type_e _state)
    {
        if (_state == vsomeip::state_type_e::ST_REGISTERED)
        {
            app_->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, 1, 0);
        }
    }

    void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
    {
        std::cout << "Service ["
                  << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
                  << "] is "
                  << (_is_available ? "available." : "NOT available.")
                  << std::endl;

        if (!_is_available)
        {
            app_->unsubscribe(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, EVENTGROUP_ID);
        }
        else
        {
            app_->subscribe(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, EVENTGROUP_ID, 1, EVENT_ID);
        }
    }

    void on_message(const std::shared_ptr<vsomeip::message> &_response)
    {
        // static int count=0;
        std::cout << "Inside on_message" << std::endl;
        std::stringstream its_message;
        std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
        std::vector<vsomeip_v3::byte_t> its_vector_data;

        for (vsomeip_v3::length_t i = 0; i < its_payload->get_length(); i++)
        {

            its_vector_data.push_back(its_payload->get_data()[i]);
        }
        struct newVehicleData nvd;
        fev::serdes<newVehicleData> dsr;
        nvd = dsr.deserialize(its_vector_data);

        std::cout << " Varibale :- " << nvd.variable << std::endl;
        std::cout << "nvd.MBC_perActEngTq=" << nvd.MBC_perActEngTq << std::endl;
        std::cout << "nvd.MBC_vWhlBasedVehSpd=" << nvd.MBC_vWhlBasedVehSpd << std::endl;
        std::cout << "nvd.MBC_perActEngTq=" << nvd.MBC_perActEngTq << std::endl;
    }

private:
    std::shared_ptr<vsomeip::application> app_;
    bool use_tcp_;
    // int count=0;
};

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
Subscriber *vdatasdv_ptr(nullptr);
void handle_signal(int _signal)
{
    if (vdatasdv_ptr != nullptr &&
        (_signal == SIGINT || _signal == SIGTERM))

        vdatasdv_ptr->stop();
}
#endif

int main(int argc, char **argv)
{
    bool use_tcp = false;

    std::string tcp_enable("--tcp");
    std::string udp_enable("--udp");

    int i = 1;
    while (i < argc)
    {
        if (tcp_enable == argv[i])
        {
            use_tcp = true;
        }
        else if (udp_enable == argv[i])
        {
            use_tcp = false;
        }
        i++;
    }

    Subscriber vdatasdv(use_tcp);
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    vdatasdv_ptr = &vdatasdv;
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
#endif
    if (vdatasdv.init())
    {
        vdatasdv.start();
        return 0;
    }
    else
    {
        return 1;
    }
}
