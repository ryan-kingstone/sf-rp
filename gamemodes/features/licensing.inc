/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

command(licenses, playerid, params[])
{
	new string[256], string1[64], string2[64], string3[64];
	if(Player[playerid][CarLicense] == 0)format(string1, sizeof(string1), "Drivers License: Not Passed.");
	if(Player[playerid][CarLicense] == 1)format(string1, sizeof(string1), "Drivers License: Passed.");
	if(Player[playerid][TruckLicense] == 0)format(string2, sizeof(string2), "Trucking License: Not Passed.");
	if(Player[playerid][TruckLicense] == 1)format(string2, sizeof(string2), "Trucking License: Passed.");
	if(Player[playerid][WeaponLicense] == 0)format(string3, sizeof(string3), "Weapon License: Not Passed.");
	if(Player[playerid][WeaponLicense] == 1)format(string3, sizeof(string3), "Weapon License: Passed.");
	SendClientMessage(playerid, BLUE, "Licenses");
	format(string, sizeof(string), "%s", string1);
	SendClientMessage(playerid, WHITE, string);
	format(string, sizeof(string), "%s", string2);
	SendClientMessage(playerid, WHITE, string);
	format(string, sizeof(string), "%s", string3);
	SendClientMessage(playerid, WHITE, string);
	return 1;
}