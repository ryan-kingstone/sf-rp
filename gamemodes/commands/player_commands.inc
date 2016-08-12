/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

command(kill, playerid, params[])
{
	new string[226];
    format(string, sizeof(string), "AdmMsg: %s[%d] attempted to suicide using /kill.", GetNameByID(playerid), playerid);
	SendAdminMessage(LIRED, string);
 	SendClientMessage(playerid, YELLOW, "You are not permitted to suicide using /kill. Make a /re(port) request and tell an admin why you need to suicide.");
	return 1;
}

// alias for /kill
command(suicide, playerid, params[])
{
	return cmd_suicide(playerid, params);
}

command(id, playerid, params[])
{
	new id, string[152];
	if(sscanf(params,"u", id)) return SendClientMessage(playerid, WHITE, "Server: /id [playerid/name]");
	{
	    if(id != INVALID_PLAYER_ID)
	    {
			format(string, sizeof(string), "Player %s is assigned to the ID %s.", GetRPName(id), id);
			SendClientMessage(id, GREY, string);
		}
		else return SendErrorMessage(playerid, 1, ERROR_NOT_CONNECTED);
	}
	return 1;
}

command(pm, playerid, params[])
{
	new id, message[128], string[152];
	if(sscanf(params,"us[128]", id, message)) return SendClientMessage(playerid, WHITE, "Server: /pm [playerid/name] [message]");
	{
	    if(id != INVALID_PLAYER_ID)
	    {
	        if(id != playerid)
	        {
				format(string, sizeof(string), "(( PM from %s: %s ))", GetRPName(playerid), message);
				SendClientMessage(id, YELLOW, string);
				format(string, sizeof(string), "(( PM to %s: %s ))", GetRPName(id), message);
				SendClientMessage(playerid, YELLOW, string);
			}
			else return SendErrorMessage(playerid, 2, "You can't send a PM to yourself.");
		}
		else return SendErrorMessage(playerid, 1, ERROR_NOT_CONNECTED);
	}
	return 1;
}

command(do, playerid, params[])
{
	new action[128], string[157];
	if(sscanf(params, "s[128]", action)) return SendClientMessage(playerid, WHITE, "Server: /do [action]");
	{
		format(string, sizeof(string), "** %s (( %s ))", action, GetRPName(playerid));
		CloseMessage(playerid, ACTION, string);
	}
	return 1;
}

command(me, playerid, params[])
{
	new action[128], string[128];
	if(sscanf(params, "s[128]", action)) return SendClientMessage(playerid, WHITE, "Server: /me [action]");
	{
        format(string, sizeof(string), "* %s %s", GetRPName(playerid), action);
		CloseMessage(playerid, ACTION, string);
	}
	return 1;
}