/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

// Textdraws
new PlayerText: vSpeedTD[MAX_PLAYERS],
	PlayerText: vSpeedTDText[MAX_PLAYERS];

//http://pastebin.com/FQtQ6ji6

#include <YSI\y_hooks>
hook OnPlayerConnect(playerid)
{
	LoadVehicleSpeedoTextdraws(playerid);

	return 1;
}

#include <YSI\y_hooks>
hook OnPlayerUpdate(playerid)
{
	new string[32];
	if(IsPlayerInAnyVehicle(playerid))
	{
		format(string, sizeof(string), "~p~%0.0f", GetVehicleSpeed(GetPlayerVehicleID(playerid)));
		PlayerTextDrawSetString(playerid, vSpeedTD[playerid], string);
	}

	return 1;
}

#include <YSI\y_hooks>
hook OnPlayerDisconnect(playerid, reason)
{
	PlayerTextDrawDestroy(playerid, vSpeedTD[playerid]);
	PlayerTextDrawDestroy(playerid, vSpeedTDText[playerid]);

	return 1;
}

#include <YSI\y_hooks>
hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	switch(newstate)
	{
		case PLAYER_STATE_DRIVER:
		{

			PlayerTextDrawShow(playerid, vSpeedTD[playerid]);
			PlayerTextDrawShow(playerid, vSpeedTDText[playerid]);
		}

		case PLAYER_STATE_ONFOOT:
		{
			PlayerTextDrawHide(playerid, vSpeedTD[playerid]);
			PlayerTextDrawHide(playerid, vSpeedTDText[playerid]);
		}
	}

	return 1;
}

stock LoadVehicleSpeedoTextdraws(playerid)
{
	vSpeedTD[playerid] = CreatePlayerTextDraw(playerid, 548.999694, 417.303710, "100");
	PlayerTextDrawLetterSize(playerid, vSpeedTD[playerid], 0.449999, 1.600000);
	PlayerTextDrawColor(playerid, vSpeedTD[playerid], -1);
	PlayerTextDrawFont(playerid, vSpeedTD[playerid], 2);
	PlayerTextDrawSetShadow(playerid, vSpeedTD[playerid], 0);
	PlayerTextDrawSetOutline(playerid, vSpeedTD[playerid], 0);

	vSpeedTDText[playerid] = CreatePlayerTextDraw(playerid, 582.000061, 420.622009, "KM/H");
	PlayerTextDrawLetterSize(playerid, vSpeedTDText[playerid], 0.269333, 1.040000);
	PlayerTextDrawColor(playerid, vSpeedTDText[playerid], -1);
	PlayerTextDrawFont(playerid, vSpeedTDText[playerid], 1);
	PlayerTextDrawSetShadow(playerid, vSpeedTDText[playerid], 0);
	PlayerTextDrawSetOutline(playerid, vSpeedTDText[playerid], 0);

	return true;
}

forward Float:GetVehicleSpeed(vehicleid);
public Float:GetVehicleSpeed(vehicleid)
{
    new Float:Vel[3];

    GetVehicleVelocity(vehicleid, Vel[0], Vel[1], Vel[2]);

    Vel[0] *= 175;
    Vel[1] *= 175;
    Vel[2] *= 175;

    return Float: VectorSize(Vel[0], Vel[1], Vel[2]);
}