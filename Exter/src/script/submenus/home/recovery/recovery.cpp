#include "recovery.h"

#include "rage/lists.h"

namespace ui::submenus
{
	void recoverySubmenu::init(submenu& submenu)
	{
		submenu.add(option("Fast Wanted Reset", "Clears wanted level immediately", []
		{
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
		}));
		submenu.add(option("Reset Escape Timer", "Resets hidden wanted escape timing", []
		{
			PLAYER::RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(PLAYER::PLAYER_ID());
		}));
		submenu.add(option("Restore Wanted Cap", "Restores the default maximum wanted level", []
		{
			PLAYER::SET_MAX_WANTED_LEVEL(5);
			PLAYER::SET_POLICE_RADAR_BLIPS(TRUE);
		}));
	}
}
