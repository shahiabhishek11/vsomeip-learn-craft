#ifndef NEW_VEHICLE_DATA_H
#define NEW_VEHICLE_DATA_H

#define UserSendStructure CVD
#define UserReceivedStructure newVehicleData
#include<iostream>
struct newVehicleData
{
	
		float timestamp;
      	float MBC_perAccrPedl;
		int MBC_percDrvDmdEngTq;
		int MBC_perActEngTq;
		double  MBS_TransCurrentGear;
		double MBC_vWhlBasedVehSpd;
		float MBC_BrakeSwitch;
		float PCM_DrvCmdPerc;
        float previousVelocity;
		char variable;


	void read_data_from_CSV()
    {
        timestamp = 0;
      	MBC_perAccrPedl=0;
	MBC_percDrvDmdEngTq=0;
	MBC_perActEngTq=0;
	MBS_TransCurrentGear=0;
	MBC_vWhlBasedVehSpd=0;
	MBC_BrakeSwitch=0;
	PCM_DrvCmdPerc=0;
        previousVelocity=0;
	variable=0;
    }

    void write_data_to_CSV()
    {
         std::cout<<"timestamp"<<timestamp<<" MBC_perAccrPedl "<<MBC_perAccrPedl<<" MBC_percDrvDmdEngTq "<<MBC_percDrvDmdEngTq<<" MBC_perActEngTq "<<MBC_perActEngTq<<" MBS_TransCurrentGear ";
    }
};

#endif