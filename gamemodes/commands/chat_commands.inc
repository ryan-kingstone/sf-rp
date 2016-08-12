/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

// OOC:

command(ooc, playerid, params[])
{
	if(CONFIG_ENABLE_OOC || Player[playerid][AdminLevel] >= 1)
	{
		new message[128], string[180];
		if(sscanf(params, "s[128]", message)) return SendClientMessage(playerid, WHITE, "Command: /o(oc) [message]");
		{
			if(Player[playerid][AdminLevel] >= 1)
			{
		    	format(string, sizeof(string), "(( [ADMIN OOC] %s: %s ))", GetNameByID(playerid), message);
		    	SendClientMessageToAll(ADUTY, string);
			}
			else
			{
			    format(string, sizeof(string), "(( [OOC] %s says: %s ))", GetNameByID(playerid), message);
		    	SendClientMessageToAll(WHITE, string);
			}
		}
	}
	else return SendErrorMessage(playerid, 2, "The OOC chat channel has been disabled.");
	return 1;
}

command(o, playerid, params[])
{
	return cmd_ooc(playerid, params);
}

command(b, playerid, params[])
{
	new message[128], string[152];
	if(sscanf(params, "s[128]", message)) return  SendClientMessage(playerid, WHITE, "Command: /b [message]");
	{
	    if(Player[playerid][AdminLevel] >= 1) {
 			format(string, sizeof(string), "(( {78AB46}[%d]%s:{808080} %s ))", playerid, GetNameByID(playerid), message);
			CloseMessage(playerid, GREY, string);
	    } else {
		    format(string, sizeof(string), "(( [%d]%s: %s ))", playerid, GetNameByID(playerid), message);
			CloseMessage(playerid, GREY, string);
		}
	}
	return 1;
}

// IC:

command(shout, playerid, params[])
{
	new message[128], string[182];
	if(sscanf(params, "s[128]", message)) return  SendClientMessage(playerid, WHITE, "Command: /s(hout) [message]");
	{
		format(string, sizeof(string), "%s shouts: %s", GetRPName(playerid), message);
	    CloseMessageEx(playerid, WHITE, string, 20.0);

	    SetPlayerChatBubble(playerid, string, SHOUT, 20.0, 10000);
	}
	return 1;
}

command(s, playerid, params[])
{
	return cmd_shout(playerid, params);
}

command(low, playerid, params[])
{
	new message[128], string[168];
	if(sscanf(params, "s[128]", message)) return  SendClientMessage(playerid, WHITE, "Command: /l(ow) [message]");
	{
		format(string, sizeof(string), "%s says(low): %s", GetRPName(playerid), message);
		CloseMessageEx(playerid, WHITE, string, 3.0);
	}
	return 1;
}

command(l, playerid, params[])
{
	return cmd_low(playerid, params);
}

command(whisper, playerid, params[])
{
	new id, message[128], string[186];
	if(sscanf(params, "us[128]", id, message)) return SendClientMessage(playerid, WHITE, "Command: /w(hisper) [playerid/name] [message]");
	{
		if(GetDistanceBetweenPlayers(playerid, id) <= 5.0)
		{
			if(id != INVALID_PLAYER_ID)
			{
				format(string, sizeof(string), "[Whisper from %s(%d)] %s", GetRPName(playerid), playerid, message);
				SendClientMessage(id, WHISPER, string);
				format(string, sizeof(string), "[Whisper to %s(%d)] %s", GetRPName(id), id, message);
				SendClientMessage(playerid, WHISPER, string);
				format(string, sizeof(string), "* %s whispers something to %s *", GetRPName(playerid), GetRPName(id));
				CloseMessage(playerid, ACTION, string);
			}
			else return SendErrorMessage(playerid, 1, ERROR_NOT_CONNECTED);
		}
		else return SendErrorMessage(playerid, 2, "You are too far away from that player.");
	}
	return 1;
}

command(w, playerid, params[])
{
	return cmd_whisper(playerid, params);
}

command(faction, playerid, params[])
{
	if(Player[playerid][Faction] != 0)
	{
		new message[128], string[256];
		if(sscanf(params, "s[128]", message)) return SendClientMessage(playerid, WHITE, "Server: /faction [message]");
		{
			format(string, sizeof(string), "{%s}(( %s %s: %s )) ", Factions[Player[playerid][Faction]][FactionColour], GetFactionRankName(playerid), GetRPName(playerid), message);
			FactionMessage(playerid, WHITE, string);
		}
	} else return SendErrorMessage(playerid, 2, "You must be in a faction.");
	return 1;
}

command(f, playerid, params[])
{
	return cmd_faction(playerid, params);
}
