#ifndef IONFLUX_TOOLS_CANVAS
#define IONFLUX_TOOLS_CANVAS
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Canvas.hpp                        Drawing canvas.
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

#include <string>
#include "ionflux/color.hpp"
#include "ionflux/Matrix3.hpp"

namespace Ionflux
{

namespace Tools
{

/** Drawing canvas.
 * \ingroup general
 *
 * Abstract base class for objects which process drawing operations.
 */
class Canvas
{
	private:
		
	protected:
		/// Default stroke color.
		Color defaultStrokeColor;
		/// Default fill color.
		Color defaultFillColor;
		/// Default stroke width.
		double defaultStrokeWidth;
		/// Default font family.
		std::string defaultFontFamily;
		/// Default font size.
		double defaultFontSize;
		/// Default transform matrix.
		Matrix3* defaultTransform;
		
	public:
		/** Constructor.
		 *
		 * Construct new Canvas object.
		 */
		Canvas();
		
		/** Destructor.
		 *
		 * Destruct Canvas object.
		 */
		virtual ~Canvas();
		
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
		width = 0.0, const Color* color = 0, Matrix3* transform = 0) = 0;
		
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
		Color* fillColor = 0, Matrix3* transform = 0) = 0;
		
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
		strokeColor = 0, const Color* fillColor = 0, Matrix3* transform = 0) = 0;
		
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
		transform = 0) = 0;
		
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
		fillColor = 0, Matrix3* transform = 0) = 0;
		
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
		0, const Color* fillColor = 0, Matrix3* transform = 0) = 0;
		
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
		0, Matrix3* transform = 0) = 0;
		
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
		transform = 0) = 0;
		
		/** Draw text.
		 *
		 * Draw a text.
		 *
		 * \param x x coordinate.
		 * \param y y coordinate.
		 * \param text Text.
		 * \param fontFamily Font family.
		 * \param fontSize Font size.
		 * \param color Color.
		 * \param transform Transform matrix.
		 */
		virtual void drawText(double x, double y, const std::string& text, const 
		std::string& fontFamily = "", double fontSize = 0.0, const Color* color =
		0, Matrix3* transform = 0) = 0;
		
		/** Set default stroke color.
		 *
		 * Set new value of default stroke color.
		 *
		 * \param newDefaultStrokeColor New value of default stroke color.
		 */
		virtual void setDefaultStrokeColor(const Color& newDefaultStrokeColor);
		
		/** Set default fill color.
		 *
		 * Set new value of default fill color.
		 *
		 * \param newDefaultFillColor New value of default fill color.
		 */
		virtual void setDefaultFillColor(const Color& newDefaultFillColor);
		
		/** Set default stroke width.
		 *
		 * Set new value of default stroke width.
		 *
		 * \param newDefaultStrokeWidth New value of default stroke width.
		 */
		virtual void setDefaultStrokeWidth(double newDefaultStrokeWidth);
		
		/** Set default font family.
		 *
		 * Set new value of default font family.
		 *
		 * \param newDefaultFontFamily New value of default font family.
		 */
		virtual void setDefaultFontFamily(const std::string& 
		newDefaultFontFamily);
		
		/** Set default font size.
		 *
		 * Set new value of default font size.
		 *
		 * \param newDefaultFontSize New value of default font size.
		 */
		virtual void setDefaultFontSize(double newDefaultFontSize);
		
		/** Set default transform matrix.
		 *
		 * Set new value of default transform matrix.
		 *
		 * \param newDefaultTransform New value of default transform matrix.
		 */
		virtual void setDefaultTransform(Matrix3* newDefaultTransform);
		
		/** Get default stroke color.
		 *
		 * \return Current value of default stroke color.
		 */
		virtual Color getDefaultStrokeColor() const;
		
		/** Get default fill color.
		 *
		 * \return Current value of default fill color.
		 */
		virtual Color getDefaultFillColor() const;
		
		/** Get default stroke width.
		 *
		 * \return Current value of default stroke width.
		 */
		virtual double getDefaultStrokeWidth() const;
		
		/** Get default font family.
		 *
		 * \return Current value of default font family.
		 */
		virtual std::string getDefaultFontFamily() const;
		
		/** Get default font size.
		 *
		 * \return Current value of default font size.
		 */
		virtual double getDefaultFontSize() const;
		
		/** Get default transform matrix.
		 *
		 * \return Current value of default transform matrix.
		 */
		virtual Matrix3* getDefaultTransform() const;
};

}

}

/** \file Canvas.hpp
 * \brief Drawing canvas header.
 */
#endif
