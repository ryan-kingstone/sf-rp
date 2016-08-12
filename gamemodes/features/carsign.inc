/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

new Text3D:callsign_text[MAX_VEHICLES];
new callsign_status[MAX_VEHICLES];


// sign removal on death moved to Vehicles.inc

// Commands:

command(carsign, playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(isnull(params)) return SendClientMessage(playerid,WHITE,"Server: /cs [text]");
		if(!callsign_status[vehicleid])
		{
			new string[128];
			format(string,sizeof(string), "%s",params);
			callsign_text[vehicleid] = Create3DTextLabel(string, 0xFFFFFFFF, 0.0, 0.0, 0.0, 50.0, 0, 1);
			Attach3DTextLabelToVehicle( callsign_text[vehicleid], vehicleid, -0.7, -1.9, -0.3);
			callsign_status[vehicleid] = 1;
		}
		else
		{
			Delete3DTextLabel(callsign_text[vehicleid]);
			callsign_status[vehicleid] = 0;
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid,WHITE,"You are not in a vehicle.");
		return 1;
	}
	return 1;
}

command(resetcs, playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid))
	{
		Delete3DTextLabel(callsign_text[vehicleid]);
		callsign_status[vehicleid] = 0;
	}
	else
   	{
    	SendClientMessage(playerid,WHITE,"You are not in a vehicle.");
    }
    return 1;
}

command(cs, playerid, params[])
{
	return cmd_carsign(playerid, params);
}