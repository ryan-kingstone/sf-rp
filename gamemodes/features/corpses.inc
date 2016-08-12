/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and concidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

#define MAX_CORPSES	2000
#define DIALOG_EXAMINE_CORPSE 8102

enum _CORPSE
{
	CorpseID,
	CorpseVictimID,
	CorpseVictimSkin,
	CorpseKillerID,
	Float:CorpseKillerDistance,
	CorpseKillWeapon,
	CorpseStatus,
	CorpseDeathTime,
	Float:CorpseX,
	Float:CorpseY,
	Float:CorpseZ
};

new Corpse[MAX_CORPSES][_CORPSE],
	Text3D:CorpseLabel[MAX_CORPSES],
	CorpseObject[MAX_CORPSES],
	bool:ValidCorpse[MAX_CORPSES],
	Total_Corpses_Created;

// Hooks
#include "YSI\y_hooks"

hook OnGameModeInit()
{
    SetTimerEx("LoadCorpses", 2000, false);
	return 1;
}

// Load corpses
forward LoadCorpses();
public LoadCorpses()
{
	new query[32];
	mysql_format(mysql, query, sizeof(query), "SELECT * FROM `corpses`");
	mysql_tquery(mysql, query, "LoadAllCorpses");

	printf("Loading corpses...");
	return 1;
}

forward LoadAllCorpses();
public LoadAllCorpses()
{
	new string[256];

	if(cache_num_rows())
	{
		for(new i = 0; i < cache_num_rows(); i++)
		{
			new cid = GetFreeCorpseSlot();
			ValidCorpse[cid] = true;
			Corpse[cid][CorpseID] = cache_get_field_content_int(i, "CorpseID");
			Corpse[cid][CorpseVictimID] = cache_get_field_content_int(i, "CorpseVictimID");
			Corpse[cid][CorpseVictimSkin] = cache_get_field_content_int(i, "CorpseVictimSkin");
			Corpse[cid][CorpseKillerID] = cache_get_field_content_int(i, "CorpseKillerID");
			Corpse[cid][CorpseKillerDistance] = cache_get_field_content_float(i, "CorpseKillerDistance");
			Corpse[cid][CorpseKillWeapon] = cache_get_field_content_int(i, "CorpseKillWeapon");
			Corpse[cid][CorpseStatus] = cache_get_field_content_int(i, "CorpseStatus");
			Corpse[cid][CorpseDeathTime] = cache_get_field_content_int(i, "CorpseDeathTime");

			Corpse[cid][CorpseX] = cache_get_field_content_float(i, "CorpseX");
			Corpse[cid][CorpseY] = cache_get_field_content_float(i, "CorpseY");
			Corpse[cid][CorpseZ] = cache_get_field_content_float(i, "CorpseZ");

			format(string, sizeof(string), "Corpse (ID: %d)\n%s\n{808080}Medical examiners may /examine the corpse.", cid, GetCorpseKillString(Corpse[cid][CorpseKillWeapon]));

			//format(string, sizeof(string), "Corpse (ID: %d)\n%s\nPerson appears to have died around %s ago.\n{808080}Medical examiners may /examine the corpse.", cid, GetCorpseKillString(Corpse[cid][CorpseKillWeapon]), timec(Corpse[cid][CorpseDeathTime]));

            CorpseLabel[cid] = Create3DTextLabel(string, CORPSE, Corpse[cid][CorpseX], Corpse[cid][CorpseY], Corpse[cid][CorpseZ], 7.0, 0, 1);
            CorpseObject[cid] = CreateDynamicObject(19944, Corpse[cid][CorpseX], Corpse[cid][CorpseY], Corpse[cid][CorpseZ] - 0.75, 0, 0, 0);

			Total_Corpses_Created++;
		}
	}
	printf("[CORPSE]: %d corpses have been successfully loaded from the database.", Total_Corpses_Created);
	return 1;
}

stock GetFreeCorpseSlot()
{
	for(new i = 1; i < sizeof(ValidCorpse); i ++)
	{
		if(!ValidCorpse[i]) return i;
	}
	return -1;
}

stock HasDNA(Float:distance, weaponid)
{
	new val;

	// 7.5m distance
	if(distance < 7.5)
	{
		switch(weaponid)
		{
			case 0 .. 15: val = 1;
			case 16 .. 40: val = 2;
			default: val = 2;
		}
	} else val = 0;

	return val;
}

stock GetCorpseKillString(weaponid)
{
	new string[72];

	switch(weaponid)
	{
		case 0: format(string, sizeof(string), "The corpse has multiple bruises.");
		case 1: format(string, sizeof(string), "The corpse has blunt force trauma wounds.");
		case 2: format(string, sizeof(string), "The corpse has blunt force trauma wounds.");
		case 3: format(string, sizeof(string), "The corpse has blunt force trauma wounds.");
		case 4: format(string, sizeof(string), "The corpse has stab wounds, likely from a knife.");
		case 5: format(string, sizeof(string), "The corpse has blunt force trauma wounds.");
		case 6: format(string, sizeof(string), "The corpse has sharp edged trauma wounds from a metal object.");
		case 7: format(string, sizeof(string), "The corpse has blunt force trauma wounds.");
		case 8: format(string, sizeof(string), "The corpse has deep stab wounds from a sword like object.");
		case 9: format(string, sizeof(string), "The corpse has severely ripped skin and wounds to that of a chainsaw.");
		case 10: format(string, sizeof(string), "The corpse has multiple bruises.");
		case 11: format(string, sizeof(string), "The corpse has multiple bruises.");
		case 12: format(string, sizeof(string), "The corpse has multiple bruises.");
		case 13: format(string, sizeof(string), "The corpse has multiple bruises.");
		case 14: format(string, sizeof(string), "The corpse has multiple bruises.");
		case 15: format(string, sizeof(string), "The corpse has blunt force trauma wounds.");
		case 16: format(string, sizeof(string), "The corpse has fragmentation and explosive related wounds.");
		case 17: format(string, sizeof(string), "The corpse has no visible cause of death.");
		case 18: format(string, sizeof(string), "The corpse has fatal third degree burns.");
		case 22: format(string, sizeof(string), "The corpse has 9mm bullet wounds from a pistol.");
		case 23: format(string, sizeof(string), "The corpse has 9mm bullet wounds from a pistol.");
		case 24: format(string, sizeof(string), "The corpse has bullet wounds from a larger caliber pistol.");
		case 25 .. 27: format(string, sizeof(string), "The corpse has bullet wounds from a shotgun.");
		case 28: format(string, sizeof(string), "The corpse has bullet wounds from an automatic pistol.");
		case 29: format(string, sizeof(string), "The corpse has bullet wounds from a small caliber automatic SMG.");
		case 30: format(string, sizeof(string), "The corpse has bullet wounds from a 7.62mm automatic rifle.");
		case 31: format(string, sizeof(string), "The corpse has bullet wounds from a 5.56mm automatic rifle.");
		case 32: format(string, sizeof(string), "The corpse has bullet wounds from a small caliber automatic SMG.");
		case 33: format(string, sizeof(string), "The corpse has bullet wounds from a hunting rifle.");
		case 34: format(string, sizeof(string), "The corpse has bullet wounds from a sniper.");
		case 35 .. 36, 39: format(string, sizeof(string), "The corpse has explosive related wounds.");
		case 41, 42: format(string, sizeof(string), "The corpse has no visible cause of death.");
		case 49: format(string, sizeof(string), "The corpse has blunt force trauma wounds from a vehicle.");
		case 50: format(string, sizeof(string), "The corpse has cut wounds from a blade.");
		case 51: format(string, sizeof(string), "The corpse has explosive related wounds.");
		case 53: format(string, sizeof(string), "The corpse appears to have drowned upon further inspection.");
		case 54: format(string, sizeof(string), "The corpse has blunt force trauma wounds caused by a fall from height.");
		case 127: format(string, sizeof(string), "The corpse has bruises and explosive wounds.");
	}

	return string;
}

command(examine, playerid, params[])
{
	new cid;
	if(sscanf(params, "i", cid)) return SendClientMessage(playerid, WHITE, "Server: /examine [corpseID]");
	{
		if(ValidCorpse[cid])
		{
			ExaminateCorpse(playerid, cid);
		} else return SendErrorMessage(playerid, 2, "That is not a corpse you can examine.");
	}
	return 1;
}

#include "YSI\y_hooks"

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(reason != 54) {
		new kid;
		if(killerid != INVALID_PLAYER_ID)
		{
			kid = killerid;
		} else {
			kid = 0;
		}
		new Float:x, Float:y, Float:z;

		GetPlayerPos(playerid, x, y, z);

		new query[336];
		mysql_format(mysql, query, sizeof(query), "INSERT INTO `corpses` (`CorpseVictimID`, `CorpseVictimSkin`, `CorpseKillerID`, `CorpseKillerDistance`, `CorpseKillWeapon`, `CorpseStatus`, `CorpseDeathTime`, `CorpseX`, `CorpseY`, `CorpseZ`) VALUES (%d, %d, %d, %f, %d, %d, %d, %f, %f, %f)", Player[playerid][AccountID], Player[playerid][Skin], Player[kid][AccountID], GetDistanceBetweenPlayers(playerid, kid), reason, 0, gettime(), x, y, z);
		mysql_tquery(mysql, query, "OnAddCorpse", "iifiiifff", playerid, kid, GetDistanceBetweenPlayers(playerid, kid), reason, 0, gettime(), x, y, z);
	}
}

forward OnAddCorpse(playerid, killerid, Float:distance, weapon, status, deathtime, Float:x, Float:y, Float:z);
public OnAddCorpse(playerid, killerid, Float:distance, weapon, status, deathtime, Float:x, Float:y, Float:z)
{
	new string[256];

	new cid = GetFreeCorpseSlot();

	ValidCorpse[cid] = true;
	Corpse[cid][CorpseID] = cache_insert_id();
	Corpse[cid][CorpseVictimID] = Player[playerid][AccountID];
	Corpse[cid][CorpseVictimSkin] = Player[playerid][Skin];
	if(killerid != 0) {
		Corpse[cid][CorpseKillerID] = Player[killerid][AccountID];
	} else {
		Corpse[cid][CorpseKillerID] = 0;
	}
	Corpse[cid][CorpseKillerDistance] = distance;
	Corpse[cid][CorpseKillWeapon] = weapon;
	Corpse[cid][CorpseStatus] = status;
	Corpse[cid][CorpseDeathTime] = deathtime;

	Corpse[cid][CorpseX] = x;
	Corpse[cid][CorpseY] = y;
	Corpse[cid][CorpseZ] = z;

	format(string, sizeof(string), "Corpse (ID: %d)\n%s\n{808080}Medical examiners may /examine the corpse.", cid, GetCorpseKillString(Corpse[cid][CorpseKillWeapon]));

    CorpseLabel[cid] = Create3DTextLabel(string, 0x0073FFFF, Corpse[cid][CorpseX], Corpse[cid][CorpseY], Corpse[cid][CorpseZ], 7.0, 0, 1);
    CorpseObject[cid] = CreateDynamicObject(19944, Corpse[cid][CorpseX], Corpse[cid][CorpseY], Corpse[cid][CorpseZ] - 1, 0, 0, 0);

	Total_Corpses_Created++;
	return 1;
}


stock ExaminateCorpse(playerid, cid)
{

	new query[128];
	mysql_format(mysql, query, sizeof(query),"SELECT `CarLicense`, `Faction`, `FactionRank`, `Number`, `Username` FROM `characters` WHERE `AccountID` = '%d' LIMIT 1", Corpse[cid][CorpseVictimID]);
	mysql_tquery(mysql, query, "OnExaminateCorpse", "iifii", playerid, cid, Corpse[cid][CorpseKillerDistance], Corpse[cid][CorpseKillWeapon], Corpse[cid][CorpseKillerID]);
	return 1;
}

forward OnExaminateCorpse(playerid, cid, distance, weapon, killer);
public OnExaminateCorpse(playerid, cid, distance, weapon, killer)
{
	new rows, fields, string[1632];

	new carlicense, faction, username[MAX_PLAYER_NAME];
	cache_get_data(rows, fields, mysql);
	if(rows) 
	{
		carlicense = cache_get_field_content_int(0, "CarLicense");
		faction = cache_get_field_content_int(0, "Faction");
		cache_get_field_content(0, "Username", username, mysql, 42);

		format(string, sizeof(string), "{FFFFFF}CORPSE (ID: %d)\n\n", cid);

		if(carlicense)
		{
			format(string, sizeof(string), "%s{FFFFFF}DRIVERS LICENSE - BODY IDENTIFIED {FFFFFF}\n", string);

			format(string, sizeof(string), "%s{FF6347}[DMV]{FFFFFF} FINGERPRINT: %s\n", string, username);

			// If a driver's license is found, assume identified victim:
			if(GetFactionType(faction) <= 2)
			{
				format(string, sizeof(string), "%s{FFFF00}[EMPLOYMENT]{FFFFFF} Employed by %s\n", string, GetFactionName(faction));
			}
		}

		if(HasDNA(distance, weapon) == 1)
		{
			format(string, sizeof(string), "%s{00FF96}[DNA PROFILE FOUND]{FFFFFF} A DNA profile was found. Analysis at laboratory required.\n", string);
		} else if(HasDNA(distance, weapon) == 2)
		{
			format(string, sizeof(string), "%s{00FF96}[PARTIAL DNA PROFILE FOUND]{FFFFFF} A DNA profile was found. Analysis at laboratory required.\n", string);
		}

		ShowPlayerDialog(playerid, DIALOG_EXAMINE_CORPSE, DIALOG_STYLE_MSGBOX, "Corpse examination", string, "Close", "");
	}
	else 
	{	
	}

	return 1;
}