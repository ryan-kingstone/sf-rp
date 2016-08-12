/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

#define DIALOG_BIZADMIN_MENU		9500
#define DIALOG_BIZADMIN_NEW			9501
#define DIALOG_BIZADMIN_LIST		9502
#define DIALOG_BIZADMIN_SELECT		9503
#define DIALOG_BIZADMIN_ACTION		9504
#define DIALOG_BIZADMIN_RENAME		9505
#define DIALOG_BIZADMIN_SELCT_INT	9506
#define DIALOG_BIZADMIN_NEW_CONFIRM	9509
#define DIALOG_BIZADMIN_I_SPOS		9510

enum _PLAYER_OPTS
{
	_bizname[64],
	_interior,
	Float:_extX,
	Float:_extY,
	Float:_extZ,
	Float:_intX,
	Float:_intY,
	Float:_intZ
}

new BizAdminOptions[MAX_PLAYERS][_PLAYER_OPTS];

new bizadmin_menu_str[91] = "{FFFF00}Close BizAdmin{FFFFFF}\nCreate a new business\nView all businesses\nView statistics";

stock BizAdmin(playerid)
{
	new string[2048];

	format(string, sizeof(string), "%s", bizadmin_menu_str);

	ShowPlayerDialog(playerid, DIALOG_BIZADMIN_MENU, DIALOG_STYLE_LIST, "BizAdmin", string, "Select", "Close");
}

// Actual bizadmin logic:
#include "YSI\y_hooks"

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new string[2048], Float:gx, Float:gy, Float:gz;

	switch(dialogid)
	{
		// Basic selection menu
		case DIALOG_BIZADMIN_MENU:
		{
			if(!response) SendClientMessage(playerid, LIME, "Closed BizAdmin");

			switch(listitem)
			{
				case 0:
				{
				}

				case 1:
				{
					format(string, sizeof(string), "Set business name [%s]\nSet interior [%d]\nSet enterance to current position [%f, %f, %f]\nSet exit to current position [%f, %f, %f]\n{FFFF00}<- Return{FFFFFF}", BizAdminOptions[playerid][_bizname], BizAdminOptions[playerid][_interior], BizAdminOptions[playerid][_extX], BizAdminOptions[playerid][_extY], BizAdminOptions[playerid][_extZ], BizAdminOptions[playerid][_intX], BizAdminOptions[playerid][_intY], BizAdminOptions[playerid][_intZ]);
					ShowPlayerDialog(playerid, DIALOG_BIZADMIN_NEW, DIALOG_STYLE_LIST, "BizAdmin: Create a new business", string, "Select", "");					
				}
			}
		}

		case DIALOG_BIZADMIN_NEW:
		{
			switch(listitem)
			{
				// Set name
				case 0:
				{
					ShowPlayerDialog(playerid, DIALOG_BIZADMIN_RENAME, DIALOG_STYLE_INPUT, "BizAdmin: Set business name", "Rename business", "Submit", "");
				}

				// Set interior
				case 1:
				{
					ShowPlayerDialog(playerid, DIALOG_BIZADMIN_SELCT_INT, DIALOG_STYLE_INPUT, "BizAdmin: Set business interior", "Set business interior", "Submit", "");
				}

				// Set enterance to current position
				case 2:
				{
					// If the player clicks "set exit to current position", set the exterior coordinates.
					GetPlayerPos(playerid, gx, gy, gz);

					BizAdminOptions[playerid][_extX] = gx;
					BizAdminOptions[playerid][_extY] = gy;
					BizAdminOptions[playerid][_extZ] = gz;

					format(string, sizeof(string), "Set business name [%s]\nSet interior [%d]\nSet enterance to current position [%f, %f, %f]\nSet exit to current position [%f, %f, %f]\n{FFFF00}<- Return{FFFFFF}", BizAdminOptions[playerid][_bizname], BizAdminOptions[playerid][_interior], BizAdminOptions[playerid][_extX], BizAdminOptions[playerid][_extY], BizAdminOptions[playerid][_extZ], BizAdminOptions[playerid][_intX], BizAdminOptions[playerid][_intY], BizAdminOptions[playerid][_intZ]);
					ShowPlayerDialog(playerid, DIALOG_BIZADMIN_NEW, DIALOG_STYLE_LIST, "BizAdmin: Create a new business", string, "Select", "");
				}

				// Set exit to current position
				case 3:
				{
					// If the player clicks set enterance to current position, set the interior coords.
					GetPlayerPos(playerid, gx, gy, gz);

					BizAdminOptions[playerid][_intX] = gx;
					BizAdminOptions[playerid][_intY] = gy;
					BizAdminOptions[playerid][_intZ] = gz;

					format(string, sizeof(string), "Set business name [%s]\nSet interior [%d]\nSet enterance to current position [%f, %f, %f]\nSet exit to current position [%f, %f, %f]\n{FFFF00}<- Return{FFFFFF}", BizAdminOptions[playerid][_bizname], BizAdminOptions[playerid][_interior], BizAdminOptions[playerid][_extX], BizAdminOptions[playerid][_extY], BizAdminOptions[playerid][_extZ], BizAdminOptions[playerid][_intX], BizAdminOptions[playerid][_intY], BizAdminOptions[playerid][_intZ]);
					ShowPlayerDialog(playerid, DIALOG_BIZADMIN_NEW, DIALOG_STYLE_LIST, "BizAdmin: Create a new business", string, "Select", "");
				}

				// <- Return
				case 4:
				{
					format(string, sizeof(string), "%s", bizadmin_menu_str);

					ShowPlayerDialog(playerid, DIALOG_BIZADMIN_MENU, DIALOG_STYLE_LIST, "BizAdmin", string, "Select", "");
				}

				// Create business:
				case 5:
				{
					//CreateBusiness()
				}
			}
		}

		// If the interior has been set:
		case DIALOG_BIZADMIN_RENAME:
		{
			if(!response)
			{
				// If no business name is entered; re open the menu at previous step.
				SendClientMessage(playerid, LIME, "You must enter a business name.");

				format(string, sizeof(string), "Set business name [%s]\nSet interior [%d]\nSet enterance to current position [%f, %f, %f]\nSet exit to current position [%f, %f, %f]\n{FFFF00}<- Return{FFFFFF}", BizAdminOptions[playerid][_bizname], BizAdminOptions[playerid][_interior], BizAdminOptions[playerid][_extX], BizAdminOptions[playerid][_extY], BizAdminOptions[playerid][_extZ], BizAdminOptions[playerid][_intX], BizAdminOptions[playerid][_intY], BizAdminOptions[playerid][_intZ]);
				ShowPlayerDialog(playerid, DIALOG_BIZADMIN_NEW, DIALOG_STYLE_LIST, "BizAdmin: Create a new business", string, "Select", "");
			}

			if(strlen(inputtext) > 1)
			{
				format(string, sizeof(string), "");
				strcpyEx(BizAdminOptions[playerid][_bizname], string);
				
				// Copy the input text:
				strins(BizAdminOptions[playerid][_bizname], inputtext, 0);

				format(string, sizeof(string), "Set business name [%s]\nSet interior [%d]\nSet enterance to current position [%f, %f, %f]\nSet exit to current position [%f, %f, %f]\n{FFFF00}<- Return{FFFFFF}", BizAdminOptions[playerid][_bizname], BizAdminOptions[playerid][_interior], BizAdminOptions[playerid][_extX], BizAdminOptions[playerid][_extY], BizAdminOptions[playerid][_extZ], BizAdminOptions[playerid][_intX], BizAdminOptions[playerid][_intY], BizAdminOptions[playerid][_intZ]);
				ShowPlayerDialog(playerid, DIALOG_BIZADMIN_NEW, DIALOG_STYLE_LIST, "BizAdmin: Create a new business", string, "Select", "");
			}
		}

		case DIALOG_BIZADMIN_SELCT_INT:
		{
			if(!response)
			{
				// No interior entered, re open menu:
				SendClientMessage(playerid, LIME, "You must enter a business interior.");

				format(string, sizeof(string), "Set business name [%s]\nSet interior [%d]\nSet enterance to current position [%f, %f, %f]\nSet exit to current position [%f, %f, %f]\n{FFFF00}<- Return{FFFFFF}", BizAdminOptions[playerid][_bizname], BizAdminOptions[playerid][_interior], BizAdminOptions[playerid][_extX], BizAdminOptions[playerid][_extY], BizAdminOptions[playerid][_extZ], BizAdminOptions[playerid][_intX], BizAdminOptions[playerid][_intY], BizAdminOptions[playerid][_intZ]);
				ShowPlayerDialog(playerid, DIALOG_BIZADMIN_NEW, DIALOG_STYLE_LIST, "BizAdmin: Create a new business", string, "Select", "");
			}

			if(strlen(inputtext) > 0)
			{
				// If the interior selected is more than 0 characters, copy the input text to the variable
				BizAdminOptions[playerid][_interior] = strval(inputtext);

				format(string, sizeof(string), "Set business name [%s]\nSet interior [%d]\nSet enterance to current position [%f, %f, %f]\nSet exit to current position [%f, %f, %f]\n{FFFF00}<- Return{FFFFFF}", BizAdminOptions[playerid][_bizname], BizAdminOptions[playerid][_interior], BizAdminOptions[playerid][_extX], BizAdminOptions[playerid][_extY], BizAdminOptions[playerid][_extZ], BizAdminOptions[playerid][_intX], BizAdminOptions[playerid][_intY], BizAdminOptions[playerid][_intZ]);
				ShowPlayerDialog(playerid, DIALOG_BIZADMIN_NEW, DIALOG_STYLE_LIST, "BizAdmin: Create a new business", string, "Select", "");
			}
		}
	}
	return 1;
}