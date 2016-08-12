/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

new _VehicleSiren[MAX_VEHICLES],
	SirenObject[MAX_VEHICLES];

command(siren, playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		new VID = GetPlayerVehicleID(playerid);

		if(Vehicles[VID][Siren])
		{
			if(_VehicleSiren[VID] == 0)
			{
				_VehicleSiren[VID] = 1;
				SirenObject[VID] = CreateObject(18646, 10.0, 10.0, 10.0, 0, 0, 0);
				AttachObjectToVehicle(SirenObject[VID], VID, 0.0, 0.75, 0.275, 0.0, 0.1, 0.0);
				return 1;
			} else
			{
				_VehicleSiren[VID] = 0;
				DestroyObject(SirenObject[VID]);
				return 1;
			}
			} else return SendErrorMessage(playerid, 2, "This vehicle does not have a siren.");
	} else return SendErrorMessage(playerid, 2, "You must be in a vehicle.");
}
