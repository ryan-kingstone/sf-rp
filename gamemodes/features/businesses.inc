/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

#define MAX_BUSINESS	2000

enum _BUSINESS
{
	BusinessID,
	BusinessName[64],
	BusinessOwnerID,
	BusinessInteriorWorld,
	BusinessExteriorWorld,
	BusinessInterior,
	Float:BusinessInteriorX,
	Float:BusinessInteriorY,
	Float:BusinessInteriorZ,
	Float:BusinessExteriorX,
	Float:BusinessExteriorY,
	Float:BusinessExteriorZ,
	BusinessLocked,
	BusinessPrice,
	BusinessCashbox
};

new Business[MAX_BUSINESS][_BUSINESS];

new Text3D:BusinessLabel[MAX_BUSINESS],
	BusinessPickup[MAX_BUSINESS],
	bool:ValidBusiness[MAX_BUSINESS],
	Total_Businesses_Created,
	InBusiness[MAX_PLAYERS];

// Hooks
#include "YSI\y_hooks"

hook OnGameModeInit()
{
    SetTimerEx("LoadBusinesses", 2000, false);
	return 1;
}

// Load Businesss
forward LoadBusinesses();
public LoadBusinesses()
{
	new query[32];
	mysql_format(mysql, query, sizeof(query), "SELECT * FROM `Businesses`");
	mysql_tquery(mysql, query, "LoadAllBusinesses");

	printf("Loading Businesses...");
	return 1;
}

forward LoadAllBusinesses();
public LoadAllBusinesses()
{
	new string[256];

	if(cache_num_rows())
	{
		for(new i = 0; i < cache_num_rows(); i++)
		{
			new bid = GetFreeBusinessSlot();
			ValidBusiness[bid] = true;

			Business[bid][BusinessID] = cache_get_field_content_int(i, "BusinessID");
			cache_get_field_content(i, "BusinessName", Business[bid][BusinessName], mysql, 64);
			Business[bid][BusinessOwnerID] = cache_get_field_content_int(i, "BusinessOwnerID");

			// Worlds
			Business[bid][BusinessInteriorWorld] = cache_get_field_content_int(i, "BusinessInteriorWorld");
			Business[bid][BusinessExteriorWorld] = cache_get_field_content_int(i, "BusinessExteriorWorld");

			// Interior
			Business[bid][BusinessInterior] = cache_get_field_content_int(i, "BusinessInterior");

			// Interior coordinates
			Business[bid][BusinessInteriorX] = cache_get_field_content_float(i, "BusinessInteriorX");
			Business[bid][BusinessInteriorY] = cache_get_field_content_float(i, "BusinessInteriorY");
			Business[bid][BusinessInteriorZ] = cache_get_field_content_float(i, "BusinessInteriorZ");

			// Exterior coordinates
			Business[bid][BusinessExteriorX] = cache_get_field_content_float(i, "BusinessExteriorX");
			Business[bid][BusinessExteriorY] = cache_get_field_content_float(i, "BusinessExteriorY");
			Business[bid][BusinessExteriorZ] = cache_get_field_content_float(i, "BusinessExteriorZ");


			format(string, sizeof(string), "Business (ID: %d)\n%s", bid, Business[bid][BusinessName]);

            BusinessLabel[bid] = Create3DTextLabel(string, BIZ, Business[bid][BusinessExteriorX], Business[bid][BusinessExteriorY], Business[bid][BusinessExteriorZ], 10.0, Business[bid][BusinessExteriorWorld], 1);
            BusinessPickup[bid] = CreatePickup(1272, 1, Business[bid][BusinessExteriorX], Business[bid][BusinessExteriorY], Business[bid][BusinessExteriorZ], 0);

			Total_Businesses_Created++;
		}
	}
	printf("[BUSINESS]: %d Businesses have been successfully loaded from the database.", Total_Businesses_Created);
	return 1;
}

stock ResetBusinessVariables(businessid)
{
	new string[64];
	Business[businessid][BusinessID] = 0;
	format(string, sizeof(string), "");
	strcpyEx(Business[businessid][BusinessName], string);
	Business[businessid][BusinessOwnerID] = 0;

	// Worlds
	Business[businessid][BusinessInteriorWorld] = 0;
	Business[businessid][BusinessExteriorWorld] = 0;

	// Interior
	Business[businessid][BusinessInterior] = 0;

	// Interior coordinates
	Business[businessid][BusinessInteriorX] = 0.0;
	Business[businessid][BusinessInteriorY] = 0.0;
	Business[businessid][BusinessInteriorZ] = 0.0;

	// Exterior coordinates
	Business[businessid][BusinessExteriorX] = 0.0;
	Business[businessid][BusinessExteriorY] = 0.0;
	Business[businessid][BusinessExteriorZ] = 0.0;

	return 1;
}

stock CreateBusiness(name[], interior, price, Float:ex, Float:ey, Float:ez, Float:ix, Float:iy, Float:iz)
{
	mysql_format(mysql, query, sizeof(query), "INSERT INTO `businesses` (`BusinessName`, `BusinessOwnerID`, `BusinessInteriorWorld`, `BusinessExteriorWorld`, `BusinessInterior`, `BusinessInteriorX`, `BusinessInteriorY`, `BusinessInteriorZ`, `BusinessExteriorX`, `BusinessExteriorY`, `BusinessExteriorZ`, `BusinessLocked`, `BusinessPrice`) VALUES (%e, %d, %d, %d, %d)", name, 0, intworld, extworld, interior);
	mysql_tquery(mysql, query, "OnAddBusiness", "s[64]iiffffff", name, interior, price, ex, ey, ez, ix, iy, iz);

	return 1;
}

forward OnAddBusiness(name[], interior, price, Float:ex, Float:ey, Float:ez, Float:ix, Float:iy, Float:iz);
public OnAddBusiness(name[], interior, price, Float:ex, Float:ey, Float:ez, Float:ix, Float:iy, Float:iz)
{
	new string[256];

	new bid = GetFreeBusinessSlot();
	ValidBusiness[bid] = true;



	format(string, sizeof(string), "Business (ID: %d)\n%s", bid, Business[bid][BusinessName]);

	BusinessLabel[bid] = Create3DTextLabel(string, BIZ, Business[bid][BusinessExteriorX], Business[bid][BusinessExteriorY], Business[bid][BusinessExteriorZ], 10.0, Business[bid][BusinessExteriorWorld], 1);
	BusinessPickup[bid] = CreatePickup(1272, 1, Business[bid][BusinessExteriorX], Business[bid][BusinessExteriorY], Business[bid][BusinessExteriorZ], 0);

	Total_Businesses_Created++;
	return 1;
}

stock GetFreeBusinessSlot()
{
	for(new i = 1; i < sizeof(ValidBusiness); i ++)
	{
		if(!ValidBusiness[i]) return i;
	}
	return -1;
}

stock ReloadAllBusinesses()
{
	Total_Businesses_Created = 0;

	for(new i = 0; i < MAX_BUSINESS; i++)
	{
		if(ValidBusiness[i])
		{
			ResetBusinessVariables(i);
			DestroyPickup(BusinessPickup[i]);
			Delete3DTextLabel(BusinessLabel[i]);

			ValidBusiness[i] = false;
		}
	}

	SetTimerEx("LoadBusinesses", 2000, false);

	return 1;
}