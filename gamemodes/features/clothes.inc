#include <a_samp>


#include <zcmd>
#include <sscanf2>
#include <h_colors>
#include <sql>


/* ***                                                  *** */

#define NEXT_PAGE_SLOT 50

// I adjusted the dialog IDs as they were clashing with my register/login system

//Dialog ID's
#define D_CLOTHES 62
#define D_BUY_CLOTHES 72

//Dialog Stats
#define ON_CLOTHES_LIST 500
#define ON_CLOTHES_NONE 501
#define ON_CLOTHES_CHOSE 502
#define ON_CLOTHES_BONE 503

#define ON_CLOTHES_BUY 504

/**************************************************************************************/
#define MAX_MODELS 5

enum _PLAYER_MODELS
{
	cID,
	cModelID,
	cBoneID,
	Float:cOffsetX,
	Float:cOffsetY,
	Float:cOffsetZ,
	Float:cRotX,
	Float:cRotY,
	Float:cRotZ,
	Float:cScaleX,
	Float:cScaleY,
	Float:cScaleZ,
	bool:cOn
}

new ClothesInfo[MAX_PLAYERS][MAX_MODELS][_PLAYER_MODELS];

/**************************************************************************************/

enum _MODELS_INFO
{
	modelID,
	modelName[64],
	modelPrice,
	modelBone
}

stock ModelsInfo[][_MODELS_INFO] = {
	{18926, "Army Hat", 70, 2},
	{18927, "Azure Hat", 70, 2},
	{18928, "Funky Hat", 70, 2},
	{18929, "Dark Gray Hat", 70, 2},
	{18930, "Fire Hat", 70, 2},
	{18931, "Dark Blue Hat", 00, 2},
	{18932, "Orange Hat", 70, 2},
	{18933, "Light Gray Hat", 70, 2},
	{18934, "Pink Hat", 70, 2},
	{18935, "Yellow Hat", 70, 2},
	{18944, "Fire Hat Boater", 10, 2},
	{18945, "Gray Hat Boater", 10, 2},
	{18946, "Gray Hat Boater 2", 10, 2},
	{18947, "Black Hat Bowler", 10, 2},
	{18948, "Azure Hat Bowler", 10, 2},
	{18949, "Green Hat Bowler", 10, 2},
	{18950, "Red Hat Bowler", 10, 2},
	{18951, "Light Green Hat Bowler", 10, 2},
	{19488, "White Hat Bowler", 10, 2},
	{18967, "Simple Black Hat", 50, 2},
	{18968, "Simple Gray Hat", 50, 2},
	{18969, "Simple Orange Hat", 50, 2},
	{18970, "Tiger Hat", 100, 2},
	{18971, "Black & White Cool Hat", 100, 2},
	{18972, "Black & Orange Cool Hat", 100, 2},
	{18973, "Black & Green Cool Hat", 100, 2},
	{19066, "Santa Hat", 300, 2},
	{19067, "Red Hoody Hat", 50, 2},
	{19068, "Tiger Hoody Hat", 50, 2},
	{19069, "Black Hoody Hat", 50, 2},
	{19093, "White Dude Hat", 130, 2},
	{19095, "Brown Cowboy Hat", 130, 2},
	{19096, "Black Cowboy Hat", 130, 2},
	{19097, "Black Cowboy Hat 2", 130, 2},
	{19098, "Brown Cowboy Hat 2", 130, 2},
	{19352, "Black Top Hat", 200, 2},
	{19487, "White Top Hat", 200, 2},
	{18964, "Black Skully Cap", 70, 2},
	{18965, "Brown Skully Cap", 70, 2},
	{18966, "Funky Skully Cap", 70, 2},
	{18921, "Blue Beret", 500, 2},
	{18922, "Red Beret", 500, 2},
	{18923, "Dark Blue Beret", 500, 2},
	{18924, "Army Beret", 500, 2},
	{18925, "Red Army Beret", 500, 2},
	{18939, "Dark Blue CapBack", 100, 2},
	{18940, "Azure CapBack", 100, 2},
	{18941, "Black CapBack", 100, 2},
	{18942, "Gray CapBack", 100, 2},
	{18943, "Green CapBack", 100, 2},
	{19006, "Red Glasses", 100, 2},
	{19007, "Green Glasses", 100, 2},
	{19008, "Yellow Glasses", 100, 2},
	{19009, "Azure Glasses", 100, 2},
	{19010, "Pink Glasses", 100, 2},
	{19011, "Funky Glasses", 100, 2},
	{19012, "Gray Glasses", 100, 2},
	{19013, "Funky Glasses 2", 100, 2},
	{19014, "Black & White Glasses", 100, 2},
	{19015, "White Glasses", 100, 2},
	{19016, "X-Ray Glasses", 300, 2},
	{19017, "Covered Yellow Glasses", 100, 2},
	{19018, "Covered Orange Glasses", 100, 2},
	{19019, "Covered Red Glasses", 100, 2},
	{19020, "Covered Blue Glasses", 100, 2},
	{19021, "Covered Green Glasses", 100, 2},
	{19022, "Cool Black Glasses", 100, 2},
	{19023, "Cool Azure Glasses", 100, 2},
	{19024, "Cool Blue Glasses", 100, 2},
	{19025, "Cool Pink Glasses", 100, 2},
	{19026, "Cool Red Glasses", 100, 2},
	{19027, "Cool Orange Glasses", 100, 2},
	{19028, "Cool Yellow Glasses", 100, 2},
	{19029, "Cool Yellow Glasses", 100, 2},
	{19030, "Pink Nerd Glasses", 150, 2},
	{19031, "Green Nerd Glasses", 150, 2},
	{19032, "Red Nerd Glasses", 150, 2},
	{19033, "Black Nerd Glasses", 150, 2},
	{19034, "Black & White Nerd Glasses", 150, 2},
	{19035, "Ocean Nerd Glasses", 150, 2},
	{18891, "Purple Bandana", 120, 2},
	{18892, "Red Bandana", 120, 2},
	{18893, "Red&White Bandana", 120, 2},
	{18894, "Orange Bandana", 120, 2},
	{18895, "Skull Bandana", 120, 2},
	{18896, "Black Bandana", 120, 2},
	{18897, "Blue Bandana", 120, 2},
	{18898, "Green Bandana", 120, 2},
	{18899, "Pink Bandana", 120, 2},
	{18900, "Funky Bandana", 120, 2},
	{18901, "Tiger Bandana", 120, 2},
	{18902, "Yellow Bandana", 120, 2},
	{18903, "Azure Bandana", 120, 2},
	{18904, "Dark Blue Bandana", 120, 2},
	{18905, "Olive Bandana", 120, 2},
	{18906, "Orange&Yellow Bandana", 80, 2},
	{18907, "Funky Bandana 2", 80, 2},
	{18907, "Blue Bandana 2", 80, 2},
	{18907, "Azure Bandana 2", 80, 2},
	{18907, "Fire Bandana", 80, 2},
	{18911, "Skull Bandana Mask", 120, 18},
	{18912, "Black Bandana Mask", 120, 18},
	{18913, "Green Bandana Mask", 120, 18},
	{18914, "Army Bandana Mask", 120, 18},
	{18915, "Funky Bandana Mask", 120, 18},
	{18916, "Light Bandana Mask", 120, 18},
	{18917, "Dark Blue Bandana Mask", 120, 18},
	{18918, "Gray Bandana Mask", 120, 18},
	{18919, "White Bandana Mask", 120, 18},
	{18920, "Colorful Bandana Mask", 120, 18},
	{19421, "White Headphones", 200, 2},
	{19422, "Black Headphones", 200, 2},
	{19423, "Gray Headphones", 200, 2},
	{19424, "Blue Headphones", 200, 2},
	{19036, "White Hockey Mask", 120, 2},
	{19037, "Red Hockey Mask", 120, 2},
	{19038, "Green Hockey Mask", 120, 2},
	{19472, "Gas Mask", 200, 2},
	{2919, "Sports Bag", 150, 5},
	{3026, "Jansport Backpack", 150, 1},
	{19559, "Hiking Backpack", 300, 1},
	{18645, "Red&White Motorcycle Helmet", 400, 2},
	{18976, "Blue Motorcycle Helmet", 400, 2},
	{18977, "Red Motorcycle Helmet", 400, 2},
	{18978, "White Motorcycle Helmet", 400, 2},
	{18979, "Purple Motorcycle Helmet", 400, 2},
	{19317, "Bass Guitar", 1400 ,1},
	{19318, "Flying Guitar", 1500, 1},
	{19319, "Warlock Guitar", 1600, 1}
};
/**************************************************************************************/

stock LoadPlayerClothes(playerid)
{
	new query[65+1];
	format(query, sizeof(query), "SELECT * FROM `clothes` WHERE `Holder`=%d", Player[playerid][AccountID]);
	mysql_tquery(mysql, query, "OnClothesLoad", "i", playerid);
}

forward OnClothesLoad(playerid);
public OnClothesLoad(playerid)
{
	new rows = cache_num_rows();
	if (rows)
	{
		for (new i = 0; i < rows; i++)
		{
			ClothesInfo[playerid][i][cID] = cache_get_field_content_int(i, "ClothingID");
			ClothesInfo[playerid][i][cModelID] = cache_get_field_content_int(i, "ModelID");
			ClothesInfo[playerid][i][cBoneID] = cache_get_field_content_int(i, "BoneID");
			ClothesInfo[playerid][i][cOffsetX] = cache_get_field_content_float(i, "OffsetX");
			ClothesInfo[playerid][i][cOffsetY] = cache_get_field_content_float(i, "OffsetY");
			ClothesInfo[playerid][i][cOffsetZ] = cache_get_field_content_float(i, "OffsetZ");
			ClothesInfo[playerid][i][cRotX] = cache_get_field_content_float(i, "RotX");
			ClothesInfo[playerid][i][cRotY] = cache_get_field_content_float(i, "RotY");
			ClothesInfo[playerid][i][cRotZ] = cache_get_field_content_float(i, "RotZ");
			ClothesInfo[playerid][i][cScaleX] = cache_get_field_content_float(i, "ScaleX");
			ClothesInfo[playerid][i][cScaleY] = cache_get_field_content_float(i, "ScaleY");
			ClothesInfo[playerid][i][cScaleZ] = cache_get_field_content_float(i, "ScaleZ");
			ClothesInfo[playerid][i][cOn] = true;
		}
	}
	return 1;
}

#include <YSI\y_hooks>

hook OnPlayerSpawn(playerid)
{
	LoadPlayerClothes(playerid);
	return 1;
}

#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	SavePlayerClothes(playerid);
	return 1;
}

#include <YSI\y_hooks>

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new status = GetPVarInt(playerid, "DialogStatus");
	if (dialogid == D_CLOTHES)
	{
		switch (status)
		{
			case ON_CLOTHES_LIST:
			{
				if (response)
				{
					new i = listitem;
					if (!ClothesInfo[playerid][i][cOn])
					{
						ShowDialog(playerid, D_CLOTHES, DIALOG_STYLE_MSGBOX, "Clothing List", "Empty index...", "<<<", "", ON_CLOTHES_NONE);
					}
					else
					{
						SetPVarInt(playerid, "IndexChose", i);
						ClothesEditDialog(playerid, i);
					}
				}
			}
			case ON_CLOTHES_NONE:
			{
				if (response || !response)
				{
					DisplayClothing(playerid);
				}
			}
			case ON_CLOTHES_CHOSE:
			{
				if (response)
				{
					new slot = GetPVarInt(playerid, "IndexChose");
					switch (listitem)
					{
						case 0: 
						{
							EditClothing(playerid, slot);
						}
						case 1:
						{
							ShowDialog(playerid, D_CLOTHES, DIALOG_STYLE_LIST, "Change The Bone Slot", "Spine\nHead\nLeft Upper Arm\nRight Upper Arm\nLeft Hand\nRight Hand\nLeft Thigh\nRight Thigh\nLeft Food\nRight Foot\nRight Calf\nLeft Calf\nLeft Forearm\nRight forearm\nLeft Clavicle\nRight Clavicle\nNeck\nJaw", "Select", "<<<", ON_CLOTHES_BONE);
						}
						case 2:
						{
							PlaceClothing(playerid, slot);
							ClothesEditDialog(playerid, slot);
						}
					}
				}
				else
				{
					DisplayClothing(playerid);
				}
			}
			case ON_CLOTHES_BONE:
			{
				new index = GetPVarInt(playerid, "IndexChose");
				if (response)
				{
					new msg[79+1], bone = listitem + 1;
					format(msg, sizeof(msg), "You have adjusted your clothing index %d to bone %s.", index, GetBoneName(bone));
					SendClientMessage(playerid, COLOR_WHITE, msg);
					ClothesInfo[playerid][index][cBoneID] = bone;
					if (IsPlayerAttachedObjectSlotUsed(playerid, index))
					{
						ReplaceClothing(playerid, index);
					}
					ClothesEditDialog(playerid, index);
				}
				else
				{
					ClothesEditDialog(playerid, index);
				}
			}		
		}
	}
	/******************************************************************************/
	if (dialogid == D_BUY_CLOTHES)
	{
		switch (status)
		{
			case ON_CLOTHES_BUY:
			{
				if (response)
				{
					new slot = GetPVarInt(playerid, "FromSlot");
					if (listitem != NEXT_PAGE_SLOT)
					{
						new i = slot + listitem;
						new price = ModelsInfo[i][modelPrice];
						new freeslot = GetFreeSlot(playerid);
						if (GetPlayerMoney(playerid) >= price)
						{
							if (freeslot != -1)
							{
								SendClientMessage(playerid, -1, "Before you complete the purchase you may take a look at the item and adjust it.");
								SendClientMessage(playerid, -1, "Press {FFFF00}ESC{FFFFFF} to cancel the purchase.");
								SetPVarInt(playerid, "SelectedItem", 1);
								SetPVarInt(playerid, "ItemIndex", i);
								SetPVarInt(playerid, "FreeSlot", freeslot);
								SetPlayerAttachedObject(playerid, freeslot, ModelsInfo[i][modelID], ModelsInfo[i][modelBone]);
								EditAttachedObject(playerid, freeslot);
							}
							else
							{
								SendClientMessage(playerid, COLOR_LIGHTRED, "Purchase failed, you do not possess any free slots.");
							}
						}
						else
						{
							new msg[43+1];
							format(msg, sizeof(msg), "You are lacking money, ${FFFF00}%d", ModelsInfo[i][modelPrice]);
							SendClientMessage(playerid, -1, msg);
						}
					}
					else
					{
						ShowClothesDialog(playerid, slot + NEXT_PAGE_SLOT);
					}
				}
				else
				{
					DeletePVar(playerid, "FromSlot");
				}
			}
		}
	}
	return 1;
}

stock GetFreeSlot(playerid)
{
	for (new i = 0; i < MAX_MODELS; i++)
	{
		if (!ClothesInfo[playerid][i][cOn])
			return i;
	}
	return -1;
}

stock OnBuyClothes(playerid, index, model, bone, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	new query[299+1];
	format(query, sizeof(query), "INSERT INTO `clothes` (Holder, ModelID, BoneID, OffsetX, OffsetY, OffsetZ, RotX, RotY, RotZ, ScaleX, ScaleY, ScaleZ) VALUES (%d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f)",
	Player[playerid][AccountID], model, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
	mysql_tquery(mysql, query, "OnFinishPurchase", "i", index);
}

forward OnFinishPurchase(index);
public OnFinishPurchase(index)
{
	return 1;
}

stock ClothesEditDialog(playerid, index)
{
	if (IsPlayerAttachedObjectSlotUsed(playerid, index))
	{
		ShowDialog(playerid, D_CLOTHES, DIALOG_STYLE_LIST, "Clothing List", "Adjust The Item\nChange Bone Slot\nTake Off", "Select", "<<<", ON_CLOTHES_CHOSE);
	}
	else
	{
		ShowDialog(playerid, D_CLOTHES, DIALOG_STYLE_LIST, "Clothing List", "Adjust The Item\nChange Bone Slot\nPlace On", "Select", "<<<", ON_CLOTHES_CHOSE);
	}
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if (GetPVarInt(playerid, "EditingNow") == 1)
	{
		new i = GetPVarInt(playerid, "EditingSlot");
		if (response)
		{
			ClothesInfo[playerid][i][cOffsetX] = fOffsetX;
			ClothesInfo[playerid][i][cOffsetY] = fOffsetY;
			ClothesInfo[playerid][i][cOffsetZ] = fOffsetZ;
			ClothesInfo[playerid][i][cRotX] = fRotX;
			ClothesInfo[playerid][i][cRotY] = fRotY;
			ClothesInfo[playerid][i][cRotZ] = fRotZ;
			ClothesInfo[playerid][i][cScaleX] = fScaleX;
			ClothesInfo[playerid][i][cScaleY] = fScaleY;
			ClothesInfo[playerid][i][cScaleZ] = fScaleZ;
		}
		DeletePVar(playerid, "EditingSlot");
		DeletePVar(playerid, "EditingNow");
		ReplaceClothing(playerid, i);
	}
	if (GetPVarInt(playerid, "SelectedItem") == 1 && GetPVarInt(playerid, "EditingNow") == 0)
	{
		new i = GetPVarInt(playerid, "ItemIndex");
		new slot = GetPVarInt(playerid, "FreeSlot");
		if (response)
		{
			new msg[139+1];
			OnBuyClothes(playerid, slot, ModelsInfo[i][modelID], ModelsInfo[i][modelBone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
			//GivePlayerMoney(playerid, -ModelsInfo[i][modelPrice]);
            //CallRemoteFunction("TakeMoney", "ii", playerid, ModelsInfo[i][modelPrice]);
			format(msg, sizeof(msg), "You have successfully purchased a {FFFF00}%s{FFFFFF} for ${FFFF00}%d", ModelsInfo[i][modelName], ModelsInfo[i][modelPrice]);
			SendClientMessage(playerid, -1, msg);
			ClothesInfo[playerid][slot][cModelID] = ModelsInfo[i][modelID];
			ClothesInfo[playerid][slot][cBoneID] = ModelsInfo[i][modelBone];
			ClothesInfo[playerid][slot][cOffsetX] = fOffsetX;
			ClothesInfo[playerid][slot][cOffsetY] = fOffsetY;
			ClothesInfo[playerid][slot][cOffsetZ] = fOffsetZ;
			ClothesInfo[playerid][slot][cRotX] = fRotX;
			ClothesInfo[playerid][slot][cRotY] = fRotY;
			ClothesInfo[playerid][slot][cRotZ] = fRotZ;
			ClothesInfo[playerid][slot][cScaleX] = fScaleX;
			ClothesInfo[playerid][slot][cScaleY] = fScaleY;
			ClothesInfo[playerid][slot][cScaleZ] = fScaleZ;
			ClothesInfo[playerid][slot][cOn] = true;
		}
		else
		{
			SendClientMessage(playerid, COLOR_LIGHTRED, "You've canceled the purchase of this item.");
			RemovePlayerAttachedObject(playerid, index);
		}
		DeletePVar(playerid, "SelectedItem");
		DeletePVar(playerid, "ItemIndex");
		DeletePVar(playerid, "FreeSlot");
	}
	return 1;
}

command(clothing, playerid, params[])
{
	new msg[98+1], option[11], secoption;
	if (GetPVarInt(playerid, "SelectedItem") == 1)
		return SendClientMessage(playerid, COLOR_LIGHTRED, "Please finish the current operation.");
	if (sscanf(params, "s[11]D(-1)", option, secoption))
	{
		SyntaxMSG(playerid, "/clothing [place | adjust | delete]");
		DisplayClothing(playerid);
		return 1;
	}
	else if (!strcmp(option, "place", true))
	{
		new slot;
		if (sscanf(params, "{s[7]}d", slot))
		{
			SyntaxMSG(playerid, "/clothing place [slot]");
			for (new i = 0; i < MAX_MODELS; i++)
			{
				if (ClothesInfo[playerid][i][cOn])
				{
					format(msg, sizeof(msg), "%d. %s", i, GetModelName(ClothesInfo[playerid][i][cModelID]));
					SendClientMessage(playerid, -1, msg);
				}
				else
				{
					format(msg, sizeof(msg), "%d. EMPTY", i);
					SendClientMessage(playerid, -1, msg);
				}
			}
			return 1;
		}
		if (slot > MAX_MODELS || slot < 0) return SendClientMessage(playerid, -1, "Invalid slot.");
		if (!ClothesInfo[playerid][slot][cOn]) return SendClientMessage(playerid, -1, "No such item.");
		PlaceClothing(playerid, slot);
	}
	else if (!strcmp(option, "adjust", true)) 
	{
		new slot;
		if (sscanf(params, "{s[7]}d", slot)) return SyntaxMSG(playerid, "/clothing adjust [slot]");
		if (slot > MAX_MODELS || slot < 0) return SendClientMessage(playerid, -1, "Invalid slot.");
		if (!ClothesInfo[playerid][slot][cOn]) return SendClientMessage(playerid, -1, "No such item.");
		EditClothing(playerid, slot);
	}
	else if (!strcmp(option, "delete", true)) 
	{
		new slot;
		if (sscanf(params, "{s[7]}d", slot)) return SyntaxMSG(playerid, "/clothing delete [slot]");
		if (slot > MAX_MODELS || slot < 0) return SendClientMessage(playerid, -1, "Invalid slot.");
		if (!ClothesInfo[playerid][slot][cOn]) return SendClientMessage(playerid, -1, "No such item.");
		format(msg, sizeof(msg), "You have dropped your {00FF00}%s{FFFFFF}, and will be no longer available.", GetModelName(ClothesInfo[playerid][slot][cModelID]));
		SendClientMessage(playerid, -1, msg);
		RemoveFromSlot(playerid, slot);
	}
	else
	{
		SendClientMessage(playerid, COLOR_LIGHTRED, "Invalid parameter.");
	}
	return 1;
}

stock ShowClothesDialog(playerid, fromslot)
{
	new string[2000];
	for (new i = fromslot; i < fromslot + NEXT_PAGE_SLOT; i++)
	{
		if ( i < sizeof( ModelsInfo ) )
		{
			format(string, sizeof(string), "%s%d - %s - {FFFF00}$%d\n", string, i+1, ModelsInfo[i][modelName], ModelsInfo[i][modelPrice]);
		}
		if ( i == ( fromslot + NEXT_PAGE_SLOT ) - 1 && i < sizeof( ModelsInfo ) )
			strcat(string, "{FFFF00}Next Page\n");
	}
	SetPVarInt(playerid, "FromSlot", fromslot);
	ShowDialog(playerid, D_BUY_CLOTHES, DIALOG_STYLE_LIST, "Select your item", string, "Select", "Cancel", ON_CLOTHES_BUY);
}

CMD:buyclothing(playerid, params[])
{
	if (GetPVarInt(playerid, "SelectedItem") == 1)
		return SendClientMessage(playerid, COLOR_LIGHTRED, "Please finish the current operation.");
	ShowClothesDialog(playerid, 0);
	return 1;
}

stock SavePlayerClothes(playerid)
{
	for (new i = 0; i < MAX_MODELS; i++)
	{
		if (ClothesInfo[playerid][i][cOn])
		{
			UpdatePlayerToy(playerid, i);
		}
	}
	return 1;
}

stock UpdatePlayerToy(playerid, slot)
{
	new query[284+1];
	format(query, sizeof(query), "UPDATE `clothes` SET `BoneID`=%d, `OffsetX`=%f, `OffsetY`=%f, `OffsetZ`=%f, `RotX`=%f, `RotY`=%f, `RotZ`=%f, `ScaleX`=%f, `ScaleY`=%f, `ScaleZ`=%f WHERE `ClothingID`=%d",
	ClothesInfo[playerid][slot][cBoneID], ClothesInfo[playerid][slot][cOffsetX], ClothesInfo[playerid][slot][cOffsetY], ClothesInfo[playerid][slot][cOffsetZ], ClothesInfo[playerid][slot][cRotX], ClothesInfo[playerid][slot][cRotY], ClothesInfo[playerid][slot][cRotZ], ClothesInfo[playerid][slot][cScaleX], ClothesInfo[playerid][slot][cScaleY], ClothesInfo[playerid][slot][cScaleZ], ClothesInfo[playerid][slot][cID]);
	mysql_tquery(mysql, query);
	return 1;
}

stock EditClothing(playerid, index)
{
	if (GetPVarInt(playerid, "EditingNow") == 1) return SendClientMessage(playerid, COLOR_LIGHTRED, "Please finish the current operation.");
	new msg[124+1];
	format(msg, sizeof(msg), "Editing now your {00FF00}%s{FFFFFF} - Index {00FF00}%d{FFFFFF}.", GetModelName(ClothesInfo[playerid][index][cModelID]), index);
	SendClientMessage(playerid, -1, msg);
	SetPVarInt(playerid, "EditingSlot", index);
	SetPVarInt(playerid, "EditingNow", 1);
	if (!IsPlayerAttachedObjectSlotUsed(playerid, index))
	{
		SetPlayerAttachedObject(playerid, index, ClothesInfo[playerid][index][cModelID], ClothesInfo[playerid][index][cBoneID], ClothesInfo[playerid][index][cOffsetX], ClothesInfo[playerid][index][cOffsetY], ClothesInfo[playerid][index][cOffsetZ], ClothesInfo[playerid][index][cRotX], ClothesInfo[playerid][index][cRotY], ClothesInfo[playerid][index][cRotZ], ClothesInfo[playerid][index][cScaleX], ClothesInfo[playerid][index][cScaleY], ClothesInfo[playerid][index][cScaleZ]);
	}
	EditAttachedObject(playerid, index);
	return 1;
}

stock ReplaceClothing(playerid, index)
{
	RemovePlayerAttachedObject(playerid, index);
	SetPlayerAttachedObject(playerid, index, ClothesInfo[playerid][index][cModelID], ClothesInfo[playerid][index][cBoneID], ClothesInfo[playerid][index][cOffsetX], ClothesInfo[playerid][index][cOffsetY], ClothesInfo[playerid][index][cOffsetZ], ClothesInfo[playerid][index][cRotX], ClothesInfo[playerid][index][cRotY], ClothesInfo[playerid][index][cRotZ], ClothesInfo[playerid][index][cScaleX], ClothesInfo[playerid][index][cScaleY], ClothesInfo[playerid][index][cScaleZ]);
}

stock PlaceClothing(playerid, index)
{
	new msg[102+1];
	if (IsPlayerAttachedObjectSlotUsed(playerid, index))
	{
		format(msg, sizeof(msg), "You have removed your {00FF00}%s{FFFFFF}.", GetModelName(ClothesInfo[playerid][index][cModelID]));
		SendClientMessage(playerid, -1, msg);
		RemovePlayerAttachedObject(playerid, index);
	}
	else
	{
		format(msg, sizeof(msg), "You have placed your {00FF00}%s{FFFFFF}.", GetModelName(ClothesInfo[playerid][index][cModelID]));
		SendClientMessage(playerid, -1, msg);
		SetPlayerAttachedObject(playerid, index, ClothesInfo[playerid][index][cModelID], ClothesInfo[playerid][index][cBoneID], ClothesInfo[playerid][index][cOffsetX], ClothesInfo[playerid][index][cOffsetY], ClothesInfo[playerid][index][cOffsetZ], ClothesInfo[playerid][index][cRotX], ClothesInfo[playerid][index][cRotY], ClothesInfo[playerid][index][cRotZ], ClothesInfo[playerid][index][cScaleX], ClothesInfo[playerid][index][cScaleY], ClothesInfo[playerid][index][cScaleZ]);
	}
	return 1;
}

stock DisplayClothing(playerid)
{
	new dstr[500];
	for (new i = 0; i < MAX_MODELS; i++)
	{
		if (ClothesInfo[playerid][i][cOn])
		{
			format(dstr, sizeof(dstr), "%s%s (Index %d)\n", dstr, GetModelName(ClothesInfo[playerid][i][cModelID]), i);
		}
		else
		{
			format(dstr, sizeof(dstr), "%sEMPTY (Index %d)\n", dstr, i);
		}
	}
	ShowDialog(playerid, D_CLOTHES, DIALOG_STYLE_LIST, "Clothes List", dstr, "Select", "Cancel", ON_CLOTHES_LIST);
	return 1;
}

stock ShowDialog(playerid, dialogid, style, caption[], info[], button1[], button2[], status)
{
	SetPVarInt(playerid, "DialogStatus", status);
	ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
	return 1;
}

stock GetModelName(model)
{
	new name[64];
	for (new i = 0; i < sizeof(ModelsInfo); i++)
	{
		if (model == ModelsInfo[i][modelID])
		{
			// Also the definition of "strcpy"
			strcat((name[0] = '\0', name), ModelsInfo[i][modelName]);
			//format(name, sizeof(name), "%s", ModelsInfo[i][modelName]);
		}
	}
	return name;
}

stock RemoveFromSlot(playerid, slot)
{
	new query[44+1];
	format(query, sizeof(query), "DELETE FROM `clothes` WHERE `ClothingID`=%d", ClothesInfo[playerid][slot][cID]);
	mysql_tquery(mysql, query, "OnRemoveFromSlot", "ii", playerid, slot);
}

forward OnRemoveFromSlot(playerid, slot);
public OnRemoveFromSlot(playerid, slot)
{
	ClothesInfo[playerid][slot][cOn] = false;
	ClothesInfo[playerid][slot][cModelID] = 0;
	ClothesInfo[playerid][slot][cBoneID] = 0;
	ClothesInfo[playerid][slot][cOffsetX] = 0.0;
	ClothesInfo[playerid][slot][cOffsetY] = 0.0;
	ClothesInfo[playerid][slot][cOffsetZ] = 0.0;
	ClothesInfo[playerid][slot][cRotX] = 0.0;
	ClothesInfo[playerid][slot][cRotY] = 0.0;
	ClothesInfo[playerid][slot][cRotZ] = 0.0;
	ClothesInfo[playerid][slot][cScaleX] = 0.0;
	ClothesInfo[playerid][slot][cScaleY] = 0.0;
	ClothesInfo[playerid][slot][cScaleZ] = 0.0;
	RemovePlayerAttachedObject(playerid, slot);
	return 1;
}

stock ResetClothes(playerid)
{
	for (new i = 0; i < MAX_MODELS; i++)
	{
		if (ClothesInfo[playerid][i][cOn] == true)
		{
			RemoveFromSlot(playerid, i);
		}
	}
}

stock SyntaxMSG(playerid, message[])
{
	new msg[144+1];
	format(msg, sizeof(msg), "{AFAFAF}USAGE:{FFFFFF} %s", (strlen(message) < 122) ? message : ("N/A"));
	return SendClientMessage(playerid, -1, msg);
}

stock GetBoneName(boneid)
{
	new bone[26];
	switch (boneid)
	{
		case 1: bone = "Spine";
		case 2: bone = "Head";
		case 3: bone = "Left upper arm";
		case 4: bone = "Right upper arm";
		case 5: bone = "Left hand";
		case 6: bone = "Right hand";
		case 7: bone = "Left thigh";
		case 8: bone = "Right thigh";
		case 9: bone = "Left foot";
		case 10: bone = "Right foot";
		case 11: bone = "Right calf";
		case 12: bone = "Left calf";
		case 13: bone = "Left forearm";
		case 14: bone = "Right forearm";
		case 15: bone = "Left clavicle (shoulder)";
		case 16: bone = "Right clavicle (shoulder)";
		case 17: bone = "Neck";
		case 18: bone = "Jaw";
		default: bone = "Unknown";
	}
	return bone;
}
