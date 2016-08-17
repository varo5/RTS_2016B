#pragma once
#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

class aeApp
{
public:
	aeApp();
	~aeApp();

	int Init();
	bool IsRunning();
	void Update();
	void Destroy();

	static aeString GetFilePath();

	static int AppLoadVariables(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int WindowLoadVariables(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int GUILoadVariables(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int TimerLoadVariables(void * data, int argument_count, char ** argument_values, char ** pszColName);
	static int SpritesCreation(void * data, int argument_count, char ** argument_values, char ** pszColName);

private:
	aeAppWindow m_Window;
	aeRenderer m_Renderer;
	aeWorld m_World;
	aeGUI m_GUI;
	aeEvent* m_pEventManager;
	uint8 m_uint8TimerManager;
	aeClock m_Clock;
	aeInputs m_Inputs;
	aeRect m_WorldRect;
	SpriteList m_Sprites;
	PresetsList m_Presets;

	bool m_bRunning;
	bool m_bDebug;

	float clickcounter;
	float keyboardcounter;
};