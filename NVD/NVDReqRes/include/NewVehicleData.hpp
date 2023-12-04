#ifndef NEW_VEHICLE_DATA_H
#define NEW_VEHICLE_DATA_H

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
};

#endif