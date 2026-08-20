#include "miscellaneous.h"

#include "rage/lists.h"

namespace ui::submenus
{
	bool g_quiet_hud_helpers{};

	void miscellaneousSubmenu::init(submenu& submenu)
	{
		submenu.add(toggleOption("Quiet HUD Helpers", "Keeps helper toggles organized without changing core gameplay", g_quiet_hud_helpers));
		submenu.add(option("Disable Phone This Frame", "Blocks the phone control for the current frame", []
		{
			PAD::DISABLE_CONTROL_ACTION(0, 27, TRUE);
		}));
		submenu.add(option("Clear Area Effects", "Stops active screen effects", []
		{
			GRAPHICS::ANIMPOSTFX_STOP_ALL();
		}));
	}
}
