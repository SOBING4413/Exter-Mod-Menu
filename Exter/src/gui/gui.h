#pragma once
#include "pch/pch.h"
#include "gui/interface.h"
#include "types.h"

namespace ui
{
	extern void draw(); //Calls all the draw functions for all elements
	inline tooltip g_tooltip{
		BRAND " ready. Press Insert or RB + Right", 1, 0.34f, {188, 231, 255, 235},
		eJustify::Center //Text, text size, text color, text justify
	};
	inline header g_header{
		BRAND, 0.105f, {9, 16, 31, 245}, //Title, size, color
		6, 0.92f, {214, 244, 255, 255}, eJustify::Center //Font, text size, text color, text justify
	};
	inline subtitle g_subtitle{
		"", 0.04f, 2.1f, {12, 19, 34, 232}, //Text, size, padding, color
		0, 0.4f, {255, 255, 255, 255}, eJustify::Left, //Font, text size, text color, text justiy
		0, 0.4f, {255, 255, 255, 255},
		eJustify::Right //Option font, option text size, option text color, option text justify
	};
	inline options g_options{
		0.035f, 2.1f, {8, 12, 24, 205}, {91, 209, 255, 245}, //Size, padding, color, selected color
		1, 0.34f, {226, 235, 247, 245}, {5, 12, 22, 255}, eJustify::Left,
		//Font, text size, text color, selected text color, text justify
		12.f, //Scroll speed
		1, 0.35f, {255, 255, 255, 255}, eJustify::Center,
		//Break font, break text size, break text color, break text justify
		{"commonmenu", "arrowright"}, {226, 235, 247, 245}, {5, 12, 22, 255}, {0.9f, 0.9f},
		//Arrow, arrow color, selected arrow color, arrow size
		{"commonmenu", "common_medal"}, {123, 92, 255, 245}, {91, 209, 255, 245},
		{1.3f, 1.3f} //Toggle, toggle color, selected toggle color, toggle size
	};
	inline footer g_footer{
		0.04f, {12, 19, 34, 232}, //Size, color
		{"commonmenu", "shop_arrows_upanddown"}, 1.f, {202, 229, 255, 245} //Sprite, sprite size, sprite color
	};
	inline description g_description{
		"", 0.033f, 0.015f, 2.f, {12, 19, 34, 232}, //Text, size, height, padding, color
		1, 0.30f, {255, 255, 255, 255}, eJustify::Left //Font, text size, text color, text justify
	};
	inline float g_width{0.285f}; //Width
	inline ImVec2 g_pos{
		0.14f, //X-Coord
		0.02f //Y-Coord
	};
	inline float g_base{}; //Holds the Y coord, constantly changing
}
