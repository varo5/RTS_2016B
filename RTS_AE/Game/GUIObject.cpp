#include "stdafx.h"
#include "GUIObject.h"

aeGUIObject::aeGUIObject()
{
	m_nClassID = ClassId::GUIObject;
}

aeGUIObject::~aeGUIObject()
{
}

int aeGUIObject::Init()
{
	return 0;
}

void aeGUIObject::Update(float fDelta)
{
	for each (auto AddOn in AddOns)
	{
		AddOn->Update(fDelta);
	}
}

void aeGUIObject::Render(aeRenderer * pRenderer)
{
	for each (auto AddOn in AddOns)
	{
		AddOn->Render(pRenderer);
	}
}

void aeGUIObject::Destroy()
{
	for each (auto AddOn in AddOns)
	{
		AddOn->Destroy();
	}
}
