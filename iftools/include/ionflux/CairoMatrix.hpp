#ifndef IONFLUX_TOOLS_CAIRO_MATRIX
#define IONFLUX_TOOLS_CAIRO_MATRIX
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoMatrix.hpp                        Cairo matrix.
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

#include "cairo.h"
#include "ionflux/Matrix3.hpp"

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

/** A point in R2.
 * \ingroup cairo
 */
struct Point
{
	/// X coordinate.
	double x;
	/// Y coordinate.
	double y;
};

/** A distance in R2.
 * \ingroup cairo
 */
struct Distance
{
	/// X distance.
	double dx;
	/// Y distance.
	double dy;
};

/** Cairo matrix.
 * \ingroup cairo
 *
 * A wrapper for the Cairo vector graphics API matrix type (see 
 * http://www.cairographics.org/).
 * 
 * \note Not all features of Cairo are supported yet by this wrapper.
 */
class Matrix
: public Ionflux::Tools::Matrix3
{
	private:
		
	protected:
		
	public:
		/** Constructor.
		 *
		 * Construct new Matrix object.
		 */
		Matrix();
		
		/** Constructor.
		 *
		 * Construct new Matrix object.
		 *
		 * \param initMatrix Cairo matrix.
		 */
		Matrix(const Matrix& initMatrix);
		
		/** Constructor.
		 *
		 * Construct new Matrix object.
		 *
		 * \param initMatrix Cairo matrix.
		 */
		Matrix(const cairo_matrix_t& initMatrix);
		
		/** Constructor.
		 *
		 * Construct new Matrix object.
		 *
		 * \param xx Xx.
		 * \param yx Yx.
		 * \param xy Xy.
		 * \param yy Yy.
		 * \param x0 X0.
		 * \param y0 Y0.
		 */
		Matrix(double xx, double yx, double xy, double yy, double x0, double y0);
		
		/** Destructor.
		 *
		 * Destruct Matrix object.
		 */
		virtual ~Matrix();
		
		/** Matrix identity.
		 *
		 * Matrix identity
		 */
		 void initIdentity();
		
		/** Matrix translate.
		 *
		 * Matrix translate
		 *
		 * \param tx Tx.
		 * \param ty Ty.
		 */
		 void initTranslate(double tx, double ty);
		
		/** Matrix scale.
		 *
		 * Matrix scale
		 *
		 * \param sx Sx.
		 * \param sy Sy.
		 */
		 void initScale(double sx, double sy);
		
		/** Matrix rotate.
		 *
		 * Matrix rotate
		 *
		 * \param radians Radians.
		 */
		 void initRotate(double radians);
		
		/** Matrix.
		 *
		 * Matrix
		 *
		 * \param tx Tx.
		 * \param ty Ty.
		 */
		 void translate(double tx, double ty);
		
		/** Matrix.
		 *
		 * Matrix
		 *
		 * \param sx Sx.
		 * \param sy Sy.
		 */
		 void scale(double sx, double sy);
		
		/** Matrix.
		 *
		 * Matrix
		 *
		 * \param radians Radians.
		 */
		 void rotate(double radians);
		
		/** Transform distance.
		 *
		 * Transform distance.
		 *
		 * \param distance Distance.
		 */
		 void transformDistance(Distance& distance);
		
		/** Transform point.
		 *
		 * Transform point.
		 *
		 * \param point Point.
		 */
		 void transformPoint(Point& point);
		
		/** Assignment operator.
		 *
		 * Assign a matrix (R3) to a Cairo matrix.
		 *
		 * \param newMatrix Matrix (R3).
		 *
		 * \return The object itself.
		 */
		virtual Matrix& operator=(const Matrix3& newMatrix);
		
		/** Assignment operator.
		 *
		 * Assign a matrix to another matrix.
		 *
		 * \param newCairoMatrix Cairo matrix.
		 *
		 * \return The object itself.
		 */
		virtual Matrix& operator=(const Matrix& newCairoMatrix);
		
		/** Assignment operator.
		 *
		 * Assign a cairo matrix to this matrix object.
		 *
		 * \param newCairoMatrix Cairo matrix.
		 *
		 * \return The object itself.
		 */
		virtual Matrix& operator=(const cairo_matrix_t& newCairoMatrix);
		
		/** Convert to Cairo matrix.
		 *
		 * Convert the matrix to a Cairo matrix.
		 *
		 * \param cairoMatrix Where to store the Cairo matrix.
		 */
		 void toCairoMatrix(cairo_matrix_t& cairoMatrix) const;
};

}

}

}

/** \file CairoMatrix.hpp
 * \brief Cairo matrix header.
 */
#endif
