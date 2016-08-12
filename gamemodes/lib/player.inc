/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

stock GetPlayerID(name[])
{
    if (strlen(name) >= 24)
        return INVALID_PLAYER_ID;
    new Name[16];
    for(new i; i < MAX_PLAYERS; i++)
    {
        GetPlayerName(i, Name, sizeof Name);
        if(!strcmp(Name, name, true))
            return i;
    }
    return INVALID_PLAYER_ID;
}