/**********************************************************************************************//**
 * @file	Game\Presets.h
 *
 * @brief	Declares the presets class.
 **************************************************************************************************/

#pragma once
#include "BaseClass.h"
#include "EnumDeclarations.h"

/**********************************************************************************************//**
 * @class	aePresets
 *
 * @brief	A presets.
 **************************************************************************************************/

class aePresets : public aeBaseClass
{
public:
	aePresets();
	virtual ~aePresets();

	virtual void Destroy();

	inline int GetPresetID()
	{
		return m_nPresetID;
	}
protected:
	int m_nPresetID;
};

typedef std::vector<aePresets*> PresetsList;