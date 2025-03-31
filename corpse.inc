enum e_corpse
{
	corpID,
	corpBody,
	corpSkin,
	corpAnim,
	bool:corpExists,
	Float:corpX,
	Float:corpY,
	Float:corpZ,
	Float:corpRX,
	Float:corpRY,
	Float:corpRZ,
	corpInt,
	corpWorld,
	Text3D:corpLabel
}

new CorpseData[MAX_PLAYERS][e_corpse];

timer DeleteCorpse[10000](playerid)
{
	CorpseData[playerid][corpExists] = false;

	// Versi Object
	//DestroyDynamicObject(CorpseData[playerid][corpID]);
	// Versi Aktor
	DestroyActor(CorpseData[playerid][corpID]);
	DestroyDynamic3DTextLabel(CorpseData[playerid][corpLabel]);
	
	CorpseData[playerid][corpX] = CorpseData[playerid][corpY] = CorpseData[playerid][corpZ] = CorpseData[playerid][corpRX] = CorpseData[playerid][corpRY] = CorpseData[playerid][corpRZ] = 0.0;
	CorpseData[playerid][corpInt] = CorpseData[playerid][corpWorld] = 0;
	CorpseData[playerid][corpID] = -1;
	CorpseData[playerid][corpLabel] = Text3D: -1;
	return 1;
}

CreateCorpse(playerid, Float:posX, Float:posY, Float:posZ)
{
	GetPlayerPos(playerid, posX, posY, posZ);

	CorpseData[playerid][corpBody] = 3092;
	CorpseData[playerid][corpX] = posX;
	CorpseData[playerid][corpY] = posY;
	CorpseData[playerid][corpZ] = posZ;
	CorpseData[playerid][corpRX] = CorpseData[playerid][corpRY] = CorpseData[playerid][corpRZ] = 0.0;
	CorpseData[playerid][corpInt] = GetPlayerInterior(playerid);
	CorpseData[playerid][corpWorld] = GetPlayerVirtualWorld(playerid);
	CorpseData[playerid][corpAnim] = ApplyActorAnimation(playerid,"CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 0, 1);

	CorpseData[playerid][corpExists] = true;
	// Versi Object
	//CorpseData[playerid][corpID] = CreateDynamicObject(CorpseData[playerid][corpBody], CorpseData[playerid][corpX], CorpseData[playerid][corpY], CorpseData[playerid][corpZ], CorpseData[playerid][corpRX], CorpseData[playerid][corpRY], CorpseData[playerid][corpRZ], CorpseData[playerid][corpWorld], CorpseData[playerid][corpInt]);
	// Versi Actor
	CorpseData[playerid][corpID] = CreateActor(CorpseData[playerid][corpSkin], CorpseData[playerid][corpX], CorpseData[playerid][corpY], CorpseData[playerid][corpZ], CorpseData[playerid][corpRX]);
	new str[128];
	format(str, 100,""WHITE_E"ketik "YELLOW_E"'/corpse' "WHITE_E"untuk mengotopsi jenazah");
	CorpseData[playerid][corpLabel] = CreateDynamic3DTextLabel(str, COLOR_WHITE, CorpseData[playerid][corpX], CorpseData[playerid][corpY], CorpseData[playerid][corpZ], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, CorpseData[playerid][corpWorld], CorpseData[playerid][corpInt], -1, 10.0);

	defer DeleteCorpse[10000](playerid); // 10000 = 10 detik
	return 1;
}


/*

public OnPlayerDeath(playerid, killerid, reason)
{
	new Float:dX, Float:dY, Float:dZ;
	GetPlayerPos(playerid, dX, dY, dZ);

	CreateCorpse(playerid, dX, dY, dZ); // ini untuk membuat objek kalo pemain mati
	return 1;
}

*/
