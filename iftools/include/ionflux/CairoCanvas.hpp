#ifndef IONFLUX_TOOLS_CAIROCANVAS
#define IONFLUX_TOOLS_CAIROCANVAS
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoCanvas.hpp                   Cairo drawing canvas.
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

#include "ionflux/CairoContext.hpp"
#include "ionflux/Canvas.hpp"

namespace Ionflux
{

namespace Tools
{

/** Cairo drawing canvas.
 * \ingroup cairo
 *
 * A canvas which uses Cairo for drawing operations.
 */
class CairoCanvas
: public Ionflux::Tools::Cairo::CairoContext, public Canvas
{
	private:
		
	protected:
		
		/** Set transform.
		 *
		 * Set transform.
		 *
		 * \param transform Transform matrix.
		 */
		virtual void setTransform(Matrix3* transform = 0);
		
	public:
		/** Constructor.
		 *
		 * Construct new CairoCanvas object.
		 */
		CairoCanvas();
		
		/** Constructor.
		 *
		 * Construct new CairoCanvas object.
		 *
		 * \param initCairoContext Cairo context.
		 */
		CairoCanvas(const Ionflux::Tools::Cairo::CairoContext& initCairoContext);
		
		/** Constructor.
		 *
		 * Construct new CairoCanvas object.
		 *
		 * \param initCairoContext Cairo context.
		 */
		CairoCanvas(cairo_t* initCairoContext);
		
		/** Constructor.
		 *
		 * Construct new CairoCanvas object.
		 *
		 * \param initSurface Cairo surface.
		 */
		CairoCanvas(cairo_surface_t* initSurface);
		
		/** Constructor.
		 *
		 * Construct new CairoCanvas object.
		 *
		 * \param initSurface Cairo surface.
		 */
		CairoCanvas(Ionflux::Tools::Cairo::Surface& initSurface);
		
		/** Constructor.
		 *
		 * Construct new CairoCanvas object.
		 *
		 * \param initCairoCanvas Cairo canvas.
		 */
		CairoCanvas(const CairoCanvas& initCairoCanvas);
		
		/** Destructor.
		 *
		 * Destruct CairoCanvas object.
		 */
		virtual ~CairoCanvas();
		
		/** Draw line.
		 *
		 * Draw a line.
		 *
		 * \param x1 x1 coordinate.
		 * \param y1 y1 coordinate.
		 * \param x2 x2 coordinate.
		 * \param y2 y2 coordinate.
		 * \param width Stroke width.
		 * \param color Stroke color.
		 * \param transform Transform matrix.
		 */
		virtual void drawLine(double x1, double y1, double x2, double y2, double 
		width = 0.0, const Color* color = 0, Matrix3* transform = 0);
		
		/** Draw rectangle.
		 *
		 * Draw a rectangle.
		 *
		 * \param x x coordinate.
		 * \param y y coordinate.
		 * \param width Width.
		 * \param height Height.
		 * \param strokeWidth Stroke width.
		 * \param strokeColor Stroke color.
		 * \param fillColor Fill color.
		 * \param transform Transform matrix.
		 */
		virtual void drawRectangle(double x, double y, double width, double 
		height, double strokeWidth = 0.0, const Color* strokeColor = 0, const 
		Color* fillColor = 0, Matrix3* transform = 0);
		
		/** Draw arc.
		 *
		 * Draw an arc.
		 *
		 * \param x x coordinate.
		 * \param y y coordinate.
		 * \param width Width.
		 * \param height Height.
		 * \param angle1 Angle 1.
		 * \param angle2 Angle 2.
		 * \param strokeWidth Stroke width.
		 * \param strokeColor Stroke color.
		 * \param fillColor Fill color.
		 * \param transform Transform matrix.
		 */
		virtual void drawArc(double x, double y, double width, double height, 
		double angle1, double angle2, double strokeWidth = 0.0, const Color* 
		strokeColor = 0, const Color* fillColor = 0, Matrix3* transform = 0);
		
		/** Draw arc.
		 *
		 * Draw an arc with specified eccentricity.
		 *
		 * \param xc x center.
		 * \param yc y center.
		 * \param radius Radius.
		 * \param angle1 Angle 1.
		 * \param angle2 Angle 2.
		 * \param eccentricity Eccentricity.
		 * \param strokeWidth Stroke width.
		 * \param strokeColor Stroke color.
		 * \param fillColor Fill color.
		 * \param transform Transform matrix.
		 */
		virtual void drawArcEc(double xc, double yc, double radius, double 
		angle1, double angle2, double eccentricity = 0.0, double strokeWidth = 
		0.0, const Color* strokeColor = 0, const Color* fillColor = 0, Matrix3* 
		transform = 0);
		
		/** Draw ellipse.
		 *
		 * Draw an ellipse.
		 *
		 * \param x x coordinate.
		 * \param y y coordinate.
		 * \param width Width.
		 * \param height Height.
		 * \param strokeWidth Stroke width.
		 * \param strokeColor Stroke color.
		 * \param fillColor Fill color.
		 * \param transform Transform matrix.
		 */
		virtual void drawEllipse(double x, double y, double width, double height,
		double strokeWidth = 0.0, const Color* strokeColor = 0, const Color* 
		fillColor = 0, Matrix3* transform = 0);
		
		/** Draw ellipse.
		 *
		 * Draw an ellipse.
		 *
		 * \param xc x center.
		 * \param yc y center.
		 * \param radius Radius.
		 * \param eccentricity Eccentricity.
		 * \param strokeWidth Stroke width.
		 * \param strokeColor Stroke color.
		 * \param fillColor Fill color.
		 * \param transform Transform matrix.
		 */
		virtual void drawEllipseEc(double xc, double yc, double radius, double 
		eccentricity = 0.0, double strokeWidth = 0.0, const Color* strokeColor = 
		0, const Color* fillColor = 0, Matrix3* transform = 0);
		
		/** Draw circle.
		 *
		 * Draw a circle.
		 *
		 * \param xc x center.
		 * \param yc y center.
		 * \param radius Radius.
		 * \param strokeWidth Stroke width.
		 * \param strokeColor Stroke color.
		 * \param fillColor Fill color.
		 * \param transform Transform matrix.
		 */
		virtual void drawCircle(double xc, double yc, double radius, double 
		strokeWidth = 0.0, const Color* strokeColor = 0, const Color* fillColor =
		0, Matrix3* transform = 0);
		
		/** Draw curve.
		 *
		 * Draw a curve.
		 *
		 * \param x1 x1 coordinate.
		 * \param y1 y1 coordinate.
		 * \param x2 x2 coordinate.
		 * \param y2 y2 coordinate.
		 * \param x3 x3 coordinate.
		 * \param y3 y3 coordinate.
		 * \param strokeWidth Stroke width.
		 * \param color Stroke color.
		 * \param transform Transform matrix.
		 */
		virtual void drawCurve(double x1, double y1, double x2, double y2, double
		x3, double y3, double strokeWidth = 0.0, const Color* color = 0, Matrix3*
		transform = 0);
		
		/** Draw text.
		 *
		 * Draw a text.
		 *
		 * \param x x coordinate.
		 * \param y y coordinate.
		 * \param text Text.
		 * \param fontDesc Font description.
		 * \param fontSize Font size.
		 * \param color Color.
		 * \param transform Transform matrix.
		 */
		virtual void drawText(double x, double y, const std::string& text, const 
		std::string& fontDesc = "", double fontSize = 0.0, const Color* color = 
		0, Matrix3* transform = 0);
		
		/** Get text size.
		 *
		 * Get the size of the specified text.
		 *
		 * \param text Text.
		 * \param width Where to store the text width.
		 * \param height Where to store the text height.
		 * \param fontDesc Font description.
		 * \param fontSize Font size.
		 * \param transform Transform matrix.
		 */
		virtual void getTextSize(const std::string& text, double& width, double& 
		height, const std::string& fontDesc = "", double fontSize = 0.0, Matrix3*
		transform = 0);
		
		/** Assignment operator.
		 *
		 * Assign a Cairo context to a Cairo canvas.
		 *
		 * \param newCairoContext Cairo context.
		 *
		 * \return The object itself.
		 */
		virtual CairoCanvas& operator=(const 
		Ionflux::Tools::Cairo::CairoContext& newCairoContext);
		
		/** Assignment operator.
		 *
		 * Assign a Cairo context to a Cairo canvas.
		 *
		 * \param newCairoContext Cairo context.
		 *
		 * \return The object itself.
		 */
		virtual CairoCanvas& operator=(cairo_t* newCairoContext);
		
		/** Assignment operator.
		 *
		 * Assign a Cairo canvas to another Cairo canvas.
		 *
		 * \param newCairoCanvas Cairo canvas.
		 *
		 * \return The object itself.
		 */
		virtual CairoCanvas& operator=(const CairoCanvas& newCairoCanvas);
};

}

}

/** \file CairoCanvas.hpp
 * \brief Cairo drawing canvas header.
 */
#endif
