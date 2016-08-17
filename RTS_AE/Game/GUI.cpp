#include "stdafx.h"
#include "GUI.h"

aeGUI::aeGUI()
{
	m_nClassID = ClassId::GUI;
}

aeGUI::~aeGUI()
{
	Destroy();
}

int aeGUI::Init(InitVariables * pInitVariables)
{
	m_pRenderer = pInitVariables->pRenderer;
	m_pWorld = pInitVariables->pWorld;
	m_pSprites = pInitVariables->pSprites;
	m_pPresetList = pInitVariables->pPresetList;
	m_WindowRect = pInitVariables->WindowRect;
	m_DstRect = aeRect{ 0, static_cast<int>(pInitVariables->WindowRect.h*0.75f), pInitVariables->WindowRect.w, static_cast<int>(pInitVariables->WindowRect.h*0.25f) };

	m_pWebListener = new CWebListener();

	std::string File = "file:///" + ws2s(pInitVariables->pszBinFilePath.c_str()) + ws2s(pInitVariables->pszFileName.c_str());

	m_pWebListener->Init(m_pRenderer->m_pRenderer, File.c_str(), m_DstRect.x, m_DstRect.y, m_DstRect.w, m_DstRect.h);


	/*aeGUIObject* Menu = new aeGUIObject();
	aeSpriteRenderer* SpriteRenderer = new aeSpriteRenderer();

	SpriteRenderer->SetParent(Menu);
	SpriteRenderer->WindowSize = aePoint{WindowRect.w,WindowRect.h};
	
	for each (auto Sprite in *m_pSprites)
	{
		if (Sprite->Name == TEXT("GUI"))
		{
			SpriteRenderer->SetSprite(Sprite);
		}
	}

	Menu->AddOns.push_back(SpriteRenderer);

	m_aObjects.push_back(Menu);*/

	return 0;
}

void aeGUI::Destroy()
{
	m_pWebListener->Destroy();
	for each (auto Object in m_aObjects)
	{
		Object->Destroy();
	}
	for each (auto Pair in m_aFonts)
	{
		Pair.second->Destroy();
	}
}

void aeGUI::Update(float fDelta)
{
	for each (auto Object in m_aObjects)
	{
		Object->Update(fDelta);
	}
	m_pWebListener->Update();
}

void aeGUI::Render(aeRenderer * pRenderer)
{
	for each(auto Object in m_aObjects)
	{
		Object->Render(pRenderer);
	}
	m_pWebListener->Render();
}

void aeGUI::Clic(aePoint & ClicPoint, int Button)
{
	switch (Button)
	{
	case VK_LBUTTON:
	{
		if (m_DstRect.HitTest(ClicPoint.x, ClicPoint.y - m_DstRect.y - 40))
		{
			m_pWebListener->m_pWebView->InjectMouseDown(Awesomium::kMouseButton_Left);
			m_pWebListener->m_pWebView->InjectMouseUp(Awesomium::kMouseButton_Left);
		}
		for each(auto Object in m_aObjects)
		{
			for each (auto AddOn in Object->AddOns)
			{
				if (AddOn->GetAddOnID() == AddOnId::Scripts)
				{
					if (((aeScript*)AddOn)->GetScriptId() == ScriptId::ButtonScript)
					{
						((aeButtonScript*)AddOn)->ClickOn(ClicPoint);
					}
				}
			}			
		}
		break;
	}
	default:
		break;
	}
	
}

void aeGUI::CursorUpdate(aePoint & CursorPosition)
{
	m_pWebListener->m_pWebView->InjectMouseMove(CursorPosition.x, CursorPosition.y - m_DstRect.y - 40);
}

int aeGUI::FontsDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName)
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

	std::string pszFolder;
	SstreamTranslator.str(GenericMapValues["Folder"]);
	SstreamTranslator >> pszFolder;
	SstreamTranslator.clear();

	std::string pszFileName;
	SstreamTranslator.str(GenericMapValues["File_name"]);
	SstreamTranslator >> pszFileName;
	SstreamTranslator.clear();

	std::string pszFileExt;
	SstreamTranslator.str(GenericMapValues["File_extension"]);
	SstreamTranslator >> pszFileExt;
	SstreamTranslator.clear();

	int nSize;
	SstreamTranslator.str(GenericMapValues["Size"]);
	SstreamTranslator >> nSize;
	SstreamTranslator.clear();

	aeString pszFilePath;
#if PLATFORM_TCHAR_IS_1_BYTE == 1
	pszFilePath = ((aeGUI*)data)->m_pszBinFilePath + "/" + pszFolder + "/" + pszFileName + "/" + pszFileExt;
	((aeGUI*)data)->m_aFonts.insert(make_pair(pszFileName, new aeFont(pszFilePath, pszFileName.c_str()), nSize)));
#else
	pszFilePath = ((aeGUI*)data)->m_pszBinFilePath + TEXT("/") + s2ws(pszFolder).c_str() + TEXT("/") + s2ws(pszFileName).c_str() + TEXT("/") + s2ws(pszFileExt).c_str();
	((aeGUI*)data)->m_aFonts.insert(std::pair<aeString, aeFont*>(s2ws(pszFileName), new aeFont(pszFilePath, aeString(s2ws(pszFileName).c_str()), nSize)));
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1

	return 0;
}

int aeGUI::ButtonsDefinition(void * data, int argument_count, char ** argument_values, char ** pszColName)
{
	std::map < std::string, std::string> GenericMapValues;
	for (int i = 0; i < argument_count; i++)
	{
		GenericMapValues[std::string(pszColName[i])] = (argument_values[i] ? argument_values[i] : NULL);
	}

	std::basic_stringstream<char, std::char_traits<char>> SstreamTranslator;

	aeString pszFontName;
	aeString pszText;
#if PLATFORM_TCHAR_IS_1_BYTE == 1
	SstreamTranslator.str(GenericMapValues["Font"]);
	SstreamTranslator >> pszFontName;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["Text"]);
	SstreamTranslator >> pszText;
	SstreamTranslator.clear();
#else
	std::string pszTemp;
	SstreamTranslator.str(GenericMapValues["Font"]);
	SstreamTranslator >> pszTemp;
	SstreamTranslator.clear();
	pszFontName = s2ws(pszTemp).c_str();

	SstreamTranslator.str(GenericMapValues["Text"]);
	SstreamTranslator >> pszTemp;
	SstreamTranslator.clear();
	pszText = s2ws(pszTemp).c_str();
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1

	int nSize = 0;
	SstreamTranslator.str(GenericMapValues["Font"]);
	SstreamTranslator >> nSize;
	SstreamTranslator.clear();

	aeRGB Color;
	SstreamTranslator.str(GenericMapValues["ColorR"]);
	SstreamTranslator >> Color.r;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["ColorG"]);
	SstreamTranslator >> Color.g;
	SstreamTranslator.clear();

	SstreamTranslator.str(GenericMapValues["ColorB"]);
	SstreamTranslator >> Color.b;
	SstreamTranslator.clear();

	aeSprite* NewSprite = aeSprite::CreateTextImage(((aeGUI*)data)->m_pRenderer, ((aeGUI*)data)->m_aFonts[pszFontName],pszText,Color);

	aeGUIObject* NewObject = new aeGUIObject();
	aeButtonScript* NewButton = new aeButtonScript(NewObject);

	NewObject->AddOns.push_back(NewButton);

	((aeGUI*)data)->m_aObjects.push_back(NewObject);

	return 0;
}
