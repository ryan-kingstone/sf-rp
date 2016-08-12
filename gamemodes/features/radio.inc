/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

command(radio, playerid, params[])
{
	new message[128], string[256];

	if(HasItem(playerid, 23) == -1) return SendErrorMessage(playerid, 2, "You do not have a radio.");

    if(Player[playerid][RadioChannel] > 1 && Player[playerid][RadioChannel] < 999999)
    {
        if(sscanf(params, "s[128]", message)) return SendClientMessage(playerid, WHITE, "Server: /r(adio) [message]");
        {
            format(string, sizeof(string), "**[CH %d] %s: %s", Player[playerid][RadioChannel], GetRPName(playerid), message);
            SendRadioMessage(playerid, RADIO, string);
		}
	}
	else return SendErrorMessage(playerid, 2, "Your radio doesn't support those frequencies.");
	return 1;
}

command(r, playerid, params[])
{
	return cmd_radio(playerid, params);
}

command(setfrequency, playerid, params[])
{
	new frequency;

	if(HasItem(playerid, 23) == -1) return SendErrorMessage(playerid, 2, "You do not have a radio.");

    if(sscanf(params, "i", frequency)) return SendClientMessage(playerid, WHITE, "Server: /setfrequency [freq]");
    {
    	if(frequency < 99999 && frequency > 1)
    	{
    		new string[64];
    		Player[playerid][RadioChannel] = frequency;

    		format(string, sizeof(string), "Your radio channel has been set to CH %d", frequency);
    		SendClientMessage(playerid, GREY, string);
    	} else return SendErrorMessage(playerid, 2, "Your radio doesn't support those frequencies.");
	}
	return 1;
}

command(sfreq, playerid, params[])
{
	return cmd_setfrequency(playerid, params);
}

stock SendRadioMessage(playerid, colour, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
	   	{
	   		if(Player[i][RadioChannel] == Player[playerid][RadioChannel])
	   		{
	   		    SendClientMessage(i, colour, string);
	   		}
		}
	}
	return 1;
}

stock SendAgencyMessage(playerid, colour, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
	   	{
	   		if(Player[i][Faction] == 1)
	   		{
	   		    SendClientMessage(i, colour, string);
	   		}
		}
	}
	return 1;
}