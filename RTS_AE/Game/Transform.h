/**********************************************************************************************//**
 * @file	Game\Transform.h
 *
 * @brief	Declares the transform class.
 **************************************************************************************************/

#pragma once

 /************************************************************************************************************************/
 /* Inclusion of the necessary header files																				*/
 /************************************************************************************************************************/
#include "Math\Matrix4.h"

/**********************************************************************************************//**
 * @struct	aeTransform
 *
 * @brief	Is a storage for the necessary components for a GameObject physics.
 **************************************************************************************************/

struct aeTransform
{
public:
	aeTransform();
	virtual ~aeTransform();

	aeCore::aeVector3 Position;
	aeCore::aeVector3 Velocity;
	aeCore::aeVector3 Direction;
	aeCore::aeVector3 Scale;
};

