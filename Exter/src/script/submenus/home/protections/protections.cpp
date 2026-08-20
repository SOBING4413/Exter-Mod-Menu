#include "protections.h"

namespace ui::submenus
{
	bool g_passive_collision_guard{};

	void protectionsSubmenu::init(submenu& submenu)
	{
		submenu.add(toggleOption("Block Wanted Level", "Use Self > Never Wanted for active wanted suppression", "neverWanted"_TC->get(0).toggle));
		submenu.add(toggleOption("Hide Police Radar Blips", "Use Self > Never Wanted to hide police radar blips", "neverWanted"_TC->get(0).toggle));
		submenu.add(toggleOption("Passive Collision Guard", "Reserved protection preset for safer passive navigation", g_passive_collision_guard));
	}
}
