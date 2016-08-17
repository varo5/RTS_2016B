#pragma once
#include <time.h>
#include <vector>
#include "GameObject.h"

class aeTiledMap : public aeGameObject
{
public:

	class aeMapTile 
	{
	public:
		aeMapTile();
		~aeMapTile();

		uint8 Layer1ID;
		uint8 Layer2ID;
		uint8 Layer3ID;
		uint8 Layer4ID;
		uint8 Layer5ID;
		int16 Cost;
		
		std::vector<aeGameObject*> GameObjectArray;

		float GetInfluence();
		void UpdateInfluence(float Influence);
	private:
		float m_fInfluence;
	};

public:
	aeTiledMap();
	~aeTiledMap();

	/************************************************************************************************************************/
	/* Functions definitions			                                     												*/
	/************************************************************************************************************************/
public:
	int Init(aeRenderer* pRenderer, PresetsList* pPresets);
	void Destroy();

	void Update(float fDelta);
	void Render(aeRenderer* pRenderer);

	int32 GetMapSize() const { return m_nMapSize; }

	int16 GetCost(const int32 x, const int32 y) const;
	void SetCost(const int32 x, const int32 y, const int16 Cost);

	uint8 GetLayer1(const int32 x, const int y) const;
	void SetLayer1(const int32 x, const int32 y, const uint8 Layer1ID);

	uint8 GetLayer2(const int32 x, const int y) const;
	void SetLayer2(const int32 x, const int32 y, const uint8 Layer2ID);

	uint8 GetLayer3(const int32 x, const int y) const;
	void SetLayer3(const int32 x, const int32 y, const uint8 Layer3ID);

	uint8 GetLayer4(const int32 x, const int y) const;
	void SetLayer4(const int32 x, const int32 y, const uint8 Layer4ID);

	uint8 GetLayer5(const int32 x, const int y) const;
	void SetLayer5(const int32 x, const int32 y, const uint8 Layer5ID);

	float GetInfluence(const int32 x, const int y) const;
	void SetInfluence(const int32 x, const int32 y, const float Influence);

	void ShowGrid(bool State);
	void SetView(bool Isometric);
	void SetPathFinder(int PathFinder);
	void CameraReference(aeWorld* Camera);
	void MakeSearch(aePoint StartPosition, aePoint EndPosition);

	int PositionOfOpenMask, PositionOfVisitedMask, PositionOfInfluenceMask;
	static int TileMapCreation(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int InfluenceDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName);
	/************************************************************************************************************************/
	/* Variable definitions                                      												*/
	/************************************************************************************************************************/
protected:
	/** @brief	Map information. */
	aeMapTile **m_ppMapGrid;
	/** @brief	Map Size. */
	int32 m_nMapSize;

	/** @brief	The tile size in x. */
	int32 m_nTileSizeX;
	/** @brief	The tile size in y. */
	int32 m_nTileSizeY;

	
	/** @brief	Precalc Size. */
	aePoint m_PrecalcSize;

	/** @brief	The camera. */
	aeWorld* m_pCamera;

	/** @brief	The presets for tile creation. */
	std::vector<aeTileType*> m_pTileTypes;
	
	/** @brief	Flag to indicate if the grid will be shown or not. */
	bool m_bShowGrid;
	/** @brief	Flag to indicate if is isometric or not. */
	bool m_bIsometric;
	bool m_bDebug;
	int m_nPathFinder;
};

