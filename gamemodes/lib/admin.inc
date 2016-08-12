/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

// Variables
new AdminDuty[MAX_PLAYERS];


#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
	AdminDuty[playerid] = 0; // Reset the player variable on connect, so that people can't be "on admin duty" after connecting.

	return 1;
}

#include <YSI\y_hooks>

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(Player[playerid][AdminLevel] >= 1) {
	    SetPlayerPosFindZ(playerid, fX, fY, fZ);
		SendClientMessage(playerid, LIRED, "AdmMsg: You have been teleported to your map-marker.");
    }
    return 1;
}

// SendAdminMessage(colour, string[])
// Sends a message to all admins
public SendAdminMessage(colour, string[]);
public SendAdminMessage(colour, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	  	if(IsPlayerConnected(i))
	  	{
	  	    if(Player[i][AdminLevel] >= 1)
	  	    {
  	        		SendClientMessage(i, colour, string);
		   	}
		}
	}
	return 1;
}

stock GetAdminRankName(rank)
{
	new adminrank[32];
	switch(rank)
	{
		case 0: adminrank = "";
		case 1: adminrank = "Moderator";
		case 2: adminrank = "Administrator";
		case 3: adminrank = "Senior Administrator";
		case 4: adminrank = "Head Administrator";
		case 5:	adminrank = "Developer";
		default: adminrank = "";
	}
	return adminrank;
}