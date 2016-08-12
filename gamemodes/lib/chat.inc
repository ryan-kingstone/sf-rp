/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>, March 2016
 */

stock CloseMessage(playerid, colour, string[])
{
	new Float: PlayerX, Float: PlayerY, Float: PlayerZ;
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
	   	{
	   		GetPlayerPos(playerid, PlayerX, PlayerY, PlayerZ);
	   		if(IsPlayerInRangeOfPoint(i, 12, PlayerX, PlayerY, PlayerZ))
	   		{
			    if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i) && GetPlayerInterior(playerid) == GetPlayerInterior(i))
	    	    {
	    			SendClientMessage(i, colour, string);
	    		}
	    	}
		}
	}
	return 1;
}

stock CloseMessageEx(playerid, color, string[], Float: range)
{
	new Float: PlayerX, Float: PlayerY, Float: PlayerZ;
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
	   	{
	   		GetPlayerPos(playerid, PlayerX, PlayerY, PlayerZ);
	   		if(IsPlayerInRangeOfPoint(i, range, PlayerX, PlayerY, PlayerZ))
	   		{
			    if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
	    	    {
	    			SendClientMessage(i, color, string);
	    		}
	    	}
		}
	}
}

#include <YSI\y_hooks>

hook OnPlayerText(playerid, text[])
{
	new string[256];

    format(string, sizeof(string), "%s says: %s", GetRPName(playerid), text);
	CloseMessage(playerid, WHITE, string);

	return 0;
}