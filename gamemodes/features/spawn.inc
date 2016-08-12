/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and concidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

#include "YSI\y_hooks"

hook OnPlayerSpawn(playerid)
{
	if(GetPlayerFaction(playerid) != 0)
	{
		if(Factions[GetPlayerFaction(playerid)][FactionSpawnX] != 0)
		{
			SetPlayerPos(playerid, Factions[GetPlayerFaction(playerid)][FactionSpawnX], Factions[GetPlayerFaction(playerid)][FactionSpawnY], Factions[GetPlayerFaction(playerid)][FactionSpawnZ]);
		} else {
			SetPlayerPos(playerid, -1951.0, 137.0, 26.0); // default spawn: train station
		}
	} else {
		SetPlayerPos(playerid, -1951.0, 137.0, 26.0); // default spawn: train station
	}
	return 1;
}