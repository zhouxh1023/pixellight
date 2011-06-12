/*********************************************************\
 *  File: JointHinge.h                                   *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


#ifndef __PLPHYSICSPHYSX_JOINTHINGE_H__
#define __PLPHYSICSPHYSX_JOINTHINGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLPhysics/JointHinge.h>
#include "PLPhysicsPhysX/PLPhysicsPhysX.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsPhysX {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PhysX physics hinge joint implementation
*/
class JointHinge : public PLPhysics::JointHinge {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class World;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICSPHYSX_API virtual ~JointHinge();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    World this joint is in
		*  @param[in] pParentBody
		*    Pointer to the parent rigid body, can be a null pointer
		*  @param[in] pChildBody
		*    Pointer to the attached rigid body, can be a null pointer
		*  @param[in] vPivotPoint
		*    Origin of the hinge in world space
		*  @param[in] vPinDir
		*    The line of action of the hinge in world space
		*/
		JointHinge(PLPhysics::World &cWorld, PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody,
				   const PLMath::Vector3 &vPivotPoint, const PLMath::Vector3 &vPinDir);


	//[-------------------------------------------------------]
	//[ Public virtual PLPhysics::JointHinge functions        ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICSPHYSX_API virtual void AddOmega(float fOmega);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsPhysX


#endif // __PLPHYSICSPHYSX_JOINTHINGE_H__