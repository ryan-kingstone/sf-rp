/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 *
 *
 * Notice: When compiling this script, you may need to use the following compiler arguments: "-;+ -(+ -v3"
 */

#include <a_samp>
#include <timerfix>
#include <a_mysql>
#include <sscanf2>
#include <streamer>
#include <zcmd>
#include <fade>

// make sure y_hooks is last!
// other scripts may depend on it
#include <YSI\y_hooks>

/*
	NOTICE ABOUT MODULES:
		These must be loaded in the correct order, or else the script will NOT compile.
		You have been warned.

		Do not load any files using the player table without loading lib/account first.

		Also notice:
		Above all functions using the prefix "hook" you will need to include y_hooks as done above.
*/

#include "config"										// <basic config for init and mysql details>
// config module MUST be loaded first

#include "lib/logging"									// mysql logging library
      
#include "lib/colors"									// <all the colour #defines

#include "lib/command"									// <handles command errors / etc>

// NO PLAYER LIB FUNCTIONS BEFORE THIS POINT ------------------------------------------------------------

// player data structure
#include "lib/account"									// <account & player library>

// watchdog libraries
#include "lib/watchdog/actions"							// <admin actions, ie bans and such>
#include "lib/watchdog/formal"							// <ensures naming standards are kept, etc, blacklisted names>

// commands & respective libraries
#include "lib/admin"									// <admin library>

#include "commands/player_commands"						// <player commands, ie, report, pm, such>

#include "commands/help"								// /help

#include "lib/chat"										// <chat library>

#include "lib/vehicle"									// <vehicle library>

// features & commands following the features:
#include "features/inventory"							// <inventory>

#include "features/faction"								// <faction system>
#include "features/licensing"							// <licensing>
#include "features/clothes"								// <clothing item system>
#include "features/carsign"								// <carsigns>
#include "features/vehicles"							// <personal and faction vehicles>
#include "features/businesses"							// <business system>
#include "features/speedometer"							// <vehicle speedometer>
#include "features/mask"								// <masks / ooc metagame protection>
#include "features/radio"								// <radio system ie. non gov coms, atc, departmental>
#include "features/siren"								// <siren system for vehicles>
#include "features/corpses"								// <corpse system>
#include "features/exitenter"							// <enter & exit commands>
#include "features/bizadmin"							// <bizadmin system>

#include "commands/chat_commands"						// <player speech, ooc, adverts)

// External library
#include "extlib/mapfix"								// map fixes
#include "extlib/extfuncs"								// external functions

#include "features/spawn"								// <determine spawn location>

#include "commands/admin_commands"						// <administrative commands - ie admin tools> (moved because vehicles requires it)
#include "commands/vehicle_commands"					// <general vehicle commands> (certain commands require vehicle information)

// libs that use only stock functions
#include "lib/distance"									// <distance comparision library>
#include "lib/name"										// <name functions (ie. display proper RP name)>
#include "lib/time"										// <time library>
#include "lib/weapon"									// <weapon library>
#include "lib/player"									// <player library>
#include "lib/location"									// <location library>

main()
{
	printf(#GAMEMODE " initializing: " #VERSION);
}

// Standard callbacks

public OnGameModeInit()
{
	SetGameModeText(GAMEMODE);
	// Set the weather to (10) to avoid issues with bad lighting.
	// To-do: implement weather system.
	SetWeather(10);
	return 1;
}

// YSI error prevention:
public OnPlayerConnect(playerid)
{
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnPlayerSpawn(playerid) return 1;
public OnPlayerDeath(playerid, killerid, reason) return 1;
public OnVehicleSpawn(vehicleid) return 1;
public OnVehicleDeath(vehicleid, killerid) return 1;
public OnPlayerText(playerid, text[]) return 0;
public OnPlayerCommandText(playerid, cmdtext[]) return 1;
public OnPlayerRequestClass(playerid, classid) return 1;
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) return 1;
public OnPlayerExitVehicle(playerid, vehicleid) return 1;
public OnPlayerStateChange(playerid, newstate, oldstate) return 1;
public OnPlayerEnterCheckpoint(playerid) return 1;
public OnPlayerLeaveCheckpoint(playerid) return 1;
public OnPlayerEnterRaceCheckpoint(playerid) return 1;
public OnPlayerLeaveRaceCheckpoint(playerid) return 1;
public OnRconCommand(cmd[]) return 1;
public OnPlayerRequestSpawn(playerid) return 1;
public OnObjectMoved(objectid) return 1;
public OnPlayerObjectMoved(playerid, objectid) return 1;
public OnPlayerPickUpPickup(playerid, pickupid) return 1;
public OnVehicleMod(playerid, vehicleid, componentid) return 1;
public OnEnterExitModShop(playerid, enterexit, interiorid) return 1;
public OnVehiclePaintjob(playerid, vehicleid, paintjobid) return 1;
public OnVehicleRespray(playerid, vehicleid, color1, color2) return 1;
public OnVehicleDamageStatusUpdate(vehicleid, playerid) return 1;
public OnPlayerSelectedMenuRow(playerid, row) return 1;
public OnPlayerExitedMenu(playerid) return 1;
public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) return 1;
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) return 1;
public OnRconLoginAttempt(ip[], password[], success) return 1;
public OnPlayerUpdate(playerid) return 1;
public OnPlayerStreamIn(playerid, forplayerid) return 1;
public OnPlayerStreamOut(playerid, forplayerid) return 1;
public OnVehicleStreamIn(vehicleid, forplayerid) return 1;
public OnVehicleStreamOut(vehicleid, forplayerid) return 1;
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) return 1;
public OnPlayerClickPlayer(playerid, clickedplayerid, source) return 1;
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid) return 1;
public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid) return 1;
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) return 1;
public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat) return 1;
public OnPlayerScreenFade(playerid) return 1;
public OnPlayerScreenColorFade(playerid) return 1;