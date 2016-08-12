
# Administrative Commands #

# Level 1 administrators:
	/adminduty - alias: /aduty
		- Toggles the admin-on-duty status of the user.
	/adminchat - alias: /a
		[message]
		- Sends a message through the admin chat to all other administrators.
	/kick
		[username/id] [reason]
		- Kicks the specified user from the server with a message detailing the reason.
	/ban
		[username/id] [reason]
		- Bans the specified user from the server, leaving them with instructions on how to appeal the ban.
	/gotopos
		[x] [y] [z]
		- Teleports you to the coordinates specified.
	/gotoveh
		[vehicle id]
		- Teleports you to the specified vehicle id (world id, not mysql id).
	/gotobiz
		[business id]
	 	- Teleports you to the specified mysql id of the business.

# Level 2 administrators:
	/setskin
		[username/id] [skin id]
		- Sets the user's skin to the specified skin id.

# Level 3 administrators:
	/toggleooc - alias: /togooc
		- Toggles the public OOC status, allowing or disallowing people to write in it.
	/reloadveh
		- Reloads all vehicles.
	/reloadbiz
		- Reloads all businesses.
	/setparkingspot
		- Sets a parking spot for a vehicle.
		* Works for all vehicles, regardless of type, except admin spawned vehicles.
	/addfactionvehicle - alias: /afv
		[faction] [colour 0] [colour 1]
		- Adds a faction vehicle using the specified colours.
		* You must be in a vehicle to use this.
	/setfaction
		[username/id] [faction]
		- Sets the specified user's faction.

# Level 4 administrators:
	/vehicle - alias: /veh
		[vehicle model] [colour 0] [colour 1]
		- Spawns an admin-spawned vehicle with the specified colours.
	/giveweapon - alias: /gw
		[username/id] [weapon id] [ammo]
		- Gives the specified user x ammo for the weapon id specified.
	/fix
		- Fixes the user's vehicle.

# Level 5 administrators:
	/jetpack
		- Spawns a jetpack onto the user's back.