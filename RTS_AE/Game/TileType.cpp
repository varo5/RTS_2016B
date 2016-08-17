#include "stdafx.h"
#include "TileType.h"

aeTileType::aeTileType() : aePresets()
{
	m_nPresetID = static_cast<int>(PresetsID::TileType);
}

aeTileType::aeTileType(int ID, aeString Name, int Cost, aeSprite* TileImage, int SpriteID, bool Isometric, int Movement) : aePresets()
{
	m_nPresetID = static_cast<int>(PresetsID::TileType);
	m_nID = ID;
	m_pszName = Name;
	m_nCost = Cost;
	m_pImage = TileImage;
	m_nSpriteID = SpriteID;
	m_bIsometric = Isometric;
	m_nMovement = Movement;
}

aeTileType::~aeTileType()
{
}

aeMapPresets::aeMapPresets() : aePresets()
{
	m_nPresetID = static_cast<int>(PresetsID::MapPreset);
}

aeMapPresets::~aeMapPresets()
{
}
