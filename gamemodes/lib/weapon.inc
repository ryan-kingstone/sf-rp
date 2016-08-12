/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

stock GetWeaponSlot(weaponid)
{
	new slot;
	switch(weaponid)
	{
		case 0,1: slot = 0;
		case 2 .. 9: slot = 1;
		case 10 .. 15: slot = 10;
		case 16 .. 18, 39: slot = 8;
		case 22 .. 24: slot = 2;
		case 25 .. 27: slot = 3;
		case 28, 29, 32: slot = 4;
		case 30, 31: slot = 5;
		case 33, 34: slot = 6;
		case 35 .. 38: slot = 7;
		case 40: slot = 12;
		case 41 .. 43: slot = 9;
		case 44 .. 46: slot = 11;
	}
	return slot;

}

#include <YSI\y_hooks>

// Disable driveby shooting
hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_PASSENGER || newstate == PLAYER_STATE_DRIVER) SetPlayerArmedWeapon(playerid, 0);
	return 1;
}

#include <YSI\y_hooks>


hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid)
{
	new Float:HP;
	GetPlayerHealth(playerid, HP);
	if(weaponid == 24) SetPlayerHealth(playerid, HP-54);    //DesertEagle
    if(weaponid == 22) SetPlayerHealth(playerid, HP-15);    //Colt45
    if(weaponid == 32) SetPlayerHealth(playerid, HP-10);    //Tec9
    if(weaponid == 28) SetPlayerHealth(playerid, HP-9);     //Uzi
    if(weaponid == 23) SetPlayerHealth(playerid, HP-31);    //SilencedColt
    if(weaponid == 31) SetPlayerHealth(playerid, HP-26);    //M4
    if(weaponid == 30) SetPlayerHealth(playerid, HP-31);    //AK
    if(weaponid == 29) SetPlayerHealth(playerid, HP-14);    //MP5
    if(weaponid == 34) SetPlayerHealth(playerid, HP-175);   //SniperRifle
    if(weaponid == 33) SetPlayerHealth(playerid, HP-80);    //CuntGun
    if(weaponid == 25) SetPlayerHealth(playerid, HP-48);    //PumpShotgun
    if(weaponid == 27) SetPlayerHealth(playerid, HP-32);    //Spaz12
	return 1;
}

stock RemovePlayerWeapon(playerid, weaponid) //Credits to Xalphox
{
    if(!IsPlayerConnected(playerid) || weaponid < 0 || weaponid > 50)
        return;
    new saveweapon[13], saveammo[13];
    for(new slot = 0; slot < 13; slot++)
        GetPlayerWeaponData(playerid, slot, saveweapon[slot], saveammo[slot]);
    ResetPlayerWeapons(playerid);
    for(new slot; slot < 13; slot++)
    {
        if(saveweapon[slot] == weaponid || saveammo[slot] == 0)
            continue;
        GivePlayerWeapon(playerid, saveweapon[slot], saveammo[slot]);
    }

}