#include "stdafx.h"
#include "TiledMap.h"


aeTiledMap::aeTiledMap() : aeGameObject()
{
	Derivative = true;
}


aeTiledMap::~aeTiledMap()
{
}

int aeTiledMap::Init(aeRenderer* pRenderer, PresetsList* pPresets)
{
	//Revisamos que esta función pueda ser llamada
	if (m_ppMapGrid != NULL)
	{//Este mapa ya fue creado anteriormente, destruimos los datos actuales y reinicializamos
		Destroy();
	}

	//Creamos el grid del mapa según el tamaño indicado
	//Lo creamos como una matriz accesible en dos dimensiones PERO EVITAMOS CREARLA COMO UNA MATRIZ DE DOS DIMENSIONES
	m_ppMapGrid = new aeMapTile*[m_nMapSize];

	int index = 0, counter = 0;
	
	
	for each (auto Preset in *pPresets)
	{
		if (Preset->GetPresetID() == static_cast<int>(PresetsID::MapPreset))
		{
			TempPreset = *(aeMapPresets*)Preset;
		}
	}
	for each (auto Preset in *pPresets)
	{
		if (Preset->GetPresetID() == static_cast<int>(PresetsID::TileType))
		{
			if (m_bIsometric == ((aeTileType*)Preset)->m_bIsometric)
			{
				m_pTileTypes.push_back((aeTileType*)Preset);
				if (((aeTileType*)Preset)->m_nID == TempPreset.m_nTileID1)
				{
					cost1 = ((aeTileType*)Preset)->m_nCost;
					Position1 = index;
				}
				else if (((aeTileType*)Preset)->m_nID == TempPreset.m_nTileID2)
				{
					cost2 = ((aeTileType*)Preset)->m_nCost;
					Position2 = index;
				}
				else if (((aeTileType*)Preset)->m_nID == TempPreset.m_nTileID3)
				{
					cost3 = ((aeTileType*)Preset)->m_nCost;
					Position3 = index;
				}
				else if (((aeTileType*)Preset)->m_pszName == TEXT("Yellow_Mask"))
				{
					PositionOfOpenMask = index;
				}
				else if (((aeTileType*)Preset)->m_pszName == TEXT("Grey_Mask"))
				{
					PositionOfVisitedMask = index;
				}
				else if (((aeTileType*)Preset)->m_pszName == TEXT("Mask"))
				{
					PositionOfInfluenceMask = index;
					m_pTileTypes[PositionOfInfluenceMask]->m_pImage->SetBlendMode(SDL_BLENDMODE_BLEND);
				}
				index++;
			}
		}
		counter++;
	}

	RNGInit(static_cast<int32>(time(NULL)));

	FractalNoise Noise(UIRand());

	Noise.SetOctaves(TempPreset.m_nOctaves);
	Noise.SetBaseFrequency(TempPreset.m_dFrequency);
	Noise.SetScale(TempPreset.m_dScale);
	Noise.SetPersistence(TempPreset.m_dPersistance);
	Noise.SetLacunarity(TempPreset.m_dLacuranity);

	double value;

	std::vector<double> tempvec;

	for (int32 i = 0; i < m_nMapSize; ++i)
	{
		m_ppMapGrid[i] = NULL;
		m_ppMapGrid[i] = new aeMapTile[m_nMapSize];
		for (int32 j = 0; j < m_nMapSize; ++j)
		{
			value = Noise.Noise(i, j, 0.5);

			tempvec.push_back(value);

			if (value <= TempPreset.m_fTopValue1)
			{
				m_ppMapGrid[i][j].Layer1ID = Position1;
				m_ppMapGrid[i][j].Cost = cost1;
			}
			else if (value <= TempPreset.m_fTopValue2)
			{
				m_ppMapGrid[i][j].Layer1ID = Position2;
				m_ppMapGrid[i][j].Cost = cost2;
			}
			else
			{
				m_ppMapGrid[i][j].Layer1ID = Position3;
				m_ppMapGrid[i][j].Cost = cost3;
			}
			m_ppMapGrid[i][j].Layer2ID = -1;
			m_ppMapGrid[i][j].Layer3ID = -1;
			m_ppMapGrid[i][j].Layer4ID = -1;
			m_ppMapGrid[i][j].Layer5ID = -1;
			m_ppMapGrid[i][j].UpdateInfluence(0);
		}
	}
	m_bShowGrid = false;

	m_PrecalcSize.x = m_nMapSize*m_nTileSizeX;
	m_PrecalcSize.y = m_nMapSize*m_nTileSizeY;

	aeDFSPathFinder* DFS = new aeDFSPathFinder(this);
	aeBFSPathFinder* BFS = new aeBFSPathFinder(this);
	aeBstFSPathFinder* BstFS = new aeBstFSPathFinder(this);
	aeDijkstraPathFinder* DijkstraS = new aeDijkstraPathFinder(this);
	aeAStarPathFinder* AStarS = new aeAStarPathFinder(this);
	

	AddOns.push_back(DFS);
	AddOns.push_back(BFS);
	AddOns.push_back(BstFS);
	AddOns.push_back(DijkstraS);
	AddOns.push_back(AStarS);

	DFS->DebugMode(m_bDebug);
	BFS->DebugMode(m_bDebug);
	BstFS->DebugMode(m_bDebug);
	DijkstraS->DebugMode(m_bDebug);
	AStarS->DebugMode(m_bDebug);

	/*if (m_nPathFinder != 255 && ((aePathFinder*)AddOns[m_nPathFinder])->GetID() != 1)
	{
		((aePathFinder*)AddOns[m_nPathFinder])->MakeSearch(aePoint{ 0,0 }, aePoint{ m_nMapSize - 1,m_nMapSize - 1 });
	}*/
	return 0;
}

void aeTiledMap::Destroy()
{
	//Revisamos si ya se creó un mapa
	if (m_ppMapGrid != NULL)
	{//Fue creado y necesitamos destruirlo
		for (int32 i = 0; i < m_nMapSize; i++)
		{
			SAFE_DELETE_ARRAY(m_ppMapGrid[i]);
		}

		SAFE_DELETE_ARRAY(m_ppMapGrid);
	}

	//Limpiamos las otras variables miembro de la clase
	m_nMapSize = 0;
	m_bShowGrid = false;

	for each (auto AddOn in AddOns)
	{
		AddOn->Destroy();
	}

	AddOns.clear();

	while (m_pTileTypes.size())
	{
		m_pTileTypes.pop_back();
	}
}

void aeTiledMap::Update(float fDelta)
{
	if (m_nPathFinder < AddOns.size())
	{
		AddOns[m_nPathFinder]->Update(fDelta);
	}
}

void aeTiledMap::Render(aeRenderer * pRenderer)
{
	if (m_nPathFinder < AddOns.size())
		AddOns[m_nPathFinder]->Render(pRenderer);
	aeVector2 DisplacedPosition;
	aeRect WindowDimensions = *m_pCamera->GetCameraRect();
	aePoint ScreenPosition = GetMapToScreenCoords(aeVector2{ Transform.Position.x,Transform.Position.y }, *m_pCamera->GetCameraPosition(), WindowDimensions, m_bIsometric);
	DisplacedPosition.x = static_cast<float>(ScreenPosition.x - (m_PrecalcSize.w >> 1));
	DisplacedPosition.y = static_cast<float>(ScreenPosition.y - (m_PrecalcSize.h >> 1));

	int tmpTypeTile;
	float tmpInfluence;
	aePoint Displacement, Size;

	Size.w = m_nTileSizeX;
	Size.h = m_nTileSizeY;
	//Obtenidas ya las posiciones iniciales y finales, rendereamos las texturas
	for (int i = 0; i < m_nMapSize; i++)
	{
		for (int j = 0; j < m_nMapSize; j++)
		{
			Displacement.x = i * m_nTileSizeX + DisplacedPosition.x;
			Displacement.y = j * m_nTileSizeY + DisplacedPosition.y;

			if (Displacement.x >=-Size.w && Displacement.y >= -Size.h && Displacement.x <= WindowDimensions.w && Displacement.y <= WindowDimensions.h)
			{
				tmpTypeTile = m_ppMapGrid[i][j].Layer1ID;
				if (tmpTypeTile != 255)
				{
					m_pTileTypes[tmpTypeTile]->m_pImage->Render(pRenderer, Displacement.x, Displacement.y, &Size);
				}
			}
		}
	}

	for (int i = 0; i < m_nMapSize; i++)
	{
		for (int j = 0; j < m_nMapSize; j++)
		{
			Displacement.x = i * m_nTileSizeX + DisplacedPosition.x;
			Displacement.y = j * m_nTileSizeY + DisplacedPosition.y;

			if (Displacement.x >= -Size.w && Displacement.y >= -Size.h && Displacement.x <= WindowDimensions.w && Displacement.y <= WindowDimensions.h)
			{
				tmpTypeTile = m_ppMapGrid[i][j].Layer4ID;
				if (tmpTypeTile != 255)
				{
					m_pTileTypes[tmpTypeTile]->m_pImage->Render(pRenderer, Displacement.x, Displacement.y, &Size);
				}
			}
		}
	}

	for (int i = 0; i < m_nMapSize; i++)
	{
		for (int j = 0; j < m_nMapSize; j++)
		{
			Displacement.x = i * m_nTileSizeX + DisplacedPosition.x;
			Displacement.y = j * m_nTileSizeY + DisplacedPosition.y;

			if (Displacement.x >= -Size.w && Displacement.y >= -Size.h && Displacement.x <= WindowDimensions.w && Displacement.y <= WindowDimensions.h)
			{
				tmpInfluence = m_ppMapGrid[i][j].GetInfluence();
				if (tmpInfluence != 0)
				{
					if (tmpInfluence > 0)
					{
						m_pTileTypes[PositionOfInfluenceMask]->m_pImage->SetAlpha(Trunc(tmpInfluence * 255));
						m_pTileTypes[PositionOfInfluenceMask]->m_pImage->SetColor(aeRGB{ 0,0,255 });
						m_pTileTypes[PositionOfInfluenceMask]->m_pImage->Render(pRenderer, Displacement.x, Displacement.y, &Size);
					}
					else if (tmpInfluence < 0)
					{
						m_pTileTypes[PositionOfInfluenceMask]->m_pImage->SetAlpha(Trunc(abs(tmpInfluence * 255)));
						m_pTileTypes[PositionOfInfluenceMask]->m_pImage->SetColor(aeRGB{ 255,0,0 });
						m_pTileTypes[PositionOfInfluenceMask]->m_pImage->Render(pRenderer, Displacement.x, Displacement.y, &Size);
					}
				}
			}
		}
	}

	if (m_bShowGrid)
	{
		aeRGBQuad TempColor = pRenderer->SetRenderDrawColor(aeRGBQuad{ 0,0,0,255 });

		aePoint Temp1, Temp2;

		for (int i = 0; i < m_nMapSize; i++)
		{
			Displacement.x = i * m_nTileSizeX + DisplacedPosition.x;
			Displacement.y = i * m_nTileSizeY + DisplacedPosition.y;

			if (Displacement.x >= -Size.w && Displacement.x <= WindowDimensions.w)
			{
				Temp1.x = Displacement.x;
				Temp1.y = 0;
				Temp2.x = Displacement.x;
				Temp2.y = WindowDimensions.h;

				pRenderer->DrawLine(Temp1, Temp2);
			}

			if (Displacement.y >= -Size.h && Displacement.y <= WindowDimensions.h)
			{
				Temp1.y = Displacement.y;
				Temp1.x = 0;
				Temp2.y = Displacement.y;
				Temp2.x = WindowDimensions.w;

				pRenderer->DrawLine(Temp1, Temp2);
			}
		}
		pRenderer->SetRenderDrawColor(aeRGBQuad{ TempColor.r,TempColor.g,TempColor.b,TempColor.a });
	}

}

int16 aeTiledMap::GetCost(const int32 x, const int32 y) const
{
	return (m_ppMapGrid[x][y]).Cost;
}

void aeTiledMap::SetCost(const int32 x, const int32 y, const int16 Cost)
{
	(m_ppMapGrid[x][y]).Cost = Cost;
}

uint8 aeTiledMap::GetLayer1(const int32 x, const int y) const
{
	return (m_ppMapGrid[x][y]).Layer1ID;
}

void aeTiledMap::SetLayer1(const int32 x, const int32 y, const uint8 Layer1ID)
{
	(m_ppMapGrid[x][y]).Layer1ID = Layer1ID;
}

uint8 aeTiledMap::GetLayer2(const int32 x, const int y) const
{
	return (m_ppMapGrid[x][y]).Layer2ID;
}

void aeTiledMap::SetLayer2(const int32 x, const int32 y, const uint8 Layer2ID)
{
	(m_ppMapGrid[x][y]).Layer2ID = Layer2ID;
}

uint8 aeTiledMap::GetLayer3(const int32 x, const int y) const
{
	return (m_ppMapGrid[x][y]).Layer3ID;
}

void aeTiledMap::SetLayer3(const int32 x, const int32 y, const uint8 Layer3ID)
{
	(m_ppMapGrid[x][y]).Layer3ID = Layer3ID;
}

uint8 aeTiledMap::GetLayer4(const int32 x, const int y) const
{
	return (m_ppMapGrid[x][y]).Layer4ID;
}

void aeTiledMap::SetLayer4(const int32 x, const int32 y, const uint8 Layer4ID)
{
	(m_ppMapGrid[x][y]).Layer4ID = Layer4ID;
}

uint8 aeTiledMap::GetLayer5(const int32 x, const int y) const
{
	return (m_ppMapGrid[x][y]).Layer5ID;
}

void aeTiledMap::SetLayer5(const int32 x, const int32 y, const uint8 Layer5ID)
{
	(m_ppMapGrid[x][y]).Layer5ID = Layer5ID;
}

float aeTiledMap::GetInfluence(const int32 x, const int y) const
{
	return (m_ppMapGrid[x][y]).GetInfluence();
}

void aeTiledMap::SetInfluence(const int32 x, const int32 y, const float Influence)
{
	(m_ppMapGrid[x][y]).UpdateInfluence(Influence);
}

void aeTiledMap::ShowGrid(bool State)
{
	m_bShowGrid = State;
}

void aeTiledMap::SetView(bool Isometric)
{
	m_bIsometric = Isometric;
}

void aeTiledMap::SetPathFinder(int PathFinder)
{
	((aePathFinder*)AddOns[m_nPathFinder])->Reset();
	m_nPathFinder = PathFinder;
	for (size_t i = 0; i < m_nMapSize; i++)
	{
		for (size_t j = 0; j < m_nMapSize; j++)
		{
			SetLayer4(i, j, -1);
			SetInfluence(i, j, 0);
		}
	}
}

void aeTiledMap::CameraReference(aeWorld * Camera)
{
	m_pCamera = Camera;
}

void aeTiledMap::MakeSearch(aePoint StartPosition, aePoint EndPosition)
{
	if (m_nPathFinder < AddOns.size() && m_nPathFinder >= 0)
	{
		if (((aePathFinder*)AddOns[m_nPathFinder])->GetID() != 1)
		{
			
			StartPosition.x += (m_PrecalcSize.w >> 1);
			StartPosition.y = (m_PrecalcSize.h >> 1) - StartPosition.y;

			StartPosition.x /= m_nTileSizeX;
			StartPosition.y /= m_nTileSizeY;

			StartPosition.x -= 1;
			StartPosition.y -= 1;

			EndPosition.x += (m_PrecalcSize.w >> 1);
			EndPosition.y = (m_PrecalcSize.h >> 1) - EndPosition.y;

			EndPosition.x /= m_nTileSizeX;
			EndPosition.y /= m_nTileSizeY;

			EndPosition.x -= 1;
			EndPosition.y -= 1;

			if(EndPosition.x < m_nMapSize*m_nTileSizeX && EndPosition.y < m_nMapSize*m_nTileSizeY && StartPosition.x > 0 && StartPosition.y > 0)
				((aePathFinder*)AddOns[m_nPathFinder])->MakeSearch(StartPosition, EndPosition);
		}
		else if (((aePathFinder*)AddOns[m_nPathFinder])->GetID() == 1)
		{
			StartPosition.x += (m_PrecalcSize.w >> 1);
			StartPosition.y = (m_PrecalcSize.h >> 1) - StartPosition.y;

			StartPosition.x /= m_nTileSizeX;
			StartPosition.y /= m_nTileSizeY;
			aeInfluencePoint Point = aeInfluencePoint{ 1,StartPosition.x,StartPosition.y  };

			((aeInfluenceCalculator*)AddOns[m_nPathFinder])->SetInfluencePoints(&Point, 1);
		}
	}
}

void aeTiledMap::MakeNoise()
{
	FractalNoise Noise(UIRand());

	Noise.SetOctaves(TempPreset.m_nOctaves);
	Noise.SetBaseFrequency(TempPreset.m_dFrequency);
	Noise.SetScale(TempPreset.m_dScale);
	Noise.SetPersistence(TempPreset.m_dPersistance);
	Noise.SetLacunarity(TempPreset.m_dLacuranity);

	double value;

	std::vector<double> tempvec;

	for (int32 i = 0; i < m_nMapSize; ++i)
	{
		m_ppMapGrid[i] = NULL;
		m_ppMapGrid[i] = new aeMapTile[m_nMapSize];
		for (int32 j = 0; j < m_nMapSize; ++j)
		{
			value = Noise.Noise(i, j, 0.5);

			tempvec.push_back(value);

			if (value <= TempPreset.m_fTopValue1)
			{
				m_ppMapGrid[i][j].Layer1ID = Position1;
				m_ppMapGrid[i][j].Cost = cost1;
			}
			else if (value <= TempPreset.m_fTopValue2)
			{
				m_ppMapGrid[i][j].Layer1ID = Position2;
				m_ppMapGrid[i][j].Cost = cost2;
			}
			else
			{
				m_ppMapGrid[i][j].Layer1ID = Position3;
				m_ppMapGrid[i][j].Cost = cost3;
			}
			m_ppMapGrid[i][j].Layer2ID = -1;
			m_ppMapGrid[i][j].Layer3ID = -1;
			m_ppMapGrid[i][j].Layer4ID = -1;
			m_ppMapGrid[i][j].Layer5ID = -1;
			m_ppMapGrid[i][j].UpdateInfluence(0);
		}
	}
}

int aeTiledMap::GetPathfinderID()
{
	return ((aePathFinder*)AddOns[m_nPathFinder])->GetID();
}

int aeTiledMap::TileMapCreation(void * data, int argument_count, char ** argument_values, char ** pszColName)
{
	std::map < std::string, std::string> GenericMapValues;
	for (int i = 0; i < argument_count; i++)
	{
		GenericMapValues[std::string(pszColName[i])] = (argument_values[i] ? argument_values[i] : NULL);
	}

	std::basic_stringstream<char, std::char_traits<char>> SstreamTranslator;

	std::string pszID;
	SstreamTranslator.str(GenericMapValues["ID"]);
	SstreamTranslator >> pszID;
	SstreamTranslator.clear();
	if (pszID == "TileMap")
	{
		std::string pszName;
		SstreamTranslator.str(GenericMapValues["Name"]);
		SstreamTranslator >> pszName;
		SstreamTranslator.clear();

		SstreamTranslator.str(GenericMapValues["Variable"]);
		if (pszName == "MapSize")
		{
			SstreamTranslator >> ((aeTiledMap*)data)->m_nMapSize;
		}
		else if (pszName == "PathFinder")
		{
			SstreamTranslator >> ((aeTiledMap*)data)->m_nPathFinder;
		}
		else if (pszName == "Debug")
		{
			int Debug;
			SstreamTranslator >> Debug;
			((aeTiledMap*)data)->m_bDebug = (Debug != 0);
		}
		else if (pszName == "TileSizeX")
		{
			SstreamTranslator >> ((aeTiledMap*)data)->m_nTileSizeX;
			if (!((aeTiledMap*)data)->m_bIsometric)
			{
				((aeTiledMap*)data)->m_nTileSizeY = ((aeTiledMap*)data)->m_nTileSizeX;
			}
		}
		else if (pszName == "TileSizeY")
		{			
			if (((aeTiledMap*)data)->m_bIsometric)
			{
				SstreamTranslator >> ((aeTiledMap*)data)->m_nTileSizeY;
			}
		}
		SstreamTranslator.clear();
	}

	return 0;
}

int aeTiledMap::InfluenceDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName)
{
	std::map < std::string, std::string> GenericMapValues;
	for (int i = 0; i < argument_count; i++)
	{
		GenericMapValues[std::string(pszColName[i])] = (argument_values[i] ? argument_values[i] : NULL);
	}

	std::basic_stringstream<char, std::char_traits<char>> SstreamTranslator;

	std::string pszID;
	SstreamTranslator.str(GenericMapValues["ID"]);
	SstreamTranslator >> pszID;
	SstreamTranslator.clear();
	if (pszID == "TileMap")
	{
		std::string pszName;
		SstreamTranslator.str(GenericMapValues["Name"]);
		SstreamTranslator >> pszName;
		SstreamTranslator.clear();

		SstreamTranslator.str(GenericMapValues["Variable"]);
		if (pszName == "Decay")
		{
			SstreamTranslator >> ((aeInfluenceCalculator*)data)->m_fDecay;
		} 
		else if (pszName == "Momentum")
		{
			SstreamTranslator >> ((aeInfluenceCalculator*)data)->m_fMomentum;
		}

		SstreamTranslator.clear();
	}

	return 0;
}

aeTiledMap::aeMapTile::aeMapTile()
{
}

aeTiledMap::aeMapTile::~aeMapTile()
{
}

float aeTiledMap::aeMapTile::GetInfluence() 
{ 
	return m_fInfluence; 
}

void aeTiledMap::aeMapTile::UpdateInfluence(float Influence)
{
	m_fInfluence = Max<float>(Min<float>(Influence, 1),-1);
}