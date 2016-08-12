/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>, March 2016
 */
#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
	if(!IsRPName(GetNameByID(playerid)))
	{
	    SendClientMessage(playerid, WHITE, "The name you have chosen is not a valid RP name.");
	    SendClientMessage(playerid, WHITE, "Please make sure that you use a '_' and no numbers or special characters.");
	    SendClientMessage(playerid, WHITE, " ");
	    SendClientMessage(playerid, LIRED, "Please rejoin with a RP name that follows the Firstname_Lastname format.");
        // kick:
	    DelayedKick(playerid);
	}

    return 1;
}


// IsRPName(playerid)
// Checks whether the playername provided is a valid RP name.
stock IsRPName(const name[], max_underscores = 2)
{
    new underscores = 0;
    if (name[0] < 'A' || name[0] > 'Z') return false; // First letter is not capital
    for(new i = 1; i < strlen(name); i++)
    {
        if(name[i] != '_' && (name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z')) return false; // a-zA-Z_
        if( (name[i] >= 'A' && name[i] <= 'Z') && (name[i - 1] != '_') ) return false; // unneeded capital letter
        if(name[i] == '_')
        {
            underscores++;
            if(underscores > max_underscores || i == strlen(name)) return false; // More underlines than limit, or underline at the last pos
            if(name[i + 1] < 'A' || name[i + 1] > 'Z') return false; // Not a capital letter after underline
        }
    }
    if (underscores == 0) return false; // No underline detected
    return true;
}

stock SendErrorMessage(playerid, type = 1, message[])
{
    new string[144];

    if(type == 1) {
        format(string, sizeof(string), "{FF6347}ERROR: {808080}%s", message);
        SendClientMessage(playerid, GREY, string);
    } else if(type == 2) {
        format(string, sizeof(string), "Info: %s", message);
        SendClientMessage(playerid, WHITE, string);
    }

    return 1;
}