/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

#define MAX_FACTIONS 25

enum _FACTION
{
	FactionID,
	FactionName[128],
	FactionType,
	FactionShortName[32],
	FactionFlags[32],
	FactionPermissions[64],
	FactionColour[8],
	Rank1[42],
	Rank2[42],
	Rank3[42],
	Rank4[42],
	Rank5[42],
	Rank6[42],
	Rank7[42],
	Rank8[42],
	Rank9[42],
	Rank10[42],
	Rank11[42],
	Rank12[42],
	Rank13[42],
	Rank14[42],
	Rank15[42],
	Rank16[42],
	Float:FactionSpawnX,
	Float:FactionSpawnY,
	Float:FactionSpawnZ,
	Float:FactionSpawnA 
};

new Factions[MAX_FACTIONS][_FACTION],
	bool:ValidFaction[MAX_FACTIONS],
	Total_Factions_Created;


#include "YSI\y_hooks"

hook OnGameModeInit()
{
    SetTimerEx("LoadFactions", 2000, false);
	return 1;
}

forward LoadFactions();
public LoadFactions()
{
	new query[32];
	mysql_format(mysql, query, sizeof(query), "SELECT * FROM `factions`");
	mysql_tquery(mysql, query, "LoadAllFactions");

	printf("Loading factions...");
	return 1;
}

forward LoadAllFactions();
public LoadAllFactions()
{
	if(cache_num_rows())
	{
		for(new i = 0; i < cache_num_rows(); i++)
		{
			new fid = GetFreeFactionSlot();
			ValidFaction[fid] = true;
			Factions[fid][FactionID] = cache_get_field_content_int(i, "FactionID");
			cache_get_field_content(i, "FactionName", Factions[fid][FactionName], mysql, 128);
			Factions[fid][FactionType] = cache_get_field_content_int(i, "FactionType");
			cache_get_field_content(i, "FactionShortName", Factions[fid][FactionShortName], mysql, 32);
			cache_get_field_content(i, "FactionFlags", Factions[fid][FactionFlags], mysql, 32);
			cache_get_field_content(i, "FactionPermissions", Factions[fid][FactionPermissions], mysql, 64);
			cache_get_field_content(i, "FactionColour", Factions[fid][FactionColour], mysql, 8);
			cache_get_field_content(i, "Rank1", Factions[fid][Rank1], mysql, 42);
			cache_get_field_content(i, "Rank2", Factions[fid][Rank2], mysql, 42);
			cache_get_field_content(i, "Rank3", Factions[fid][Rank3], mysql, 42);
			cache_get_field_content(i, "Rank4", Factions[fid][Rank4], mysql, 42);
			cache_get_field_content(i, "Rank5", Factions[fid][Rank5], mysql, 42);
			cache_get_field_content(i, "Rank6", Factions[fid][Rank6], mysql, 42);
			cache_get_field_content(i, "Rank7", Factions[fid][Rank7], mysql, 42);
			cache_get_field_content(i, "Rank8", Factions[fid][Rank8], mysql, 42);
			cache_get_field_content(i, "Rank9", Factions[fid][Rank9], mysql, 42);
			cache_get_field_content(i, "Rank10", Factions[fid][Rank10], mysql, 42);
			cache_get_field_content(i, "Rank11", Factions[fid][Rank11], mysql, 42);
			cache_get_field_content(i, "Rank12", Factions[fid][Rank12], mysql, 42);
			cache_get_field_content(i, "Rank13", Factions[fid][Rank13], mysql, 42);
			cache_get_field_content(i, "Rank14", Factions[fid][Rank14], mysql, 42);
			cache_get_field_content(i, "Rank15", Factions[fid][Rank15], mysql, 42);
			cache_get_field_content(i, "Rank16", Factions[fid][Rank16], mysql, 42);
			Factions[fid][FactionSpawnX] = cache_get_field_content_float(i, "FactionSpawnX");
			Factions[fid][FactionSpawnY] = cache_get_field_content_float(i, "FactionSpawnY");
			Factions[fid][FactionSpawnZ] = cache_get_field_content_float(i, "FactionSpawnZ");
			Factions[fid][FactionSpawnA] = cache_get_field_content_float(i, "FactionSpawnA");

			Total_Factions_Created++;

		}
	}
	printf("[FACTION]: %d factions have been successfully loaded from the database.", Total_Factions_Created);
	return 1;
}

// Commands
command(myfaction, playerid, params[])
{
	new string[256];

	if(GetPlayerFaction(playerid) != 0)
	{
		format(string, sizeof(string), "%s - %s", Factions[GetPlayerFaction(playerid)][FactionName], GetFactionRankName(playerid));
		SendClientMessage(playerid, WHITE, string);
	}
	return 1;
}

// Stocks
stock GetFreeFactionSlot()
{
	for(new i = 1; i < sizeof(ValidFaction); i ++)
	{
		if(!ValidFaction[i]) return i;
	}
	return -1;
}

stock GetFactionRankName(playerid)
{
	new fstring[42];
	
	switch(Player[playerid][FactionRank])
	{
		case 1: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank1]);
		case 2: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank2]);
		case 3: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank3]);
		case 4: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank4]);
		case 5: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank5]);
		case 6: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank6]);
		case 7: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank7]);
		case 8: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank8]);
		case 9: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank9]);
		case 10: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank10]);
		case 11: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank11]);
		case 12: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank12]);
		case 13: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank13]);
		case 14: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank14]);
		case 15: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank15]);
		case 16: format(fstring, sizeof(fstring), "%s", Factions[GetPlayerFaction(playerid)][Rank16]);
		default: fstring = "<unknown>";
	}

	return fstring;
}

stock GetPlayerFaction(playerid)
{
	return Player[playerid][Faction];
}

stock GetFactionType(factionid)
{
	return Factions[factionid][FactionType];
}

stock GetFactionName(factionid)
{
	new name[128];
	
	format(name, sizeof(name), "%s", Factions[factionid][FactionName]);

	return name;
}

stock FactionMessage(playerid, colour, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
	   	{
	   		if(Player[i][Faction] == Player[playerid][Faction])
	   		{
	   		    SendClientMessage(i, colour, string);
	   		}
		}
	}
	return 1;
}