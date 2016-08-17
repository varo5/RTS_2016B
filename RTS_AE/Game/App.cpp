#include "stdafx.h"
#include "App.h"


aeApp::aeApp()
{
}

aeApp::~aeApp()
{
}

int aeApp::Init()
{
	m_pEventManager = nullptr;
	m_bRunning = true;
	clickcounter = 0;
	keyboardcounter = 0;
	aeAppWindow::OnLoad OnLoadVariables;
	aeString pszFilepath = GetFilePath();
	////Open database connection
	aeSQLConnector* vConnector = new aeSQLConnector();
	vConnector->OpenDatabase(aeString(pszFilepath + TEXT("Database/Database.db")).c_str());
	//Execute a query on the database
	vConnector->QueryDatabase(TEXT("SELECT * FROM OnLoadVariables"), &(AppLoadVariables), (void*)this);
	vConnector->QueryDatabase(TEXT("SELECT * FROM OnLoadVariables"), &(WindowLoadVariables), (void*)&OnLoadVariables);
	if (m_Window.Init(OnLoadVariables, &m_Renderer))
	{
		vConnector->CloseDatabase();
		return -1;
	}
	vConnector->QueryDatabase(TEXT("SELECT * FROM OnLoadVariables"), &(TimerLoadVariables), (void*)&m_Clock);
	vConnector->QueryDatabase(TEXT("SELECT * FROM Sprites"), &(SpritesCreation), (void*)this);

	aeGUI::InitVariables *GUIInitVariables = new aeGUI::InitVariables();
	vConnector->QueryDatabase(TEXT("SELECT * FROM OnLoadVariables"), &(GUILoadVariables), (void*)GUIInitVariables);
	vConnector->CloseDatabase();

	delete vConnector;
	
	//Insert the rest of the values for the GUI
	GUIInitVariables->pszBinFilePath = pszFilepath;
	GUIInitVariables->WindowRect = aeRect{ m_Window.GetPosX(),m_Window.GetPosY(), m_Window.GetWidth(), m_Window.GetHeight() };
	GUIInitVariables->pWorld = &m_World;
	GUIInitVariables->pRenderer = &m_Renderer;
	GUIInitVariables->pSprites = &m_Sprites;
	GUIInitVariables->pPresetList = &m_Presets;
	if (m_GUI.Init(GUIInitVariables))
	{
		m_Window.Destroy();
		return -1;
	}
	if (m_Inputs.Init())
	{
		m_Window.Destroy();
		return -1;
	}
	if (m_Clock.Init())
	{
		m_Window.Destroy();
		return -1;
	}
	aeWorld::InitVariables WorldInitVariables;
	WorldInitVariables.pszBinFilePath = &pszFilepath;
	WorldInitVariables.WindowRect = aeRect{ m_Window.GetPosX(),m_Window.GetPosY(), m_Window.GetWidth(), m_Window.GetHeight() };
	WorldInitVariables.pRenderer = &m_Renderer;
	WorldInitVariables.pSprites = &m_Sprites;
	WorldInitVariables.pPresetList = &m_Presets;
	WorldInitVariables.pClock = &m_Clock;

	if (m_World.Init(&WorldInitVariables))
	{
		m_Window.Destroy();
		return -1;
	}
	
	return 0;
}

bool aeApp::IsRunning()
{
	return m_bRunning;
}

void aeApp::Update()
{
	m_Clock.Update();
	while (m_Clock.PollEvents(&m_uint8TimerManager))
	{
		switch (m_uint8TimerManager)
		{
		case static_cast<uint8>(TimersID::Update) :
		{
			clickcounter += m_Clock.RealDeltaTime();
			keyboardcounter += m_Clock.RealDeltaTime();
			m_Window.ProcessWindowEvents();
			m_Inputs.Update();
			while (PollEvent(&m_pEventManager))
			{
				switch (m_pEventManager->Type)
				{
				case static_cast<uint8>(EventTypes::KeyboardEvent) :
				{
					if (((aeKeyboardEvent*)m_pEventManager)->State == static_cast<uint8>(KeyStatesDecode::JustPressed))
					{
						keyboardcounter = 0;
						m_World.Keyboard(((aeKeyboardEvent*)m_pEventManager)->Key);
					}
					break;
				}				
				case static_cast<uint8>(EventTypes::MouseClic) :
				{
					if (clickcounter > 0.2)
					{
						clickcounter = 0;
						aePoint MousePosition = aePoint{ ((aeMouseButtonEvent*)m_pEventManager)->x, ((aeMouseButtonEvent*)m_pEventManager)->y };
						if (m_World.GetWorldRect()->HitTest(MousePosition.x, MousePosition.y))
							m_World.Clic(MousePosition, ((aeMouseButtonEvent*)m_pEventManager)->Button);
						else
							m_GUI.Clic(MousePosition, ((aeMouseButtonEvent*)m_pEventManager)->Button);
					}
					break;
				}
				case static_cast<uint8>(EventTypes::MouseMove) :
				{
					m_GUI.CursorUpdate(aePoint{ ((aeMouseMoveEvent*)m_pEventManager)->x, ((aeMouseMoveEvent*)m_pEventManager)->y });
					m_World.CursorUpdate(aePoint{ ((aeMouseMoveEvent*)m_pEventManager)->x, ((aeMouseMoveEvent*)m_pEventManager)->y });
					break;
				}		
				case static_cast<uint8>(EventTypes::MoveEvent) :
				{

					break;
				}
				case static_cast<uint8>(EventTypes::ResizeEvent) :
				{
					break;
				}
				case static_cast<uint8>(EventTypes::UserEvent) :
				{
					break;
				}															   
				case static_cast<uint8>(EventTypes::QuitEvent) :
				{
					Destroy(); 
					m_bRunning = false;
					return;
				}
				default:
					break;
				}
			}
			m_World.Update(m_Clock.VirtualDeltaTime());
			m_GUI.Update(m_Clock.VirtualDeltaTime());
			break;
		}												  
		case static_cast<uint8>(TimersID::Render) :
		{
			m_Renderer.Clear();
			m_World.Render(&m_Renderer);
			m_GUI.Render(&m_Renderer);
			m_Window.Render(&m_Renderer);
			break;
		}
		default:
			break;
		}
	}
	m_bRunning = true;
}

void aeApp::Destroy()
{
	m_Clock.Destroy();
	m_Renderer.Destroy();
	m_World.Destroy();
	m_Window.Destroy();
	for each (auto Sprite in m_Sprites)
	{
		Sprite->Free();
	}
}

int aeApp::AppLoadVariables(void * data, int argument_count, char ** argument_values, char ** pszColName)
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
	if (pszID == "App")
	{
		std::string pszName;
		SstreamTranslator.str(GenericMapValues["Name"]);
		SstreamTranslator >> pszName;
		SstreamTranslator.clear();

		SstreamTranslator.str(GenericMapValues["Variable"]);
		if (pszName == "WorldX")
		{
			SstreamTranslator >> ((aeApp*)data)->m_WorldRect.x;
		}
		else if (pszName == "WorldY")
		{
			SstreamTranslator >> ((aeApp*)data)->m_WorldRect.x;
		}
		else if (pszName == "WorldW")
		{
			SstreamTranslator >> ((aeApp*)data)->m_WorldRect.w;
		}
		else if (pszName == "WorldH")
		{
			SstreamTranslator >> ((aeApp*)data)->m_WorldRect.h;
		}
		SstreamTranslator.clear();
	}

	return 0;
}

int aeApp::WindowLoadVariables(void * data, int argument_count, char ** argument_values, char ** pszColName)
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
	if (pszID == "Window")
	{
		std::string pszName;
		SstreamTranslator.str(GenericMapValues["Name"]);
		SstreamTranslator >> pszName;
		SstreamTranslator.clear();

		SstreamTranslator.str(GenericMapValues["Variable"]);
		if (pszName == "WindowName")
		{
#if PLATFORM_TCHAR_IS_1_BYTE == 1
			SstreamTranslator >> ((aeAppWindow::OnLoad*)data)->pszWindowName;
#else
			std::string pszWindowName;
			SstreamTranslator >> pszWindowName;
			((aeAppWindow::OnLoad*)data)->pszWindowName = s2ws(pszWindowName);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		}
		else if (pszName == "X")
		{
			SstreamTranslator >> ((aeAppWindow::OnLoad*)data)->X;
		}
		else if (pszName == "Y")
		{
			SstreamTranslator >> ((aeAppWindow::OnLoad*)data)->Y;
		}
		else if (pszName == "Width")
		{
			SstreamTranslator >> ((aeAppWindow::OnLoad*)data)->Width;
		}
		else if (pszName == "Height")
		{
			SstreamTranslator >> ((aeAppWindow::OnLoad*)data)->Height;
		}
		else if (pszName == "WindowFlag")
		{
			SstreamTranslator >> ((aeAppWindow::OnLoad*)data)->WindowFlag;
		}
		else if(pszName == "Driver")
		{
#if PLATFORM_TCHAR_IS_1_BYTE == 1
			SstreamTranslator >> ((aeAppWindow::OnLoad*)data)->pszWindowName;
#else
			std::string pszDriverName;
			SstreamTranslator >> pszDriverName;
			((aeAppWindow::OnLoad*)data)->pszDriverName = s2ws(pszDriverName);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		}
		SstreamTranslator.clear();
	}
	return 0;
}

int aeApp::GUILoadVariables(void * data, int argument_count, char ** argument_values, char ** pszColName)
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
	if (pszID == "GUI")
	{
		std::string pszName;
		SstreamTranslator.str(GenericMapValues["Name"]);
		SstreamTranslator >> pszName;
		SstreamTranslator.clear();

		SstreamTranslator.str(GenericMapValues["Variable"]);
		if (pszName == "HTML")
		{
#if PLATFORM_TCHAR_IS_1_BYTE == 1
			SstreamTranslator >> ((aeGUI::InitVariables*)data)->pszFileName;
#else
			std::string pszFileName;
			SstreamTranslator >> pszFileName;
			((aeGUI::InitVariables*)data)->pszFileName = s2ws(pszFileName);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
			
		}
		SstreamTranslator.clear();
	}

	return 0;
}

int aeApp::TimerLoadVariables(void * data, int argument_count, char ** argument_values, char ** pszColName)
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
	if (pszID == "Timer")
	{
		std::string pszName;
		SstreamTranslator.str(GenericMapValues["Name"]);
		SstreamTranslator >> pszName;
		SstreamTranslator.clear();

		SstreamTranslator.str(GenericMapValues["Variable"]);
		if (pszName == "Update")
		{
			float Timer = 0;
			SstreamTranslator >> Timer;
			((aeClock*)data)->SetTimer(Timer, static_cast<uint8>(TimersID::Update));
		}
		else if (pszName == "Render")
		{
			float Timer = 0;
			SstreamTranslator >> Timer;
			((aeClock*)data)->SetTimer(1.0f/Timer, static_cast<uint8>(TimersID::Render));
		}
		SstreamTranslator.clear();
	}

	return 0;
}

int aeApp::SpritesCreation(void * data, int argument_count, char ** argument_values, char ** pszColName)
{
	std::map < std::string, std::string> GenericMapValues;
	for (int i = 0; i < argument_count; i++)
	{
		GenericMapValues[std::string(pszColName[i])] = (argument_values[i] ? argument_values[i] : NULL);
	}

	std::basic_stringstream<char, std::char_traits<char>> SstreamTranslator;

	aeString pszPath, pszFolder, pszName, pszExtension;

#if PLATFORM_TCHAR_IS_1_BYTE == 1
	SstreamTranslator.str(GenericMapValues["Folder"]);
	SstreamTranslator >> pszFolder;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["File_name"]);
	SstreamTranslator >> pszName;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["File_extension"]);
	SstreamTranslator >> pszExtension;
	SstreamTranslator.clear();
#else
	std::string pszTemp;

	SstreamTranslator.str(GenericMapValues["Folder"]);
	SstreamTranslator >> pszTemp;
	SstreamTranslator.clear();
	pszFolder = s2ws(pszTemp).c_str();

	SstreamTranslator.str(GenericMapValues["File_name"]);
	SstreamTranslator >> pszTemp;
	SstreamTranslator.clear();
	pszName = s2ws(pszTemp).c_str();

	SstreamTranslator.str(GenericMapValues["File_extension"]);
	SstreamTranslator >> pszTemp;
	SstreamTranslator.clear();
	pszExtension = s2ws(pszTemp).c_str();
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1

	pszPath = GetFilePath() + pszFolder + _T('\\') + pszName + _T('.') + pszExtension;

	int ID;
	SstreamTranslator.str(GenericMapValues["ID"]);
	SstreamTranslator >> ID;
	SstreamTranslator.clear();
	aeSprite* tmpSprite = aeSprite::CreateSprite(pszPath, pszName, &((aeApp*)data)->m_Renderer, ID);

	((aeApp*)data)->m_Sprites.push_back(tmpSprite);

	return 0;
}

aeString aeApp::GetFilePath()
{

#if PLATFORM_TCHAR_IS_1_BYTE == 1
	aeString s = EXPAND(UNITTESTPRJ);
	s.erase(0, 1); // erase the first quote
	s.erase(s.size() - 2); // erase the last quote and the dot
	return s;
#else
	std::string s = EXPAND(UNITTESTPRJ);
	s.erase(0, 1); // erase the first quote
	s.erase(s.size() - 2); // erase the last quote and the dot
	return aeString(s2ws(s));
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1

}