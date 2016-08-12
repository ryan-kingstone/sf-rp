/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>, March 2016
 */

#define DIALOG_REGISTER    			6450
#define DIALOG_LOGIN        		6451

enum pInfo
{
	AccountID,
	Username[32],
	Password[129],
	Money,
	BankMoney,
	Level,
	AdminLevel,
	Faction,
	FactionRank,
	MinutesPlayed,
	ExperiencePoints,
	DonatorLevel,
	Deaths,
	Kills,
	Banned,
	// Actual RP things:
	Skin,
	CarLicense,
	TruckLicense,
	HeliLicense,
	PlaneLicense,
	MedicalLicense,
	WeaponLicense,
	Job,
	Number,
	RadioChannel,
};

new Player[MAX_PLAYERS][pInfo],
	Logged[MAX_PLAYERS],
	IP[MAX_PLAYERS][16],
	MinuteTimer[MAX_PLAYERS],
	SaveDataTimer[MAX_PLAYERS];

// include the whirlpool hash function
native WP_Hash(buffer[], len, const str[]);

// include the gpci function (serial string)
native gpci (playerid, serial [], len);

hook OnGameModeInit()
{
	return 1;
}

#include <YSI\y_hooks>

// Prepare player load/registration
hook OnPlayerConnect(playerid)
{
	GetPlayerIp(playerid, IP[playerid], 16); 

	Logged[playerid] = 0;
	new query[256], string[128]; 
	mysql_format(mysql, query, sizeof(query),"SELECT `Password`, `AccountID` FROM `characters` WHERE `Username` = '%e' LIMIT 1", GetNameByID(playerid));
	mysql_tquery(mysql, query, "OnAccountCheck", "i", playerid);
	format(string, sizeof string, "%s has joined the server.", GetNameByID(playerid));
	//SendClientMessageToAll(GREY, string);

	new serial[128];
	gpci(playerid, serial, sizeof(serial));

	format(string, sizeof(string), "Connection by %s from IP %s (GPCI HASH: %s )", GetNameByID(playerid), IP[playerid], serial);
	LogEvent("connect", string, GetNameByID(playerid));

	mysql_format(mysql, query, sizeof(query), "UPDATE `characters` SET `IP` = '%s', `GPCIHash` = '%s' WHERE `Username` = '%e'", IP[playerid], serial, GetNameByID(playerid));
	mysql_tquery(mysql, query);

	return 1;
}

#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	// Make sure player data is saved
	SavePlayerAccount(playerid);

	// Stop the minute counting timer
	KillTimer(MinuteTimer[playerid]);
	KillTimer(SaveDataTimer[playerid]);

	new string[128];
	format(string, sizeof(string), "Player %s disconnected: %i", GetNameByID(playerid), reason);
	LogEvent("disconnect", string, GetNameByID(playerid));


	return 1;
}

forward OnAccountCheck(playerid);
public OnAccountCheck(playerid)
{
	new rows, fields; 
	cache_get_data(rows, fields, mysql);
	if(rows) 
	{
		cache_get_field_content(0, "Password", Player[playerid][Password], mysql, 129);
		Player[playerid][AccountID] = cache_get_field_content_int(0, "AccountID"); 
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login", "{FFFFFF}Please enter your password in order to log in.", "Login", "Quit"); 
	}
	else 
	{
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Register", "{FFFFFF}Please register using your desired password.", "Register", "Quit");
		
	}
	return 1;
}

#include <YSI\y_hooks>

hook OnPlayerSpawn(playerid)
{
	SetPlayerSkin(playerid, Player[playerid][Skin]);
	SetPlayerColor(playerid, WHITE);
	return 1;
}

#include <YSI\y_hooks>

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
	    case DIALOG_LOGIN: 
	    {
			if(!response) Kick(playerid);
			new hpass[129], query[100];
			WP_Hash(hpass, 129, inputtext); 

			if(!strcmp(hpass, Player[playerid][Password])) 
			{ 
				mysql_format(mysql, query, sizeof(query), "SELECT * FROM `characters` WHERE `Username` = '%e' LIMIT 1", GetNameByID(playerid));
				mysql_tquery(mysql, query, "OnAccountLoad", "i", playerid);
			}
			else 
			{
				ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login", "{FFFFFF}Please enter your password in order to log in.\n{FFFF00}Wrong password!", "Login", "Quit");

				new string[76];
				format(string, sizeof(string), "Wrong password submitted by %s from IP %s", GetNameByID(playerid), IP[playerid]);
				LogEvent("wrong_password", string, GetNameByID(playerid));
			}
		}
		case DIALOG_REGISTER: 
		{
		    if(!response) return Kick(playerid); 
		    if(strlen(inputtext) < 6) return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Register", "{FFFFFF}Please register using a password you will remember.\nYour password must be at least 6 characters long!", "Register", "Quit");
			
            new query[2048];
			WP_Hash(Player[playerid][Password], 129, inputtext); 

			mysql_format(mysql, query, sizeof(query), "INSERT INTO `characters` (`Username`, `Password`, `IP`, `AdminLevel`, `Level`, `Skin`, `Money`, `Banned`) VALUES ('%e', '%e', '%e', 0, 1, %d, %d, 0)", GetNameByID(playerid), Player[playerid][Password], IP[playerid], CONFIG_DEFAULT_SKIN, CONFIG_DEFAULT_MONEY);
			
			mysql_tquery(mysql, query, "OnAccountRegister", "i", playerid);		
		}
	}
	return 1;
}

forward OnAccountLoad(playerid);
public OnAccountLoad(playerid)
{
	LoadPlayerAccount(playerid);

	new string[70];
	if(Player[playerid][Banned] == 1)
	{
		Logged[playerid] = 0;
		SendClientMessage(playerid, LIRED, "________________ NOTIFICATION ________________");
		SendClientMessage(playerid, LIRED, "Your account has been banned from the server.");
		SendClientMessage(playerid, LIRED, "If you still want to play, you are required to");
		SendClientMessage(playerid, LIRED, "make a ban-appeal via our website.");

		format(string, sizeof(string), "Kicked banned user %s", GetNameByID(playerid));
		LogEvent("banned_user_kick", string, GetNameByID(playerid));

		DelayedKick(playerid);
	} else 
	{
		format(string, sizeof(string), "Welcome to the server, {F5FF00}%s", GetRPName(playerid));
		SendClientMessage(playerid, WHITE, string);
		Logged[playerid] = 1;

		new ip[16];
		GetPlayerIp(playerid, ip, 16);

		format(string, sizeof(string), "Login: %s from IP %s", GetNameByID(playerid), ip);
		LogEvent("login", string, GetNameByID(playerid));
	}

	return 1;
}

forward OnAccountRegister(playerid);
public OnAccountRegister(playerid)
{
	Logged[playerid] = 1;
    Player[playerid][AccountID] = cache_insert_id(); 
    printf("New account registered. ID: %d", Player[playerid][AccountID]);

    // Registered player variables:
    Player[playerid][Skin] = CONFIG_DEFAULT_SKIN;
    SetPlayerSkin(playerid, Player[playerid][Skin]);

    // Money (default)
    Player[playerid][Money] = CONFIG_DEFAULT_MONEY;

    SavePlayerAccount(playerid);

	new string[128];
	format(string, sizeof(string), "Account %s has registered on the server", GetNameByID(playerid));
	LogEvent("registration", string, GetNameByID(playerid));
    return 1;
}

stock LoadPlayerAccount(playerid)
{
	Logged[playerid] = 1;

	Player[playerid][AccountID] = cache_get_field_content_int(0, "AccountID");
	Player[playerid][Username] = GetNameByID(playerid);
	Player[playerid][Money] = cache_get_field_content_int(0, "Money");
	Player[playerid][BankMoney] = cache_get_field_content_int(0, "BankMoney");
	Player[playerid][Level] = cache_get_field_content_int(0, "Level");
	Player[playerid][Skin] = cache_get_field_content_int(0, "Skin");
	Player[playerid][AdminLevel] = cache_get_field_content_int(0, "AdminLevel");
	Player[playerid][Faction] = cache_get_field_content_int(0, "Faction");
	Player[playerid][FactionRank] = cache_get_field_content_int(0, "FactionRank");
	Player[playerid][MinutesPlayed] = cache_get_field_content_int(0, "MinutesPlayed");
	Player[playerid][ExperiencePoints] = cache_get_field_content_int(0, "ExperiencePoints");
	Player[playerid][DonatorLevel] = cache_get_field_content_int(0, "DonatorLevel");
	Player[playerid][Deaths] = cache_get_field_content_int(0, "Deaths");
	Player[playerid][Kills] = cache_get_field_content_int(0, "Kills");
	Player[playerid][Banned] = cache_get_field_content_int(0, "Banned");

	// RP vars:
	Player[playerid][CarLicense] = cache_get_field_content_int(0, "CarLicense");
	Player[playerid][TruckLicense] = cache_get_field_content_int(0, "TruckLicense");
	Player[playerid][HeliLicense] = cache_get_field_content_int(0, "HeliLicense");
	Player[playerid][PlaneLicense] = cache_get_field_content_int(0, "PlaneLicense");
	Player[playerid][MedicalLicense] = cache_get_field_content_int(0, "MedicalLicense");
	Player[playerid][WeaponLicense] = cache_get_field_content_int(0, "WeaponLicense");
	Player[playerid][Job] = cache_get_field_content_int(0, "Job");
	Player[playerid][Number] = cache_get_field_content_int(0, "Number");
	Player[playerid][RadioChannel] = cache_get_field_content_int(0, "RadioChannel");
	
	GivePlayerMoney(playerid, Player[playerid][Money]);
	SetPlayerScore(playerid, Player[playerid][Level]);
	
	MinuteTimer[playerid] = SetTimerEx("MinutePlayed", 60000, 1, "i", playerid);
	SaveDataTimer[playerid] = SetTimerEx("SaveData", 30000, 1, "i", playerid);
}

stock SavePlayerAccount(playerid)
{
	if(Logged[playerid] == 1)
	{
		new query[2048];
		mysql_format(mysql, query, sizeof(query), "UPDATE `characters` SET `IP`=%d, `Money`=%d, `BankMoney`=%d, `Level`=%d, `AdminLevel`=%d, `Faction`=%d, `FactionRank`=%d, `MinutesPlayed`=%d, `ExperiencePoints`=%d, `Deaths`=%d, `Kills`=%d, `Banned`=%d, `Skin`=%d, `CarLicense`=%d, `TruckLicense`=%d, `HeliLicense`=%d, `PlaneLicense`=%d, `MedicalLicense`=%d, `WeaponLicense`=%d, `Job`=%d, `RadioChannel`=%d WHERE `AccountID`=%d",
		IP[playerid],
		Player[playerid][Money],
		Player[playerid][BankMoney],
		Player[playerid][Level],
		Player[playerid][AdminLevel],
		Player[playerid][Faction],
		Player[playerid][FactionRank],
		Player[playerid][MinutesPlayed],
		Player[playerid][ExperiencePoints],
		Player[playerid][Deaths],
		Player[playerid][Kills],
		Player[playerid][Banned],

		// RP Vars:
		Player[playerid][Skin],
		Player[playerid][CarLicense],
		Player[playerid][TruckLicense],
		Player[playerid][HeliLicense],
		Player[playerid][PlaneLicense],
		Player[playerid][MedicalLicense],
		Player[playerid][WeaponLicense],
		Player[playerid][Job],
		Player[playerid][RadioChannel],

		// where id
		Player[playerid][AccountID]);
		mysql_tquery(mysql, query);
		return 1;
	} else {
		return SendErrorMessage(playerid, 1, "Your account has not been saved because you were not logged in.");
	}
}

forward MinutePlayed(playerid);
public MinutePlayed(playerid)
{
	Player[playerid][MinutesPlayed] ++;
	return 1;
}

forward SaveData(playerid);
public SaveData(playerid)
{
	SavePlayerAccount(playerid);
	return 1;
}