/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

// level 1 commands:

command(adminhelp, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 1)
    {
    	SendClientMessage(playerid, LIRED, "Commands available to you:");
    	SendClientMessage(playerid, GREY, "LEVEL 1: /adminduty (/aduty), /a(dminchat), /kick, /ban /gotopos /gotoveh /gotobiz");

    	if(Player[playerid][AdminLevel] >= 2)
    	{
			SendClientMessage(playerid, GREY, "LEVEL 2: /setskin");
    	}

    	if(Player[playerid][AdminLevel] >= 3)
    	{
			SendClientMessage(playerid, GREY, "LEVEL 3: /tog(gle)ooc /reloadveh /reloadbiz /setparkingspot /addfactionvehicle (/afv)");
			SendClientMessage(playerid, GREY, "LEVEL 3: /setfaction");
    	}

    	if(Player[playerid][AdminLevel] >= 4)
    	{
			SendClientMessage(playerid, GREY, "LEVEL 4: /veh(icle), /giveweapon (/gw), /fix");
    	}

    	if(Player[playerid][AdminLevel] >= 5)
    	{
			SendClientMessage(playerid, GREY, "LEVEL 5: /jetpack");
    	}


    }
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(ah, playerid, params[])
{
	return cmd_adminhelp(playerid, params);
}

command(adminduty, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 1)
	{
		new string[70];
		if(!AdminDuty[playerid]) 
		{
			AdminDuty[playerid] = 1;
            format(string, sizeof(string), "AdmCmd: %s is now on admin duty.", GetNameByID(playerid));
            SendAdminMessage(LIRED, string);

			SetPlayerColor(playerid, ADUTY);
		} else {
			AdminDuty[playerid] = 0;
            format(string, sizeof(string), "AdmCmd: %s is no longer on admin duty.", GetNameByID(playerid));
            SendAdminMessage(LIRED, string);

			SetPlayerColor(playerid, WHITE);
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(aduty, playerid, params[])
{
	return cmd_adminduty(playerid, params);
}

command(adminchat, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 1)
	{
		new message[128], string[256];
		if(sscanf(params, "s[128]", message)) return SendClientMessage(playerid, WHITE, "Command: /a [message]");
		{
		    format(string, sizeof(string), "(({78AB46} Admin Chat: %s: {FFFFFF}%s {808080}))", GetNameByID(playerid), message);
		    SendAdminMessage(GREY, string);
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(a, playerid, params[])
{
	return cmd_adminchat(playerid, params);
}

command(kick, playerid, params[])
{
	new id, reason[128], string[256];
	if(Player[playerid][AdminLevel] >= 1)
	{
	    if(sscanf(params, "us[128]", id, reason)) return SendClientMessage(playerid, WHITE, "Command: /kick [playerid/name] [reason]");
	    {
	        if(id != INVALID_PLAYER_ID)
	        {
	            if(Player[playerid][AdminLevel] <= Player[id][AdminLevel]) return SendErrorMessage(playerid, 1, ERROR_ADMINLEVEL);
	            format(string, sizeof(string), "AdmCmd: %s has kicked %s [Reason: %s]", GetNameByID(playerid), GetNameByID(id), reason);
	            SendClientMessageToAll(LIRED, string);
	            LogEvent("a_cmd_kick", string, GetNameByID(id));
				
				DelayedKick(id);
			}
			else return SendErrorMessage(playerid, 1, ERROR_NOT_CONNECTED);
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(ban, playerid, params[])
{
	new id, reason[128], string[256];
	if(Player[playerid][AdminLevel] >= 1)
	{
	    if(sscanf(params, "us[128]", id, reason)) return SendClientMessage(playerid, WHITE, "Command: /ban [playerid/name] [reason]");
	    {
	        if(id != INVALID_PLAYER_ID)
	        {
	            if(Player[playerid][AdminLevel] <= Player[id][AdminLevel]) return SendErrorMessage(playerid, 1, ERROR_ADMINLEVEL);
	            format(string, sizeof(string), "AdmCmd: %s has banned %s [Reason: %s]", GetNameByID(playerid), GetNameByID(id), reason);
	            SendClientMessageToAll(LIRED, string);
				Player[id][Banned] = 1;

	            LogEvent("a_cmd_ban", string, GetNameByID(id));
				DelayedKick(id);
			}
			else return SendErrorMessage(playerid, 1, ERROR_NOT_CONNECTED);
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(gotoveh, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 1)
	{
	    new id;
		if(sscanf(params, "i", id)) return SendClientMessage(playerid, WHITE, "Server: /gotoveh [vehicleID]");
		{
			new Float:x, Float:y, Float:z;
		    GetVehiclePos(id, x, y, z);
		    SetPlayerPos(playerid, x, y, z+2);
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(gotobiz, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 1)
	{
	    new id, string[42];
	    if(sscanf(params, "i", id)) return SendClientMessage(playerid, WHITE, "Server: /gotobiz [businessid]");
	    {
	        SetPlayerPos(playerid, Business[id][BusinessExteriorX], Business[id][BusinessExteriorY], Business[id][BusinessExteriorZ]);
	        format(string, sizeof(string), "You have teleported to business ID: %i", id);
	        SendClientMessage(playerid, WHITE, string);
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(gotopos, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 1)
	{
    	new Float:x, Float:y, Float:z;
    	if(sscanf(params, "fff", x, y, z)) return SendClientMessage(playerid, 0xFF0000FF, "Usage: /gotopos [x] [y] [z]");

    	SetPlayerPos(playerid, x, y, z);
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

// level 2 commands:

command(setskin, playerid, params[])
{
	new id, skin, string[128];
	if(Player[playerid][AdminLevel] >= 1)
	{
	    if(sscanf(params, "ud", id, skin)) return SendClientMessage(playerid, WHITE, "Command: /setskin [playerid/name] [skin id]");
	    {
	        if(id != INVALID_PLAYER_ID)
	        {
		    	if(skin < 0 || skin > 312) return SendErrorMessage(playerid, 1, "You cannot set a player's skin to anything higher than 311 and not lower than -1.");
	            format(string, sizeof(string), "AdmCmd: %s has set the skin of %s to %d.", GetNameByID(playerid), GetNameByID(id), skin);
	            SendAdminMessage(LIRED, string);

	            SetPlayerSkin(id, skin);
	            Player[id][Skin] = skin;

	            LogEvent("a_cmd_setskin", string, GetNameByID(id));

			}
			else return SendErrorMessage(playerid, 1, ERROR_NOT_CONNECTED);
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

// level 3 commands:

command(toggleooc, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 3)
	{
		new string[128];
		if(CONFIG_ENABLE_OOC == 0) {
			format(string, sizeof(string), "AdmMsg: %s has toggled the OOC chat (Enabled).", GetNameByID(playerid));
			SendAdminMessage(LIRED, string);

			CONFIG_ENABLE_OOC = 1;
		} else {
			format(string, sizeof(string), "AdmMsg: %s has toggled the OOC chat (Disabled).", GetNameByID(playerid));
			SendAdminMessage(LIRED, string);

			CONFIG_ENABLE_OOC = 0;
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(togooc, playerid, params[])
{
	return cmd_toggleooc(playerid, params);
}

command(reloadveh, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 3)
	{
		ReloadAllVehicles();
		SendClientMessage(playerid, LIME, "You have reloaded all vehicles.");
	} else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(reloadbiz, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 3)
	{
		ReloadAllBusinesses();
		SendClientMessage(playerid, LIME, "You have reloaded all businesses.");
	} else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(bizadmin, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 3)
	{
		BizAdmin(playerid);
	} else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(setparkingspot, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 3)
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new Float:x, Float:y, Float:z, Float:a;

			GetVehicleZAngle(vehicleid, a);
			GetVehiclePos(vehicleid, x, y, z);

			SetVehicleParkingSpot(vehicleid, x, y, z, a);

			SendClientMessage(playerid, LIME, "You have set the vehicle's parking spot.");
		} else return SendErrorMessage(playerid, 2, "You must be in a vehicle.");
	} else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(addfactionvehicle, playerid, params[])
{
	new Float:VX, Float:VY, Float:VZ, Float:VA, col1, col2, faction, dModel = GetVehicleModel(GetPlayerVehicleID(playerid)), vehicleid = GetPlayerVehicleID(playerid);

    if(Player[playerid][AdminLevel] >= 3)
    {
		if(sscanf(params, "iii", faction, col1, col2)) return SendClientMessage(playerid, WHITE, "Server: /addfactionvehicle [faction id] [color 1] [color 2]");
		{
			if(faction < 1) return SendErrorMessage(playerid, 2, "The vehicle faction cannot be 0 (no faction).");
			GetVehiclePos(vehicleid, VX, VY, VZ);
			GetVehicleZAngle(vehicleid, VA);
			if(IsPlayerInAnyVehicle(playerid))
			{
				CreateFactionVehicle(playerid, dModel, faction, col1, col2, Float:VX, Float:VY, Float:VZ, Float:VA);
				ResetVehicleVariables(vehicleid);
				Vehicles[vehicleid][Faction] = faction;
				ChangeVehicleColor(vehicleid, col1, col2);

				DestroyVehicle(vehicleid);
				SendClientMessage(playerid, LIME, "You have added this faction vehicle (it will be spawned upon next server restart or vehicle reload).");
			}
			else return SendClientMessage(playerid, WHITE, "You must be in a vehicle (spawn one with /vehicle).");
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(afv, playerid, params[])
{
	return cmd_addfactionvehicle(playerid, params);
}

command(setfaction, playerid, params[])
{
	new id, faction, rank, string[128];
	if(Player[playerid][AdminLevel] >= 3)
	{
	    if(sscanf(params, "udd", id, faction, rank)) return SendClientMessage(playerid, WHITE, "Command: /setfaction [playerid/name] [faction id] [rank]");
	    {
	        if(id != INVALID_PLAYER_ID)
	        {
		    	if(faction < 0) return SendErrorMessage(playerid, 1, "You cannot set a player's faction to anything below 0.");
		    	if(rank < 0 || rank > 16) return SendErrorMessage(playerid, 1, "The rank must be between 1 and 16.");
	            format(string, sizeof(string), "AdmCmd: %s has set the faction of %s to %d. (Rank %d)", GetNameByID(playerid), GetNameByID(id), faction, rank);
	            SendAdminMessage(LIRED, string);

	            Player[id][Faction] = faction;
	            Player[id][FactionRank] = rank;

	            LogEvent("a_cmd_setfaction", string, GetNameByID(id));

			}
			else return SendErrorMessage(playerid, 1, ERROR_NOT_CONNECTED);
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

// level 4 commands:

command(vehicle, playerid, params[])
{
    if(Player[playerid][AdminLevel] >= 4)
    {
    	if(!AdminDuty[playerid]) return SendErrorMessage(playerid, 1, ERROR_ADMINDUTY);
    	
        new id, car,
	        color0, color1,
	        string[128];
        if(sscanf(params, "ddd", id, color0, color1)) return SendClientMessage(playerid, WHITE, "Command: /vehicle [vehicle model ID] [color 0] [color 1]");
        {
			new Float:x, Float:y, Float:z, Float:a;
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, a);
			car = CreateVehicle(id, x, y, z+3, a, 1, 1, 99999999);
			SetVehicleNumberPlate(car, "ADMIN");
        	SetVehicleToRespawn(car);
			SetVehicleVirtualWorld(car, GetPlayerVirtualWorld(playerid));
			ChangeVehicleColor(car, color0, color1);

			PutPlayerInVehicle(playerid, car, 0);
			format(string, sizeof(string), "AdmMsg: %s has spawned a vehicle %i, id: %i", GetNameByID(playerid), GetVehicleModel(GetPlayerVehicleID(playerid)), GetPlayerVehicleID(playerid));
			SendAdminMessage(LIRED, string);

			LogEvent("a_cmd_vehicle", string, GetNameByID(playerid));

			// Add the AdminSpawned flag.
			Vehicles[car][AdminSpawned] = 1;
		}
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(veh, playerid, params[])
{
	return cmd_vehicle(playerid, params);
}

command(giveweapon, playerid, params[])
{

	if(Player[playerid][AdminLevel] >= 4)
	{
    	if(!AdminDuty[playerid]) return SendErrorMessage(playerid, 1, ERROR_ADMINDUTY);

	    new id, wid, ammo, string[128];
	    if(sscanf(params, "uii", id, wid, ammo)) return SendClientMessage(playerid, WHITE, "Command: /giveweapon [playerid/name] [weapon id] [ammo]");
	    {
			if(ammo <= 1) return SendErrorMessage(playerid, 1, "You must give more than 1 ammo.");
			if(id != INVALID_PLAYER_ID)
			{
				GivePlayerWeapon(id, wid, ammo);
				format(string, sizeof(string), "AdmMsg: %s has given %s weapon %i with %i ammo.", GetNameByID(playerid), GetNameByID(id), wid, ammo);
				SendAdminMessage(LIRED, string);
				LogEvent("a_cmd_giveweapon", string, GetNameByID(id));
			}
			else return SendClientMessage(playerid, GREY, ERROR_NOT_CONNECTED);
		} 
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

command(gw, playerid, params[])
{
	return cmd_giveweapon(playerid, params);
}

command(fix, playerid, params[])
{
	if(Player[playerid][AdminLevel] >= 4)
    {
		if(!AdminDuty[playerid]) return SendErrorMessage(playerid, 1, ERROR_ADMINDUTY);

    	RepairVehicle(GetPlayerVehicleID(playerid));
    	new Float:posX, Float:posY, Float:posZ;
    	GetPlayerPos(playerid, posX, posY, posZ);
    	PlayerPlaySound(playerid, 1133, posX, posY, posZ);
    	SendClientMessage(playerid, GREY, "Your vehicle has been restored to full health.");
    }
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}

// level 5 commands:
command(jetpack, playerid, params[])
{
	new string[128];
	if(Player[playerid][AdminLevel] >= 5)
	{
    	if(!AdminDuty[playerid]) return SendErrorMessage(playerid, 1, ERROR_ADMINDUTY);

	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
    	format(string, sizeof(string), "AdmCmd: %s has spawned a jetpack.", GetNameByID(playerid));
		SendAdminMessage(LIRED, string);

		LogEvent("a_cmd_jetpack", string, GetNameByID(playerid));
	}
	else return SendErrorMessage(playerid, 1, ERROR_UNAUTHORIZED);
	return 1;
}