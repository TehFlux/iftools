#ifndef IONFLUX_TOOLS_VECTOR3
#define IONFLUX_TOOLS_VECTOR3
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vector3.hpp                       Vector (R3).
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
#include "ionflux/ManagedObject.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup vecmath Vector mathematics
 *
 * Tools for handling vectors and matrices in R3.
 *
 * @{
 */

/** Vector (R3).
 *
 * A vector in three dimensional space.
 */
class Vector3
: public ManagedObject
{
	protected:
		/// Components.
		double* comp;
		
	public:
		/** Constructor.
		 *
		 * Construct new Vector3 object.
		 */
		Vector3();
		
		/** Constructor.
		 *
		 * Construct new Vector3 object.
		 *
		 * \param initX1 x1 component.
		 * \param initX2 x2 component.
		 * \param initX3 x3 component.
		 */
		Vector3(double initX1, double initX2, double initX3);
		
		/** Constructor.
		 *
		 * Construct new Vector3 object.
		 *
		 * \param initVec Vector (R3).
		 */
		Vector3(const Vector3& initVec);
		
		/** Constructor.
		 *
		 * Construct new Vector3 object.
		 *
		 * \note \c initComp is expected to have a size of at least 3.
		 *
		 * \param initComp Array of vector components.
		 */
		Vector3(const double* initComp);
		
		/** Destructor.
		 *
		 * Destruct Vector3 object.
		 */
		virtual ~Vector3();
		
		/** Set components.
		 *
		 * Set the components of the vector.
		 *
		 * \param newX1 x1 component.
		 * \param newX2 x2 component.
		 * \param newX3 x3 component.
		 */
		virtual void setComps(double newX1, double newX2, double newX3);
		
		/** Set components.
		 *
		 * Set the components of the vector. 
		 *
		 * \note \c newComp is expected to have a size of at least 3.
		 *
		 * \param newComp Component array.
		 */
		virtual void setComps(const double* newComp);
		
		/** Set component.
		 *
		 * Set the specified component of the vector. 
		 *
		 * \note If \c compIndex is out of range, this function does nothing.
		 *
		 * \param compIndex Component index (0...2)
		 * \param newComp New value of component.
		 */
		virtual void setComp(int compIndex, double newComp);
		
		/** Create string representation.
		 *
		 * Create a string representation of the vector 
		 * (i.e. "(&lt;x1&gt;,&lt;x2&gt;,&lt;x3&gt;))").
		 */
		virtual std::string toString() const;
		
		/** Assignment operator.
		 *
		 * Assign one vector to another vector.
		 *
		 * \param newVec Vector (R3).
		 */
		virtual Vector3& operator=(const Vector3& newVec);
		
		/** Add operator.
		 *
		 * Add one vector to another vector.
		 *
		 * \param otherVec Vector (R3).
		 */
		virtual Vector3 operator+(const Vector3& otherVec) const;
		
		/** Subtract operator.
		 *
		 * Subtract one vector from another vector.
		 *
		 * \param otherVec Vector (R3).
		 */
		virtual Vector3 operator-(const Vector3& otherVec) const;
		
		/** Add operator.
		 *
		 * Add one vector to another vector.
		 *
		 * \param otherVec Vector (R3).
		 */
		virtual Vector3& operator+=(const Vector3& otherVec);
		
		/** Subtract operator.
		 *
		 * Subtract one vector from another vector.
		 *
		 * \param otherVec Vector (R3).
		 */
		virtual Vector3& operator-=(const Vector3& otherVec);
		
		/** Multiply operator.
		 *
		 * Calculate the scalar product of two vectors.
		 *
		 * \param otherVec Vector (R3).
		 */
		virtual double operator*(const Vector3& otherVec) const;
		
		/** Multiply operator.
		 *
		 * Calculate the product of the vector and a scalar.
		 *
		 * \param a Scalar.
		 */
		virtual Vector3& operator*=(double a);
		
		/** Multiply operator.
		 *
		 * Calculate the product of the vector and a scalar.
		 *
		 * \param a Scalar.
		 */
		virtual Vector3 operator*(double a) const;
		
		/** Subscript operator.
		 *
		 * Access a component of the vector.
		 *
		 * \note If \c compIndex is out of range, the function returns 0.
		 *
		 * \param compIndex Component index (0...2).
		 */
		virtual double operator[](int compIndex) const;
		
		/** Set x1 component.
		 *
		 * Set new value of x1 component.
		 *
		 * \param newX1 New value of x1 component.
		 */
		virtual void setX1(double newX1);
		
		/** Set x2 component.
		 *
		 * Set new value of x2 component.
		 *
		 * \param newX2 New value of x2 component.
		 */
		virtual void setX2(double newX2);
		
		/** Set x3 component.
		 *
		 * Set new value of x3 component.
		 *
		 * \param newX3 New value of x3 component.
		 */
		virtual void setX3(double newX3);
		
		/** Get x1 component.
		 *
		 * \return Current value of x1 component.
		 */
		virtual double getX1() const;
		
		/** Get x2 component.
		 *
		 * \return Current value of x2 component.
		 */
		virtual double getX2() const;
		
		/** Get x3 component.
		 *
		 * \return Current value of x3 component.
		 */
		virtual double getX3() const;
};

/** Multiply operator.
 *
 * Calculate the product of the vector and a scalar.
 *
 * \param a Scalar.
 * \param vec Vector (R3).
 */
Vector3 operator*(double a, const Vector3& vec);

/// @}

}

}

/** \file Vector3.hpp
 * \brief Vector (R3) header.
 */
#endif
