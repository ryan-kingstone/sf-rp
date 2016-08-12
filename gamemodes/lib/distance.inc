/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>, March 2016
 */

forward Float:GetDistanceBetweenPlayers(p1,p2);
public Float:GetDistanceBetweenPlayers(p1,p2)
{
    new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
    if(!IsPlayerConnected(p1) || !IsPlayerConnected(p2))
    {
        return -1.00;
    }
    GetPlayerPos(p1,x1,y1,z1);
    GetPlayerPos(p2,x2,y2,z2);
    return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock GetNearestVehicle(playerid, Float:Distance = 1000.0)
{
    Distance = floatabs(Distance);
    if(!Distance) Distance = 1000.0;
    new
        Float:pX,
        Float:pY,
        Float:pZ,
        Float:NearestPos = Distance,
        Float:NearestDist,
        NearestVeh = INVALID_VEHICLE_ID;

    GetPlayerPos(playerid, pX, pY, pZ);

    for(new i; i<MAX_VEHICLES; i++)
    {
        if(!IsVehicleStreamedIn(i, playerid))continue;
        NearestDist=GetVehicleDistanceFromPoint(i, pX, pY, pZ);
        if(NearestPos > NearestDist)
        {
            NearestPos = NearestDist;
            NearestVeh = i;
        }
    }
    return NearestVeh;
}
