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
#include <chrono>
#include <mutex>
#include <stdint.h>
#include <vsomeip/vsomeip.hpp>
#include "../include/sample-ids.hpp"
#include "../include/serdes.hpp"
#include "declaration.hpp"
#include <vector>
#include <opencv2/opencv.hpp>

class NotifyNVD
{
public:
    NotifyNVD(bool _use_tcp, bool _be_quiet, uint32_t _cycle) : app_(vsomeip::runtime::get()->create_application()),
                                                                is_registered_(false),
                                                                use_tcp_(_use_tcp),
                                                                be_quiet_(_be_quiet),
                                                                cycle_(_cycle), blocked_(false),
                                                                running_(true),
                                                                is_offered_(false), notify_thread_nvd(std::bind(&NotifyNVD::notify_camdata, this))
    {
    }

    bool init()
    {
        std::lock_guard<std::mutex> its_lock(mutex_);

        if (!app_->init())
        {
            std::cerr << "Couldn't initialize application" << std::endl;
            return false;
        }
        app_->register_state_handler(
            std::bind(&NotifyNVD::on_state, this,
                      std::placeholders::_1));

        std::set<vsomeip::eventgroup_t> its_groups;
        its_groups.insert(EVENTGROUP_ID);
        app_->offer_event(
            SAMPLE_SERVICE_ID,
            SAMPLE_INSTANCE_ID,
            EVENT_ID,
            its_groups,
            vsomeip::event_type_e::ET_EVENT, std::chrono::milliseconds(200),
            false, true, nullptr, vsomeip::reliability_type_e::RT_UNKNOWN);
        {
            std::lock_guard<std::mutex> its_lock(payload_mutex_);
            payload_cam_data = vsomeip::runtime::get()->create_payload();
        }
        blocked_ = true;
        offer_camdata();

        return true;
    }

    void start()
    {
        app_->start();
    }

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING

    void stop()
    {
        running_ = false;
        blocked_ = true;
        condition_.notify_one();
        notify_condition_nvd.notify_one();
        notify_thread_nvd.join();
        app_->clear_all_handler();
        offer_thread_run.join();
        stop_offer();
        app_->stop();
    }

#endif

    void offer_camdata()
    {
        std::lock_guard<std::mutex> its_lock(notify_mutex_nvd);
        app_->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, 1, 0);

        notify_condition_nvd.notify_one();
    }

    void stop_offer()
    {
        app_->stop_offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
        is_offered_ = false;
    }

    void on_state(vsomeip::state_type_e _state)
    {
        std::cout << "Application " << app_->get_name() << " is "
                  << (_state == vsomeip::state_type_e::ST_REGISTERED ? "registered." : "deregistered.") << std::endl;

        if (_state == vsomeip::state_type_e::ST_REGISTERED)
        {
            if (!is_registered_)
            {
                is_registered_ = true;
            }
        }
        else
        {
            is_registered_ = false;
        }
    }

    void run()
    {
        std::unique_lock<std::mutex> its_lock(mutex_);
        while (!blocked_)
            condition_.wait(its_lock);
        bool is_offered_(true);
        while (running_)
        {
            if (is_offered_)
            {
                offer_camdata();
            }
            else
            {
                break;
            }
        }
    }

    void notify_camdata()
    {

        int i = 1;
        std::unique_lock<std::mutex> its_lock(notify_mutex_nvd);
        {
            notify_condition_nvd.wait(its_lock);
        }

        while (running_)
        {
            if (i > 10)
            {

            //    i=1;
            break;
            }
            std::string x = "../images/" + std::to_string(i) + ".jpg";
            i++;
            cv::Mat image1;
            std::cout << x << std::endl;
            image1 = cv::imread(x, cv::IMREAD_COLOR);
            std::vector<uint8_t> image_data;

            if (image1.empty())
            {
                std::cout << "Couldn't load the image " << std::endl;
            }
            else
            {
                int new_width = 300;  // Replace with your desired width
                int new_height = 200; // Replace with your desired height

                // Resize the image
                cv::Mat image;
                cv::resize(image1, image, cv::Size(new_width, new_height));

                for (int i = 0; i < image.rows; i++)
                {
                    for (int j = 0; j < image.cols; j++)
                    {
                        cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
                        image_data.push_back(pixel[0]); // Blue
                        image_data.push_back(pixel[1]); // Green
                        image_data.push_back(pixel[2]); // Red
                    }
                }
            }
            {
                std::lock_guard<std::mutex> its_lock(payload_mutex_);
                payload_cam_data->set_data(image_data);
                app_->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, EVENT_ID, payload_cam_data);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::cout << " Notified \n";
        }
    }

private:
    std::shared_ptr<vsomeip::application> app_;
    bool is_registered_;
    bool use_tcp_;
    bool be_quiet_;
    uint32_t cycle_;

    std::mutex mutex_;
    std::condition_variable condition_;
    bool blocked_;
    bool running_;
    bool is_offered_;
    std::mutex payload_mutex_;
    std::thread offer_thread_run;

    std::mutex notify_mutex_nvd;
    std::condition_variable notify_condition_nvd;
    std::shared_ptr<vsomeip::payload> payload_cam_data;
    std::thread notify_thread_nvd;
};

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
NotifyNVD *vdatasdvobj_ptr(nullptr);
void handle_signal(int _signal)
{
    if (vdatasdvobj_ptr != nullptr &&
        (_signal == SIGINT || _signal == SIGTERM))

        vdatasdvobj_ptr->stop();
}
#endif

int main()
{
    bool _use_tcp;
    bool _be_quiet;
    uint32_t _cycle;
    NotifyNVD vdatasdvobj(_use_tcp, _be_quiet, _cycle);
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    vdatasdvobj_ptr = &vdatasdvobj;
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
#endif
    if (vdatasdvobj.init())
    {
        vdatasdvobj.start();
        return 0;
    }
    else
    {
        return 1;
    }
}
