/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>, March 2016
 */

forward DelayedKick(playerid);
public DelayedKick(playerid)
{
    SetTimerEx("KickPlayer", 1000, false, "d", playerid);
}


// internal function; don't use
forward KickPlayer(playerid);
public KickPlayer(playerid)
{
    Kick(playerid);
}