/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

// Define mapname and gamemode, for display purposes.
#define GAMEMODE 	"San Fierro Roleplay"
#define MAPNAME 	"San Fierro"
#define VERSION 	"16-05"

// MYSQL connection details.
#define MYSQL_HOST	"127.0.0.1"
#define MYSQL_USER	"sf-rp"
#define MYSQL_PASS	"sf-rp"
#define MYSQL_DB	"sf-rp"

new mysql,
	CONFIG_ENABLE_OOC,
	CONFIG_DEFAULT_SKIN,
	CONFIG_DEFAULT_MONEY;

#include <YSI\y_hooks>
// Actual gamemode variables and stuff, set sa-mp specific configuration
hook OnGameModeInit()
{
	// create a mysql connection
	mysql_log(LOG_ERROR | LOG_WARNING);
	mysql = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_DB, MYSQL_PASS);

	// In case a database connection fails, exit the application
	if(mysql_errno(mysql) != 0)
	{
		print("[MYSQL] Could not connect to database!");
		SendRconCommand("exit");
	}


    // World variables
    ShowPlayerMarkers(0);	// hide player markers
	ManualVehicleEngineAndLights(); // require engine and lights to be turned on manually
	EnableStuntBonusForAll(0); // disable stunt bonus
	DisableInteriorEnterExits(); // disable yellow interior enter exits


	// CONFIG:
	CONFIG_ENABLE_OOC = 0; // Enable OOC chat by default? This can be changed via admin commands in game.

	CONFIG_DEFAULT_SKIN = 210; // Default skin (ie. id 210)
	CONFIG_DEFAULT_MONEY = 2000;

	return 1;
}