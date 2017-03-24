/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef VEHICLEMETHODS_H
#define VEHICLEMETHODS_H
#ifndef CLASSIC
#ifndef TBC

/***
 * Inherits all methods from: none
 */
namespace LuaVehicle
{
    /**
     * Returns true if the [Unit] passenger is on board
     *
     * @param [Unit] passenger
     * @return bool isOnBoard
     */
    int IsOnBoard(Eluna* /*E*/, lua_State* L, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(L, 2);
#ifndef TRINITY
        Eluna::Push(L, vehicle->HasOnBoard(passenger));
#else
        Eluna::Push(L, passenger->IsOnVehicle(vehicle->GetBase()));
#endif
        return 1;
    }

    /**
     * Returns the [Vehicle]'s owner
     *
     * @return [Unit] owner
     */
    int GetOwner(Eluna* /*E*/, lua_State* L, Vehicle* vehicle)
    {
#ifndef TRINITY
        Eluna::Push(L, vehicle->GetOwner());
#else
        Eluna::Push(L, vehicle->GetBase());
#endif
        return 1;
    }

    /**
     * Returns the [Vehicle]'s entry
     *
     * @return uint32 entry
     */
    int GetEntry(Eluna* /*E*/, lua_State* L, Vehicle* vehicle)
    {
#ifndef TRINITY
        Eluna::Push(L, vehicle->GetVehicleEntry()->m_ID);
#else
        Eluna::Push(L, vehicle->GetVehicleInfo()->m_ID);
#endif
        return 1;
    }

    /**
     * Returns the [Vehicle]'s passenger in the specified seat
     *
     * @param int8 seat
     * @return [Unit] passenger
     */
    int GetPassenger(Eluna* /*E*/, lua_State* L, Vehicle* vehicle)
    {
        int8 seatId = Eluna::CHECKVAL<int8>(L, 2);
        Eluna::Push(L, vehicle->GetPassenger(seatId));
        return 1;
    }

    /**
     * Adds [Unit] passenger to a specified seat in the [Vehicle]
     *
     * @param [Unit] passenger
     * @param int8 seat
     */
    int AddPassenger(Eluna* /*E*/, lua_State* L, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(L, 2);
        int8 seatId = Eluna::CHECKVAL<int8>(L, 3);
#ifndef TRINITY
        if (vehicle->CanBoard(passenger))
            vehicle->Board(passenger, seatId);
#else
        vehicle->AddPassenger(passenger, seatId);
#endif
        return 0;
    }

    /**
     * Removes [Unit] passenger from the [Vehicle]
     *
     * @param [Unit] passenger
     */
    int RemovePassenger(Eluna* /*E*/, lua_State* L, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(L, 2);
#ifndef TRINITY
        vehicle->UnBoard(passenger, false);
#else
        vehicle->RemovePassenger(passenger);
#endif
        return 0;
    }

	int RemoveAllGameObjects(Eluna* /*E*/, lua_State* L, Vehicle* vehicle)
	{
		vehicle->RemoveAllGameObjects(true);
		return 0;
	}

	int AttachPassenger(Eluna* /*E*/, lua_State* L, Vehicle* vehicle)
	{
		Player* player = Eluna::CHECKOBJ<Player>(L, 2, NULL);
		float radius = Eluna::CHECKVAL<float>(L, 3);
		float angle = Eluna::CHECKVAL<float>(L, 4);
		float pos_z = Eluna::CHECKVAL<float>(L, 5);
		float orientation = Eluna::CHECKVAL<float>(L, 6);
		uint32 spawnid = vehicle->GetBase()->ToCreature()->GetSpawnId();
		uint32 guidlow = player->GetGUID().GetCounter();
		if (spawnid && guidlow) {
			sObjectMgr->AddVehiclePassenger(spawnid, guidlow, radius, angle, pos_z, orientation, 1);
		}
		return 0;
	}

	int GetBodyGameObjectGUID(Eluna* /*E*/, lua_State* L, Vehicle* vehicle)
	{
		CreatureGameObjectsList const* gameobjects = sObjectMgr->GetCreatureGameObjectsList(vehicle->GetBase()->ToCreature()->GetSpawnId());
		if (!gameobjects) {
			return 0;
		}
		else {
			// Берём данные о ГОшках из хранимого контейнера.
			for (CreatureGameObjectsList::const_iterator itr = gameobjects->begin(); itr != gameobjects->end(); ++itr) {
				if (itr->gameobject_type == 1)
				{
					Eluna::Push(L, itr->gameobject_guid);
					return 1;
				}
			}
		}
		return 0;
	}

}

#endif // CLASSIC
#endif // TBC
#endif // VEHICLEMETHODS_H