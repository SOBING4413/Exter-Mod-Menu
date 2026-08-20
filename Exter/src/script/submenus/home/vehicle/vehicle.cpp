#include "vehicle.h"

#include "rage/lists.h"

namespace ui::submenus
{
	void vehicleSubmenu::init(submenu& submenu)
	{
		submenu.add(toggleOption("vehicleGodMode"_TC));
		submenu.add(breakOption("Maintenance"));
		submenu.add(option("Repair Vehicle", "Fully repairs the current vehicle", []
		{
			const auto ped{PLAYER::PLAYER_PED_ID()};
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE))
				return;

			VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_IN(ped, FALSE));
		}));
		submenu.add(option("Clean Vehicle", "Removes dirt from the current vehicle", []
		{
			const auto ped{PLAYER::PLAYER_PED_ID()};
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE))
				return;

			VEHICLE::SET_VEHICLE_DIRT_LEVEL(PED::GET_VEHICLE_PED_IS_IN(ped, FALSE), 0.f);
		}));
		submenu.add(option("Max Engine Health", "Restores engine health to maximum", []
		{
			const auto ped{PLAYER::PLAYER_PED_ID()};
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE))
				return;

			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(PED::GET_VEHICLE_PED_IS_IN(ped, FALSE), 1000.f);
		}));
	}
}
