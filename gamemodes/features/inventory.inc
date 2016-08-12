/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

#define DIALOG_INVENTORY 	1336

#define ON_INVENTORY_LIST 	533

// Remember to increase this whenever you add a new item.
#define MAX_ITEMS 			31

enum _PLAYER_ITEMS
{
	ItemSQLID,
	ItemOwner,
	ItemType,
	ItemAmount,
	bool:PlayerItem
};

new Inventory[MAX_PLAYERS][MAX_ITEMS][_PLAYER_ITEMS];

enum _ITEMS
{
	ItemID,
	ItemName[32],
	GiveID,
	Weight
};

// Notice: first entry is name, second is weapon to give, third is weight (aka grams)
// For weapons that don't give any weapons (ie. static items, set the give ID to 0)
// ALWAYS ADD NEW ITEMS AFTER LAST ENTRY. DO NOT ADD NEW ITEMS IN THE MIDDLE OF THE STACK.
stock Items[][_ITEMS] = {
	{0, "Brass Knuckles", 1, 50},
	{1, "Golf Club", 2, 100},
	{2, "Baton", 3, 100},
	{3, "Knife", 4, 200},
	{4, "Bat", 5, 80},
	{5, "Shovel", 6, 120},
	{6, "Katana", 8, 180},
	{7, "Teargas Canister", 17, 100},
	{8, "Molotov Cocktail", 18, 100},
	{9, "Colt .45 Pistol", 22, 10},
	{10, "Silenced .45 Pistol", 23, 10},
	{11, "Deagle", 24, 15},
	{12, "Shotgun", 25, 20},
	{13, "Sawnoff Shotgun", 26, 20},
	{14, "Combat Shotgun", 27, 10},
	{15, "UZI", 28, 8},
	{16, "MP5", 29, 9},
	{17, "AK47", 30, 10},
	{18, "M4", 31, 10},
	{19, "TEC-9", 32, 8},
	{20, "Country Rifle", 33, 30},
	{21, "Sniper Rifle", 34, 40},
	{22, "Spray Can", 41, 1},
	{23, "Radio", 0, 0},
	{24, "Pack of Cigarettes", 0, 10},
	{25, "Car Advertisement Sign", 0, 50},
	{26, "Camera", 43, 10},
	{27, "Cannabis Seeds", 0, 1},
	{28, "Weed", 0, 1},
	{29, "Metal Parts", 0, 5},
	{30, "Medical Examiner Certificate", 0, 1}
};

new total_weight[MAX_PLAYERS];

#include <YSI\y_hooks>

hook OnPlayerSpawn(playerid)
{
	LoadInventory(playerid);
	return 1;
}

#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	total_weight[playerid] = 0;
}

#include <YSI\y_hooks>

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new status = GetPVarInt(playerid, "DialogStatus");
	if (dialogid == DIALOG_INVENTORY)
	{
		switch (status)
		{
			case ON_INVENTORY_LIST:
			{
				if(response)
				{
					UseItem(playerid, Inventory[playerid][listitem][ItemType], Inventory[playerid][listitem][ItemAmount]);
				}
			}
		}
	}
	return 1;
}

stock LoadInventory(playerid)
{
	new query[65+1];
	format(query, sizeof(query), "SELECT * FROM `inventory` WHERE `ItemOwnerID`=%d", Player[playerid][AccountID]);
	mysql_tquery(mysql, query, "OnInventoryLoad", "i", playerid);
	return 1;
}

forward OnInventoryLoad(playerid);
public OnInventoryLoad(playerid)
{
	new rows = cache_num_rows();
	if (rows)
	{
		for (new i = 0; i < rows; i++)
		{
			Inventory[playerid][i][ItemSQLID] = cache_get_field_content_int(i, "ItemID");
			Inventory[playerid][i][ItemOwner] = cache_get_field_content_int(i, "ItemOwnerID");
			Inventory[playerid][i][ItemType] = cache_get_field_content_int(i, "ItemType");
			Inventory[playerid][i][ItemAmount] = cache_get_field_content_int(i, "Amount");
			Inventory[playerid][i][PlayerItem] = true;

			// Calculate the total weight upon loading:
			total_weight[playerid] = total_weight[playerid] + GetItemWeight(Inventory[playerid][i][ItemType], Inventory[playerid][i][ItemAmount]);
		}
	}
	return 1;
}

stock InventoryList(playerid)
{
	new dstr[2048];
	new title[64];

	format(title, sizeof(title), "{FFFF00}INVENTORY {FFFFFF}%dg/%dg", total_weight[playerid], GetMaxWeight(playerid));

	format(dstr, sizeof(dstr), "%sSlot\tName\tAmount\n", dstr);

	for (new i = 0; i < MAX_ITEMS; i++)
	{
		// if item is valid. ie not removed, etc- display it
		if (Inventory[playerid][i][PlayerItem] == true)
		{
			// If the item is not usable, make it look gray, else make it yellow
			if(GetGiveID(Inventory[playerid][i][ItemType]) == 0)
			{
				format(dstr, sizeof(dstr), "%s%d\t{808080}%s\t{FFFFFF}%d\n", dstr, i, GetItemName(Inventory[playerid][i][ItemType]), Inventory[playerid][i][ItemAmount]);
			} else {
				format(dstr, sizeof(dstr), "%s%d\t{FFFF00}%s\t{FFFFFF}%d\n", dstr, i, GetItemName(Inventory[playerid][i][ItemType]), Inventory[playerid][i][ItemAmount]);
			}
		}
		else
		{
			// skip if item doesn't exist
			format(dstr, sizeof(dstr), "%s%d\n", dstr, i);
		}
	}
	ShowDialog(playerid, DIALOG_INVENTORY, DIALOG_STYLE_TABLIST_HEADERS, title, dstr, "Select", "Cancel", ON_INVENTORY_LIST);
	return 1;
}

stock UseItem(playerid, itemid, amount)
{
	new string[64];
	for (new i = 0; i < MAX_ITEMS; i++)
	{
		if(itemid == Inventory[playerid][i][ItemType])
		{
			if(Inventory[playerid][i][PlayerItem])
			{
				if(HasItem(playerid, itemid) != -1 || amount > Inventory[playerid][i][ItemAmount])
				{
					if(GetGiveID(Inventory[playerid][i][ItemType]) == 0)
					{
						SendErrorMessage(playerid, 2, "You cannot use this item.");
					} else {
						format(string, sizeof(string), "You have used %s.", GetItemName(Inventory[playerid][i][ItemType]));
						SendClientMessage(playerid, YELLOW, string);

						GivePlayerWeapon(playerid, GetGiveID(Inventory[playerid][i][ItemType]), amount);
						total_weight[playerid] = total_weight[playerid] - GetItemWeight(Inventory[playerid][i][ItemType], Inventory[playerid][i][ItemAmount]);

						// Remove the item:
						RemoveItem(playerid, Inventory[playerid][i][ItemSQLID]);

						format(string, sizeof(string), "Player %s used item %i x %i", GetNameByID(playerid), itemid, amount);
						LogEvent("item_use", string, GetNameByID(playerid));
					}
				} else return SendErrorMessage(playerid, 2, "You do not have that item or are trying to use more than you have.");
			}
		}
	}
	return 1;
}

forward RemoveItem(playerid, slot);
public RemoveItem(playerid, slot)
{

	for (new i = 0; i < MAX_ITEMS; i++)
	{
		if(slot == Inventory[playerid][i][ItemSQLID])
		{
			new query[47];
			format(query, sizeof(query), "DELETE FROM `inventory` WHERE `ItemID`=%d", Inventory[playerid][i][ItemSQLID]);
			mysql_tquery(mysql, query);

			Inventory[playerid][i][PlayerItem] = false;

			Inventory[playerid][i][ItemSQLID] = 0;
			Inventory[playerid][i][ItemOwner] = 0;
			Inventory[playerid][i][ItemType] = 0;
			Inventory[playerid][i][ItemAmount] = 0;

			new string[128];
			format(string, sizeof(string), "Player %s cleared inventory slot %i", GetNameByID(playerid), slot);
			LogEvent("item_remove", string, GetNameByID(playerid));
		}
	}
	return 1;
}

stock AddItem(playerid, itemid, amount)
{
	new query[128];
	mysql_format(mysql, query, sizeof(query), "INSERT INTO `inventory` (`ItemOwnerID`, `ItemType`, `Amount`) VALUES (%d, %d, %d)", Player[playerid][AccountID], itemid, amount);
	mysql_tquery(mysql, query, "OnAddItem", "iii", playerid, itemid, amount);

	return 1;
}

forward OnAddItem(playerid, itemid, amount);
public OnAddItem(playerid, itemid, amount)
{
	new slot = GetFreeInventorySlot(playerid);
	
	Inventory[playerid][slot][ItemSQLID] = cache_insert_id();
	Inventory[playerid][slot][ItemOwner] = Player[playerid][AccountID];
	Inventory[playerid][slot][ItemType] = itemid;
	Inventory[playerid][slot][ItemAmount] = amount;

	Inventory[playerid][slot][PlayerItem] = true;

	total_weight[playerid] = total_weight[playerid] + GetItemWeight(Inventory[playerid][slot][ItemType], Inventory[playerid][slot][ItemAmount]);

	new string[128];
	format(string, sizeof(string), "Player %s has added item %ix%i to their inventory", GetNameByID(playerid), itemid, amount);
	LogEvent("item_additem", string, GetNameByID(playerid));
	return 1;
}

stock HasItem(playerid, itemid)
{
	for (new i = 0; i < MAX_ITEMS; i++)
	{
		if(itemid == Inventory[playerid][i][ItemType])
		{
			if(Inventory[playerid][i][ItemAmount] > 0) 
			{
				return i;
			} else {
				return -1;
			}
		}
	}
	return -1;
}

stock GetItemName(itemid)
{
	new name[32];

	format(name, sizeof(name), "%s", Items[itemid][ItemName]);
	return name;
}

stock GetGiveID(itemid)
{
	return Items[itemid][GiveID];
}

stock GetItemWeight(itemid, amount)
{
	return Items[itemid][Weight] * amount;
}

stock GetMaxWeight(playerid)
{
	new max_weight;

	max_weight = (Player[playerid][Level] * 100) + (Player[playerid][DonatorLevel] * 1000) + 1000;
	return max_weight;
}

stock GetItemType(weaponid)
{
	for (new i = 0; i < MAX_ITEMS; i++)
	{
		if(weaponid == Items[i][GiveID])
		{
			return Items[i][ItemID];
		} else {
			if(i > MAX_ITEMS - 1) {
				return -1;
			}
		}
	}
	return -1;
}

stock GetFreeInventorySlot(playerid)
{
	for (new i = 0; i < MAX_ITEMS; i++)
	{
		if (!Inventory[playerid][i][PlayerItem])
		{
			return i;
		}
	}
	return -1;
}

// Main command
command(inventory, playerid, params[])
{
	InventoryList(playerid);
	return 1;
}

// Alias of /inventory
command(inv, playerid, params[])
{
	return cmd_inventory(playerid, params);
}

command(holster, playerid, params[])
{
	if(GetPlayerWeapon(playerid) > 0)
	{
		// If the Item give type is -1 (invalid), don't try to add it to the inventory
		if(GetItemType(GetPlayerWeapon(playerid)) == -1) return SendErrorMessage(playerid, 1, "This item cannot be holstered.");

		new item = GetItemType(GetPlayerWeapon(playerid));

		if((GetItemWeight(item, GetPlayerAmmo(playerid)) + total_weight[playerid]) > GetMaxWeight(playerid)) return SendErrorMessage(playerid, 2, "That item is too heavy.");

		AddItem(playerid, item, GetPlayerAmmo(playerid));
		RemovePlayerWeapon(playerid, GetPlayerWeapon(playerid));

		SendClientMessage(playerid, YELLOW, "You have holstered your active weapon into your inventory.");

		new string[128];
		format(string, sizeof(string), "Player %s has holstered item %i", GetNameByID(playerid), item);
		LogEvent("item_use", string, GetNameByID(playerid));

	} else return SendErrorMessage(playerid, 1, "You can't holster that.");
	return 1;
}