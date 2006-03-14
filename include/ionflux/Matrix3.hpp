#ifndef IONFLUX_TOOLS_MATRIX3
#define IONFLUX_TOOLS_MATRIX3
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Matrix3.hpp                       Matrix (R3 x R3).
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
#include <iostream>
#include <sstream>
#include <math.h>
#include "ionflux/Vector3.hpp"
#include "ionflux/ManagedObject.hpp"

namespace Ionflux
{

namespace Tools
{

/** Matrix (R3 x R3).
 * \ingroup vecmath
 *
 * A matrix in three dimensional space.
 */
class Matrix3
: public ManagedObject
{
	protected:
		/// Entries.
		double* entry;
		
	public:
		/** Constructor.
		 *
		 * Construct new Matrix3 object.
		 */
		Matrix3();
		
		/** Constructor.
		 *
		 * Construct new Matrix3 object.
		 *
		 * \param initX11 x11 entry.
		 * \param initX12 x12 entry.
		 * \param initX13 x13 entry.
		 * \param initX21 x21 entry.
		 * \param initX22 x22 entry.
		 * \param initX23 x23 entry.
		 * \param initX31 x31 entry.
		 * \param initX32 x32 entry.
		 * \param initX33 x33 entry.
		 */
		Matrix3(double initX11, double initX12, double initX13, double initX21, 
		double initX22, double initX23, double initX31, double initX32, double 
		initX33);
		
		/** Constructor.
		 *
		 * Construct new Matrix3 object.
		 *
		 * \param initMat Matrix (R3 x R3).
		 */
		Matrix3(const Matrix3& initMat);
		
		/** Constructor.
		 *
		 * Construct new Matrix3 object.
		 *
		 * \param initC1 First column vector.
		 * \param initC2 Second column vector.
		 * \param initC3 Third column vector.
		 */
		Matrix3(const Vector3& initC1, const Vector3& initC2, const Vector3& 
		initC3);
		
		/** Constructor.
		 *
		 * Construct new Matrix3 object.
		 *
		 * \param initEntry Array of matrix entries.
		 */
		Matrix3(const double* initEntry);
		
		/** Destructor.
		 *
		 * Destruct Matrix3 object.
		 */
		virtual ~Matrix3();
		
		/** Set entries.
		 *
		 * Set the entries of the matrix.
		 *
		 * \param newX11 x11 entry.
		 * \param newX12 x12 entry.
		 * \param newX13 x13 entry.
		 * \param newX21 x21 entry.
		 * \param newX22 x22 entry.
		 * \param newX23 x23 entry.
		 * \param newX31 x31 entry.
		 * \param newX32 x32 entry.
		 * \param newX33 x33 entry.
		 */
		virtual void setEntries(double newX11, double newX12, double newX13, 
			double newX21, double newX22, double newX23, double newX31, 
			double newX32, double newX33);
		
		/** Set entries.
		 *
		 * Set the entries of the matrix. 
		 * 
		 * \note \c newEntry is expected to have a size of at least 9.
		 *
		 * \param newEntry Array of entries.
		 */
		virtual void setEntries(const double* newEntry);
		
		/** Set column vectors.
		 *
		 * Set the column vectors of the matrix.
		 *
		 * \param newC1 First column vector.
		 * \param newC2 Second column vector.
		 * \param newC3 Third column vector.
		 */
		virtual void setColumns(const Vector3& newC1, const Vector3& newC2, 
			const Vector3& newC3);
		
		/** Set row vectors.
		 *
		 * Set the row vectors of the matrix.
		 *
		 * \param newR1 First row vector.
		 * \param newR2 Second row vector.
		 * \param newR3 Third row vector.
		 */
		virtual void setRows(const Vector3& newR1, const Vector3& newR2, 
			const Vector3& newR3);
		
		/** Set entry.
		 *
		 * Set the specified entry of the matrix. 
		 * 
		 * \note If either \c rowIndex or \c colIndex is out of range, this 
		 * function does nothing.
		 *
		 * \param rowIndex Row index (0...2).
		 * \param colIndex Column index (0...2).
		 * \param newEntry New value of entry.
		 */
		virtual void setEntry(int rowIndex, int colIndex, double newEntry);
		
		/** Set column vector.
		 *
		 * Set the specified column vector of the matrix.
		 *
		 * \note If \c colIndex is out of range, this function does nothing.
		 *
		 * \param colIndex Column index (0...2).
		 * \param newCol Column vector.
		 */
		virtual void setColumn(int colIndex, const Vector3& newCol);
		
		/** Set row vector.
		 *
		 * Set the specified row vector of the matrix.
		 *
		 * \note If \c rowIndex is out of range, this function does nothing.
		 *
		 * \param rowIndex Row index (0...2).
		 * \param newRow Row vector.
		 */
		virtual void setRow(int rowIndex, const Vector3& newRow);
		
		/** Get column vector.
		 *
		 * Get the specified column vector of the matrix.
		 *
		 * \note If \c colIndex is out of range, this function returns the null
		 * vector.
		 *
		 * \param colIndex Column index (0...2).
		 *
		 * \return Column vector.
		 */
		virtual Vector3 getColumn(int colIndex) const;
		
		/** Get row vector.
		 *
		 * Get the specified row vector of the matrix.
		 *
		 * \note If \c rowIndex is out of range, this function returns the null
		 * vector.
		 *
		 * \param rowIndex Row index (0...2).
		 *
		 * \return Row vector.
		 */
		virtual Vector3 getRow(int rowIndex) const;
		
		/** Get entry.
		 *
		 * Get the specified entry of the matrix. 
		 * 
		 * \note If either \c rowIndex or \c colIndex is out of range, this 
		 * function does nothing.
		 *
		 * \param rowIndex Row index (0...2).
		 * \param colIndex Column index (0...2).
		 *
		 * \return Matrix entry.
		 */
		virtual double getEntry(int rowIndex, int colIndex) const;
		
		/** Assignment operator.
		 *
		 * Assign one matrix to another matrix.
		 *
		 * \param newMat Matrix (R3 x R3).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& operator=(const Matrix3& newMat);
		
		/** Add operator.
		 *
		 * Add one matrix to another matrix.
		 *
		 * \param otherMat Matrix (R3 x R3).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3 operator+(const Matrix3& otherMat) const;
		
		/** Subtract operator.
		 *
		 * Subtract one matrix from another matrix.
		 *
		 * \param otherMat Matrix (R3 x R3).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3 operator-(const Matrix3& otherMat) const;
		
		/** Multiply operator.
		 *
		 * Calculate the product of two matrices.
		 *
		 * \param otherMat Matrix (R3 x R3).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3 operator*(const Matrix3& otherMat) const;
		
		/** Add operator.
		 *
		 * Add one matrix to another matrix.
		 *
		 * \param otherMat Matrix (R3 x R3).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& operator+=(const Matrix3& otherMat);
		
		/** Subtract operator.
		 *
		 * Subtract one matrix from another matrix.
		 *
		 * \param otherMat Matrix (R3 x R3).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& operator-=(const Matrix3& otherMat);
		
		/** Multiply operator.
		 *
		 * Calculate the product of two matrices.
		 *
		 * \param otherMat Matrix (R3 x R3).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& operator*=(const Matrix3& otherMat);
		
		/** Multiply operator.
		 *
		 * Calculate the product of the matrix and a scalar.
		 *
		 * \param a Scalar.
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& operator*=(double a);
		
		/** Multiply operator.
		 *
		 * Apply a matrix to a vector.
		 *
		 * \param argVec Vector (R3).
		 *
		 * \return Result of the operation.
		 */
		virtual Vector3 operator*(const Vector3& argVec) const;
		
		/** Multiply operator.
		 *
		 * Calculate the product of the matrix and a scalar.
		 *
		 * \param a Scalar.
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3 operator*(double a) const;
		
		/** Subscript operator.
		 *
		 * Access a row vector of the matrix.
		 * 
		 * \note If \c rowIndex is out of range, the function returns the null 
		 * vector.
		 *
		 * \param rowIndex Row index (0...2).
		 *
		 * \return Row vector.
		 */
		virtual Vector3 operator[](int rowIndex) const;
		
		/** Create string representation.
		 *
		 * Create a string representation of the matrix (i.e. 
		 * "[&lt;R1&gt;,&lt;R2&gt;,&lt;R3&gt;]", R1...R3 being the string 
		 * representations of the row vectors).
		 *
		 * \return String representation.
		 */
		virtual std::string toString() const;
		
		/** Calculate subdeterminant.
		 *
		 * Calculate a subdeterminant of the matrix. A subdeterminant is
		 * obtained by calculating the determinant of the matrix resulting
		 * from removing a row and a column from the original matrix.
		 *
		 * \param rowIndex Row index of the row to be removed (0...2).
		 * \param colIndex Column index of the column to be removed (0...2).
		 *
		 * \return Subdeterminant.
		 */
		virtual double getSubDet(int rowIndex, int colIndex) const;
		
		/** Calculate determinant.
		 *
		 * Calculate the determinant of the matrix.
		 *
		 * \return Determinant.
		 */
		virtual double getDet() const;
		
		/** Get adjoint.
		 *
		 * Get the adjoint of the matrix.
		 *
		 * \return Adjoint matrix.
		 */
		virtual Matrix3 getAdjoint() const;
		
		/** Transpose.
		 *
		 * Transpose the matrix.
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& transpose();
		
		/** Invert.
		 *
		 * Invert the matrix.
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& invert();
		
		/** Clear.
		 *
		 * Clear the matrix (set all entries to zero).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& clear();
		
		/** Set identity matrix.
		 *
		 * Set the matrix to the identity matrix.
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& setIdentity();
		
		/** Set rotation matrix (X).
		 *
		 * Set the matrix to a rotation matrix around the X axis.
		 *
		 * \param phi Rotation angle (rad).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& setRotateX(double phi);
		
		/** Set rotation matrix (X).
		 *
		 * Set the matrix to a rotation matrix around the Y axis.
		 *
		 * \param phi Rotation angle (rad).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& setRotateY(double phi);
		
		/** Set rotation matrix (Z).
		 *
		 * Set the matrix to a rotation matrix around the Z axis.
		 *
		 * \param phi Rotation angle (rad).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& setRotateZ(double phi);
		
		/** Set scale matrix.
		 *
		 * Set the matrix to a scale matrix.
		 *
		 * \param scaleX Scale factor (X).
		 * \param scaleY Scale factor (Y).
		 * \param scaleZ Scale factor (Z).
		 *
		 * \return Result of the operation.
		 */
		virtual Matrix3& setScale(double scaleX, double scaleY, double scaleZ);
		
		/** Set x11 entry.
		 *
		 * Set new value of x11 entry.
		 *
		 * \param newX11 New value of x11 entry.
		 */
		virtual void setX11(double newX11);
		
		/** Set x13 entry.
		 *
		 * Set new value of x13 entry.
		 *
		 * \param newX12 New value of x13 entry.
		 */
		virtual void setX12(double newX12);
		
		/** Set x13 entry.
		 *
		 * Set new value of x13 entry.
		 *
		 * \param newX13 New value of x13 entry.
		 */
		virtual void setX13(double newX13);
		
		/** Set x21 entry.
		 *
		 * Set new value of x21 entry.
		 *
		 * \param newX21 New value of x21 entry.
		 */
		virtual void setX21(double newX21);
		
		/** Set x22 entry.
		 *
		 * Set new value of x22 entry.
		 *
		 * \param newX22 New value of x22 entry.
		 */
		virtual void setX22(double newX22);
		
		/** Set x23 entry.
		 *
		 * Set new value of x23 entry.
		 *
		 * \param newX23 New value of x23 entry.
		 */
		virtual void setX23(double newX23);
		
		/** Set x31 entry.
		 *
		 * Set new value of x31 entry.
		 *
		 * \param newX31 New value of x31 entry.
		 */
		virtual void setX31(double newX31);
		
		/** Set x32 entry.
		 *
		 * Set new value of x32 entry.
		 *
		 * \param newX32 New value of x32 entry.
		 */
		virtual void setX32(double newX32);
		
		/** Set x33 entry.
		 *
		 * Set new value of x33 entry.
		 *
		 * \param newX33 New value of x33 entry.
		 */
		virtual void setX33(double newX33);
		
		/** Get x11 entry.
		 *
		 * \return Current value of x11 entry.
		 */
		virtual double getX11() const;
		
		/** Get x13 entry.
		 *
		 * \return Current value of x13 entry.
		 */
		virtual double getX12() const;
		
		/** Get x13 entry.
		 *
		 * \return Current value of x13 entry.
		 */
		virtual double getX13() const;
		
		/** Get x21 entry.
		 *
		 * \return Current value of x21 entry.
		 */
		virtual double getX21() const;
		
		/** Get x22 entry.
		 *
		 * \return Current value of x22 entry.
		 */
		virtual double getX22() const;
		
		/** Get x23 entry.
		 *
		 * \return Current value of x23 entry.
		 */
		virtual double getX23() const;
		
		/** Get x31 entry.
		 *
		 * \return Current value of x31 entry.
		 */
		virtual double getX31() const;
		
		/** Get x32 entry.
		 *
		 * \return Current value of x32 entry.
		 */
		virtual double getX32() const;
		
		/** Get x33 entry.
		 *
		 * \return Current value of x33 entry.
		 */
		virtual double getX33() const;
};

/** Multiply operator.
 * \ingroup vecmath
 *
 * Calculate the product of a matrix (R3 x R3) and a scalar.
 *
 * \param a Scalar.
 * \param mat Matrix (R3 x R3).
 */
Matrix3 operator*(double a, const Matrix3& mat);

}

}

/** \file Matrix3.hpp
 * \brief Matrix (R3 x R3) header.
 */
#endif
