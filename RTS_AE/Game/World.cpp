#include "stdafx.h"
#include "World.h"

aeWorld::aeWorld()
{
}


aeWorld::~aeWorld()
{
}

int aeWorld::Init(InitVariables * pInitVariables)
{
	SetWindowDimensions(pInitVariables->WindowRect, pInitVariables->WorldRenderRect);
	m_pSprites = pInitVariables->pSprites;
	m_pPresets = pInitVariables->pPresetList;
	m_pClock = pInitVariables->pClock;
	m_pszBinFilePath = *pInitVariables->pszBinFilePath;
	m_pRenderer = pInitVariables->pRenderer;
	m_CameraPosition = aeVector2{ 0,0 };
	//Init State Machine
	aeStateMachine* UnitStateMachine = new aeStateMachine();
	CUnitStateMachine* FSM = new CUnitStateMachine();
	CAttack* State0 = new CAttack();
	CIdle* State1 = new CIdle();
	CDeath* State2 = new CDeath();
	CMove_To* State3 = new CMove_To();
	UnitStateMachine->AddState(State0);
	UnitStateMachine->AddState(State1);
	UnitStateMachine->AddState(State2);
	UnitStateMachine->AddState(State3);
	UnitStateMachine->Init(FSM);

	aeStateMachine* AnimationStateMachine = new aeStateMachine();
	CAnimationStateMachine* ASM = new CAnimationStateMachine();;
	ASM->pPassAlong = (void*)this;
	CAttackAState* State4 = new CAttackAState();
	CIdleAState* State5 = new CIdleAState();
	CDeathAState* State6 = new CDeathAState();
	CMoveToAState* State7 = new CMoveToAState();
	AnimationStateMachine->AddState(State4);
	AnimationStateMachine->AddState(State5);
	AnimationStateMachine->AddState(State6);
	AnimationStateMachine->AddState(State7);
	AnimationStateMachine->Init(ASM);

	m_aStateMachines.push_back(UnitStateMachine);
	m_aStateMachines.push_back(AnimationStateMachine);

	aeTiledMap* NewTileMap = new aeTiledMap();
	NewTileMap->SetView(m_bIsometric);

	//TileMap = NewTileMap;

	aeInfluenceCalculator* IC = new aeInfluenceCalculator();
	NewTileMap->AddOns.push_back(IC);


	////Open database connection
	aeSQLConnector vConnector;
	vConnector.OpenDatabase(aeString(*pInitVariables->pszBinFilePath + TEXT("Database/Database.db")).c_str());
	//Execute a query on the database
	vConnector.QueryDatabase(TEXT("SELECT * FROM OnLoadVariables"), &(aeWorld::WorldLoadVariablesDeclaration), (void*)this);
	vConnector.QueryDatabase(TEXT("SELECT * FROM OnLoadVariables"), &(aeTiledMap::TileMapCreation), (void*)NewTileMap);
	vConnector.QueryDatabase(TEXT("SELECT * FROM OnLoadVariables"), &(aeTiledMap::InfluenceDefinition), (void*)IC);
	vConnector.QueryDatabase(TEXT("SELECT * FROM unit_type"), &(aeWorld::UnitTypeDefinition), (void*)this);
	vConnector.QueryDatabase(TEXT("SELECT * FROM Tile_Type"), &(aeWorld::TileTypeDefinition), (void*)this);
	vConnector.QueryDatabase(TEXT("SELECT * FROM Map_Presets"), &(aeWorld::MapCreationPresets), (void*)this);
	vConnector.QueryDatabase(TEXT("SELECT * FROM Unit_Sprites"), &(aeWorld::AnimationsCreation), (void*)this);
	//vConnector.QueryDatabase(TEXT("SELECT * FROM teams"), &(aeWorld::UnitsCreation), (void*)this);
	//Close database connection
	vConnector.CloseDatabase();

	Precalc();

	NewTileMap->CameraReference(this);
	NewTileMap->Init(pInitVariables->pRenderer, m_pPresets);
	IC->Init(NewTileMap);

	m_aObjects.push_back(NewTileMap);

	return 0;
}

void aeWorld::Destroy()
{
	for each(auto object in m_aObjects)
	{
		object->Destroy();
	}
	for each (auto StateMachine in m_aStateMachines)
	{
		StateMachine->Destroy();
	}
}

void aeWorld::Update(float fDelta)
{
	float fDistance = fDelta * m_fCameraSpeed;
	MoveCamera(fDistance * m_CameraDirection.x, fDistance * m_CameraDirection.y);
	for each(auto object in m_aObjects)
	{
		object->Update(fDelta);
	}
}

void aeWorld::Render(aeRenderer * pRenderer)
{
	for each(auto object in m_aObjects)
	{
		object->Render(pRenderer);
	}
}

void aeWorld::SetWindowDimensions(aeRect &WindowRect, aeRect &WorldRect)
{
	m_WindowRect.x = WindowRect.x;
	m_WindowRect.y = WindowRect.y;
	m_WindowRect.w = WindowRect.w;
	m_WindowRect.h = WindowRect.h;
	m_WorldRect = m_WindowRect;
	m_WorldRect.h = static_cast<int>(WindowRect.h*.75);
	m_DestRect = aeRect{ 0,0, WindowRect.w, static_cast<int>(WindowRect.h*.75) };
	m_PrecalcWorldWindowRect.x = WorldRect.x;
	m_PrecalcWorldWindowRect.y = WorldRect.y;
	Precalc();
}

void aeWorld::Keyboard(uint8 key)
{
	static bool bGrid = false;
	if (key != VK_LBUTTON && key >=0x30 && key <= 0x39 || key == 0x47)
	for each (auto object in m_aObjects)
	{
		if (object->Derivative)
		{
			if (key != 0x47)
				((aeTiledMap*)object)->SetPathFinder(key - 49);
			else
				((aeTiledMap*)object)->ShowGrid(bGrid = !bGrid);
		}
	}
}

void aeWorld::Clic(aePoint & ClicPoint, int Button)
{
	if (Button == VK_LBUTTON)
	{
		if (Click1 == nullptr)
		{
			aeVector2 temp = GetScreenToMapCoords(ClicPoint, m_CameraPosition, *GetCameraRect(), m_bIsometric);
			Click1 = new aePoint();

			Click1->x = temp.x;
			Click1->y = temp.y;
		}
		else if (Click2 == nullptr)
		{
			aeVector2 temp = GetScreenToMapCoords(ClicPoint, m_CameraPosition, *GetCameraRect(), m_bIsometric);
			Click2 = new aePoint();

			Click2->x = temp.x;
			Click2->y = temp.y;

			for each (auto object in m_aObjects)
			{
				if(object->Derivative)
					((aeTiledMap*)object)->MakeSearch(*Click1, *Click2);
			}
			

			delete Click1;
			delete Click2;

			Click1 = nullptr;
			Click2 = nullptr;
		}
	}
}

void aeWorld::MoveCamera(float dX, float dY)
{
	m_CameraPosition.x += dX;
	m_CameraPosition.y += dY;
}

void aeWorld::Precalc()
{
	m_PrecalcWorldWindowRect.w = m_WindowRect.w >> 1;
	m_PrecalcWorldWindowRect.h = m_WindowRect.h >> 1;
	m_PrecalcWindowActionSpace.w = m_WindowRect.w - m_nActionSpace;
	m_PrecalcWindowActionSpace.h = m_WindowRect.h - m_nActionSpace;
}

void aeWorld::CursorUpdate(aePoint& CursorPosition)
{
	m_CameraDirection.x = 0;
	m_CameraDirection.y = 0;
	if (CursorPosition.x <  m_nActionSpace  &&  CursorPosition.x >= m_WindowRect.x)
	{
		if (m_bIsometric)
		{
			m_CameraDirection.x += -COS_PI_QUARTER;
			m_CameraDirection.y += -COS_PI_QUARTER;
		}
		else
		{
			m_CameraDirection.x = -1;
		}
	}
	else if (CursorPosition.x > m_PrecalcWindowActionSpace.w && CursorPosition.x <= m_WindowRect.x+m_WindowRect.w)
	{
		if (m_bIsometric)
		{
			m_CameraDirection.x += COS_PI_QUARTER;
			m_CameraDirection.y += COS_PI_QUARTER;
		}
		else
		{
			m_CameraDirection.x = 1;
		}
	}
	if (CursorPosition.y > m_PrecalcWindowActionSpace.h && CursorPosition.y <= m_WindowRect.y+m_WindowRect.h)
	{
		if (m_bIsometric)
		{
			m_CameraDirection.x += COS_PI_QUARTER;
			m_CameraDirection.y += -COS_PI_QUARTER;
		}
		else
		{
			m_CameraDirection.y = -1;
		}
	}
	else if (CursorPosition.y < m_nActionSpace &&  CursorPosition.y >= m_WindowRect.y)
	{
		if (m_bIsometric)
		{
			m_CameraDirection.x += -COS_PI_QUARTER;
			m_CameraDirection.y += COS_PI_QUARTER;
		}
		else
		{
			m_CameraDirection.y = 1;
		}
	}
	m_CameraDirection.x = Min<float>(m_CameraDirection.x, 1);
	m_CameraDirection.y = Min<float>(m_CameraDirection.y, 1);
}

void aeWorld::CreateUnit(aeString UnitName, aeVector2 Position, aeVector2 Direction, int TeamID)
{
	m_aObjects.push_back(UnitFactory(UnitName, Position, Direction, TeamID, &m_aStateMachines));
}

CAnimation * aeWorld::GetAnimation(int ID, int State, int Direction)
{
	return m_aAnimations[ID][State][Direction];
}

aeGameObject * aeWorld::UnitFactory(aeString UnitName, aeVector2 Position, aeVector2 Direction, int TeamID, std::vector<aeStateMachine*>* StateMachines)
{
	for each (auto Preset in *m_pPresets)
	{
		if (Preset->GetPresetID() == static_cast<int>(PresetsID::UnitType))
		{
			if (((aeUnitType*)Preset)->m_pszName == UnitName)
			{
				aeGameObject* NewGameObject = new aeGameObject();
				CUnit * NewUnit = new CUnit();
				CAnimationRenderer* NewRenderer = new CAnimationRenderer();
				NewRenderer->Init(NewGameObject);

				NewUnit->m_pBaseUnit = ((aeUnitType*)Preset);
				NewUnit->m_vPosition = Position;
				NewUnit->m_vDirection = Direction;
				NewUnit->m_nTeam_ID = TeamID;
				NewUnit->Init(NewGameObject);
				NewUnit->m_pRenderer = NewRenderer;
				NewUnit->m_pStateMachines = StateMachines;

				NewGameObject->AddOns.push_back(NewUnit);
				NewGameObject->AddOns.push_back(NewRenderer);
				NewGameObject->Transform.Position = aeVector3{ Position.x,Position.y };

				return NewGameObject;
			}
		}
	}
	MessageBox(NULL, TEXT("UnitType Unknown"), TEXT("UnitFactory Error"), MB_ICONERROR);
	return nullptr;
}

bool * aeWorld::IsIsometric()
{
	return &m_bIsometric;
}

aePoint *aeWorld::GetSizeOfWorld()
{
	return &m_WorldSize;
}

aeRect *aeWorld::GetCameraRect()
{
	return &m_DestRect;
}

aeRect * aeWorld::GetWorldRect()
{
	return &m_WorldRect;
}

aeVector2 *aeWorld::GetCameraPosition()
{
	return &m_CameraPosition;
}

int aeWorld::UnitTypeDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName)
{
	std::map < std::string, std::string> GenericMapValues;
	for (int i = 0; i < argument_count; i++)
	{
		GenericMapValues[std::string(pszColName[i])] = (argument_values[i] ? argument_values[i] : NULL);
	}

	aeUnitType * NewType = new aeUnitType();

	int nTemp;
	std::basic_stringstream<char, std::char_traits<char>> SstreamTranslator;

	SstreamTranslator.str(GenericMapValues["ID"]);
	SstreamTranslator >> NewType->m_nID;
	SstreamTranslator.clear();

#if PLATFORM_TCHAR_IS_1_BYTE == 1
	SstreamTranslator.str(GenericMapValues["Name"]);
	SstreamTranslator >> NewType->m_pszName;
	SstreamTranslator.clear();
#else
	std::string pszTemp;
	SstreamTranslator.str(GenericMapValues["Name"]);
	SstreamTranslator >> pszTemp;
	SstreamTranslator.clear();
	NewType->m_pszName = s2ws(pszTemp).c_str();
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1

	SstreamTranslator.str(GenericMapValues["HP_Max"]);
	SstreamTranslator >> NewType->m_fHP_Max;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Attack_Range_Max"]);
	SstreamTranslator >> NewType->m_fAttack_Range_Max;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Attack_Range_Min"]);
	SstreamTranslator >> NewType->m_fAttack_Range_Min;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Attack_timer"]);
	SstreamTranslator >> NewType->m_fAttack_Speed;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["View_Range"]);
	SstreamTranslator >> NewType->m_fView_Range;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Speed"]);
	SstreamTranslator >> NewType->m_fSpeed;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["IsMilitant"]);
	SstreamTranslator >> nTemp;
	NewType->IsMilitant = (nTemp == 0) ? false:true;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Canbuild"]);
	SstreamTranslator >> nTemp;
	NewType->CanBuild = (nTemp == 0) ? false : true;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Radius"]);
	SstreamTranslator >> NewType->m_nRadius;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Image_ID"]);
	SstreamTranslator >> NewType->m_nImageID;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Strength"]);
	SstreamTranslator >> NewType->m_fStrength;
	SstreamTranslator.clear();

	for each (auto Sprite in *(((aeWorld*)data)->m_pSprites))
	{
		if (NewType->m_nImageID == Sprite->GetID())
		{
			NewType->m_pImage = Sprite;
		}
	}

	((aeWorld*)data)->m_pPresets->push_back(NewType);
	
	return 0;
}

int aeWorld::TileTypeDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName)
{
	std::map < std::string, std::string> GenericMapValues;
	for (int i = 0; i < argument_count; i++)
	{
		GenericMapValues[std::string(pszColName[i])] = (argument_values[i] ? argument_values[i] : NULL);
	}

	aeTileType * NewType = new aeTileType();

	std::basic_stringstream<char, std::char_traits<char>> SstreamTranslator;

	SstreamTranslator.str(GenericMapValues["ID"]);
	SstreamTranslator >> NewType->m_nID;
	SstreamTranslator.clear();

#if PLATFORM_TCHAR_IS_1_BYTE == 1
	SstreamTranslator.str(GenericMapValues["Name"]);
	SstreamTranslator >> NewType->m_pszName;
	SstreamTranslator.clear();
#else
	std::string pszTemp;
	SstreamTranslator.str(GenericMapValues["Name"]);
	SstreamTranslator >> pszTemp;
	SstreamTranslator.clear();
	NewType->m_pszName = s2ws(pszTemp).c_str();
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1

	SstreamTranslator.str(GenericMapValues["Cost"]);
	SstreamTranslator >> NewType->m_nCost;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Sprite_ID"]);
	SstreamTranslator >> NewType->m_nSpriteID;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Isometric"]);
	SstreamTranslator >> NewType->m_bIsometric;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Movement"]);
	SstreamTranslator >> NewType->m_nMovement;
	SstreamTranslator.clear();

	for each (auto Sprite in *(((aeWorld*)data)->m_pSprites))
	{
		if (NewType->m_nSpriteID == Sprite->GetID())
		{
			NewType->m_pImage = Sprite;
		}
	}

	((aeWorld*)data)->m_pPresets->push_back(NewType);

	return 0;
}

int aeWorld::MapCreationPresets(void * data, int argument_count, char ** argument_values, char ** pszColName)
{
	std::map < std::string, std::string> GenericMapValues;
	for (int i = 0; i < argument_count; i++)
	{
		GenericMapValues[std::string(pszColName[i])] = (argument_values[i] ? argument_values[i] : NULL);
	}

	aeMapPresets * NewType = new aeMapPresets();

	std::basic_stringstream<char, std::char_traits<char>> SstreamTranslator;

	SstreamTranslator.str(GenericMapValues["ID"]);
	SstreamTranslator >> NewType->m_nID;
	SstreamTranslator.clear();

#if PLATFORM_TCHAR_IS_1_BYTE == 1
	SstreamTranslator.str(GenericMapValues["Name"]);
	SstreamTranslator >> NewType->m_pszName;
	SstreamTranslator.clear();
#else
	std::string pszTemp;
	SstreamTranslator.str(GenericMapValues["Name"]);
	SstreamTranslator >> pszTemp;
	SstreamTranslator.clear();
	NewType->m_pszName = s2ws(pszTemp).c_str();
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1

	SstreamTranslator.str(GenericMapValues["Octaves"]);
	SstreamTranslator >> NewType->m_nOctaves;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Frequency"]);
	SstreamTranslator >> NewType->m_dFrequency;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Scale"]);
	SstreamTranslator >> NewType->m_dScale;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Persistance"]);
	SstreamTranslator >> NewType->m_dPersistance;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Lacuranity"]);
	SstreamTranslator >> NewType->m_dLacuranity;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Tile1_ID"]);
	SstreamTranslator >> NewType->m_nTileID1;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Tile2_ID"]);
	SstreamTranslator >> NewType->m_nTileID2;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Tile3_ID"]);
	SstreamTranslator >> NewType->m_nTileID3;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Top_Value1"]);
	SstreamTranslator >> NewType->m_fTopValue1;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Top_Value2"]);
	SstreamTranslator >> NewType->m_fTopValue2;
	SstreamTranslator.clear();
	
	((aeWorld*)data)->m_pPresets->push_back(NewType);

	return 0;
}

int aeWorld::UnitsCreation(void * data, int argument_count, char ** argument_values, char ** pszColName)
{
	std::map < std::string, std::string> GenericMapValues;
	for (int i = 0; i < argument_count; i++)
	{
		GenericMapValues[std::string(pszColName[i])] = (argument_values[i] ? argument_values[i] : NULL);
	}

	std::basic_stringstream<char, std::char_traits<char>> SstreamTranslator;

	SstreamTranslator.str(GenericMapValues["TeamID"]);
	int TeamID;
	SstreamTranslator >> TeamID;
	SstreamTranslator.clear();

	aeVector2 SpawnCenter;
	SstreamTranslator.str(GenericMapValues["Spawn_Area_X"]);
	SstreamTranslator >> SpawnCenter.x;
	SstreamTranslator.clear();
	SstreamTranslator.str(GenericMapValues["Spawn_Area_Y"]);
	SstreamTranslator >> SpawnCenter.y;
	SstreamTranslator.clear();

	float SpawningRadius;
	SstreamTranslator.str(GenericMapValues["Spawning_Radius"]);
	SstreamTranslator >> SpawningRadius;
	SstreamTranslator.clear();

	int nUnits;
	SstreamTranslator.str(GenericMapValues["Number_of_units"]);
	SstreamTranslator >> nUnits;
	SstreamTranslator.clear();

#if PLATFORM_TCHAR_IS_1_BYTE == 1
	aeString UnitName;
	SstreamTranslator.str(GenericMapValues["Type_of_unit"]);
	SstreamTranslator >> UnitName;
	SstreamTranslator.clear();
#else
	std::string pszTemp;
	SstreamTranslator.str(GenericMapValues["Type_of_unit"]);
	SstreamTranslator >> pszTemp;
	SstreamTranslator.clear();
	aeString UnitName = s2ws(pszTemp).c_str();
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1

	for (int i = 0; i < nUnits; i++)
	{
		int DisplacementX = rand() % (int)SpawningRadius;
		int DisplacementY = rand() % (int)SpawningRadius;
		aeVector2 SpawnPoint = { SpawnCenter.x + DisplacementX,SpawnCenter.y + DisplacementY };
		((aeWorld*)data)->CreateUnit(UnitName, SpawnPoint, SpawnPoint.Normalize(), TeamID);
	}

	return 0;
}

int aeWorld::WorldLoadVariablesDeclaration(void * data, int argument_count, char ** argument_values, char ** pszColName)
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
	if (pszID == "World")
	{
		std::string pszName;
		SstreamTranslator.str(GenericMapValues["Name"]);
		SstreamTranslator >> pszName;
		SstreamTranslator.clear();

		SstreamTranslator.str(GenericMapValues["Variable"]);
		if (pszName == "ActionSpace")
		{
			SstreamTranslator >> ((aeWorld*)data)->m_nActionSpace;
		}
		else if (pszName == "ScreenSpeed")
		{
			SstreamTranslator >> ((aeWorld*)data)->m_fCameraSpeed;
		}
		else if (pszName == "WorldSize")
		{
			SstreamTranslator >> ((aeWorld*)data)->m_WorldSize.x;
			((aeWorld*)data)->m_WorldSize.y = ((aeWorld*)data)->m_WorldSize.x;
		}
		else if (pszName == "FramesPerSec")
		{
			SstreamTranslator >> ((aeWorld*)data)->m_fFramesPerSec;
		}
		else if (pszName == "TimeScale")
		{
			SstreamTranslator >> ((aeWorld*)data)->m_fTimeScale;
			((aeWorld*)data)->m_pClock->SetVirtualTimeScale(((aeWorld*)data)->m_fTimeScale);
		}
		else if (pszName == "Isometric")
		{
			SstreamTranslator >> ((aeWorld*)data)->m_bIsometric;
		}
		SstreamTranslator.clear();
	}

	return 0;
}

int aeWorld::AnimationsCreation(void * data, int argument_count, char ** argument_values, char ** pszColName)
{
	std::map < std::string, std::string> GenericMapValues;
	for (int i = 0; i < argument_count; i++)
	{
		GenericMapValues[std::string(pszColName[i])] = (argument_values[i] ? argument_values[i] : NULL);
	}

	std::basic_stringstream<char, std::char_traits<char>> SstreamTranslator;

	int ID;
	SstreamTranslator.str(GenericMapValues["Name_ID"]);
	SstreamTranslator >> ID;
	SstreamTranslator.clear();

	int nState;
	SstreamTranslator.str(GenericMapValues["State"]);
	SstreamTranslator >> nState;
	SstreamTranslator.clear();

	int nDirection;
	SstreamTranslator.str(GenericMapValues["Direction"]);
	SstreamTranslator >> nDirection;
	SstreamTranslator.clear();

	aeUnitType* Unit = nullptr;
	for each (auto Preset in *((aeWorld*)data)->m_pPresets)
	{
		if (Preset->GetPresetID() == static_cast<int>(PresetsID::UnitType))
		{
			if (((aeUnitType*)Preset)->m_nImageID == ID)
			{
				Unit = (aeUnitType*)Preset;
				break;
			}
		}
	}

	int nFrame;
	SstreamTranslator.str(GenericMapValues["Frame"]);
	SstreamTranslator >> nFrame;
	SstreamTranslator.clear();

	aeRect rFrame;
	SstreamTranslator.str(GenericMapValues["Frame_Size_x"]);
	SstreamTranslator >> rFrame.x;
	SstreamTranslator.clear();
	SstreamTranslator.str(GenericMapValues["Frame_Size_y"]);
	SstreamTranslator >> rFrame.y;
	SstreamTranslator.clear();
	SstreamTranslator.str(GenericMapValues["Frame_Size_h"]);
	SstreamTranslator >> rFrame.h;
	SstreamTranslator.clear();
	SstreamTranslator.str(GenericMapValues["Frame_Size_w"]);
	SstreamTranslator >> rFrame.w;
	SstreamTranslator.clear();

	float fTimePerSec = 1.0f / ((aeWorld*)data)->m_fFramesPerSec;

	if (Unit != nullptr)
	{
		if (((aeWorld*)data)->m_aAnimations.empty()) {

			CAnimation* NewAnimation = new CAnimation(((aeWorld*)data)->GetCameraRect(), ((aeWorld*)data)->GetCameraPosition(), ((aeWorld*)data)->IsIsometric());
			NewAnimation->LoadSprite((aeSprite*)Unit->m_pImage);
			NewAnimation->InsertFrame(rFrame, fTimePerSec*nFrame, false);
			std::map<int, CAnimation*> DirectionArray;
			DirectionArray.insert(std::pair<int, CAnimation*>(nDirection, NewAnimation));
			std::map<int, std::map<int, CAnimation*> >Statearray;
			Statearray.insert(std::pair<int, std::map<int, CAnimation*>>(nState, DirectionArray));
			((aeWorld*)data)->m_aAnimations.insert(std::pair<char, std::map<int, std::map<int, CAnimation*> >>(ID, Statearray));

		}
		else {
			if (((aeWorld*)data)->m_aAnimations.find(ID) == ((aeWorld*)data)->m_aAnimations.end()) {
				CAnimation* NewAnimation = new CAnimation(((aeWorld*)data)->GetCameraRect(), ((aeWorld*)data)->GetCameraPosition(), ((aeWorld*)data)->IsIsometric());
				NewAnimation->LoadSprite((aeSprite*)Unit->m_pImage);
				NewAnimation->InsertFrame(rFrame, fTimePerSec*nFrame, false);
				std::map<int, CAnimation*> DirectionArray;
				DirectionArray.insert(std::pair<int, CAnimation*>(nDirection, NewAnimation));
				std::map<int, std::map<int, CAnimation*> >Statearray;
				Statearray.insert(std::pair<int, std::map<int, CAnimation*>>(nState, DirectionArray));
				((aeWorld*)data)->m_aAnimations.insert(std::pair<char, std::map<int, std::map<int, CAnimation*> >>(ID, Statearray));
			}
			else {
				if (((aeWorld*)data)->m_aAnimations[ID].find(nState) == ((aeWorld*)data)->m_aAnimations[ID].end())
				{
					CAnimation* NewAnimation = new CAnimation(((aeWorld*)data)->GetCameraRect(), ((aeWorld*)data)->GetCameraPosition(), ((aeWorld*)data)->IsIsometric());
					NewAnimation->LoadSprite((aeSprite*)Unit->m_pImage);
					NewAnimation->InsertFrame(rFrame, fTimePerSec*nFrame, false);
					std::map<int, CAnimation*> DirectionArray;
					DirectionArray.insert(std::pair<int, CAnimation*>(nDirection, NewAnimation));
					((aeWorld*)data)->m_aAnimations[ID].insert(std::pair<int, std::map<int, CAnimation*>>(nState, DirectionArray));
				}
				else
				{
					if (((aeWorld*)data)->m_aAnimations[ID][nState].find(nDirection) == ((aeWorld*)data)->m_aAnimations[ID][nState].end())
					{
						CAnimation* NewAnimation = new CAnimation(((aeWorld*)data)->GetCameraRect(), ((aeWorld*)data)->GetCameraPosition(), ((aeWorld*)data)->IsIsometric());
						NewAnimation->LoadSprite((aeSprite*)Unit->m_pImage);
						NewAnimation->InsertFrame(rFrame, fTimePerSec*nFrame, false);
						((aeWorld*)data)->m_aAnimations[ID][nState].insert(std::pair<int, CAnimation*>(nDirection, NewAnimation));
					}
					else {
						((aeWorld*)data)->m_aAnimations[ID][nState][nDirection]->InsertFrame(rFrame, fTimePerSec*nFrame, false);
					}
				}
			}
		}
	}
	return 0;
}
