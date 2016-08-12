/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

enum _VEHICLE
{
	VehicleID,
	ModelID,
	OwnerID,
	Plate[11],
	Insurance,
	Float:Fuel,
	Float:Traveled,
	Float:VehicleState,
	Colour1,
	Colour2,
	Float:ParkedX,
	Float:ParkedY,
	Float:ParkedZ,
	Float:ParkedA,
	Nitrous,
	Hydraulics,
	Wheels,
	Siren,
	VehiclePanels,
	VehicleDoors,
	VehicleLights,
	VehicleTires,
	Broken,
	Faction,
	Carsign[64],
	Type,
	AdminSpawned
};

new Vehicles[MAX_VEHICLES][_VEHICLE], Total_Vehicles_Created;
new alarm[MAX_VEHICLES], bonnet[MAX_VEHICLES], boot[MAX_VEHICLES], objective[MAX_VEHICLES];
new bool:ValidVehicle[MAX_VEHICLES];


#include "YSI\y_hooks"

hook OnGameModeInit()
{
	SetTimerEx("LoadVehicles", 2000, false);
	return 1;
}

#include "YSI\y_hooks"

hook OnVehicleDeath(vehicleid, killerid)
{
	if(Vehicles[vehicleid][Faction] == 0)
	{
		DestroyVehicle(vehicleid);
		Total_Vehicles_Created--;

		ValidVehicle[vehicleid] = false;
		ResetVehicleVariables(vehicleid);
	}

	if(strlen(Vehicles[vehicleid][Carsign]) < 1)
	{
		Delete3DTextLabel(callsign_text[vehicleid]);
		callsign_status[vehicleid] = 0;
	}
}

forward LoadVehicles();
public LoadVehicles()
{
	new query[32];
	mysql_format(mysql, query, sizeof(query), "SELECT * FROM `vehicles`");
	mysql_tquery(mysql, query, "LoadAllVehicles");

	printf("Loading vehicles...");
	return 1;
}

forward LoadAllVehicles();
public LoadAllVehicles()
{
	if(cache_num_rows())
	{
		for(new i = 0; i < cache_num_rows(); i++)
		{
			new vid = GetFreeVehicleSlot();
			ResetVehicleVariables(vid);
			ValidVehicle[vid] = true;
			Vehicles[vid][VehicleID] = cache_get_field_content_int(i, "VehicleID");
			Vehicles[vid][ModelID] = cache_get_field_content_int(i, "ModelID");
			Vehicles[vid][OwnerID] = cache_get_field_content_int(i, "OwnerID");
			cache_get_field_content(i, "Plate", Vehicles[vid][Plate], mysql, 11);
			Vehicles[vid][Insurance] = cache_get_field_content_int(i, "Insurance");
			Vehicles[vid][Fuel] = cache_get_field_content_float(i, "Fuel");
			Vehicles[vid][Traveled] = cache_get_field_content_float(i, "Traveled");
			Vehicles[vid][VehicleState] = cache_get_field_content_float(i, "VehicleState");
			Vehicles[vid][Colour1] = cache_get_field_content_int(i, "Colour1");
			Vehicles[vid][Colour2] = cache_get_field_content_int(i, "Colour2");
			Vehicles[vid][ParkedX] = cache_get_field_content_float(i, "ParkedX");
			Vehicles[vid][ParkedY] = cache_get_field_content_float(i, "ParkedY");
			Vehicles[vid][ParkedZ] = cache_get_field_content_float(i, "ParkedZ");
			Vehicles[vid][ParkedA] = cache_get_field_content_float(i, "ParkedA");
			Vehicles[vid][Nitrous] = cache_get_field_content_int(i, "Nitrous");
			Vehicles[vid][Hydraulics] = cache_get_field_content_int(i, "Hydraulics");
			Vehicles[vid][Wheels] = cache_get_field_content_int(i, "Wheels");
			Vehicles[vid][Siren] = cache_get_field_content_int(i, "Siren");
			Vehicles[vid][VehiclePanels] = cache_get_field_content_int(i, "VehiclePanels");
			Vehicles[vid][VehicleDoors] = cache_get_field_content_int(i, "VehicleDoors");
			Vehicles[vid][VehicleLights] = cache_get_field_content_int(i, "VehicleLights");
			Vehicles[vid][VehicleTires] = cache_get_field_content_int(i, "VehicleTires");
			Vehicles[vid][Broken] = cache_get_field_content_int(i, "Broken");
			Vehicles[vid][Faction] = cache_get_field_content_int(i, "Faction");
			cache_get_field_content(i, "Carsign", Vehicles[vid][Carsign], mysql, 64);
			Vehicles[vid][Type] = cache_get_field_content_int(i, "Type");
			Vehicles[vid][AdminSpawned] = 0;

			if(Vehicles[vid][Type] == 1 || Vehicles[vid][Faction] != 0) {
				new Vehicle;
				if(Vehicles[vid][Siren]) {
					Vehicle = CreateVehicle(Vehicles[vid][ModelID], Vehicles[vid][ParkedX], Vehicles[vid][ParkedY], Vehicles[vid][ParkedZ], Vehicles[vid][ParkedA], Vehicles[vid][Colour1], Vehicles[vid][Colour2], -1, 1);
				} else {
					Vehicle = CreateVehicle(Vehicles[vid][ModelID], Vehicles[vid][ParkedX], Vehicles[vid][ParkedY], Vehicles[vid][ParkedZ], Vehicles[vid][ParkedA], Vehicles[vid][Colour1], Vehicles[vid][Colour2], -1, 0);
				}
				// Vehicle plate:
				new plate[11];
				format(plate, sizeof(plate), "%s", Vehicles[vid][Plate]);
				SetVehicleNumberPlate(Vehicle, plate);

				if(strlen(Vehicles[vid][Carsign]) > 0)
				{
					new string[128];
					format(string,sizeof(string), "%s", Vehicles[vid][Carsign]);
					callsign_text[vid] = Create3DTextLabel(string, 0xFFFFFFFF, 0.0, 0.0, 0.0, 50.0, 0, 1);
					Attach3DTextLabelToVehicle( callsign_text[vid], vid, -0.7, -1.9, -0.3);
					callsign_status[vid] = 1;
				}

				SetVehicleToRespawn(Vehicle);

				if(Vehicles[vid][Faction] == 0 || Vehicles[vid][Type] == 3)
				{
					SetVehicleParamsEx(Vehicle, 0, 0, alarm[vid], 1, bonnet[vid], boot[vid], objective[vid]);
				} else {
					SetVehicleParamsEx(Vehicle, 0, 0, alarm[vid], 0, bonnet[vid], boot[vid], objective[vid]);	
				}

				// Modifications:

				// Nitro
				switch(Vehicles[vid][Nitrous])
				{
					case 0: {}
					case 1: AddVehicleComponent(vid, 1008); // 1x
					case 2: AddVehicleComponent(vid, 1009); // 2x
					case 3: AddVehicleComponent(vid, 1010); // 10x
					default: {}
				}

				// Hydraulics
				if(Vehicles[vid][Hydraulics] == 1)
				{
					AddVehicleComponent(vid, 1087);
				}

				// Wheels
				switch(Vehicles[vid][Wheels])
				{
					case 0: {}
					case 1: AddVehicleComponent(vid, 1073); // shadow
					case 2: AddVehicleComponent(vid, 1074); // mega
					case 3: AddVehicleComponent(vid, 1075); // rimshine
					case 4: AddVehicleComponent(vid, 1076); // wires
					case 5: AddVehicleComponent(vid, 1077); // classic
					case 6: AddVehicleComponent(vid, 1078); // twist
					case 7: AddVehicleComponent(vid, 1079); // cutter
					case 8: AddVehicleComponent(vid, 1080); // switch
					case 9: AddVehicleComponent(vid, 1081); // grove
					case 10: AddVehicleComponent(vid, 1082);// import
					case 11: AddVehicleComponent(vid, 1083);// dollar
					case 12: AddVehicleComponent(vid, 1084);// trance
					case 13: AddVehicleComponent(vid, 1085);// atomic
					case 14: AddVehicleComponent(vid, 1096);// ahab
					case 15: AddVehicleComponent(vid, 1097);// virtual
					case 16: AddVehicleComponent(vid, 1098);// access
					case 17: AddVehicleComponent(vid, 1025);// offroad
					default: {}
				}

				Total_Vehicles_Created++;
			}
		}
	}
	printf("[VEHICLE]: %d Vehicles have been successfully loaded from the database.", Total_Vehicles_Created);
	return 1;
}

stock ReloadAllVehicles()
{
	Total_Vehicles_Created = 0;

	for(new i = 0; i < MAX_VEHICLES; i++)
	{
		if(ValidVehicle[i])
		{
			ResetVehicleVariables(i);
			DestroyVehicle(i);

			ValidVehicle[i] = false;
		}
	}

	SetTimerEx("LoadVehicles", 2000, false);

	return 1;
}

stock GetFreeVehicleSlot()
{
	for(new i = 1; i < sizeof(ValidVehicle); i ++)
	{
		if(!ValidVehicle[i]) return i;
	}
	return -1;
}

stock GetVehicleFaction(vehicleid)
{
	return Vehicles[vehicleid][Faction];
}

stock SetVehicleParkingSpot(vehicleid, Float:x, Float:y, Float:z, Float:a)
{
	new query[2048];
	mysql_format(mysql, query, sizeof(query), "UPDATE `vehicles` SET `ParkedX`=%f, `ParkedY`=%f, `ParkedZ`=%f, `ParkedA`=%f WHERE `VehicleID`=%d",
	x,
	y,
	z,
	a,

	// where id
	Vehicles[vehicleid][VehicleID]);
	mysql_tquery(mysql, query);

	Vehicles[vehicleid][ParkedX] = x;
	Vehicles[vehicleid][ParkedY] = y;
	Vehicles[vehicleid][ParkedZ] = z;
	Vehicles[vehicleid][ParkedA] = a;

	return 1;
}

stock ResetVehicleVariables(vehicleid)
{
	Vehicles[vehicleid][VehicleID] = 0;
	Vehicles[vehicleid][ModelID] = 0;
	Vehicles[vehicleid][OwnerID] = 0;

	Vehicles[vehicleid][Insurance] = 0;
	Vehicles[vehicleid][Fuel] = 0;
	Vehicles[vehicleid][Traveled] = 0;
	Vehicles[vehicleid][VehicleState] = 0;
	Vehicles[vehicleid][Colour1] = 0;
	Vehicles[vehicleid][Colour2] = 0;
	Vehicles[vehicleid][ParkedX] = 0;
	Vehicles[vehicleid][ParkedY] = 0;
	Vehicles[vehicleid][ParkedZ] = 0;
	Vehicles[vehicleid][ParkedA] = 0;
	Vehicles[vehicleid][Nitrous] = 0;
	Vehicles[vehicleid][Hydraulics] = 0;
	Vehicles[vehicleid][Wheels] = 0;
	Vehicles[vehicleid][VehiclePanels] = 0;
	Vehicles[vehicleid][VehicleDoors] = 0;
	Vehicles[vehicleid][VehicleLights] = 0;
	Vehicles[vehicleid][VehicleTires] = 0;
	Vehicles[vehicleid][Broken] = 0;
	Vehicles[vehicleid][Faction] = 0;
	Vehicles[vehicleid][Type] = 0;
	Vehicles[vehicleid][AdminSpawned] = 0;

	return 1;
}

stock CreateFactionVehicle(playerid, VehicleModel, VFaction, VColour1, VColour2, Float:VX, Float:VY, Float:VZ, Float:VA)
{
	new query[612];

	mysql_format(mysql, query, sizeof(query), "INSERT INTO `Vehicles` (`ModelID`, `OwnerID`, `Plate`, `Insurance`, `Fuel`, `Traveled`, `VehicleState`, `Colour1`, `Colour2`, `ParkedX`, `ParkedY`, `ParkedZ`, `ParkedA`, `Nitrous`, `Hydraulics`, `Wheels`, `VehiclePanels`, `VehicleDoors`, `VehicleLights`, `Broken`, `Faction`, `Type`) VALUES (%d, %d, '%e', %d, %f, %f, %f, %d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
	VehicleModel, 0, GenerateRandomPlate(), 4, 100.0, 0.0, 100.0, VColour1, VColour2, VX, VY, VZ, VA, 0, 0, 0, 0, 0, 0, 0, VFaction, 1);
	mysql_tquery(mysql, query);

	new string[128];
	format(string, sizeof(string), "Vehicle(%i) created with faction [%i]", VehicleModel, VFaction);
	LogEvent("createfactionvehicle", string, GetNameByID(playerid));
	return 1;
}

stock RandomEx(min, max)
{
	//Credits to y_less    
	new rand = random(max-min)+min;    
	return rand;
}

stock GenerateRandomPlate()
{
	new randomPlate[10];
	format(randomPlate, sizeof(randomPlate), "%c%c%c-%d%d%d", RandomEx('A', 'Z'), RandomEx('A', 'Z'), RandomEx('A', 'Z'), random(10), random(10), random(10));
	return randomPlate;
}

stock IsVehicleOwnedByPlayer(vehicleid, playerid)
{
	if(Vehicles[vehicleid][OwnerID] == Player[playerid][AccountID])
	{
		return 1;
	} else return 0;
}

stock CanUseVehicle(vehicleid, playerid)
{
	if(Vehicles[vehicleid][OwnerID] == Player[playerid][AccountID])
	{
		return 1;
	} else if(Vehicles[vehicleid][Faction] == Player[playerid][Faction]) {
		return 1;
	} else if(Vehicles[vehicleid][AdminSpawned] == 1 && Player[playerid][AdminLevel] > 0) {
		return 1;
	} else {
		return 0;
	}
}