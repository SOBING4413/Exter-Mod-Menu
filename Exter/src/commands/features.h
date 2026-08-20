#pragma once
#include "rage/classes.h"
#include "manager/manager.h"

namespace commands::features
{
	inline CPed* cPed{};
	inline CPedWeaponManager* cPedWeaponManager{};
	inline CWeaponInfo* cWeaponInfo{};
	inline CAmmoInfo* cAmmoInfo{};
	inline CVehicle* cVehicle{};
	inline CPlayerInfo* cPlayerInfo{};

	namespace self
	{
		inline bool disable_godmode = false;
		extern void god_mode(toggleCommand* command);
		extern void beast_jump(toggleCommand* command);
		extern void graceful_landing(toggleCommand* command);
		extern void never_wanted(toggleCommand* command);
		extern void no_ragdoll(toggleCommand* command);
		extern void invisible(toggleCommand* command);
		extern void super_run(toggleCommand* command);
	}

	namespace weapons
	{
		extern void infinite_ammo(toggleCommand* command);
		extern void infinite_clip(toggleCommand* command);
		extern void explosive_ammo(toggleCommand* command);
		extern void fire_ammo(toggleCommand* command);
		extern void explosive_melee(toggleCommand* command);
	}

	namespace vehicle
	{
		extern void vehicle_god_mode(toggleCommand* command);
	}

	extern void init();
	extern void uninit();
	extern void on_init();
	extern void on_tick();
}
