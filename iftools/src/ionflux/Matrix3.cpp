/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix3.cpp                     Matrix (R3 x R3).
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

#include "ionflux/Matrix3.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

Matrix3::Matrix3()
{
	entry = new double[9];
	for (unsigned int i = 0; i < 9; i++)
		entry[i] = 0.0;
}

Matrix3::Matrix3(double initX11, double initX12, double initX13, 
	double initX21, double initX22, double initX23, double initX31, 
	double initX32, double initX33)
{
	entry = new double[9];
	setEntries(initX11, initX12, initX13, initX21, initX22, initX23, initX31, 
		initX32, initX33);
}

Matrix3::Matrix3(const Matrix3& initMat)
{
	entry = new double[9];
	*this = initMat;
}

Matrix3::Matrix3(const Vector3& initC1, const Vector3& initC2, const 
Vector3& initC3)
{
	entry = new double[9];
	setColumns(initC1, initC2, initC3);
}

Matrix3::Matrix3(const double* initEntry)
{
	entry = new double[9];
	setEntries(initEntry);
}

Matrix3::~Matrix3()
{
	if (entry != 0)
		delete[] entry;
	entry = 0;
}

void Matrix3::setEntries(double newX11, double newX12, double newX13, 
	double newX21, double newX22, double newX23, double newX31, double newX32, 
	double newX33)
{
	entry[0] = newX11;
	entry[1] = newX12;
	entry[2] = newX13;
	entry[3] = newX21;
	entry[4] = newX22;
	entry[5] = newX23;
	entry[6] = newX31;
	entry[7] = newX32;
	entry[8] = newX33;
}

void Matrix3::setEntries(const double* newEntry)
{
	for (unsigned int i = 0; i < 9; i++)
		entry[i] = newEntry[i];
}

void Matrix3::setColumns(const Vector3& newC1, const Vector3& newC2, 
	const Vector3& newC3)
{
	setColumn(0, newC1);
	setColumn(1, newC2);
	setColumn(2, newC3);
}

void Matrix3::setRows(const Vector3& newR1, const Vector3& newR2, 
	const Vector3& newR3)
{
	setRow(0, newR1);
	setRow(1, newR2);
	setRow(2, newR3);
}

void Matrix3::setEntry(int rowIndex, int colIndex, double newEntry)
{
	if ((rowIndex < 0) || (colIndex < 0) || (rowIndex > 2) || (colIndex > 2))
		return;
	entry[rowIndex * 3 + colIndex] = newEntry;
}

void Matrix3::setColumn(int colIndex, const Vector3& newCol)
{
	if ((colIndex < 0) || (colIndex > 2))
		return;
	for (unsigned int i = 0; i < 3; i++)
		entry[i * 3 + colIndex] = newCol[i];
}

void Matrix3::setRow(int rowIndex, const Vector3& newRow)
{
	if ((rowIndex < 0) || (rowIndex > 2))
		return;
	for (unsigned int i = 0; i < 3; i++)
		entry[rowIndex * 3 + i] = newRow[i];
}

Vector3 Matrix3::getColumn(int colIndex) const
{
	Vector3 result;
	if ((colIndex >= 0) || (colIndex <= 2))
		for (unsigned int i = 0; i < 3; i++)
			result.setComp(i, entry[i * 3 + colIndex]);
	return result;
}

Vector3 Matrix3::getRow(int rowIndex) const
{
	Vector3 result;
	if ((rowIndex >= 0) || (rowIndex <= 2))
		for (unsigned int i = 0; i < 3; i++)
			result.setComp(i, entry[rowIndex * 3 + i]);
    return result;
}

double Matrix3::getEntry(int rowIndex, int colIndex) const
{
	if ((rowIndex < 0) || (colIndex < 0) || (rowIndex > 2) || (colIndex > 2))
		return 0.0;
	return entry[rowIndex * 3 + colIndex];
}

Matrix3& Matrix3::operator=(const Matrix3& newMat)
{
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			entry[i * 3 + j] = newMat.getEntry(i, j);
	return *this;
}

Matrix3 Matrix3::operator+(const Matrix3& otherMat) const
{
	Matrix3 result;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			result.setEntry(i, j, entry[i * 3 + j] + otherMat.getEntry(i, j));
	return result;
}

Matrix3 Matrix3::operator-(const Matrix3& otherMat) const
{
	Matrix3 result;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			result.setEntry(i, j, entry[i * 3 + j] - otherMat.getEntry(i, j));
	return result;
}

Matrix3 Matrix3::operator*(const Matrix3& otherMat) const
{
	Matrix3 result;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			result.setEntry(i, j, getRow(i) * otherMat.getColumn(j));
	return result;
}

Matrix3& Matrix3::operator+=(const Matrix3& otherMat)
{
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			entry[i * 3 + j] += otherMat.getEntry(i, j);
	return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& otherMat)
{
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			entry[i * 3 + j] -= otherMat.getEntry(i, j);
	return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& otherMat)
{
	*this = *this * otherMat;
	return *this;
}

Matrix3& Matrix3::operator*=(double a)
{
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			entry[i * 3 + j] *= a;
	return *this;
}

Vector3 Matrix3::operator*(const Vector3& argVec) const
{
	Vector3 result;
	for (unsigned int i = 0; i < 3; i++)
		result.setComp(i, getRow(i) * argVec);
	return result;
}

Matrix3 Matrix3::operator*(double a) const
{
	Matrix3 result;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			result.setEntry(i, j, entry[i * 3 + j] * a);
	return result;
}

Vector3 Matrix3::operator[](int rowIndex) const
{
	return getRow(rowIndex);
}

std::string Matrix3::toString() const
{
	ostringstream result;
	result << "[";
	for (unsigned int i = 0; i < 3; i++)
	{
		result << getRow(i).toString();
		if (i < 2)
			result << ",";
	}
	result << "]";
	return result.str();
}

double Matrix3::getSubDet(int rowIndex, int colIndex) const
{
	if ((rowIndex < 0) || (colIndex < 0) || (rowIndex > 2) || (colIndex > 2))
		return 0.0;
	double result = 0.0;
	double *subMat2 = new double[4];
	int subIndex = 0;
	// Extract the (R2 x R2) submatrix to be used in the calculation.
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if ((i != rowIndex) && (j != colIndex))
			{
				subMat2[subIndex] = entry[i * 3 + j];
				subIndex++;
			}
	result = subMat2[0] * subMat2[3] - subMat2[2] * subMat2[1];
	delete[] subMat2;
	return result;
}

double Matrix3::getDet() const
{
	double result = 0.0;
	int signum = 1;
	for (unsigned int i = 0; i < 3; i++)
	{
		result += (signum * entry[i * 3] * getSubDet(i, 0));
		signum *= -1;
	}
	return result;
}

Matrix3 Matrix3::getAdjoint() const
{
	Matrix3 result;
	int signum = 1;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
		{
			result.setEntry(j, i, signum * getSubDet(i, j));
			signum *= -1;
		}
	return result;
}

Matrix3& Matrix3::transpose()
{
	Matrix3 result;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			result.setEntry(j, i, entry[i * 3 + j]);
	*this = result;
	return *this;
}

Matrix3& Matrix3::invert()
{
	Matrix3 adj = getAdjoint();
	adj *= (1.0 / getDet());
	*this = adj;
	return *this;
}

Matrix3& Matrix3::clear()
{
	for (unsigned int i = 0; i < 9; i++)
		entry[i] = 0.0;
	return *this;
}

Matrix3& Matrix3::setIdentity()
{
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			if (i != j)
				entry[i * 3 + j] = 0.0;
			else
				entry[i * 3 + j] = 1.0;
	return *this;
}

Matrix3& Matrix3::setRotateX(double phi)
{
	setEntries(
		1.0, 0.0, 0.0,
		0.0, cos(phi), sin(phi),
		0.0, -sin(phi), cos(phi));
	return *this;
}

Matrix3& Matrix3::setRotateY(double phi)
{
	setEntries(
		cos(phi), 0.0, -sin(phi),
		0.0, 1.0, 0.0,
		sin(phi), 0.0, cos(phi));
	return *this;
}

Matrix3& Matrix3::setRotateZ(double phi)
{
	setEntries(
		cos(phi), sin(phi), 0.0,
		-sin(phi), cos(phi), 0.0,
		0.0, 0.0, 1.0);
	return *this;
}

Matrix3& Matrix3::setScale(double scaleX, double scaleY, double scaleZ)
{
	setEntries(
		scaleX, 0.0, 0.0,
		0.0, scaleY, 0.0,
		0.0, 0.0, scaleZ);
	return *this;
}

void Matrix3::setX11(double newX11)
{
	entry[0] = newX11;
}

void Matrix3::setX12(double newX12)
{
	entry[1] = newX12;
}

void Matrix3::setX13(double newX13)
{
	entry[2] = newX13;
}

void Matrix3::setX21(double newX21)
{
	entry[3] = newX21;
}

void Matrix3::setX22(double newX22)
{
	entry[4] = newX22;
}

void Matrix3::setX23(double newX23)
{
	entry[5] = newX23;
}

void Matrix3::setX31(double newX31)
{
	entry[6] = newX31;
}

void Matrix3::setX32(double newX32)
{
	entry[7] = newX32;
}

void Matrix3::setX33(double newX33)
{
	entry[8] = newX33;
}

double Matrix3::getX11() const
{
	return entry[0];
}

double Matrix3::getX12() const
{
	return entry[1];
}

double Matrix3::getX13() const
{
	return entry[2];
}

double Matrix3::getX21() const
{
	return entry[3];
}

double Matrix3::getX22() const
{
	return entry[4];
}

double Matrix3::getX23() const
{
	return entry[5];
}

double Matrix3::getX31() const
{
	return entry[6];
}

double Matrix3::getX32() const
{
	return entry[7];
}

double Matrix3::getX33() const
{
	return entry[8];
}

Matrix3 operator*(double a, const Matrix3& mat)
{
	return mat * a;
}

}

}

/** \file Matrix3.cpp
 * \brief Matrix (R3 x R3) implementation.
 */
