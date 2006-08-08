#ifndef IONFLUX_TOOLS_CAIRO_CAIROCONTEXT
#define IONFLUX_TOOLS_CAIRO_CAIROCONTEXT
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoContext.hpp                  Cairo context.
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
#include "cairo.h"
#include "ionflux/color.hpp"
#include "ionflux/ManagedObject.hpp"
#include "ionflux/CairoMatrix.hpp"
#include "ionflux/CairoPattern.hpp"
#include "ionflux/CairoSurface.hpp"
#include "ionflux/CairoPath.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

/** \addtogroup cairo Cairo
 *
 * The Cairo vector graphics API.
 *
 * @{
 */

/** Cairo context.
 *
 * A wrapper for the Cairo vector graphics API (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class CairoContext
: public ManagedObject
{
	private:
		
	protected:
		/// Cairo context.
		cairo_t* cairoContext;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new CairoContext object.
		 */
		CairoContext();
		
		/** Constructor.
		 *
		 * Construct new CairoContext object.
		 *
		 * \param initCairoContext Cairo context.
		 */
		CairoContext(const CairoContext& initCairoContext);
		
		/** Constructor.
		 *
		 * Construct new CairoContext object.
		 *
		 * \param initCairoContext Cairo context.
		 */
		CairoContext(cairo_t* initCairoContext);
		
		/** Constructor.
		 *
		 * Construct new CairoContext object.
		 *
		 * \param initSurface Cairo surface.
		 */
		CairoContext(cairo_surface_t* initSurface);
		
		/** Constructor.
		 *
		 * Construct new CairoContext object.
		 *
		 * \param initSurface Cairo surface.
		 */
		CairoContext(Surface& initSurface);
		
		/** Destructor.
		 *
		 * Destruct CairoContext object.
		 */
		virtual ~CairoContext();
		
		/** Reference.
		 *
		 * Reference
		 */
		virtual void reference();
		
		/** Destroy.
		 *
		 * Destroy
		 */
		virtual void destroy();
		
		/** Save.
		 *
		 * Save
		 */
		virtual void save();
		
		/** Restore.
		 *
		 * Restore
		 */
		virtual void restore();
		
		/** Set operator.
		 *
		 * Set operator
		 *
		 * \param op Op.
		 */
		virtual void setOperator(cairo_operator_t op);
		
		/** Set source.
		 *
		 * Set source
		 *
		 * \param source Source.
		 */
		virtual void setSource(cairo_pattern_t* source);
		
		/** Set source.
		 *
		 * Set source
		 *
		 * \param source Source.
		 */
		virtual void setSource(const Pattern& source);
		
		/** Set source rgb.
		 *
		 * Set source rgb
		 *
		 * \param red Red.
		 * \param green Green.
		 * \param blue Blue.
		 */
		virtual void setSourceRgb(double red, double green, double blue);
		
		/** Set source rgba.
		 *
		 * Set source rgba
		 *
		 * \param red Red.
		 * \param green Green.
		 * \param blue Blue.
		 * \param alpha Alpha.
		 */
		virtual void setSourceRgba(double red, double green, double blue, double 
		alpha);
		
		/** Set source color.
		 *
		 * Set source Color
		 *
		 * \param color Color.
		 */
		virtual void setSourceColor(const Ionflux::Tools::Color& color);
		
		/** Set source surface.
		 *
		 * Set source surface
		 *
		 * \param surface Surface.
		 * \param x X.
		 * \param y Y.
		 */
		virtual void setSourceSurface(cairo_surface_t* surface, double x, double 
		y);
		
		/** Set source surface.
		 *
		 * Set source surface
		 *
		 * \param surface Surface.
		 * \param x X.
		 * \param y Y.
		 */
		virtual void setSourceSurface(Surface& surface, double x, double y);
		
		/** Set tolerance.
		 *
		 * Set tolerance
		 *
		 * \param tolerance Tolerance.
		 */
		virtual void setTolerance(double tolerance);
		
		/** Set fill rule.
		 *
		 * Set fill rule
		 *
		 * \param fill_rule Fill_rule.
		 */
		virtual void setFillRule(cairo_fill_rule_t fill_rule);
		
		/** Set line width.
		 *
		 * Set line width
		 *
		 * \param width Width.
		 */
		virtual void setLineWidth(double width);
		
		/** Set line cap.
		 *
		 * Set line cap
		 *
		 * \param line_cap Line_cap.
		 */
		virtual void setLineCap(cairo_line_cap_t line_cap);
		
		/** Set line join.
		 *
		 * Set line join
		 *
		 * \param line_join Line_join.
		 */
		virtual void setLineJoin(cairo_line_join_t line_join);
		
		/** Set dash.
		 *
		 * Set dash
		 *
		 * \param dashes Dashes.
		 * \param ndash Ndash.
		 * \param offset Offset.
		 */
		virtual void setDash(double* dashes, int ndash, double offset);
		
		/** Set miter limit.
		 *
		 * Set miter limit
		 *
		 * \param limit Limit.
		 */
		virtual void setMiterLimit(double limit);
		
		/** Translate.
		 *
		 * Translate
		 *
		 * \param tx Tx.
		 * \param ty Ty.
		 */
		virtual void translate(double tx, double ty);
		
		/** Scale.
		 *
		 * Scale
		 *
		 * \param sx Sx.
		 * \param sy Sy.
		 */
		virtual void scale(double sx, double sy);
		
		/** Rotate.
		 *
		 * Rotate
		 *
		 * \param angle Angle.
		 */
		virtual void rotate(double angle);
		
		/** Transform.
		 *
		 * Transform
		 *
		 * \param matrix Matrix.
		 */
		virtual void transform(const cairo_matrix_t* matrix);
		
		/** Transform.
		 *
		 * Transform
		 *
		 * \param matrix Matrix.
		 */
		virtual void transform(const Matrix& matrix);
		
		/** Set matrix.
		 *
		 * Set matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void setMatrix(const cairo_matrix_t* matrix);
		
		/** Set matrix.
		 *
		 * Set matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void setMatrix(const Matrix& matrix);
		
		/** Identity matrix.
		 *
		 * Identity matrix
		 */
		virtual void identityMatrix();
		
		/** User to device.
		 *
		 * User to device
		 *
		 * \param x X.
		 * \param y Y.
		 */
		virtual void userToDevice(double* x, double* y);
		
		/** User to device distance.
		 *
		 * User to device distance
		 *
		 * \param dx Dx.
		 * \param dy Dy.
		 */
		virtual void userToDeviceDistance(double* dx, double* dy);
		
		/** Device to user.
		 *
		 * Device to user
		 *
		 * \param x X.
		 * \param y Y.
		 */
		virtual void deviceToUser(double* x, double* y);
		
		/** Device to user distance.
		 *
		 * Device to user distance
		 *
		 * \param dx Dx.
		 * \param dy Dy.
		 */
		virtual void deviceToUserDistance(double* dx, double* dy);
		
		/** New path.
		 *
		 * New path
		 */
		virtual void newPath();
		
		/** Move to.
		 *
		 * Move to
		 *
		 * \param x X.
		 * \param y Y.
		 */
		virtual void moveTo(double x, double y);
		
		/** Line to.
		 *
		 * Line to
		 *
		 * \param x X.
		 * \param y Y.
		 */
		virtual void lineTo(double x, double y);
		
		/** Curve to.
		 *
		 * Curve to
		 *
		 * \param x1 X1.
		 * \param y1 Y1.
		 * \param x2 X2.
		 * \param y2 Y2.
		 * \param x3 X3.
		 * \param y3 Y3.
		 */
		virtual void curveTo(double x1, double y1, double x2, double y2, double 
		x3, double y3);
		
		/** Arc.
		 *
		 * Arc
		 *
		 * \param xc Xc.
		 * \param yc Yc.
		 * \param radius Radius.
		 * \param angle1 Angle1.
		 * \param angle2 Angle2.
		 */
		virtual void arc(double xc, double yc, double radius, double angle1, 
		double angle2);
		
		/** Arc negative.
		 *
		 * Arc negative
		 *
		 * \param xc Xc.
		 * \param yc Yc.
		 * \param radius Radius.
		 * \param angle1 Angle1.
		 * \param angle2 Angle2.
		 */
		virtual void arcNegative(double xc, double yc, double radius, double 
		angle1, double angle2);
		
		/** Rel move to.
		 *
		 * Rel move to
		 *
		 * \param dx Dx.
		 * \param dy Dy.
		 */
		virtual void relMoveTo(double dx, double dy);
		
		/** Rel line to.
		 *
		 * Rel line to
		 *
		 * \param dx Dx.
		 * \param dy Dy.
		 */
		virtual void relLineTo(double dx, double dy);
		
		/** Rel curve to.
		 *
		 * Rel curve to
		 *
		 * \param dx1 Dx1.
		 * \param dy1 Dy1.
		 * \param dx2 Dx2.
		 * \param dy2 Dy2.
		 * \param dx3 Dx3.
		 * \param dy3 Dy3.
		 */
		virtual void relCurveTo(double dx1, double dy1, double dx2, double dy2, 
		double dx3, double dy3);
		
		/** Rectangle.
		 *
		 * Rectangle
		 *
		 * \param x X.
		 * \param y Y.
		 * \param width Width.
		 * \param height Height.
		 */
		virtual void rectangle(double x, double y, double width, double height);
		
		/** Close path.
		 *
		 * Close path
		 */
		virtual void closePath();
		
		/** Paint.
		 *
		 * Paint
		 */
		virtual void paint();
		
		/** Paint with alpha.
		 *
		 * Paint with alpha
		 *
		 * \param alpha Alpha.
		 */
		virtual void paintWithAlpha(double alpha);
		
		/** Mask.
		 *
		 * Mask
		 *
		 * \param pattern Pattern.
		 */
		virtual void mask(cairo_pattern_t* pattern);
		
		/** Mask.
		 *
		 * Mask
		 *
		 * \param pattern Pattern.
		 */
		virtual void mask(const Pattern& pattern);
		
		/** Mask surface.
		 *
		 * Mask surface
		 *
		 * \param surface Surface.
		 * \param surface_x Surface_x.
		 * \param surface_y Surface_y.
		 */
		virtual void maskSurface(cairo_surface_t* surface, double surface_x, 
		double surface_y);
		
		/** Mask surface.
		 *
		 * Mask surface
		 *
		 * \param surface Surface.
		 * \param surface_x Surface_x.
		 * \param surface_y Surface_y.
		 */
		virtual void maskSurface(Surface& surface, double surface_x, double 
		surface_y);
		
		/** Stroke.
		 *
		 * Stroke
		 */
		virtual void stroke();
		
		/** Stroke preserve.
		 *
		 * Stroke preserve
		 */
		virtual void strokePreserve();
		
		/** Fill.
		 *
		 * Fill
		 */
		virtual void fill();
		
		/** Fill preserve.
		 *
		 * Fill preserve
		 */
		virtual void fillPreserve();
		
		/** Copy page.
		 *
		 * Copy page
		 */
		virtual void copyPage();
		
		/** Show page.
		 *
		 * Show page
		 */
		virtual void showPage();
		
		/** In stroke.
		 *
		 * In stroke
		 *
		 * \param x X.
		 * \param y Y.
		 *
		 * \return .
		 */
		virtual cairo_bool_t inStroke(double x, double y);
		
		/** In fill.
		 *
		 * In fill
		 *
		 * \param x X.
		 * \param y Y.
		 *
		 * \return .
		 */
		virtual cairo_bool_t inFill(double x, double y);
		
		/** Stroke extents.
		 *
		 * Stroke extents
		 *
		 * \param x1 X1.
		 * \param y1 Y1.
		 * \param x2 X2.
		 * \param y2 Y2.
		 */
		virtual void strokeExtents(double* x1, double* y1, double* x2, double* 
		y2);
		
		/** Fill extents.
		 *
		 * Fill extents
		 *
		 * \param x1 X1.
		 * \param y1 Y1.
		 * \param x2 X2.
		 * \param y2 Y2.
		 */
		virtual void fillExtents(double* x1, double* y1, double* x2, double* y2);
		
		/** Reset clip.
		 *
		 * Reset clip
		 */
		virtual void resetClip();
		
		/** Clip.
		 *
		 * Clip
		 */
		virtual void clip();
		
		/** Clip preserve.
		 *
		 * Clip preserve
		 */
		virtual void clipPreserve();
		
		/** Select font face.
		 *
		 * Select font face
		 *
		 * \param family Family.
		 * \param slant Slant.
		 * \param weight Weight.
		 */
		virtual void selectFontFace(const std::string& family, cairo_font_slant_t
		slant, cairo_font_weight_t weight);
		
		/** Set font size.
		 *
		 * Set font size
		 *
		 * \param size Size.
		 */
		virtual void setFontSize(double size);
		
		/** Set font matrix.
		 *
		 * Set font matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void setFontMatrix(const cairo_matrix_t* matrix);
		
		/** Set font matrix.
		 *
		 * Set font matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void setFontMatrix(const Matrix& matrix);
		
		/** Get font matrix.
		 *
		 * Get font matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void getFontMatrix(cairo_matrix_t* matrix);
		
		/** Get font matrix.
		 *
		 * Get font matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void getFontMatrix(Matrix& matrix);
		
		/** Show text.
		 *
		 * Show text
		 *
		 * \param utf8 Utf8.
		 */
		virtual void showText(const std::string& utf8);
		
		/** Show glyphs.
		 *
		 * Show glyphs
		 *
		 * \param glyphs Glyphs.
		 * \param num_glyphs Num_glyphs.
		 */
		virtual void showGlyphs(cairo_glyph_t* glyphs, int num_glyphs);
		
		/** Get font face.
		 *
		 * Get font face
		 *
		 * \return .
		 */
		virtual cairo_font_face_t* getFontFace();
		
		/** Font extents.
		 *
		 * Font extents
		 *
		 * \param extents Extents.
		 */
		virtual void fontExtents(cairo_font_extents_t* extents);
		
		/** Set font face.
		 *
		 * Set font face
		 *
		 * \param font_face Font_face.
		 */
		virtual void setFontFace(cairo_font_face_t* font_face);
		
		/** Text extents.
		 *
		 * Text extents
		 *
		 * \param utf8 Utf8.
		 * \param extents Extents.
		 */
		virtual void textExtents(const std::string& utf8, cairo_text_extents_t* 
		extents);
		
		/** Glyph extents.
		 *
		 * Glyph extents
		 *
		 * \param glyphs Glyphs.
		 * \param num_glyphs Num_glyphs.
		 * \param extents Extents.
		 */
		virtual void glyphExtents(cairo_glyph_t* glyphs, int num_glyphs, 
		cairo_text_extents_t* extents);
		
		/** Text path.
		 *
		 * Text path
		 *
		 * \param utf8 Utf8.
		 */
		virtual void textPath(const std::string& utf8);
		
		/** Glyph path.
		 *
		 * Glyph path
		 *
		 * \param glyphs Glyphs.
		 * \param num_glyphs Num_glyphs.
		 */
		virtual void glyphPath(cairo_glyph_t* glyphs, int num_glyphs);
		
		/** Get operator.
		 *
		 * Get operator
		 *
		 * \return .
		 */
		virtual cairo_operator_t getOperator();
		
		/** Get source.
		 *
		 * Get source
		 *
		 * \return .
		 */
		virtual cairo_pattern_t* getSource();
		
		/** Get tolerance.
		 *
		 * Get tolerance
		 *
		 * \return .
		 */
		virtual double getTolerance();
		
		/** Get current point.
		 *
		 * Get current point
		 *
		 * \param x X.
		 * \param y Y.
		 */
		virtual void getCurrentPoint(double* x, double* y);
		
		/** Get fill rule.
		 *
		 * Get fill rule
		 *
		 * \return .
		 */
		virtual cairo_fill_rule_t getFillRule();
		
		/** Get line width.
		 *
		 * Get line width
		 *
		 * \return .
		 */
		virtual double getLineWidth();
		
		/** Get line cap.
		 *
		 * Get line cap
		 *
		 * \return .
		 */
		virtual cairo_line_cap_t getLineCap();
		
		/** Get line join.
		 *
		 * Get line join
		 *
		 * \return .
		 */
		virtual cairo_line_join_t getLineJoin();
		
		/** Get miter limit.
		 *
		 * Get miter limit
		 *
		 * \return .
		 */
		virtual double getMiterLimit();
		
		/** Get matrix.
		 *
		 * Get matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void getMatrix(cairo_matrix_t* matrix);
		
		/** Get matrix.
		 *
		 * Get matrix
		 *
		 * \param matrix Matrix.
		 */
		virtual void getMatrix(Matrix& matrix);
		
		/** Get target.
		 *
		 * Get target
		 *
		 * \return .
		 */
		virtual cairo_surface_t* getTarget();
		
		/** Get target.
		 *
		 * Get target
		 *
		 * \param surface Where to store the surface.
		 */
		virtual void getTarget(Surface& surface);
		
		/** Copy path.
		 *
		 * Copy path
		 *
		 * \return .
		 */
		virtual cairo_path_t* copyPath();
		
		/** Copy path.
		 *
		 * Copy path
		 *
		 * \param target Where to store the path.
		 */
		virtual void copyPath(Path& target);
		
		/** Copy path flat.
		 *
		 * Copy path flat
		 *
		 * \return .
		 */
		virtual cairo_path_t* copyPathFlat();
		
		/** Copy path flat.
		 *
		 * Copy path flat
		 *
		 * \param target Where to store the path.
		 */
		virtual void copyPathFlat(Path& target);
		
		/** Append path.
		 *
		 * Append path
		 *
		 * \param path Path.
		 */
		virtual void appendPath(cairo_path_t* path);
		
		/** Append path.
		 *
		 * Append path
		 *
		 * \param path Path.
		 */
		virtual void appendPath(Path& path);
		
		/** Status.
		 *
		 * Status
		 *
		 * \return .
		 */
		virtual cairo_status_t status();
		
		/** Status to string.
		 *
		 * Status to string
		 *
		 * \param status Status.
		 *
		 * \return .
		 */
		virtual std::string statusToString(cairo_status_t status);
		
		/** Assignment operator.
		 *
		 * Assign one cairo object to another Cairo object.
		 *
		 * \param newCairoContext Cairo context.
		 *
		 * \return The object itself.
		 */
		virtual CairoContext& operator=(const CairoContext& newCairoContext);
		
		/** Assignment operator.
		 *
		 * Assign a cairo context to this Cairo object.
		 *
		 * \param newCairoContext Cairo context.
		 *
		 * \return The object itself.
		 */
		virtual CairoContext& operator=(cairo_t* newCairoContext);
		
		/** Set cairo context.
		 *
		 * Set new value of cairo context.
		 *
		 * \param newCairoContext New value of cairo context.
		 */
		virtual void setCairoContext(cairo_t* newCairoContext);
		
		/** Get cairo context.
		 *
		 * \return Current value of cairo context.
		 */
		virtual cairo_t* getCairoContext() const;
};

/// @}

}

}

}

/** \file CairoContext.hpp
 * \brief Cairo context header.
 */
#endif
