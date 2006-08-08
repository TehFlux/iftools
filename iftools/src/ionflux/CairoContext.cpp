/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoContext.cpp                Cairo context.
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

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

CairoContext::CairoContext()
: cairoContext(0)
{
	// TODO: Nothing ATM. ;-)
}

CairoContext::CairoContext(const CairoContext& initCairoContext)
{
	setCairoContext(initCairoContext.getCairoContext());
}

CairoContext::CairoContext(cairo_t* initCairoContext)
{
	setCairoContext(initCairoContext);
}

CairoContext::CairoContext(cairo_surface_t* initSurface)
{
	cairoContext = cairo_create(initSurface);
}

CairoContext::CairoContext(Surface& initSurface)
{
	cairoContext = cairo_create(initSurface.getCairoSurface());
}

CairoContext::~CairoContext()
{
	if (cairoContext != 0)
		cairo_destroy(cairoContext);
	cairoContext = 0;
}

void CairoContext::reference()
{
	cairo_reference(cairoContext);
}

void CairoContext::destroy()
{
	cairo_destroy(cairoContext);
}

void CairoContext::save()
{
	cairo_save(cairoContext);
}

void CairoContext::restore()
{
	cairo_restore(cairoContext);
}

void CairoContext::setOperator(cairo_operator_t op)
{
	cairo_set_operator(cairoContext, op);
}

void CairoContext::setSource(cairo_pattern_t* source)
{
	cairo_set_source(cairoContext, source);
}

void CairoContext::setSource(const Pattern& source)
{
	setSource(source.getCairoPattern());
}

void CairoContext::setSourceRgb(double red, double green, double blue)
{
	cairo_set_source_rgb(cairoContext, red, green, blue);
}

void CairoContext::setSourceRgba(double red, double green, double blue, 
double alpha)
{
	cairo_set_source_rgba(cairoContext, red, green, blue, alpha);
}

void CairoContext::setSourceColor(const Ionflux::Tools::Color& color)
{
	setSourceRgba(color.red, color.green, color.blue, color.alpha);
}

void CairoContext::setSourceSurface(cairo_surface_t* surface, double x, 
double y)
{
	cairo_set_source_surface(cairoContext, surface, x, y);
}

void CairoContext::setSourceSurface(Surface& surface, double x, double y)
{
	cairo_set_source_surface(cairoContext, surface.getCairoSurface(), x, y);
}

void CairoContext::setTolerance(double tolerance)
{
	cairo_set_tolerance(cairoContext, tolerance);
}

void CairoContext::setFillRule(cairo_fill_rule_t fill_rule)
{
	cairo_set_fill_rule(cairoContext, fill_rule);
}

void CairoContext::setLineWidth(double width)
{
	cairo_set_line_width(cairoContext, width);
}

void CairoContext::setLineCap(cairo_line_cap_t line_cap)
{
	cairo_set_line_cap(cairoContext, line_cap);
}

void CairoContext::setLineJoin(cairo_line_join_t line_join)
{
	cairo_set_line_join(cairoContext, line_join);
}

void CairoContext::setDash(double* dashes, int ndash, double offset)
{
	cairo_set_dash(cairoContext, dashes, ndash, offset);
}

void CairoContext::setMiterLimit(double limit)
{
	cairo_set_miter_limit(cairoContext, limit);
}

void CairoContext::translate(double tx, double ty)
{
	cairo_translate(cairoContext, tx, ty);
}

void CairoContext::scale(double sx, double sy)
{
	cairo_scale(cairoContext, sx, sy);
}

void CairoContext::rotate(double angle)
{
	cairo_rotate(cairoContext, angle);
}

void CairoContext::transform(const cairo_matrix_t* matrix)
{
	cairo_transform(cairoContext, matrix);
}

void CairoContext::transform(const Matrix& matrix)
{
	cairo_matrix_t cairoMatrix;
	matrix.toCairoMatrix(cairoMatrix);
	transform(&cairoMatrix);
}

void CairoContext::setMatrix(const cairo_matrix_t* matrix)
{
	cairo_set_matrix(cairoContext, matrix);
}

void CairoContext::setMatrix(const Matrix& matrix)
{
	cairo_matrix_t cairoMatrix;
	matrix.toCairoMatrix(cairoMatrix);
	setMatrix(&cairoMatrix);
}

void CairoContext::identityMatrix()
{
	cairo_identity_matrix(cairoContext);
}

void CairoContext::userToDevice(double* x, double* y)
{
	cairo_user_to_device(cairoContext, x, y);
}

void CairoContext::userToDeviceDistance(double* dx, double* dy)
{
	cairo_user_to_device_distance(cairoContext, dx, dy);
}

void CairoContext::deviceToUser(double* x, double* y)
{
	cairo_device_to_user(cairoContext, x, y);
}

void CairoContext::deviceToUserDistance(double* dx, double* dy)
{
	cairo_device_to_user_distance(cairoContext, dx, dy);
}

void CairoContext::newPath()
{
	cairo_new_path(cairoContext);
}

void CairoContext::moveTo(double x, double y)
{
	cairo_move_to(cairoContext, x, y);
}

void CairoContext::lineTo(double x, double y)
{
	cairo_line_to(cairoContext, x, y);
}

void CairoContext::curveTo(double x1, double y1, double x2, double y2, 
double x3, double y3)
{
	cairo_curve_to(cairoContext, x1, y1, x2, y2, x3, y3);
}

void CairoContext::arc(double xc, double yc, double radius, double angle1, 
double angle2)
{
	cairo_arc(cairoContext, xc, yc, radius, angle1, angle2);
}

void CairoContext::arcNegative(double xc, double yc, double radius, double 
angle1, double angle2)
{
	cairo_arc_negative(cairoContext, xc, yc, radius, angle1, angle2);
}

void CairoContext::relMoveTo(double dx, double dy)
{
	cairo_rel_move_to(cairoContext, dx, dy);
}

void CairoContext::relLineTo(double dx, double dy)
{
	cairo_rel_line_to(cairoContext, dx, dy);
}

void CairoContext::relCurveTo(double dx1, double dy1, double dx2, double 
dy2, double dx3, double dy3)
{
	cairo_rel_curve_to(cairoContext, dx1, dy1, dx2, dy2, dx3, dy3);
}

void CairoContext::rectangle(double x, double y, double width, double 
height)
{
	cairo_rectangle(cairoContext, x, y, width, height);
}

void CairoContext::closePath()
{
	cairo_close_path(cairoContext);
}

void CairoContext::paint()
{
	cairo_paint(cairoContext);
}

void CairoContext::paintWithAlpha(double alpha)
{
	cairo_paint_with_alpha(cairoContext, alpha);
}

void CairoContext::mask(cairo_pattern_t* pattern)
{
	cairo_mask(cairoContext, pattern);
}

void CairoContext::mask(const Pattern& pattern)
{
	mask(pattern.getCairoPattern());
}

void CairoContext::maskSurface(cairo_surface_t* surface, double surface_x, 
double surface_y)
{
	cairo_mask_surface(cairoContext, surface, surface_x, surface_y);
}

void CairoContext::maskSurface(Surface& surface, double surface_x, double 
surface_y)
{
	cairo_mask_surface(cairoContext, surface.getCairoSurface(), surface_x, 
		surface_y);
}

void CairoContext::stroke()
{
	cairo_stroke(cairoContext);
}

void CairoContext::strokePreserve()
{
	cairo_stroke_preserve(cairoContext);
}

void CairoContext::fill()
{
	cairo_fill(cairoContext);
}

void CairoContext::fillPreserve()
{
	cairo_fill_preserve(cairoContext);
}

void CairoContext::copyPage()
{
	cairo_copy_page(cairoContext);
}

void CairoContext::showPage()
{
	cairo_show_page(cairoContext);
}

cairo_bool_t CairoContext::inStroke(double x, double y)
{
	return cairo_in_stroke(cairoContext, x, y);
}

cairo_bool_t CairoContext::inFill(double x, double y)
{
	return cairo_in_fill(cairoContext, x, y);
}

void CairoContext::strokeExtents(double* x1, double* y1, double* x2, 
double* y2)
{
	cairo_stroke_extents(cairoContext, x1, y1, x2, y2);
}

void CairoContext::fillExtents(double* x1, double* y1, double* x2, double* 
y2)
{
	cairo_fill_extents(cairoContext, x1, y1, x2, y2);
}

void CairoContext::resetClip()
{
	cairo_reset_clip(cairoContext);
}

void CairoContext::clip()
{
	cairo_clip(cairoContext);
}

void CairoContext::clipPreserve()
{
	cairo_clip_preserve(cairoContext);
}

void CairoContext::selectFontFace(const std::string& family, cairo_font_slant_t 
slant, cairo_font_weight_t weight)
{
	cairo_select_font_face(cairoContext, family.c_str(), slant, weight);
}

void CairoContext::setFontSize(double size)
{
	cairo_set_font_size(cairoContext, size);
}

void CairoContext::setFontMatrix(const cairo_matrix_t* matrix)
{
	cairo_set_font_matrix(cairoContext, matrix);
}

void CairoContext::setFontMatrix(const Matrix& matrix)
{
	cairo_matrix_t cairoMatrix;
	matrix.toCairoMatrix(cairoMatrix);
	setFontMatrix(&cairoMatrix);
}

void CairoContext::getFontMatrix(cairo_matrix_t* matrix)
{
	cairo_get_font_matrix(cairoContext, matrix);
}

void CairoContext::getFontMatrix(Matrix& matrix)
{
	cairo_matrix_t cairoMatrix;
	getFontMatrix(&cairoMatrix);
	matrix = cairoMatrix;
}

void CairoContext::showText(const std::string& utf8)
{
	cairo_show_text(cairoContext, utf8.c_str());
}

void CairoContext::showGlyphs(cairo_glyph_t* glyphs, int num_glyphs)
{
	cairo_show_glyphs(cairoContext, glyphs, num_glyphs);
}

cairo_font_face_t* CairoContext::getFontFace()
{
	return cairo_get_font_face(cairoContext);
}

void CairoContext::fontExtents(cairo_font_extents_t* extents)
{
	cairo_font_extents(cairoContext, extents);
}

void CairoContext::setFontFace(cairo_font_face_t* font_face)
{
	cairo_set_font_face(cairoContext, font_face);
}

void CairoContext::textExtents(const std::string& utf8, cairo_text_extents_t* 
extents)
{
	cairo_text_extents(cairoContext, utf8.c_str(), extents);
}

void CairoContext::glyphExtents(cairo_glyph_t* glyphs, int num_glyphs, 
cairo_text_extents_t* extents)
{
	cairo_glyph_extents(cairoContext, glyphs, num_glyphs, extents);
}

void CairoContext::textPath(const std::string& utf8)
{
	cairo_text_path(cairoContext, utf8.c_str());
}

void CairoContext::glyphPath(cairo_glyph_t* glyphs, int num_glyphs)
{
	cairo_glyph_path(cairoContext, glyphs, num_glyphs);
}

cairo_operator_t CairoContext::getOperator()
{
	return cairo_get_operator(cairoContext);
}

cairo_pattern_t* CairoContext::getSource()
{
	return cairo_get_source(cairoContext);
}

double CairoContext::getTolerance()
{
	return cairo_get_tolerance(cairoContext);
}

void CairoContext::getCurrentPoint(double* x, double* y)
{
	cairo_get_current_point(cairoContext, x, y);
}

cairo_fill_rule_t CairoContext::getFillRule()
{
	return cairo_get_fill_rule(cairoContext);
}

double CairoContext::getLineWidth()
{
	return cairo_get_line_width(cairoContext);
}

cairo_line_cap_t CairoContext::getLineCap()
{
	return cairo_get_line_cap(cairoContext);
}

cairo_line_join_t CairoContext::getLineJoin()
{
	return cairo_get_line_join(cairoContext);
}

double CairoContext::getMiterLimit()
{
	return cairo_get_miter_limit(cairoContext);
}

void CairoContext::getMatrix(cairo_matrix_t* matrix)
{
	cairo_get_matrix(cairoContext, matrix);
}

void CairoContext::getMatrix(Matrix& matrix)
{
	cairo_matrix_t cairoMatrix;
	getMatrix(&cairoMatrix);
	matrix = cairoMatrix;
}

cairo_surface_t* CairoContext::getTarget()
{
	return cairo_get_target(cairoContext);
}

void CairoContext::getTarget(Surface& surface)
{
	surface.setCairoSurface(getTarget());
}

cairo_path_t* CairoContext::copyPath()
{
	return cairo_copy_path(cairoContext);
}

void CairoContext::copyPath(Path& target)
{
	target = copyPath();
}

cairo_path_t* CairoContext::copyPathFlat()
{
	return cairo_copy_path_flat(cairoContext);
}

void CairoContext::copyPathFlat(Path& target)
{
	target = copyPathFlat();
}

void CairoContext::appendPath(cairo_path_t* path)
{
	cairo_append_path(cairoContext, path);
}

void CairoContext::appendPath(Path& path)
{
	cairo_append_path(cairoContext, path.getCairoPath());
}

cairo_status_t CairoContext::status()
{
	return cairo_status(cairoContext);
}

std::string CairoContext::statusToString(cairo_status_t status)
{
	return cairo_status_to_string(status);
}

CairoContext& CairoContext::operator=(const CairoContext& newCairoContext)
{
	setCairoContext(newCairoContext.getCairoContext());
	return *this;
}

CairoContext& CairoContext::operator=(cairo_t* newCairoContext)
{
	setCairoContext(newCairoContext);
	return *this;
}

void CairoContext::setCairoContext(cairo_t* newCairoContext)
{
	if (cairoContext != 0)
		destroy();
	cairoContext = newCairoContext;
	if (cairoContext != 0)
		reference();
}

cairo_t* CairoContext::getCairoContext() const
{
	return cairoContext;
}

}

}

}

/** \file CairoContext.cpp
 * \brief Cairo context implementation.
 */
