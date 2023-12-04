// Copyright (C) 2014-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VSOMEIP_EXAMPLES_SAMPLE_IDS_HPP
#define VSOMEIP_EXAMPLES_SAMPLE_IDS_HPP

/*
#define IGN_SERVICE_ID       257
#define IGN_INSTANCE_ID      54
#define IGN_METHOD_ID        0x1100
#define IGN_EVENT_ID         32779
#define IGN_EVENTGROUP_ID    1
*/


#define IGN_SERVICE_ID 167 //0xf01
#define IGN_INSTANCE_ID 140
#define IGN_METHOD_ID 0
#define IGN_EVENT_ID 65411
#define IGN_EVENTGROUP_ID 1


// #define ACC_Activation_SERVICE_ID 61703
// #define ACC_Activation_INSTANCE_ID 1794
// #define ACC_Activation_METHOD_ID 0x3200
// #define ACC_Activation_EVENT_ID 45784
// #define ACC_Activation_EVENTGROUP_ID 32767

/*
#define ACC_Activation_SERVICE_ID 2222
#define ACC_Activation_INSTANCE_ID 2000
#define ACC_Activation_METHOD_ID 0x3200
#define ACC_Activation_EVENT_ID 2020
#define ACC_Activation_EVENTGROUP_ID 2200
*/

#define ACC_Activation_SERVICE_ID 61703
#define ACC_Activation_INSTANCE_ID 1793
#define ACC_Activation_METHOD_ID 0x3200
#define ACC_Activation_EVENT_ID 45784
#define ACC_Activation_EVENTGROUP_ID 32767

// Acceleration

#define Acceleration_SERVICE_ID 61699 //0xf103
#define Acceleration_INSTANCE_ID 769 //0x0301 
#define Acceleration_METHOD_ID 0x3200
#define Acceleration_EVENT_ID 45787
#define Acceleration_EVENTGROUP_ID 32766

// Break

#define Break_SERVICE_ID 61700
#define Break_INSTANCE_ID 1025
#define Break_METHOD_ID 0x3200
#define Break_EVENT_ID 45780
#define Break_EVENTGROUP_ID 32765

/*
#define BAG_SERVICE_ID 9999
#define BAG_INSTANCE_ID 9000
#define BAG_METHOD_ID 0x0422
#define BAG_EVENT_ID 9090
#define BAG_EVENTGROUP_ID 9900
*/

#define Gear_MODE_SERVICE_ID 61702
#define Gear_MODE_INSTANCE_ID 1537
#define Gear_MODE_EVENT_ID 45790
#define Gear_MODE_EVENTGROUP_ID 32759

#define DRIVE_MODE_SERVICE_ID 61701
#define DRIVE_MODE_INSTANCE_ID 1281
#define DRIVE_MODE_EVENT_ID 45794
#define DRIVE_MODE_EVENTGROUP_ID 32760


#define NEW_VEHICLE_SERVICE_ID       4609   //ox1201
#define NEW_VEHICLE_INSTANCE_ID      257
#define NEW_VEHICLE_METHOD_ID        0x2200
#define NEW_VEHICLE_EVENT_ID         45746
#define NEW_VEHICLE_EVENTGROUP_ID    32753

#endif // VSOMEIP_EXAMPLES_SAMPLE_IDS_HCLE