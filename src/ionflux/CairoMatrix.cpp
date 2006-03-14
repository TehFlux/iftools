/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CairoCairoMatrix.cpp                      Cairo matrix.
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

#include "ionflux/CairoMatrix.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

namespace Cairo
{

Matrix::Matrix()
{
	// TODO: Nothing ATM. ;-)
}

Matrix::Matrix(const Matrix& initMatrix)
{
	*this = initMatrix;
}

Matrix::Matrix(const cairo_matrix_t& initMatrix)
{
	*this = initMatrix;
}

Matrix::Matrix(double xx, double yx, double xy, double yy, double x0, 
double y0)
{
	setX11(xx);
	setX12(yx);
	setX13(x0);
	setX21(xy);
	setX22(yy);
	setX23(y0);
	setX33(1.0);
}

Matrix::~Matrix()
{
	// TODO: Nothing ATM. ;-)
}

void Matrix::initIdentity()
{
	setIdentity();
}

void Matrix::initTranslate(double tx, double ty)
{
	setIdentity();
	setX13(tx);
	setX23(ty);
}

void Matrix::initScale(double sx, double sy)
{
	setScale(sx, sy, 1.0);
}

void Matrix::initRotate(double radians)
{
	setRotateZ(radians);
}

void Matrix::translate(double tx, double ty)
{
	Matrix3 translate;
	translate.setIdentity();
	translate.setX13(tx);
	translate.setX23(ty);
	*this = translate * (*this);
}

void Matrix::scale(double sx, double sy)
{
	Matrix3 scale;
	scale.setScale(sx, sy, 1.0);
	*this = scale * (*this);
}

void Matrix::rotate(double radians)
{
	Matrix3 rotate;
	rotate.setRotateZ(radians);
	*this = rotate * (*this);
}

void Matrix::transformDistance(Distance& distance)
{
	Vector3 x0;
	Vector3 x1;
	Vector3 diff;
	x1.setX1(distance.dx);
	x1.setX2(distance.dy);
	x1.setX3(1.0);
	x0 = (*this) * x0;
	x1 = (*this) * x1;
	diff = x1 - x0;
	distance.dx = diff.getX1();
	distance.dy = diff.getX2();
}

void Matrix::transformPoint(Point& point)
{
	Vector3 x0;
	x0.setX1(point.x);
	x0.setX2(point.y);
	x0.setX3(1.0);
	x0 = (*this) * x0;
	point.x = x0.getX1();
	point.y = x0.getX2();
}

Matrix& Matrix::operator=(const Matrix3& newMatrix)
{
	setX11(newMatrix.getX11());
	setX12(newMatrix.getX12());
	setX13(newMatrix.getX13());
	setX21(newMatrix.getX21());
	setX22(newMatrix.getX22());
	setX23(newMatrix.getX23());
	setX31(newMatrix.getX31());
	setX32(newMatrix.getX32());
	setX33(newMatrix.getX33());
	return *this;
}

Matrix& Matrix::operator=(const Matrix& newCairoMatrix)
{
	setX11(newCairoMatrix.getX11());
	setX12(newCairoMatrix.getX12());
	setX13(newCairoMatrix.getX13());
	setX21(newCairoMatrix.getX21());
	setX22(newCairoMatrix.getX22());
	setX23(newCairoMatrix.getX23());
	setX31(newCairoMatrix.getX31());
	setX32(newCairoMatrix.getX32());
	setX33(newCairoMatrix.getX33());
	return *this;
}

Matrix& Matrix::operator=(const cairo_matrix_t& newCairoMatrix)
{
	setIdentity();
	setX11(newCairoMatrix.xx);
	setX12(newCairoMatrix.yx);
	setX13(newCairoMatrix.x0);
	setX21(newCairoMatrix.xy);
	setX22(newCairoMatrix.yy);
	setX23(newCairoMatrix.y0);
	return *this;
}

void Matrix::toCairoMatrix(cairo_matrix_t& cairoMatrix) const
{
	cairoMatrix.xx = getX11();
	cairoMatrix.yx = getX12();
	cairoMatrix.x0 = getX13();
	cairoMatrix.xy = getX21();
	cairoMatrix.yy = getX22();
	cairoMatrix.y0 = getX23();
}

}

}

}

/** \file CairoMatrix.cpp
 * \brief Cairo matrix implementation.
 */
