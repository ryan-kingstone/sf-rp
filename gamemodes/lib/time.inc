/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

#include <YSI\y_hooks>

hook OnGameModeInit()
{
	// Set world time to real time of server
	new hour, minute, second;

	gettime(hour, minute, second);
	SetWorldTime(hour);

	return 1;
}


stock timec(timestamp, compare = -1) {
	if (compare == -1) {
		compare = gettime();
	}
	new
	n,
	// on the following line, I have removed the need for the diff() function.
	// if you want to use the diff() function in pawn, replace the following with:
	// Float:d = diff(timestamp, compare),
	Float:d = diff(timestamp, compare),
	returnstr[32];

	if (d < 60) {
		format(returnstr, sizeof(returnstr), "< 1 minute");
		return returnstr;
	} else if (d < 3600) { // 3600 = 1 hour
		n = floatround(floatdiv(d, 60.0), floatround_floor);
		format(returnstr, sizeof(returnstr), "minute");
	} else if (d < 86400) { // 86400 = 1 day
		n = floatround(floatdiv(d, 3600.0), floatround_floor);
		format(returnstr, sizeof(returnstr), "hour");
	} else if (d < 2592000) { // 2592000 = 1 month
		n = floatround(floatdiv(d, 86400.0), floatround_floor);
		format(returnstr, sizeof(returnstr), "day");
	} else if (d < 31536000) { // 31536000 = 1 year
		n = floatround(floatdiv(d, 2592000.0), floatround_floor);
		format(returnstr, sizeof(returnstr), "month");
	} else {
		n = floatround(floatdiv(d, 31536000.0), floatround_floor);
		format(returnstr, sizeof(returnstr), "year");
	}
	if (n == 1) {
		format(returnstr, sizeof(returnstr), "1 %s", returnstr);
	} else {
		format(returnstr, sizeof(returnstr), "%d %ss", n, returnstr);
	}
	return returnstr;
}

stock GetDayOfMonth()
{
	new Year, Month, Day, string[5];
	getdate(Year, Month, Day);
	switch(Day) { 
		case 1: format(string, sizeof(string), "1st");
		case 2: format(string, sizeof(string), "2nd");
		case 3: format(string, sizeof(string), "3rd");
		case 4: format(string, sizeof(string), "4th");
		case 5: format(string, sizeof(string), "5th");
		case 6: format(string, sizeof(string), "6th");
		case 7: format(string, sizeof(string), "7th");
		case 8: format(string, sizeof(string), "8th");
		case 9: format(string, sizeof(string), "9th");
		case 10: format(string, sizeof(string), "10th");
		case 11: format(string, sizeof(string), "11th");
		case 12: format(string, sizeof(string), "12th");
		case 13: format(string, sizeof(string), "13th");
		case 14: format(string, sizeof(string), "14th");
		case 15: format(string, sizeof(string), "15th");
		case 16: format(string, sizeof(string), "16th");
		case 17: format(string, sizeof(string), "17th");
		case 18: format(string, sizeof(string), "18th");
		case 19: format(string, sizeof(string), "19th");
		case 20: format(string, sizeof(string), "20th");
		case 21: format(string, sizeof(string), "21st");
		case 22: format(string, sizeof(string), "22nd");
		case 23: format(string, sizeof(string), "23rd");
		case 24: format(string, sizeof(string), "24th");
		case 25: format(string, sizeof(string), "25th");
		case 26: format(string, sizeof(string), "26th");
		case 27: format(string, sizeof(string), "27th");
		case 28: format(string, sizeof(string), "28th");
		case 29: format(string, sizeof(string), "29th");
		case 30: format(string, sizeof(string), "30th");
		case 31: format(string, sizeof(string), "31st");
		default: format(string, sizeof(string), "ERR_TIME_INC");
	}
	return string;
}