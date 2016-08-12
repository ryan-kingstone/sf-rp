/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

command(engine, playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(CanUseVehicle(vehicleid, playerid)) {
			new string[128];
			new _engine, _lights, _alarm, _doors, _bonnet, _boot, _objective;
			GetVehicleParamsEx(vehicleid, _engine, _lights, _alarm, _doors, _bonnet, _boot, _objective);

			if(_engine == 1) {
				SetVehicleParamsEx(vehicleid, 0, _lights, _alarm, _doors, _bonnet, _boot, _objective);
				format(string, sizeof(string), "* %s has stopped the engine of the %s.", GetRPName(playerid), GetVehicleName(GetPlayerVehicleID(playerid)));
				CloseMessage(playerid, ACTION, string);
			}
			else {
				SetVehicleParamsEx(vehicleid, 1, _lights, _alarm, _doors, _bonnet, _boot, _objective);
				format(string, sizeof(string), "* %s has started the engine of the %s.", GetRPName(playerid), GetVehicleName(GetPlayerVehicleID(playerid)));
				CloseMessage(playerid, ACTION, string);
			}
		} else return SendErrorMessage(playerid, 2, "You do not have access to this vehicle.");
	}
	else return SendErrorMessage(playerid, 2, "You must be in a vehicle.");
	return 1;
}

command(lock, playerid, params[])
{
	new string[128];

	new vehicleid;
	vehicleid = GetNearestVehicle(playerid, 4.0);

	if(!VehicleExists(vehicleid)) return SendErrorMessage(playerid, 1, "You are too far away from a vehicle.");

	new _engine, _lights, _alarm, _doors, _bonnet, _boot, _objective;
	GetVehicleParamsEx(vehicleid, _engine, _lights, _alarm, _doors, _bonnet, _boot, _objective);

	if(CanUseVehicle(vehicleid, playerid))
	{
    	new Float:posX, Float:posY, Float:posZ;
    	GetPlayerPos(playerid, posX, posY, posZ);
    	PlayerPlaySound(playerid, 24600, posX, posY, posZ);

		if(_doors == 1) {
			// Unlock
			SetVehicleParamsEx(vehicleid, _engine, _lights, _alarm, 0, _bonnet, _boot, _objective);

			format(string, sizeof(string), "* %s has unlocked the %s.", GetRPName(playerid), GetVehicleName(vehicleid));
			CloseMessage(playerid, ACTION, string);
		} else if(_doors == 0) {
			// Lock
			SetVehicleParamsEx(vehicleid, _engine, _lights, _alarm, 1, _bonnet, _boot, _objective);

			format(string, sizeof(string), "* %s has locked the %s.", GetRPName(playerid), GetVehicleName(vehicleid));
			CloseMessage(playerid, ACTION, string);
		}
	} else {
		return SendErrorMessage(playerid, 1, "You do not have keys to that vehicle.");
	}
	return 1;
}