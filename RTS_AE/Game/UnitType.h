/**********************************************************************************************//**
 * @file	Game\UnitType.h
 *
 * @brief	Declares the unit type class.
 **************************************************************************************************/

#pragma once
#include "Presets.h"

/**********************************************************************************************//**
 * @class	aeUnitType
 *
 * @brief	A unit type.
 **************************************************************************************************/

class aeUnitType : public aePresets
{

public:
	aeUnitType();
	~aeUnitType();

public:
	void Destroy();

public:
	union
	{
		struct
		{
			bool IsMilitant : 1;
			bool CanBuild : 1;
		};
		bool BehaviourFlags;
	};
	int m_nID;
	int m_nRadius;
	int m_nImageID;
	aeString m_pszName;
	float m_fHP_Max;
	float m_fAttack_Range_Max;
	float m_fAttack_Range_Min;
	float m_fAttack_Speed;
	float m_fView_Range;
	float m_fSpeed;
	float m_fStrength;

	void* m_pImage;
};

