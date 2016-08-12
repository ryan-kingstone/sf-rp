/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

command(enter, playerid, params[])
{
	/*
	for(new i = 1; i < MAX_HOUSES; i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 3.0, Houses[i][HouseExteriorX], Houses[i][HouseExteriorY], Houses[i][HouseExteriorZ]))
		{
		    if(Houses[i][HouseLocked] == 0)
		    {
		    	new string[256];
    			SetPlayerPos(playerid, Houses[i][HouseInteriorX], Houses[i][HouseInteriorY], Houses[i][HouseInteriorZ]);
		    	SetPlayerInterior(playerid, Houses[i][HouseInteriorID]);
		    	format(string, sizeof(string), "~w~%s~n~~r~Type /exit to go outside", Houses[i][HouseName]);
				GameTextForPlayer(playerid, string, 3000, 5);
				SetPlayerVirtualWorld(playerid, Houses[i][HouseWorld]);
				LoadInterior(playerid);
				FadePlayerScreen(playerid, BLACK, 5);
			}
			else
			{
			    new string[256];
			    format(string, sizeof(string), "%s is currently locked.", Houses[i][HouseName]);
			    SendClientMessage(playerid, WHITE, string);
			}
		}
	}
	*/
	for(new i = 1; i < MAX_BUSINESS; i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 3.0, Business[i][BusinessExteriorX], Business[i][BusinessExteriorY], Business[i][BusinessExteriorZ]))
		{
			if(Business[i][BusinessLocked] == 0)
			{
				new string[36+64];
				SetPlayerPos(playerid, Business[i][BusinessInteriorX], Business[i][BusinessInteriorY], Business[i][BusinessInteriorZ]);

				// Set the player interior to the business interior
				SetPlayerInterior(playerid, Business[i][BusinessInterior]);

				SetPlayerVirtualWorld(playerid, Business[i][BusinessInteriorWorld]);
				format(string, sizeof(string), "~w~%s~n~~r~Type /exit to go outside", Business[i][BusinessName]);
				GameTextForPlayer(playerid, string, 3000, 5);
				LoadInterior(playerid);
				FadePlayerScreen(playerid, BLACK, 5);

				InBusiness[playerid] = i;
			}
			else return SendErrorMessage(playerid, 2, "The business is locked.");
		}
	}
	return 1;
}

command(exit, playerid, params[])
{
	for(new i = 1; i < MAX_BUSINESS; i++)
	{
        if(GetPlayerVirtualWorld(playerid) == Business[i][BusinessInteriorWorld])
        {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, Business[i][BusinessInteriorX], Business[i][BusinessInteriorY], Business[i][BusinessInteriorZ]))
			{
			    SetPlayerPos(playerid, Business[i][BusinessExteriorX], Business[i][BusinessExteriorY], Business[i][BusinessExteriorZ]);
			    SetPlayerInterior(playerid, 0);
			    InBusiness[playerid] = -1;
			    SetPlayerVirtualWorld(playerid, Business[i][BusinessExteriorWorld]);
			    LoadInterior(playerid);
			    FadePlayerScreen(playerid, BLACK, 5);
			}
		}
	}
	/*
	for(new i = 1; i < MAX_HOUSES; i++)
	{
	    if(GetPlayerVirtualWorld(playerid) == Houses[i][HouseWorld])
	    {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, Houses[i][HouseInteriorX], Houses[i][HouseInteriorY], Houses[i][HouseInteriorZ]))
			{
			    SetPlayerPos(playerid, Houses[i][HouseExteriorX], Houses[i][HouseExteriorY], Houses[i][HouseExteriorZ]);
			    SetPlayerInterior(playerid, 0);
			    LoadInterior(playerid);
			    SetPlayerVirtualWorld(playerid, 0);
			    FadePlayerScreen(playerid, BLACK, 5);
			}
		}
	}
	*/
	return 1;
}

stock LoadInterior(playerid)
{
	TogglePlayerControllable(playerid, 0);
	SetTimerEx("LoadObjectsTimer", 1500, false, "i", playerid);
}

forward LoadObjectsTimer(playerid);
public LoadObjectsTimer(playerid)
{
	TogglePlayerControllable(playerid, 1);
}

#include "YSI\y_hooks"

hook OnPlayerDeath(playerid, killerid, reason)
{
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
}