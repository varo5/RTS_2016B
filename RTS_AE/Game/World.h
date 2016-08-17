#pragma once
#include "StateMachine.h"

class aeGUI;

class aeWorld : public aeBaseClass
{
private:
	friend class aeGUI;
	PresetsList* m_pPresets;
	std::list<aeGameObject*> m_aObjects;
	std::vector<aeStateMachine*> m_aStateMachines;
	SpriteList* m_pSprites;
	std::map<int,std::map<int,std::map<int,CAnimation*>>> m_aAnimations;

	aeRect m_WindowRect;
	aeRect m_DestRect;
	aeRect m_WorldRect;
	aeRect m_PrecalcWorldWindowRect;
	aePoint m_PrecalcWindowActionSpace;
	aePoint m_WorldSize;
	aeVector2 m_CameraDirection;
	aeVector2 m_CameraPosition;

	aePoint* Click1;
	aePoint* Click2;

	aeString m_pszBinFilePath;

	aeRenderer* m_pRenderer;
	aeGameObject* Controlled;
	aeClock* m_pClock;

	//aeTiledMap* TileMap;

	int m_nActionSpace;
	float m_fCameraSpeed;
	float m_fFramesPerSec;
	float m_fTimeScale;

	bool m_bIsometric;

	static int UnitTypeDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int TileTypeDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int MapCreationPresets(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int UnitsCreation(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int WorldLoadVariablesDeclaration(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int AnimationsCreation(void * data, int argument_count, char ** argument_values, char ** pszColName);

	aeGameObject* UnitFactory(aeString UnitName, aeVector2 Position, aeVector2 Direction, int TeamID, std::vector<aeStateMachine*>* StateMachines);

	void MoveCamera(float dX, float dY);
	void Precalc();
public:
	aeWorld();
	~aeWorld();
public:
	struct InitVariables
	{
		aeString *pszBinFilePath;
		aeRect WindowRect;
		aeRect WorldRenderRect;
		aeRenderer * pRenderer;
		aeClock* pClock;
		SpriteList* pSprites;
		PresetsList* pPresetList;
	};

	int Init(InitVariables * pInitVariables);
	void Destroy();
	void Update(float fDelta);
	void Render(aeRenderer * pRenderer);	
	void SetWindowDimensions(aeRect &WindowRect, aeRect &WorldRect);

	void Keyboard(uint8 key);
	void Clic(aePoint& ClicPoint, int Button);
	void CursorUpdate(aePoint& CursorPosition);
	void CreateUnit(aeString UnitName, aeVector2 Position, aeVector2 Direction, int TeamID);

	bool* IsIsometric();
	aePoint *GetSizeOfWorld();
	aeRect *GetCameraRect();
	aeRect *GetWorldRect();
	aeVector2 *GetCameraPosition();
	CAnimation* GetAnimation(int ID, int State, int Direction);
};

