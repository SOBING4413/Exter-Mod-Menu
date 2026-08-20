#include "features.h"
#include "fiber/pool.h"
#include "hooking/hooking.h"
#include "rage/lists.h"
#include "renderer/renderer.h"

namespace commands::features
{
	namespace self
	{
		u32 m_last_god_mode_bits = 0;
		u32 god_mode_bits = 0;

		void god_mode(toggleCommand* command)
		{
			if (cPed == nullptr)
			{
				LOG(Warn, "Cped is nullptr")
				return;
			}
			if (command->get(0).toggle && !disable_godmode)
			{
				god_mode_bits |= 0x100;
				const u32 changed_bits = god_mode_bits ^ m_last_god_mode_bits;
				const u32 enabled_or_changed_bits = god_mode_bits | changed_bits;
				const u32 unchanged_bits = cPed->m_damage_bits & ~enabled_or_changed_bits;
				cPed->m_damage_bits = unchanged_bits | god_mode_bits;
				disable_godmode = true;
			}
			if (cPed != nullptr && !command->get(0).toggle && disable_godmode)
			{
				cPed->m_damage_bits = NULL;
				disable_godmode = false;
			}
		}

		void beast_jump(toggleCommand* command)
		{
			if (command->get(0).toggle)
				MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
		}

		void graceful_landing(toggleCommand* command)
		{
			if (command->get(0).toggle)
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), FALSE);
		}

		void never_wanted(toggleCommand* command)
		{
			if (!command->get(0).toggle)
				return;

			const auto player{PLAYER::PLAYER_ID()};
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
			PLAYER::SET_MAX_WANTED_LEVEL(0);
			PLAYER::SET_POLICE_RADAR_BLIPS(FALSE);
		}

		void no_ragdoll(toggleCommand* command)
		{
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), command->get(0).toggle ? FALSE : TRUE);
		}

		void invisible(toggleCommand* command)
		{
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), command->get(0).toggle ? FALSE : TRUE, FALSE);
		}

		void super_run(toggleCommand* command)
		{
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), command->get(0).toggle ? 1.49f : 1.0f);
		}
	}

	namespace weapons
	{
		void infinite_ammo(toggleCommand* command)
		{
			WEAPON::SET_PED_INFINITE_AMMO(PLAYER::PLAYER_PED_ID(), command->get(0).toggle, 0);
		}

		void infinite_clip(toggleCommand* command)
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), command->get(0).toggle);
		}

		void explosive_ammo(toggleCommand* command)
		{
			if (command->get(0).toggle)
				MISC::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
		}

		void fire_ammo(toggleCommand* command)
		{
			if (command->get(0).toggle)
				MISC::SET_FIRE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
		}

		void explosive_melee(toggleCommand* command)
		{
			if (command->get(0).toggle)
				MISC::SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER::PLAYER_ID());
		}
	}

	namespace vehicle
	{
		void vehicle_god_mode(toggleCommand* command)
		{
			const auto ped{PLAYER::PLAYER_PED_ID()};
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE))
				return;

			const auto veh{PED::GET_VEHICLE_PED_IS_IN(ped, FALSE)};
			ENTITY::SET_ENTITY_INVINCIBLE(veh, command->get(0).toggle);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, command->get(0).toggle ? 1000.f : VEHICLE::GET_VEHICLE_ENGINE_HEALTH(veh));
		}
	}

	const std::vector<std::string> g_textures = {
		"commonmenu"
	};

	void request_textures()
	{
		g_pool.add([]
		{
			for (const auto& texture : g_textures)
			{
				while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(texture.c_str()))
				{
					GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(texture.c_str(), TRUE);
					LOG(Registers, "Requesting in game textures: {}", texture.c_str())
					fiber::current()->sleep();
				}
			}
		});
	}

	void unload_textures()
	{
		g_pool.add([]
		{
			for (const auto& textures : g_textures)
			{
				if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(textures.c_str()))
				{
					GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(textures.c_str());
					LOG(Registers, "Unloading in game textures: {}", textures.c_str())
				}
				else
				{
					LOG(Info, "Unloading without removing any in game textures")
				}
			}
		});
	}

	void init()
	{
		g_manager.add(toggleCommand("godMode", "GodMode", self::god_mode));
		g_manager.add(toggleCommand("gracefulLanding", "Graceful Landing", self::graceful_landing));
		g_manager.add(toggleCommand("beastJump", "Beast Jump", "Enables a higher jump every frame", self::beast_jump));
		g_manager.add(toggleCommand("neverWanted", "Never Wanted", "Continuously clears wanted level and suppresses wanted stars", self::never_wanted));
		g_manager.add(toggleCommand("noRagdoll", "No Ragdoll", "Prevents the player from falling into ragdoll state", self::no_ragdoll));
		g_manager.add(toggleCommand("invisible", "Invisible Player", "Toggles player visibility", self::invisible));
		g_manager.add(toggleCommand("superRun", "Super Run", "Applies the maximum safe sprint multiplier", self::super_run));
		g_manager.add(toggleCommand("infiniteAmmo", "Infinite Ammo", "Keeps ammo from being consumed", weapons::infinite_ammo));
		g_manager.add(toggleCommand("infiniteClip", "Infinite Clip", "Keeps the current weapon clip full", weapons::infinite_clip));
		g_manager.add(toggleCommand("explosiveAmmo", "Explosive Ammo", "Applies explosive rounds this frame", weapons::explosive_ammo));
		g_manager.add(toggleCommand("fireAmmo", "Fire Ammo", "Applies fire rounds this frame", weapons::fire_ammo));
		g_manager.add(toggleCommand("explosiveMelee", "Explosive Melee", "Applies explosive melee hits this frame", weapons::explosive_melee));
		g_manager.add(toggleCommand("vehicleGodMode", "Vehicle God Mode", "Makes the current vehicle invincible", vehicle::vehicle_god_mode));
	}

	void uninit()
	{
		const auto ped{PLAYER::PLAYER_PED_ID()};
		ENTITY::SET_ENTITY_COLLISION(ped, TRUE, TRUE);
		ENTITY::RESET_ENTITY_ALPHA(ped);
		ENTITY::SET_ENTITY_VISIBLE(ped, TRUE, FALSE);
		ENTITY::SET_ENTITY_HAS_GRAVITY(ped, TRUE);
		PLAYER::SET_MAX_WANTED_LEVEL(5);
		PLAYER::SET_POLICE_RADAR_BLIPS(TRUE);
		const auto player{PLAYER::PLAYER_ID()};
		PLAYER::RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(player);
		unload_textures();
	}

	void on_init()
	{
		request_textures();
		//These need to be after init because the values aren't created yet
	}

	void on_tick()
	{
		cPed = util::classes::getPed();
		cPlayerInfo = util::classes::getPlayerInfo();

		if (!cPed)
		{
			cPedWeaponManager = nullptr;
			cWeaponInfo = nullptr;
			cAmmoInfo = nullptr;
			cVehicle = nullptr;
			return;
		}

		cPedWeaponManager = cPed->m_weapon_manager;
		cWeaponInfo = cPedWeaponManager ? cPedWeaponManager->m_weapon_info : nullptr;
		cAmmoInfo = cWeaponInfo ? cWeaponInfo->m_ammo_info : nullptr;
		cVehicle = cPed->m_vehicle;
	}
}
