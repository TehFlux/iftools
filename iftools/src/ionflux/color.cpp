/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * color.cpp                  Tools for handling colors.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <cstdlib>

#include "ionflux/color.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

Color8bpp to8bpp(const Color& color)
{
	Color8bpp newColor;
	newColor.name = color.name;
	newColor.red = static_cast<unsigned char>(round(color.red * 255.0));
	newColor.green = static_cast<unsigned char>(round(color.green * 255.0));
	newColor.blue = static_cast<unsigned char>(round(color.blue * 255.0));
	newColor.alpha = static_cast<unsigned char>(round(color.alpha * 255.0));
	return newColor;
}

std::string toHex(const Color& color)
{
	ostringstream buffer;
	buffer << "#" << right << setfill('0') << hex
		<< setw(2) << int(round(color.red * 255.0))
		<< setw(2) << int(round(color.green * 255.0))
		<< setw(2) << int(round(color.blue * 255.0));
	if (color.alpha != 1.0)
		buffer << setw(2) << int(round(color.alpha * 255.0));
	return buffer.str();
}

Color createColorFromHex(const std::string& hexColor)
{
	Color result;
	result.red = 0.0;
	result.green = 0.0;
	result.blue = 0.0;
	result.alpha = 1.0;
	if ((hexColor.size() < 1)
		|| (hexColor[0] != '#'))
		return result;
	if (hexColor.size() >= 3)
		result.red = static_cast<double>(
			strtol(hexColor.substr(1, 2).c_str(), 0, 16)) / 255.0;
	if (hexColor.size() >= 5)
		result.green = static_cast<double>(
			strtol(hexColor.substr(3, 2).c_str(), 0, 16)) / 255.0;
	if (hexColor.size() >= 7)
		result.blue = static_cast<double>(
			strtol(hexColor.substr(5, 2).c_str(), 0, 16)) / 255.0;
	if (hexColor.size() >= 9)
		result.alpha = static_cast<double>(
			strtol(hexColor.substr(7, 2).c_str(), 0, 16)) / 255.0;
	return result;
}

void addBasicColors(ColorMap& colorMap)
{
	// Add SVG colors.
	colorMap[COLOR_ALICEBLUE.name] = &COLOR_ALICEBLUE;
	colorMap[COLOR_ANTIQUEWHITE.name] = &COLOR_ANTIQUEWHITE;
	colorMap[COLOR_AQUA.name] = &COLOR_AQUA;
	colorMap[COLOR_AQUAMARINE.name] = &COLOR_AQUAMARINE;
	colorMap[COLOR_AZURE.name] = &COLOR_AZURE;
	colorMap[COLOR_BEIGE.name] = &COLOR_BEIGE;
	colorMap[COLOR_BISQUE.name] = &COLOR_BISQUE;
	colorMap[COLOR_BLACK.name] = &COLOR_BLACK;
	colorMap[COLOR_BLANCHEDALMOND.name] = &COLOR_BLANCHEDALMOND;
	colorMap[COLOR_BLUE.name] = &COLOR_BLUE;
	colorMap[COLOR_BLUEVIOLET.name] = &COLOR_BLUEVIOLET;
	colorMap[COLOR_BROWN.name] = &COLOR_BROWN;
	colorMap[COLOR_BURLYWOOD.name] = &COLOR_BURLYWOOD;
	colorMap[COLOR_CADETBLUE.name] = &COLOR_CADETBLUE;
	colorMap[COLOR_CHARTREUSE.name] = &COLOR_CHARTREUSE;
	colorMap[COLOR_CHOCOLATE.name] = &COLOR_CHOCOLATE;
	colorMap[COLOR_CORAL.name] = &COLOR_CORAL;
	colorMap[COLOR_CORNFLOWERBLUE.name] = &COLOR_CORNFLOWERBLUE;
	colorMap[COLOR_CORNSILK.name] = &COLOR_CORNSILK;
	colorMap[COLOR_CRIMSON.name] = &COLOR_CRIMSON;
	colorMap[COLOR_CYAN.name] = &COLOR_CYAN;
	colorMap[COLOR_DARKBLUE.name] = &COLOR_DARKBLUE;
	colorMap[COLOR_DARKCYAN.name] = &COLOR_DARKCYAN;
	colorMap[COLOR_DARKGOLDENROD.name] = &COLOR_DARKGOLDENROD;
	colorMap[COLOR_DARKGRAY.name] = &COLOR_DARKGRAY;
	colorMap[COLOR_DARKGREEN.name] = &COLOR_DARKGREEN;
	colorMap[COLOR_DARKGREY.name] = &COLOR_DARKGREY;
	colorMap[COLOR_DARKKHAKI.name] = &COLOR_DARKKHAKI;
	colorMap[COLOR_DARKMAGENTA.name] = &COLOR_DARKMAGENTA;
	colorMap[COLOR_DARKOLIVEGREEN.name] = &COLOR_DARKOLIVEGREEN;
	colorMap[COLOR_DARKORANGE.name] = &COLOR_DARKORANGE;
	colorMap[COLOR_DARKORCHID.name] = &COLOR_DARKORCHID;
	colorMap[COLOR_DARKRED.name] = &COLOR_DARKRED;
	colorMap[COLOR_DARKSALMON.name] = &COLOR_DARKSALMON;
	colorMap[COLOR_DARKSEAGREEN.name] = &COLOR_DARKSEAGREEN;
	colorMap[COLOR_DARKSLATEBLUE.name] = &COLOR_DARKSLATEBLUE;
	colorMap[COLOR_DARKSLATEGRAY.name] = &COLOR_DARKSLATEGRAY;
	colorMap[COLOR_DARKSLATEGREY.name] = &COLOR_DARKSLATEGREY;
	colorMap[COLOR_DARKTURQUOISE.name] = &COLOR_DARKTURQUOISE;
	colorMap[COLOR_DARKVIOLET.name] = &COLOR_DARKVIOLET;
	colorMap[COLOR_DEEPPINK.name] = &COLOR_DEEPPINK;
	colorMap[COLOR_DEEPSKYBLUE.name] = &COLOR_DEEPSKYBLUE;
	colorMap[COLOR_DIMGRAY.name] = &COLOR_DIMGRAY;
	colorMap[COLOR_DIMGREY.name] = &COLOR_DIMGREY;
	colorMap[COLOR_DODGERBLUE.name] = &COLOR_DODGERBLUE;
	colorMap[COLOR_FIREBRICK.name] = &COLOR_FIREBRICK;
	colorMap[COLOR_FLORALWHITE.name] = &COLOR_FLORALWHITE;
	colorMap[COLOR_FORESTGREEN.name] = &COLOR_FORESTGREEN;
	colorMap[COLOR_FUCHSIA.name] = &COLOR_FUCHSIA;
	colorMap[COLOR_GAINSBORO.name] = &COLOR_GAINSBORO;
	colorMap[COLOR_GHOSTWHITE.name] = &COLOR_GHOSTWHITE;
	colorMap[COLOR_GOLD.name] = &COLOR_GOLD;
	colorMap[COLOR_GOLDENROD.name] = &COLOR_GOLDENROD;
	colorMap[COLOR_GRAY.name] = &COLOR_GRAY;
	colorMap[COLOR_GREY.name] = &COLOR_GREY;
	colorMap[COLOR_GREEN.name] = &COLOR_GREEN;
	colorMap[COLOR_GREENYELLOW.name] = &COLOR_GREENYELLOW;
	colorMap[COLOR_HONEYDEW.name] = &COLOR_HONEYDEW;
	colorMap[COLOR_HOTPINK.name] = &COLOR_HOTPINK;
	colorMap[COLOR_INDIANRED.name] = &COLOR_INDIANRED;
	colorMap[COLOR_INDIGO.name] = &COLOR_INDIGO;
	colorMap[COLOR_IVORY.name] = &COLOR_IVORY;
	colorMap[COLOR_KHAKI.name] = &COLOR_KHAKI;
	colorMap[COLOR_LAVENDER.name] = &COLOR_LAVENDER;
	colorMap[COLOR_LAVENDERBLUSH.name] = &COLOR_LAVENDERBLUSH;
	colorMap[COLOR_LAWNGREEN.name] = &COLOR_LAWNGREEN;
	colorMap[COLOR_LEMONCHIFFON.name] = &COLOR_LEMONCHIFFON;
	colorMap[COLOR_LIGHTBLUE.name] = &COLOR_LIGHTBLUE;
	colorMap[COLOR_LIGHTCORAL.name] = &COLOR_LIGHTCORAL;
	colorMap[COLOR_LIGHTCYAN.name] = &COLOR_LIGHTCYAN;
	colorMap[COLOR_LIGHTGOLDENRODYELLOW.name] = &COLOR_LIGHTGOLDENRODYELLOW;
	colorMap[COLOR_LIGHTGRAY.name] = &COLOR_LIGHTGRAY;
	colorMap[COLOR_LIGHTGREEN.name] = &COLOR_LIGHTGREEN;
	colorMap[COLOR_LIGHTGREY.name] = &COLOR_LIGHTGREY;
	colorMap[COLOR_LIGHTPINK.name] = &COLOR_LIGHTPINK;
	colorMap[COLOR_LIGHTSALMON.name] = &COLOR_LIGHTSALMON;
	colorMap[COLOR_LIGHTSEAGREEN.name] = &COLOR_LIGHTSEAGREEN;
	colorMap[COLOR_LIGHTSKYBLUE.name] = &COLOR_LIGHTSKYBLUE;
	colorMap[COLOR_LIGHTSLATEGRAY.name] = &COLOR_LIGHTSLATEGRAY;
	colorMap[COLOR_LIGHTSLATEGREY.name] = &COLOR_LIGHTSLATEGREY;
	colorMap[COLOR_LIGHTSTEELBLUE.name] = &COLOR_LIGHTSTEELBLUE;
	colorMap[COLOR_LIGHTYELLOW.name] = &COLOR_LIGHTYELLOW;
	colorMap[COLOR_LIME.name] = &COLOR_LIME;
	colorMap[COLOR_LIMEGREEN.name] = &COLOR_LIMEGREEN;
	colorMap[COLOR_LINEN.name] = &COLOR_LINEN;
	colorMap[COLOR_MAGENTA.name] = &COLOR_MAGENTA;
	colorMap[COLOR_MAROON.name] = &COLOR_MAROON;
	colorMap[COLOR_MEDIUMAQUAMARINE.name] = &COLOR_MEDIUMAQUAMARINE;
	colorMap[COLOR_MEDIUMBLUE.name] = &COLOR_MEDIUMBLUE;
	colorMap[COLOR_MEDIUMORCHID.name] = &COLOR_MEDIUMORCHID;
	colorMap[COLOR_MEDIUMPURPLE.name] = &COLOR_MEDIUMPURPLE;
	colorMap[COLOR_MEDIUMSEAGREEN.name] = &COLOR_MEDIUMSEAGREEN;
	colorMap[COLOR_MEDIUMSLATEBLUE.name] = &COLOR_MEDIUMSLATEBLUE;
	colorMap[COLOR_MEDIUMSPRINGGREEN.name] = &COLOR_MEDIUMSPRINGGREEN;
	colorMap[COLOR_MEDIUMTURQUOISE.name] = &COLOR_MEDIUMTURQUOISE;
	colorMap[COLOR_MEDIUMVIOLETRED.name] = &COLOR_MEDIUMVIOLETRED;
	colorMap[COLOR_MIDNIGHTBLUE.name] = &COLOR_MIDNIGHTBLUE;
	colorMap[COLOR_MINTCREAM.name] = &COLOR_MINTCREAM;
	colorMap[COLOR_MISTYROSE.name] = &COLOR_MISTYROSE;
	colorMap[COLOR_MOCCASIN.name] = &COLOR_MOCCASIN;
	colorMap[COLOR_NAVAJOWHITE.name] = &COLOR_NAVAJOWHITE;
	colorMap[COLOR_NAVY.name] = &COLOR_NAVY;
	colorMap[COLOR_OLDLACE.name] = &COLOR_OLDLACE;
	colorMap[COLOR_OLIVE.name] = &COLOR_OLIVE;
	colorMap[COLOR_OLIVEDRAB.name] = &COLOR_OLIVEDRAB;
	colorMap[COLOR_ORANGE.name] = &COLOR_ORANGE;
	colorMap[COLOR_ORANGERED.name] = &COLOR_ORANGERED;
	colorMap[COLOR_ORCHID.name] = &COLOR_ORCHID;
	colorMap[COLOR_PALEGOLDENROD.name] = &COLOR_PALEGOLDENROD;
	colorMap[COLOR_PALEGREEN.name] = &COLOR_PALEGREEN;
	colorMap[COLOR_PALETURQUOISE.name] = &COLOR_PALETURQUOISE;
	colorMap[COLOR_PALEVIOLETRED.name] = &COLOR_PALEVIOLETRED;
	colorMap[COLOR_PAPAYAWHIP.name] = &COLOR_PAPAYAWHIP;
	colorMap[COLOR_PEACHPUFF.name] = &COLOR_PEACHPUFF;
	colorMap[COLOR_PERU.name] = &COLOR_PERU;
	colorMap[COLOR_PINK.name] = &COLOR_PINK;
	colorMap[COLOR_PLUM.name] = &COLOR_PLUM;
	colorMap[COLOR_POWDERBLUE.name] = &COLOR_POWDERBLUE;
	colorMap[COLOR_PURPLE.name] = &COLOR_PURPLE;
	colorMap[COLOR_RED.name] = &COLOR_RED;
	colorMap[COLOR_ROSYBROWN.name] = &COLOR_ROSYBROWN;
	colorMap[COLOR_ROYALBLUE.name] = &COLOR_ROYALBLUE;
	colorMap[COLOR_SADDLEBROWN.name] = &COLOR_SADDLEBROWN;
	colorMap[COLOR_SALMON.name] = &COLOR_SALMON;
	colorMap[COLOR_SANDYBROWN.name] = &COLOR_SANDYBROWN;
	colorMap[COLOR_SEAGREEN.name] = &COLOR_SEAGREEN;
	colorMap[COLOR_SEASHELL.name] = &COLOR_SEASHELL;
	colorMap[COLOR_SIENNA.name] = &COLOR_SIENNA;
	colorMap[COLOR_SILVER.name] = &COLOR_SILVER;
	colorMap[COLOR_SKYBLUE.name] = &COLOR_SKYBLUE;
	colorMap[COLOR_SLATEBLUE.name] = &COLOR_SLATEBLUE;
	colorMap[COLOR_SLATEGRAY.name] = &COLOR_SLATEGRAY;
	colorMap[COLOR_SLATEGREY.name] = &COLOR_SLATEGREY;
	colorMap[COLOR_SNOW.name] = &COLOR_SNOW;
	colorMap[COLOR_SPRINGGREEN.name] = &COLOR_SPRINGGREEN;
	colorMap[COLOR_STEELBLUE.name] = &COLOR_STEELBLUE;
	colorMap[COLOR_TAN.name] = &COLOR_TAN;
	colorMap[COLOR_TEAL.name] = &COLOR_TEAL;
	colorMap[COLOR_THISTLE.name] = &COLOR_THISTLE;
	colorMap[COLOR_TOMATO.name] = &COLOR_TOMATO;
	colorMap[COLOR_TURQUOISE.name] = &COLOR_TURQUOISE;
	colorMap[COLOR_VIOLET.name] = &COLOR_VIOLET;
	colorMap[COLOR_WHEAT.name] = &COLOR_WHEAT;
	colorMap[COLOR_WHITE.name] = &COLOR_WHITE;
	colorMap[COLOR_WHITESMOKE.name] = &COLOR_WHITESMOKE;
	colorMap[COLOR_YELLOW.name] = &COLOR_YELLOW;
	colorMap[COLOR_YELLOWGREEN.name] = &COLOR_YELLOWGREEN;
	// Add Ionflux Tools colors.
	colorMap[COLOR_NONE.name] = &COLOR_NONE;
	colorMap[COLOR_GREY_10.name] = &COLOR_GREY_10;
	colorMap[COLOR_GREY_20.name] = &COLOR_GREY_20;
	colorMap[COLOR_GREY_30.name] = &COLOR_GREY_30;
	colorMap[COLOR_GREY_40.name] = &COLOR_GREY_40;
	colorMap[COLOR_GREY_50.name] = &COLOR_GREY_50;
	colorMap[COLOR_GREY_60.name] = &COLOR_GREY_60;
	colorMap[COLOR_GREY_70.name] = &COLOR_GREY_70;
	colorMap[COLOR_GREY_80.name] = &COLOR_GREY_80;
	colorMap[COLOR_GREY_90.name] = &COLOR_GREY_90;
}

const Color* getByName(const std::string& colorName, ColorMap& colorMap)
{
	ColorMap::const_iterator i = colorMap.find(colorName);
	if (i != colorMap.end())
		return (*i).second;
	return 0;
}

}

}

/** \file color.cpp
 * \brief Tools for handling colors.
 */
