#include "self.h"

#include "rage/lists.h"

namespace ui::submenus
{
	void selfSubmenu::init(submenu& submenu)
	{
		submenu.add(breakOption("Survivability"));
		submenu.add(toggleOption("godMode"_TC));
		submenu.add(toggleOption("neverWanted"_TC));
		submenu.add(toggleOption("noRagdoll"_TC));
		submenu.add(toggleOption("invisible"_TC));
		submenu.add(breakOption("Movement"));
		submenu.add(toggleOption("beastJump"_TC));
		submenu.add(toggleOption("gracefulLanding"_TC));
		submenu.add(toggleOption("superRun"_TC));
		submenu.add(breakOption("Quick Actions"));
		submenu.add(option("Heal Player", "Restores player health and armor", []
		{
			const auto ped{PLAYER::PLAYER_PED_ID()};
			ENTITY::SET_ENTITY_HEALTH(ped, ENTITY::GET_ENTITY_MAX_HEALTH(ped), 0, 0);
			PED::SET_PED_ARMOUR(ped, 100);
		}));
		submenu.add(option("Clear Wanted Level", "Immediately clears the current wanted level", []
		{
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
		}));
	}
}
