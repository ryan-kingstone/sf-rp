/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

command(help, playerid, params[])
{
    if(isnull(params))
	{
		SendClientMessage(playerid, WHITE, "Server: /help [section]");
		SendClientMessage(playerid, GREY, "Sections: General | Faction | Phone | Animations | Donator | Vehicle | Job | House | Business");
	}
	if(!strcmp(params, "phone", true))
	{
	    SendClientMessage(playerid, BLUE, "Phone Help:");
	    SendClientMessage(playerid, WHITE, "/p(hone)off /p(hone)on /getnumber /h(angup) /call /pinfo /p(ickup) /sms");
	}

	if(!strcmp(params, "donator", true))
	{
	    if(Player[playerid][DonatorLevel] >= 1)
	    {
	    	SendClientMessage(playerid, DONATOR, "Donator Help:");
			SendClientMessage(playerid, WHITE, "/tokens /accent /fightstyle");
		}
		else return SendClientMessage(playerid, WHITE, "You aren't a Donator.");
	}

	if(!strcmp(params, "vehicle", true))
	{
	    SendClientMessage(playerid, BLUE, "Vehicle Help:");
	    SendClientMessage(playerid, WHITE, "/engine /v buy /v lights /v buypark");
	}

	if(!strcmp(params, "job", true))
	{
	    SendClientMessage(playerid, BLUE, "Job Help:");
	    SendClientMessage(playerid, WHITE, "== COMING SOON ==");
	}

	if(!strcmp(params, "house", true))
	{
		SendClientMessage(playerid, BLUE, "House Help:");
		SendClientMessage(playerid, WHITE, "/myhouse /buyhouse /sellhouse");
	}

	if(!strcmp(params, "business", true))
	{
		SendClientMessage(playerid, BLUE, "Business Help:");
		SendClientMessage(playerid, WHITE, "/mybizz /buybusiness /checkearnings");
	}

    if(!strcmp(params, "general", true))
    {
        SendClientMessage(playerid, BLUE, "General Help:");
        SendClientMessage(playerid, WHITE, "/report /stats /t(otal)t(ime)p(layed) /kill /pm /b /o(oc) /n(ewbie) /me/r(adio) /rtune /rinfo");
        SendClientMessage(playerid, WHITE, "/inventory /pay /time /age /admins /factions /do ");
        SendClientMessage(playerid, WHITE, "/eatcrisps /drinksprunk /time /smokecig /help /drink /enter /exit /buyclothes /drop /s(hout)");
		SendClientMessage(playerid, WHITE, "/w(hisper) /l(ow) /ame /advert /padvert /mask /shake /afk /back /isafk /accept /changespawn");
		return 1;
    }

    if(!strcmp(params, "faction", true))
    {
		if(Player[playerid][Faction] >= 1)
		{
		}
		else return SendClientMessage(playerid, WHITE, "You aren't in a Faction.");
	}


    if(!strcmp(params, "animations", true))
    {
        SendClientMessage(playerid, BLUE, "Animation Help:");
        SendClientMessage(playerid, WHITE, "/laugh /crack /wave /sit /talk /dance /finger");
        SendClientMessage(playerid, WHITE, "/relax /sleep /gsit /wank /lay /riot /bomb /crossarms");
        SendClientMessage(playerid, WHITE, "/hitchhike /kostomach /rap /fallback /fall /lean /handsup");
        SendClientMessage(playerid, WHITE, "/deal /hide /throwup /reload");
        return 1;
    }
    return true;
}