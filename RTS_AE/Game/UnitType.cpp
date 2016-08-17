#include "stdafx.h"
#include "UnitType.h"

aeUnitType::aeUnitType()
{
	m_nClassID = ClassId::Preset;
	m_nPresetID = static_cast<int>(PresetsID::UnitType);
}

aeUnitType::~aeUnitType()
{
}

void aeUnitType::Destroy()
{
}
