/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3.cpp                     Vector (R3).
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

#include "ionflux/Vector3.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

Vector3::Vector3()
{
	comp = new double[3];
	for (unsigned int i = 0; i < 3; i++)
		comp[i] = 0.0;
}

Vector3::Vector3(double initX1, double initX2, double initX3)
{
	comp = new double[3];
	setComps(initX1, initX2, initX3);
}

Vector3::Vector3(const Vector3& initVec)
{
	comp = new double[3];
	*this = initVec;
}

Vector3::Vector3(const double* initComp)
{
	comp = new double[3];
	setComps(initComp);
}

Vector3::~Vector3()
{
	if (comp != 0)
		delete[] comp;
	comp = 0;
}

void Vector3::setComps(double newX1, double newX2, double newX3)
{
	comp[0] = newX1;
	comp[1] = newX2;
	comp[2] = newX3;
}

void Vector3::setComps(const double* newComp)
{
	if (newComp == 0)
		return;
	for (unsigned int i = 0; i < 3; i++)
		comp[i] = newComp[i];
}

void Vector3::setComp(int compIndex, double newComp)
{
	comp[compIndex] = newComp;
}

std::string Vector3::toString() const
{
	ostringstream output;
	output << "(" << comp[0] << "," << comp[1] << "," << comp[2] << ")";
	return output.str();
}

Vector3& Vector3::operator=(const Vector3& newVec)
{
	for (unsigned int i = 0; i < 3; i++)
		comp[i] = newVec[i];
	return *this;
}

Vector3 Vector3::operator+(const Vector3& otherVec) const
{
	Vector3 result;
	for (unsigned int i = 0; i < 3; i++)
		result.setComp(i, comp[i] + otherVec[i]);
	return result;
}

Vector3 Vector3::operator-(const Vector3& otherVec) const
{
	Vector3 result;
	for (unsigned int i = 0; i < 3; i++)
		result.setComp(i, comp[i] - otherVec[i]);
	return result;
}

Vector3& Vector3::operator+=(const Vector3& otherVec)
{
	for (unsigned int i = 0; i < 3; i++)
		comp[i] += otherVec[i];
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& otherVec)
{
	for (unsigned int i = 0; i < 3; i++)
		comp[i] -= otherVec[i];
	return *this;
}

double Vector3::operator*(const Vector3& otherVec) const
{
	double result = 0.0;
	for (unsigned int i = 0; i < 3; i++)
		result += (comp[i] * otherVec[i]);
	return result;
}

Vector3 Vector3::operator*(double a) const
{
	Vector3 result;
	for (unsigned int i = 0; i < 3; i++)
		result.setComp(i, comp[i] * a);
	return result;
}

Vector3& Vector3::operator*=(double a)
{
	for (unsigned int i = 0; i < 3; i++)
		comp[i] *= a;
	return *this;
}

double Vector3::operator[](int compIndex) const
{
	return comp[compIndex];
}

void Vector3::setX1(double newX1)
{
	comp[0] = newX1;
}

void Vector3::setX2(double newX2)
{
	comp[1] = newX2;
}

void Vector3::setX3(double newX3)
{
	comp[2] = newX3;
}

double Vector3::getX1() const
{
	return comp[0];
}

double Vector3::getX2() const
{
	return comp[1];
}

double Vector3::getX3() const
{
	return comp[2];
}

Vector3 operator*(double a, const Vector3& vec)
{
	return vec * a;
}

}

}

/** \file Vector3.cpp
 * \brief Vector (R3) implementation.
 */
