/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoCanvas.cpp                 Cairo drawing canvas.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/CairoCanvas.hpp"
#include <pango/pangocairo.h>

using namespace std;
using namespace Ionflux::Tools::Cairo;

namespace Ionflux
{

namespace Tools
{

CairoCanvas::CairoCanvas()
{
	cairoContext = 0;
	defaultStrokeColor = COLOR_BLACK;
	defaultFillColor = COLOR_WHITE;
	defaultStrokeWidth = 1.0;
	defaultFontFamily = "sans-serif";
	defaultFontSize = 12.0;
	defaultTransform = 0;
}

CairoCanvas::CairoCanvas(const Ionflux::Tools::Cairo::CairoContext& 
initCairoContext)
{
	setCairoContext(initCairoContext.getCairoContext());
	defaultStrokeColor = COLOR_BLACK;
	defaultFillColor = COLOR_WHITE;
	defaultStrokeWidth = 1.0;
	defaultFontFamily = "sans-serif";
	defaultFontSize = 12.0;
	defaultTransform = 0;
}

CairoCanvas::CairoCanvas(cairo_t* initCairoContext)
{
	setCairoContext(initCairoContext);
	defaultStrokeColor = COLOR_BLACK;
	defaultFillColor = COLOR_WHITE;
	defaultStrokeWidth = 1.0;
	defaultFontFamily = "sans-serif";
	defaultFontSize = 12.0;
	defaultTransform = 0;
}

CairoCanvas::CairoCanvas(cairo_surface_t* initSurface)
{
	cairoContext = cairo_create(initSurface);
	defaultStrokeColor = COLOR_BLACK;
	defaultFillColor = COLOR_WHITE;
	defaultStrokeWidth = 1.0;
	defaultFontFamily = "sans-serif";
	defaultFontSize = 12.0;
	defaultTransform = 0;
}

CairoCanvas::CairoCanvas(Surface& initSurface)
{
	cairoContext = cairo_create(initSurface.getCairoSurface());
	defaultStrokeColor = COLOR_BLACK;
	defaultFillColor = COLOR_WHITE;
	defaultStrokeWidth = 1.0;
	defaultFontFamily = "sans-serif";
	defaultFontSize = 12.0;
	defaultTransform = 0;
}

CairoCanvas::CairoCanvas(const CairoCanvas& initCairoCanvas)
{
	*this = initCairoCanvas;
}

CairoCanvas::~CairoCanvas()
{
	if (cairoContext != 0)
		cairo_destroy(cairoContext);
	cairoContext = 0;
}

void CairoCanvas::setTransform(Matrix3* transform)
{
	Matrix theTransform;
	if ((transform != 0) && (defaultTransform != 0))
		theTransform = (*transform) * (*defaultTransform);
	else
	if (transform != 0)
		theTransform = *transform;
	else
	if (defaultTransform != 0)
		theTransform = *defaultTransform;
	else
		return;
	this->transform(theTransform);
}

void CairoCanvas::drawLine(double x1, double y1, double x2, double y2, 
double width, const Color* color, Matrix3* transform)
{
	Color theStrokeColor;
	double theStrokeWidth;
	if (color != 0)
		theStrokeColor = *color;
	else
		theStrokeColor = defaultStrokeColor;
	if (width != 0.0)
		theStrokeWidth = width;
	else
		theStrokeWidth = defaultStrokeWidth;
	save();
	setTransform(transform);
	moveTo(x1, y1);
	lineTo(x2, y2);
	setSourceColor(theStrokeColor);
	setLineWidth(theStrokeWidth);
	stroke();
	restore();
}

void CairoCanvas::drawRectangle(double x, double y, double width, double 
height, double strokeWidth, const Color* strokeColor, const Color* 
fillColor, Matrix3* transform)
{
	Color theStrokeColor;
	Color theFillColor;
	double theStrokeWidth;
	if (strokeColor != 0)
		theStrokeColor = *strokeColor;
	else
		theStrokeColor = defaultStrokeColor;
	if (fillColor != 0)
		theFillColor = *fillColor;
	else
		theFillColor = defaultFillColor;
	if (strokeWidth != 0.0)
		theStrokeWidth = strokeWidth;
	else
		theStrokeWidth = defaultStrokeWidth;
	save();
	setTransform(transform);
	if (theFillColor.alpha != 0.0)
	{
		rectangle(x, y, width, height);
		setSourceColor(theFillColor);
		fill();
	}
	if (theStrokeColor.alpha != 0.0)
	{
		rectangle(x, y, width, height);
		setSourceColor(theStrokeColor);
		setLineWidth(theStrokeWidth);
		stroke();
	}
	restore();
}

void CairoCanvas::drawArc(double x, double y, double width, double height,
double angle1, double angle2, double strokeWidth, const Color* strokeColor,
const Color* fillColor, Matrix3* transform)
{
	double a = width / 2.0;
	double b = height / 2.0;
	Color theStrokeColor;
	Color theFillColor;
	double theStrokeWidth;
	if (strokeColor != 0)
		theStrokeColor = *strokeColor;
	else
		theStrokeColor = defaultStrokeColor;
	if (fillColor != 0)
		theFillColor = *fillColor;
	else
		theFillColor = defaultFillColor;
	if (strokeWidth != 0.0)
		theStrokeWidth = strokeWidth;
	else
		theStrokeWidth = defaultStrokeWidth;
	save();
	setTransform(transform);
	translate(x + a, y + b);
	scale(1.0, b / a);
	if (theFillColor.alpha != 0.0)
	{
		arc(0.0, 0.0, a, angle1, angle2);
		setSourceColor(theFillColor);
		fill();
	}
	if (theStrokeColor.alpha != 0.0)
	{
		arc(0.0, 0.0, a, angle1, angle2);
		setSourceColor(theStrokeColor);
		setLineWidth(theStrokeWidth);
		stroke();
	}
	restore();
}

void CairoCanvas::drawArcEc(double xc, double yc, double radius, double
angle1, double angle2, double eccentricity, double strokeWidth, const
Color* strokeColor, const Color* fillColor, Matrix3* transform)
{
	double b = radius * sqrt(1.0 - eccentricity * eccentricity);
	drawArc(xc - radius, yc - b, 2.0 * radius, 2.0 * b, angle1, angle2, 
		strokeWidth, strokeColor, fillColor, transform);
}

void CairoCanvas::drawEllipse(double x, double y, double width, double 
height, double strokeWidth, const Color* strokeColor, const Color* 
fillColor, Matrix3* transform)
{
	drawArc(x, y, width, height, 0.0, M_PI * 2.0, strokeWidth, 
		strokeColor, fillColor, transform);
}

void CairoCanvas::drawEllipseEc(double xc, double yc, double radius, double
eccentricity, double strokeWidth, const Color* strokeColor, const Color* 
fillColor, Matrix3* transform)
{
	drawArcEc(xc, yc, radius, 0.0, M_PI * 2.0, eccentricity, 
		strokeWidth, strokeColor, fillColor, transform);
}

void CairoCanvas::drawCircle(double xc, double yc, double radius, double
strokeWidth, const Color* strokeColor, const Color* fillColor, Matrix3*
transform)
{
	drawEllipseEc(xc, yc, radius, 0.0, strokeWidth, strokeColor, 
		fillColor, transform);
}

void CairoCanvas::drawCurve(double x1, double y1, double x2, double y2, 
double x3, double y3, double strokeWidth, const Color* color, Matrix3* 
transform)
{
	Color theStrokeColor;
	double theStrokeWidth;
	if (color != 0)
		theStrokeColor = *color;
	else
		theStrokeColor = defaultStrokeColor;
	if (strokeWidth != 0.0)
		theStrokeWidth = strokeWidth;
	else
		theStrokeWidth = defaultStrokeWidth;
	save();
	setTransform(transform);
	moveTo(x1, y1);
	curveTo(x1, y1, x2, y2, x3, y3);
	setSourceColor(theStrokeColor);
	setLineWidth(theStrokeWidth);
	stroke();
	restore();
}

void CairoCanvas::drawText(double x, double y, const std::string& text, 
const std::string& fontDesc, double fontSize, const Color* color, Matrix3* 
transform)
{
	Color theFillColor;
	string theFontDesc;
	if (color != 0)
		theFillColor = *color;
	else
		theFillColor = defaultFillColor;
	if (fontDesc.size() > 0)
		theFontDesc = fontDesc;
	else
		theFontDesc = defaultFontFamily;
	if (fontSize == 0.0)
		fontSize = defaultFontSize;
	PangoLayout* layout = pango_cairo_create_layout(cairoContext);;
	pango_layout_set_text(layout, text.c_str(), -1);
	PangoFontDescription* pangoFontDesc = pango_font_description_from_string(
		fontDesc.c_str());
	pango_font_description_set_absolute_size(pangoFontDesc, 
		fontSize * PANGO_SCALE);
	pango_layout_set_font_description(layout, pangoFontDesc);
	pango_font_description_free(pangoFontDesc);
	save();
	setTransform(transform);
	pango_cairo_update_layout(cairoContext, layout);
	moveTo(x, y);
	setSourceColor(theFillColor);
	pango_cairo_show_layout(cairoContext, layout);
	restore();
	g_object_unref(layout);
}

void CairoCanvas::getTextSize(const std::string& text, double& width, 
double& height, const std::string& fontDesc, double fontSize, Matrix3* 
transform)
{
	string theFontDesc;
	if (fontDesc.size() > 0)
		theFontDesc = fontDesc;
	else
		theFontDesc = defaultFontFamily;
	if (fontSize == 0.0)
		fontSize = defaultFontSize;
	PangoLayout* layout = pango_cairo_create_layout(cairoContext);;
	pango_layout_set_text(layout, text.c_str(), -1);
	PangoFontDescription* pangoFontDesc = pango_font_description_from_string(
		fontDesc.c_str());
	pango_font_description_set_absolute_size(pangoFontDesc, 
		fontSize * PANGO_SCALE);
	pango_layout_set_font_description(layout, pangoFontDesc);
	pango_font_description_free(pangoFontDesc);
	save();
	setTransform(transform);
	pango_cairo_update_layout(cairoContext, layout);
	int rawWidth;
	int rawHeight;
	pango_layout_get_size(layout, &rawWidth, &rawHeight);
	width = static_cast<double>(rawWidth) / PANGO_SCALE;
	height = static_cast<double>(rawHeight) / PANGO_SCALE;
	restore();
	g_object_unref(layout);
}

CairoCanvas& CairoCanvas::operator=(const Ionflux::Tools::Cairo::CairoContext& 
newCairoContext)
{
	setCairoContext(newCairoContext.getCairoContext());
	return *this;
}

CairoCanvas& CairoCanvas::operator=(cairo_t* newCairoContext)
{
	setCairoContext(newCairoContext);
	return *this;
}

CairoCanvas& CairoCanvas::operator=(const CairoCanvas& newCairoCanvas)
{
	setCairoContext(newCairoCanvas.getCairoContext());
	defaultStrokeColor = newCairoCanvas.getDefaultStrokeColor();
	defaultFillColor = newCairoCanvas.getDefaultFillColor();
	defaultStrokeWidth = newCairoCanvas.getDefaultStrokeWidth();
	defaultFontFamily = newCairoCanvas.getDefaultFontFamily();
	defaultFontSize = newCairoCanvas.getDefaultFontSize();
	defaultTransform = newCairoCanvas.getDefaultTransform();
	return *this;
}

}

}

/** \file CairoCanvas.cpp
 * \brief Cairo drawing canvas implementation.
 */
