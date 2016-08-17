#include "stdafx.h"
#include "Transform.h"

aeTransform::aeTransform()
{
	Position = aeCore::aeVector3{ 0,0,0 };
	Velocity = aeCore::aeVector3{ 0,0,0 };
	Direction = aeCore::aeVector3{ 0,1,0 };
	Scale = aeCore::aeVector3{ 1,1,1 };
}


aeTransform::~aeTransform()
{
}


