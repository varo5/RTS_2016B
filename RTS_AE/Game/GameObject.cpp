#include "stdafx.h"
#include "GameObject.h"


aeGameObject::aeGameObject()
{
	m_nClassID = ClassId::GameObject;
	Derivative = false;
}


aeGameObject::~aeGameObject()
{
}

int aeGameObject::Init()
{
	return 0;
}

void aeGameObject::Update(float fDelta)
{
	for each (auto AddOn in AddOns)
	{
		((aeAddOn*)AddOn)->Update(fDelta);
	}
}

void aeGameObject::Render(aeRenderer * pRenderer)
{
	for each (auto AddOn in AddOns)
	{
		((aeAddOn*)AddOn)->Render(pRenderer);
	}
}

void aeGameObject::Destroy()
{
	for each (auto AddOn in AddOns)
	{
		AddOn->Destroy();
	}
}


