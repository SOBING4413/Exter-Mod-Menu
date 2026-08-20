#include "teleport.h"

#include "rage/lists.h"

namespace ui::submenus
{
	Vector3 g_saved_position{};

	void teleportSubmenu::init(submenu& submenu)
	{
		submenu.add(option("Save Current Position", "Stores the current player position", []
		{
			g_saved_position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
		}));
		submenu.add(option("Teleport To Saved Position", "Moves the player to the stored position", []
		{
			if (g_saved_position.empty())
				return;

			const auto ped{PLAYER::PLAYER_PED_ID()};
			ENTITY::SET_ENTITY_COORDS(ped, g_saved_position.x, g_saved_position.y, g_saved_position.z, FALSE, FALSE, FALSE, TRUE);
		}));
		submenu.add(option("Teleport Forward", "Moves the player forward in the facing direction", []
		{
			const auto ped{PLAYER::PLAYER_PED_ID()};
			const auto coords{ENTITY::GET_ENTITY_COORDS(ped, TRUE)};
			const auto forward{ENTITY::GET_ENTITY_FORWARD_VECTOR(ped)};
			ENTITY::SET_ENTITY_COORDS(ped, coords.x + forward.x * 8.f, coords.y + forward.y * 8.f, coords.z + forward.z * 8.f, FALSE, FALSE, FALSE, TRUE);
		}));
		submenu.add(option("Teleport Up", "Raises the player above the current position", []
		{
			const auto ped{PLAYER::PLAYER_PED_ID()};
			const auto coords{ENTITY::GET_ENTITY_COORDS(ped, TRUE)};
			ENTITY::SET_ENTITY_COORDS(ped, coords.x, coords.y, coords.z + 15.f, FALSE, FALSE, FALSE, TRUE);
		}));
	}
}
