/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

stock LogEvent(event[], message[], playerid[] = "")
{
	new query[256];
    mysql_format(mysql, query, sizeof(query), "INSERT INTO logs (LogName, LogString, LogPlayer) VALUES('%e', '%e', '%e')", event, message, playerid);
    mysql_tquery(mysql, query);
	return 1;
}