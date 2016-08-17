#pragma once

class aeTileType : public aePresets
{
public:
	aeTileType();
	aeTileType(int ID, aeString Name, int Cost, aeSprite* TileImage, int SpriteID, bool Isometric, int Movement);
	~aeTileType();
public:
	int m_nID;
	aeString m_pszName;
	int m_nCost;
	aeSprite* m_pImage;
	int m_nSpriteID;
	bool m_bIsometric;
	int m_nMovement;

};

class aeMapPresets : public aePresets
{
public:
	aeMapPresets();
	~aeMapPresets();
public:
	int m_nID;
	aeString m_pszName;
	int m_nOctaves;
	double m_dFrequency;
	double m_dScale;
	double m_dPersistance;
	double m_dLacuranity;
	int m_nTileID1;
	int m_nTileID2;
	int m_nTileID3;
	float m_fTopValue1;
	float m_fTopValue2;
};