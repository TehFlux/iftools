#ifndef IONFLUX_TOOLS_COLOR
#define IONFLUX_TOOLS_COLOR
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * color.hpp                    Tools for handling colors.
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

#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <math.h>

namespace Ionflux
{

namespace Tools
{

/** \addtogroup general General tools
 *
 * General tools and utility classes and functions.
 *
 * @{
 */

/// Color.
struct Color
{
	/// Name.
	const char* name;
	/// Value: red.
	double red;
	/// Value: green.
	double green;
	/// Value: blue.
	double blue;
	/// Value: alpha.
	double alpha;
};

/// Color (8 bits per pixel, RGBA).
struct Color8bpp
{
	/// Name.
	const char* name;
	/// Value: red.
	unsigned char red;
	/// Value: green.
	unsigned char green;
	/// Value: blue.
	unsigned char blue;
	/// Value: alpha.
	unsigned char alpha;
};

/// Maps for color lookup by name.
typedef std::map<const std::string, const Color*> ColorMap;

/** Basic colors as defined by the SVG 1.1 specification.
 * see http://www.w3.org/TR/SVG11/types.html#ColorKeywords
 */
const Color COLOR_ALICEBLUE = { "aliceblue",
	0.941176, 0.972549, 1.000000, 1.000000 };
const Color COLOR_ANTIQUEWHITE = { "antiquewhite",
	0.980392, 0.921569, 0.843137, 1.000000 };
const Color COLOR_AQUA = { "aqua",
	0.000000, 1.000000, 1.000000, 1.000000 };
const Color COLOR_AQUAMARINE = { "aquamarine",
	0.498039, 1.000000, 0.831373, 1.000000 };
const Color COLOR_AZURE = { "azure",
	0.941176, 1.000000, 1.000000, 1.000000 };
const Color COLOR_BEIGE = { "beige",
	0.960784, 0.960784, 0.862745, 1.000000 };
const Color COLOR_BISQUE = { "bisque",
	1.000000, 0.894118, 0.768627, 1.000000 };
const Color COLOR_BLACK = { "black",
	0.000000, 0.000000, 0.000000, 1.000000 };
const Color COLOR_BLANCHEDALMOND = { "blanchedalmond",
	1.000000, 0.921569, 0.803922, 1.000000 };
const Color COLOR_BLUE = { "blue",
	0.000000, 0.000000, 1.000000, 1.000000 };
const Color COLOR_BLUEVIOLET = { "blueviolet",
	0.541176, 0.168627, 0.886275, 1.000000 };
const Color COLOR_BROWN = { "brown",
	0.647059, 0.164706, 0.164706, 1.000000 };
const Color COLOR_BURLYWOOD = { "burlywood",
	0.870588, 0.721569, 0.529412, 1.000000 };
const Color COLOR_CADETBLUE = { "cadetblue",
	0.372549, 0.619608, 0.627451, 1.000000 };
const Color COLOR_CHARTREUSE = { "chartreuse",
	0.498039, 1.000000, 0.000000, 1.000000 };
const Color COLOR_CHOCOLATE = { "chocolate",
	0.823529, 0.411765, 0.117647, 1.000000 };
const Color COLOR_CORAL = { "coral",
	1.000000, 0.498039, 0.313725, 1.000000 };
const Color COLOR_CORNFLOWERBLUE = { "cornflowerblue",
	0.392157, 0.584314, 0.929412, 1.000000 };
const Color COLOR_CORNSILK = { "cornsilk",
	1.000000, 0.972549, 0.862745, 1.000000 };
const Color COLOR_CRIMSON = { "crimson",
	0.862745, 0.078431, 0.235294, 1.000000 };
const Color COLOR_CYAN = { "cyan",
	0.000000, 1.000000, 1.000000, 1.000000 };
const Color COLOR_DARKBLUE = { "darkblue",
	0.000000, 0.000000, 0.545098, 1.000000 };
const Color COLOR_DARKCYAN = { "darkcyan",
	0.000000, 0.545098, 0.545098, 1.000000 };
const Color COLOR_DARKGOLDENROD = { "darkgoldenrod",
	0.721569, 0.525490, 0.043137, 1.000000 };
const Color COLOR_DARKGRAY = { "darkgray",
	0.662745, 0.662745, 0.662745, 1.000000 };
const Color COLOR_DARKGREEN = { "darkgreen",
	0.000000, 0.392157, 0.000000, 1.000000 };
const Color COLOR_DARKGREY = { "darkgrey",
	0.662745, 0.662745, 0.662745, 1.000000 };
const Color COLOR_DARKKHAKI = { "darkkhaki",
	0.741176, 0.717647, 0.419608, 1.000000 };
const Color COLOR_DARKMAGENTA = { "darkmagenta",
	0.545098, 0.000000, 0.545098, 1.000000 };
const Color COLOR_DARKOLIVEGREEN = { "darkolivegreen",
	0.333333, 0.419608, 0.184314, 1.000000 };
const Color COLOR_DARKORANGE = { "darkorange",
	1.000000, 0.549020, 0.000000, 1.000000 };
const Color COLOR_DARKORCHID = { "darkorchid",
	0.600000, 0.196078, 0.800000, 1.000000 };
const Color COLOR_DARKRED = { "darkred",
	0.545098, 0.000000, 0.000000, 1.000000 };
const Color COLOR_DARKSALMON = { "darksalmon",
	0.913725, 0.588235, 0.478431, 1.000000 };
const Color COLOR_DARKSEAGREEN = { "darkseagreen",
	0.560784, 0.737255, 0.560784, 1.000000 };
const Color COLOR_DARKSLATEBLUE = { "darkslateblue",
	0.282353, 0.239216, 0.545098, 1.000000 };
const Color COLOR_DARKSLATEGRAY = { "darkslategray",
	0.184314, 0.309804, 0.309804, 1.000000 };
const Color COLOR_DARKSLATEGREY = { "darkslategrey",
	0.184314, 0.309804, 0.309804, 1.000000 };
const Color COLOR_DARKTURQUOISE = { "darkturquoise",
	0.000000, 0.807843, 0.819608, 1.000000 };
const Color COLOR_DARKVIOLET = { "darkviolet",
	0.580392, 0.000000, 0.827451, 1.000000 };
const Color COLOR_DEEPPINK = { "deeppink",
	1.000000, 0.078431, 0.576471, 1.000000 };
const Color COLOR_DEEPSKYBLUE = { "deepskyblue",
	0.000000, 0.749020, 1.000000, 1.000000 };
const Color COLOR_DIMGRAY = { "dimgray",
	0.411765, 0.411765, 0.411765, 1.000000 };
const Color COLOR_DIMGREY = { "dimgrey",
	0.411765, 0.411765, 0.411765, 1.000000 };
const Color COLOR_DODGERBLUE = { "dodgerblue",
	0.117647, 0.564706, 1.000000, 1.000000 };
const Color COLOR_FIREBRICK = { "firebrick",
	0.698039, 0.133333, 0.133333, 1.000000 };
const Color COLOR_FLORALWHITE = { "floralwhite",
	1.000000, 0.980392, 0.941176, 1.000000 };
const Color COLOR_FORESTGREEN = { "forestgreen",
	0.133333, 0.545098, 0.133333, 1.000000 };
const Color COLOR_FUCHSIA = { "fuchsia",
	1.000000, 0.000000, 1.000000, 1.000000 };
const Color COLOR_GAINSBORO = { "gainsboro",
	0.862745, 0.862745, 0.862745, 1.000000 };
const Color COLOR_GHOSTWHITE = { "ghostwhite",
	0.972549, 0.972549, 1.000000, 1.000000 };
const Color COLOR_GOLD = { "gold",
	1.000000, 0.843137, 0.000000, 1.000000 };
const Color COLOR_GOLDENROD = { "goldenrod",
	0.854902, 0.647059, 0.125490, 1.000000 };
const Color COLOR_GRAY = { "gray",
	0.501961, 0.501961, 0.501961, 1.000000 };
const Color COLOR_GREY = { "grey",
	0.501961, 0.501961, 0.501961, 1.000000 };
const Color COLOR_GREEN = { "green",
	0.000000, 0.501961, 0.000000, 1.000000 };
const Color COLOR_GREENYELLOW = { "greenyellow",
	0.678431, 1.000000, 0.184314, 1.000000 };
const Color COLOR_HONEYDEW = { "honeydew",
	0.941176, 1.000000, 0.941176, 1.000000 };
const Color COLOR_HOTPINK = { "hotpink",
	1.000000, 0.411765, 0.705882, 1.000000 };
const Color COLOR_INDIANRED = { "indianred",
	0.803922, 0.360784, 0.360784, 1.000000 };
const Color COLOR_INDIGO = { "indigo",
	0.294118, 0.000000, 0.509804, 1.000000 };
const Color COLOR_IVORY = { "ivory",
	1.000000, 1.000000, 0.941176, 1.000000 };
const Color COLOR_KHAKI = { "khaki",
	0.941176, 0.901961, 0.549020, 1.000000 };
const Color COLOR_LAVENDER = { "lavender",
	0.901961, 0.901961, 0.980392, 1.000000 };
const Color COLOR_LAVENDERBLUSH = { "lavenderblush",
	1.000000, 0.941176, 0.960784, 1.000000 };
const Color COLOR_LAWNGREEN = { "lawngreen",
	0.486275, 0.988235, 0.000000, 1.000000 };
const Color COLOR_LEMONCHIFFON = { "lemonchiffon",
	1.000000, 0.980392, 0.803922, 1.000000 };
const Color COLOR_LIGHTBLUE = { "lightblue",
	0.678431, 0.847059, 0.901961, 1.000000 };
const Color COLOR_LIGHTCORAL = { "lightcoral",
	0.941176, 0.501961, 0.501961, 1.000000 };
const Color COLOR_LIGHTCYAN = { "lightcyan",
	0.878431, 1.000000, 1.000000, 1.000000 };
const Color COLOR_LIGHTGOLDENRODYELLOW = { "lightgoldenrodyellow",
	0.980392, 0.980392, 0.823529, 1.000000 };
const Color COLOR_LIGHTGRAY = { "lightgray",
	0.827451, 0.827451, 0.827451, 1.000000 };
const Color COLOR_LIGHTGREEN = { "lightgreen",
	0.564706, 0.933333, 0.564706, 1.000000 };
const Color COLOR_LIGHTGREY = { "lightgrey",
	0.827451, 0.827451, 0.827451, 1.000000 };
const Color COLOR_LIGHTPINK = { "lightpink",
	1.000000, 0.713725, 0.756863, 1.000000 };
const Color COLOR_LIGHTSALMON = { "lightsalmon",
	1.000000, 0.627451, 0.478431, 1.000000 };
const Color COLOR_LIGHTSEAGREEN = { "lightseagreen",
	0.125490, 0.698039, 0.666667, 1.000000 };
const Color COLOR_LIGHTSKYBLUE = { "lightskyblue",
	0.529412, 0.807843, 0.980392, 1.000000 };
const Color COLOR_LIGHTSLATEGRAY = { "lightslategray",
	0.466667, 0.533333, 0.600000, 1.000000 };
const Color COLOR_LIGHTSLATEGREY = { "lightslategrey",
	0.466667, 0.533333, 0.600000, 1.000000 };
const Color COLOR_LIGHTSTEELBLUE = { "lightsteelblue",
	0.690196, 0.768627, 0.870588, 1.000000 };
const Color COLOR_LIGHTYELLOW = { "lightyellow",
	1.000000, 1.000000, 0.878431, 1.000000 };
const Color COLOR_LIME = { "lime",
	0.000000, 1.000000, 0.000000, 1.000000 };
const Color COLOR_LIMEGREEN = { "limegreen",
	0.196078, 0.803922, 0.196078, 1.000000 };
const Color COLOR_LINEN = { "linen",
	0.980392, 0.941176, 0.901961, 1.000000 };
const Color COLOR_MAGENTA = { "magenta",
	1.000000, 0.000000, 1.000000, 1.000000 };
const Color COLOR_MAROON = { "maroon",
	0.501961, 0.000000, 0.000000, 1.000000 };
const Color COLOR_MEDIUMAQUAMARINE = { "mediumaquamarine",
	0.400000, 0.803922, 0.666667, 1.000000 };
const Color COLOR_MEDIUMBLUE = { "mediumblue",
	0.000000, 0.000000, 0.803922, 1.000000 };
const Color COLOR_MEDIUMORCHID = { "mediumorchid",
	0.729412, 0.333333, 0.827451, 1.000000 };
const Color COLOR_MEDIUMPURPLE = { "mediumpurple",
	0.576471, 0.439216, 0.858824, 1.000000 };
const Color COLOR_MEDIUMSEAGREEN = { "mediumseagreen",
	0.235294, 0.701961, 0.443137, 1.000000 };
const Color COLOR_MEDIUMSLATEBLUE = { "mediumslateblue",
	0.482353, 0.407843, 0.933333, 1.000000 };
const Color COLOR_MEDIUMSPRINGGREEN = { "mediumspringgreen",
	0.000000, 0.980392, 0.603922, 1.000000 };
const Color COLOR_MEDIUMTURQUOISE = { "mediumturquoise",
	0.282353, 0.819608, 0.800000, 1.000000 };
const Color COLOR_MEDIUMVIOLETRED = { "mediumvioletred",
	0.780392, 0.082353, 0.521569, 1.000000 };
const Color COLOR_MIDNIGHTBLUE = { "midnightblue",
	0.098039, 0.098039, 0.439216, 1.000000 };
const Color COLOR_MINTCREAM = { "mintcream",
	0.960784, 1.000000, 0.980392, 1.000000 };
const Color COLOR_MISTYROSE = { "mistyrose",
	1.000000, 0.894118, 0.882353, 1.000000 };
const Color COLOR_MOCCASIN = { "moccasin",
	1.000000, 0.894118, 0.709804, 1.000000 };
const Color COLOR_NAVAJOWHITE = { "navajowhite",
	1.000000, 0.870588, 0.678431, 1.000000 };
const Color COLOR_NAVY = { "navy",
	0.000000, 0.000000, 0.501961, 1.000000 };
const Color COLOR_OLDLACE = { "oldlace",
	0.992157, 0.960784, 0.901961, 1.000000 };
const Color COLOR_OLIVE = { "olive",
	0.501961, 0.501961, 0.000000, 1.000000 };
const Color COLOR_OLIVEDRAB = { "olivedrab",
	0.419608, 0.556863, 0.137255, 1.000000 };
const Color COLOR_ORANGE = { "orange",
	1.000000, 0.647059, 0.000000, 1.000000 };
const Color COLOR_ORANGERED = { "orangered",
	1.000000, 0.270588, 0.000000, 1.000000 };
const Color COLOR_ORCHID = { "orchid",
	0.854902, 0.439216, 0.839216, 1.000000 };
const Color COLOR_PALEGOLDENROD = { "palegoldenrod",
	0.933333, 0.909804, 0.666667, 1.000000 };
const Color COLOR_PALEGREEN = { "palegreen",
	0.596078, 0.984314, 0.596078, 1.000000 };
const Color COLOR_PALETURQUOISE = { "paleturquoise",
	0.686275, 0.933333, 0.933333, 1.000000 };
const Color COLOR_PALEVIOLETRED = { "palevioletred",
	0.858824, 0.439216, 0.576471, 1.000000 };
const Color COLOR_PAPAYAWHIP = { "papayawhip",
	1.000000, 0.937255, 0.835294, 1.000000 };
const Color COLOR_PEACHPUFF = { "peachpuff",
	1.000000, 0.854902, 0.725490, 1.000000 };
const Color COLOR_PERU = { "peru",
	0.803922, 0.521569, 0.247059, 1.000000 };
const Color COLOR_PINK = { "pink",
	1.000000, 0.752941, 0.796078, 1.000000 };
const Color COLOR_PLUM = { "plum",
	0.866667, 0.627451, 0.866667, 1.000000 };
const Color COLOR_POWDERBLUE = { "powderblue",
	0.690196, 0.878431, 0.901961, 1.000000 };
const Color COLOR_PURPLE = { "purple",
	0.501961, 0.000000, 0.501961, 1.000000 };
const Color COLOR_RED = { "red",
	1.000000, 0.000000, 0.000000, 1.000000 };
const Color COLOR_ROSYBROWN = { "rosybrown",
	0.737255, 0.560784, 0.560784, 1.000000 };
const Color COLOR_ROYALBLUE = { "royalblue",
	0.254902, 0.411765, 0.882353, 1.000000 };
const Color COLOR_SADDLEBROWN = { "saddlebrown",
	0.545098, 0.270588, 0.074510, 1.000000 };
const Color COLOR_SALMON = { "salmon",
	0.980392, 0.501961, 0.447059, 1.000000 };
const Color COLOR_SANDYBROWN = { "sandybrown",
	0.956863, 0.643137, 0.376471, 1.000000 };
const Color COLOR_SEAGREEN = { "seagreen",
	0.180392, 0.545098, 0.341176, 1.000000 };
const Color COLOR_SEASHELL = { "seashell",
	1.000000, 0.960784, 0.933333, 1.000000 };
const Color COLOR_SIENNA = { "sienna",
	0.627451, 0.321569, 0.176471, 1.000000 };
const Color COLOR_SILVER = { "silver",
	0.752941, 0.752941, 0.752941, 1.000000 };
const Color COLOR_SKYBLUE = { "skyblue",
	0.529412, 0.807843, 0.921569, 1.000000 };
const Color COLOR_SLATEBLUE = { "slateblue",
	0.415686, 0.352941, 0.803922, 1.000000 };
const Color COLOR_SLATEGRAY = { "slategray",
	0.439216, 0.501961, 0.564706, 1.000000 };
const Color COLOR_SLATEGREY = { "slategrey",
	0.439216, 0.501961, 0.564706, 1.000000 };
const Color COLOR_SNOW = { "snow",
	1.000000, 0.980392, 0.980392, 1.000000 };
const Color COLOR_SPRINGGREEN = { "springgreen",
	0.000000, 1.000000, 0.498039, 1.000000 };
const Color COLOR_STEELBLUE = { "steelblue",
	0.274510, 0.509804, 0.705882, 1.000000 };
const Color COLOR_TAN = { "tan",
	0.823529, 0.705882, 0.549020, 1.000000 };
const Color COLOR_TEAL = { "teal",
	0.000000, 0.501961, 0.501961, 1.000000 };
const Color COLOR_THISTLE = { "thistle",
	0.847059, 0.749020, 0.847059, 1.000000 };
const Color COLOR_TOMATO = { "tomato",
	1.000000, 0.388235, 0.278431, 1.000000 };
const Color COLOR_TURQUOISE = { "turquoise",
	0.250980, 0.878431, 0.815686, 1.000000 };
const Color COLOR_VIOLET = { "violet",
	0.933333, 0.509804, 0.933333, 1.000000 };
const Color COLOR_WHEAT = { "wheat",
	0.960784, 0.870588, 0.701961, 1.000000 };
const Color COLOR_WHITE = { "white",
	1.000000, 1.000000, 1.000000, 1.000000 };
const Color COLOR_WHITESMOKE = { "whitesmoke",
	0.960784, 0.960784, 0.960784, 1.000000 };
const Color COLOR_YELLOW = { "yellow",
	1.000000, 1.000000, 0.000000, 1.000000 };
const Color COLOR_YELLOWGREEN = { "yellowgreen",
	0.603922, 0.803922, 0.196078, 1.000000 };

/// Basic colors defined by the Ionflux Tools.
const Color COLOR_NONE = { "<none>",
	0.000000, 0.000000, 0.000000, 0.000000 };
const Color COLOR_GREY_10 = { "grey_10",
	0.900000, 0.900000, 0.900000, 1.000000 };
const Color COLOR_GREY_20 = { "grey_20",
	0.800000, 0.800000, 0.800000, 1.000000 };
const Color COLOR_GREY_30 = { "grey_30",
	0.700000, 0.700000, 0.700000, 1.000000 };
const Color COLOR_GREY_40 = { "grey_40",
	0.600000, 0.600000, 0.600000, 1.000000 };
const Color COLOR_GREY_50 = { "grey_50",
	0.500000, 0.500000, 0.500000, 1.000000 };
const Color COLOR_GREY_60 = { "grey_60",
	0.400000, 0.400000, 0.400000, 1.000000 };
const Color COLOR_GREY_70 = { "grey_70",
	0.300000, 0.300000, 0.300000, 1.000000 };
const Color COLOR_GREY_80 = { "grey_80",
	0.200000, 0.200000, 0.200000, 1.000000 };
const Color COLOR_GREY_90 = { "grey_90",
	0.100000, 0.100000, 0.100000, 1.000000 };

/** Get 8 bpp representation.
 *
 * Get an 8 bits per pixel RGBA representation of a color.
 *
 * \param color Color.
 *
 * \return 8 bpp RGBA representation of the color.
 */
Color8bpp to8bpp(const Color& color);

/** Get hexadecimal representation.
 *
 * Get the hexadecimal representation of a color.
 *
 * \param color Color.
 *
 * \return Hexadecimal representation of the color.
 */
std::string toHex(const Color& color);

/** Create color from hexadecimal representation.
 *
 * Create a color from a hexadecimal representation.
 *
 * \param hexColor Hexadecimal color.
 *
 * \return Color.
 */
Color createColorFromHex(const std::string& hexColor);

/** Add basic colors.
 *
 * Add basic colors to a color map.
 *
 * \param colorMap Color map.
 */
void addBasicColors(ColorMap& colorMap);

/** Get color by name.
 *
 * Get a color from a color map by name.
 *
 * \param colorName Color name.
 * \param colorMap Color map.
 *
 * \return Color with specified name, or 0 if no matching color is found.
 */
const Color* getByName(const std::string& colorName, ColorMap& colorMap);

/// @}

}

}

/** \file color.hpp
 * \brief Tools for handling colors.
 */
#endif
