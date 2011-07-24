/*********************************************************\
 *  File: SNMPhysicsBodyEllipsoid.h                      *
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_BODYELLIPSOID_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_BODYELLIPSOID_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBody.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
}
namespace PLScene {
	class VisNode;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Physics ellipsoid body scene node modifier
*
*  @remarks
*    Sphere collision are generalized ellipsoids, the application can create many different kind
*    of objects by just playing with dimensions of the radius. For example to make a sphere set all
*    tree radius to the same value, to make a ellipse of revolution just set two of the tree radius
*    to the same value.\n
*    General ellipsoids are very good hull geometries to represent the outer shell of avatars in a game.
*/
class SNMPhysicsBodyEllipsoid : public SNMPhysicsBody {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsBodyEllipsoid, "PLPhysics", PLPhysics::SNMPhysicsBody, "Physics ellipsoid body scene node modifier")
		// Attributes
		pl_attribute(Radius,	PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,	"Ellipsoid radius along each axis, if null, a ellipsoid 'inside' the axis align bounding box in 'scene node space' is used as default",	"Min='0.0 0.0 0.0'")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
		// Slots
		pl_slot_2(OnDrawDebug,	PLRenderer::Renderer&,	const PLScene::VisNode*,	"Called on scene node debug draw, the used renderer as first parameter, the current visibility node of this scene node as second parameter (can be a null pointer)",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API const PLMath::Vector3 &GetRadius() const;
		PLPHYSICS_API void SetRadius(const PLMath::Vector3 &vValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLPHYSICS_API SNMPhysicsBodyEllipsoid(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNMPhysicsBodyEllipsoid();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called on scene node debug draw
		*
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] pVisNode
		*    The current visibility node of this scene node, can be a null pointer
		*/
		void OnDrawDebug(PLRenderer::Renderer &cRenderer, const PLScene::VisNode *pVisNode);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3 m_vRadius;	/**< Ellipsoid radius along each axis, if null, a ellipsoid 'inside' the axis align bounding box in 'scene node space' is used as default */


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNodeModifier functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void OnActivate(bool bActivate);


	//[-------------------------------------------------------]
	//[ Private virtual SNMPhysicsBody functions              ]
	//[-------------------------------------------------------]
	private:
		virtual void CreatePhysicsBody();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_BODYELLIPSOID_H__