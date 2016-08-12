/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>, March 2016
 */

#define ERROR_UNKNOWN 			"Unknown command. Please use /help for a list of commands."
#define ERROR_UNAUTHORIZED 		"You are not authorized to use this command."
#define ERROR_NOT_CONNECTED 	"That player is not connected."

#define ERROR_ADMINLEVEL		"That cannot be performed on a higher level administrator."
#define ERROR_ADMINDUTY			"You must be on admin duty to use this command."


#include <YSI\y_hooks>

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	if(!success)
	{
		SendErrorMessage(playerid, 1, ERROR_UNKNOWN);
	}
	else
	{
		printf("[COMMAND] %s entered command: %s", GetNameByID(playerid), cmdtext);
		return 1;
	}
	return 1;
}
