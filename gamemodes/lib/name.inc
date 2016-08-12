/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>, March 2016
 */

stock GetNameByID(playerid)
{
	new name[32];
	GetPlayerName(playerid, name, sizeof(name));
	return name;
}

stock GetPlayerIDByName(name[])
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

stock GetRPName(playerid)
{
    new name[MAX_PLAYER_NAME];
    
    GetPlayerName(playerid,name,sizeof(name));
    for(new i = 0; i < MAX_PLAYER_NAME; i++)
    {
        if(name[i] == '_') name[i] = ' ';
    }

    if(Mask[playerid] == 1) format(name, sizeof(name), "Stranger(%d)", MaskNumber[playerid]);

    return name;
}

stock RemoveUnderScore(name[])
{
    for(new i; i < MAX_PLAYER_NAME; i++)
    {
        if(name[i] == '_') name[i] = ' ';
    }
    return name;
}
