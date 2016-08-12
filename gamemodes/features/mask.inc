/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

new MaskNumber[MAX_PLAYERS],
	Mask[MAX_PLAYERS];

#include <YSI\y_hooks>

hook OnPlayerUpdate(playerid)
{
	if(Mask[playerid] == 1)
	{
        for(new i = 0; i < MAX_PLAYERS; i++)
		{
			ShowPlayerNameTagForPlayer(i, playerid, false);
		}
	}

	return 1;
}

#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
	Mask[playerid] = 0;
	MaskNumber[playerid] = -1;

	return 1;
}

// Commands:

command(mask, playerid, params[])
{
	if(Player[playerid][Level] >= 3)
	{
	    if(Mask[playerid] == 0)
	    {
	        Mask[playerid] = 1;
	        new rand = 1000 + random(8999);
			MaskNumber[playerid] = rand;
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				ShowPlayerNameTagForPlayer(i, playerid, false);
			}
			GameTextForPlayer(playerid, "Mask on.", 3000, 5);
			SendClientMessage(playerid, LIRED, "(( Notice - Masks are fully OOC which means you may be identified if you do not wear any clothing that covers your face. ))");
		}
		else
	    {
	        Mask[playerid] = 0;
			MaskNumber[playerid] = -1;
			GameTextForPlayer(playerid, "Mask off.", 3000, 5);
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				ShowPlayerNameTagForPlayer(i, playerid, true);
			}
		}
	}
	else return SendClientMessage(playerid, WHITE, "You must be level 3 and above to use a mask.");
	return 1;
}