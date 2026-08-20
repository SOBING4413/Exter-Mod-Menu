#include "weapons.h"

#include "rage/lists.h"

namespace ui::submenus
{
	void weaponsSubmenu::init(submenu& submenu)
	{
		submenu.add(breakOption("Weapon Modifiers"));
		submenu.add(toggleOption("infiniteAmmo"_TC));
		submenu.add(toggleOption("infiniteClip"_TC));
		submenu.add(toggleOption("explosiveAmmo"_TC));
		submenu.add(toggleOption("fireAmmo"_TC));
		submenu.add(toggleOption("explosiveMelee"_TC));
		submenu.add(breakOption("Loadout"));
		submenu.add(option("Give Core Loadout", "Gives a compact, reliable weapon set", []
		{
			const auto ped{PLAYER::PLAYER_PED_ID()};
			const std::array<const char*, 6> weapons{
				"WEAPON_PISTOL", "WEAPON_SMG", "WEAPON_CARBINERIFLE", "WEAPON_PUMPSHOTGUN", "WEAPON_SNIPERRIFLE", "WEAPON_GRENADELAUNCHER"
			};

			for (const auto weapon : weapons)
				WEAPON::GIVE_WEAPON_TO_PED(ped, MISC::GET_HASH_KEY(weapon), 9999, FALSE, FALSE);
		}));
		submenu.add(option("Remove All Weapons", "Clears every weapon from the player", []
		{
			WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), TRUE);
		}));
	}
}
