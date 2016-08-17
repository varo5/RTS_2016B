#include "stdafx.h"

#include "Awesomium\\WebManager.h"
#include "Awesomium\method_dispatcher.h"

CWebListener::CWebListener() : m_pWebView(nullptr)
{
}

CWebListener::~CWebListener()
{
	Destroy();
}
//!event fired when app and webcore have been loaded

void CWebListener::OnLoaded()
{
	BindMethods(m_pWebView);
}

inline void CWebListener::OnUpdate()
{
	//! ?????????
}

inline void CWebListener::OnShutdown()
{
	//! ??????????????????????
}

void CWebListener::Init(SDL_Renderer * pRenderer, const char * pAdress, int X, int Y, int sizeX, int sizeY)
{
	m_SizeX = sizeX;
	m_SizeY = sizeY;

	m_DstRect.x = X;
	m_DstRect.y = Y;
	m_DstRect.w = sizeX;
	m_DstRect.h = sizeY;
	m_pAdress = pAdress;
	m_pRenderer = pRenderer;
	Load();

	//! get a texture in the dedicated videomemory or w/e this shit initializes memory to.
	m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, sizeX, sizeY);
	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);	//! SET THE GODDAMN BLEND MODE 
}

void CWebListener::Update()
{
	do {
		m_pWebCore->Update();					//! update the webcore until the webview loads completely
	} while (m_pWebView->IsLoading());

	OnUpdate();

	m_pSurface = m_pWebView->surface();		//! ???????? this can be moved somewhere else where it isn't called 60 times per second TODO

	Awesomium::BitmapSurface* pBMPSurface = static_cast<Awesomium::BitmapSurface*>(m_pSurface);
	unsigned char* pBuffer;
	int pitch = 0;

	if (SDL_LockTexture(m_pTexture, nullptr, (void**)&pBuffer, &pitch))	//! lock the texture
	{
		printf(SDL_GetError());						//! adsfasdf
	}
	pBMPSurface->CopyTo(pBuffer, pitch, 4, false, false);	//! transfer the buffer from the surface to the sdl texture

	SDL_UnlockTexture(m_pTexture);
}

void CWebListener::Render()
{
	//! render stuff
	if (SDL_RenderCopy(m_pRenderer, m_pTexture, nullptr, &m_DstRect))
	{
		printf("Error");
	}
}

void CWebListener::Destroy()
{
	if (m_pWebView)
	{
		m_pWebView->Destroy();
		m_pWebView = nullptr;
	}

	OnShutdown();

	if (m_pWebCore)
		m_pWebCore->Shutdown();
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}
	//SAFE_DELETE(m_pSurface);

	m_SizeX = 0;
	m_SizeY = 0;
	m_pAdress = nullptr;
	m_pRenderer = nullptr;

	SAFE_DELETE(m_pMethodDispatcher);
}

void CWebListener::BindMethods(Awesomium::WebView * pWebView)
{
	//Create a global js object named app
	Awesomium::JSValue result = pWebView->CreateGlobalJavascriptObject(Awesomium::WSLit("UI"));
	if (result.IsObject())
	{
		//Bind our custom method to it.
		Awesomium::JSObject& app_object = result.ToObject();
		if (!m_pMethodDispatcher)
			m_pMethodDispatcher = new MethodDispatcher();
		
		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("MapGenerator"), JSDelegate(this, &CWebListener::OnGeneratorClick));
		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("Brush"), JSDelegate(this, &CWebListener::OnBrushClick));
		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("Pathfinding"), JSDelegate(this, &CWebListener::OnPathfindingClick));
		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("Influence"), JSDelegate(this, &CWebListener::OnInfluenceClick));

		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("Start"), JSDelegate(this, &CWebListener::OnStart));
		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("Stop"), JSDelegate(this, &CWebListener::OnStop));
		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("Reset"), JSDelegate(this, &CWebListener::OnReset));

		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("ChangeBrush"), JSDelegate(this, &CWebListener::OnChangeBrush));
		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("ChangePathfinding"), JSDelegate(this, &CWebListener::OnChangePathfinding));
		m_pMethodDispatcher->Bind(app_object, Awesomium::WSLit("ChangeHeuristic"), JSDelegate(this, &CWebListener::OnChangeHeuristic));
		
	}
	//BInd our method dispatcher to the webView
	pWebView->set_js_method_handler(m_pMethodDispatcher);
}

void CWebListener::OnBrushClick(Awesomium::WebView* pCaller, const Awesomium::JSArray& args)
{
	/*UIData* pData = new UIData();
	pData->type = UI_BRUSH;
	g_MESSAGE()->PostMsg(new CMessage(MSG_UI_CHANGE, (void*)pData, 0));*/
}

void CWebListener::OnGeneratorClick(Awesomium::WebView * pCaller, const Awesomium::JSArray & args)
{
	/*UIData* pData = new UIData();
	pData->type = UI_BRUSH;
	g_MESSAGE()->PostMsg(new CMessage(MSG_UI_CHANGE, (void*)pData, 0));*/
}

void CWebListener::OnPathfindingClick(Awesomium::WebView * pCaller, const Awesomium::JSArray & args)
{

	/*UIData* pData = new UIData();
	pData->type = UI_PATHFINDING;
	g_MESSAGE()->PostMsg(new CMessage(MSG_UI_CHANGE, (void*)pData, 0));*/
}

void CWebListener::OnInfluenceClick(Awesomium::WebView * pCaller, const Awesomium::JSArray & args)
{
	/*UIData* pData = new UIData();
	pData->type = UI_INFLUENCEMAP;
	g_MESSAGE()->PostMsg(new CMessage(MSG_UI_CHANGE, (void*)pData, 0));*/
}

void CWebListener::OnStart(Awesomium::WebView * pCaller, const Awesomium::JSArray & args)
{
	for (int i = 0; i < args.size(); i++)
	{
		Awesomium::JSValue a = args[i];
	}

}

void CWebListener::OnStop(Awesomium::WebView * pCaller, const Awesomium::JSArray & args)
{
	for (int i = 0; i < args.size(); i++)
	{
		Awesomium::JSValue a = args[i];
	}

}

void CWebListener::OnReset(Awesomium::WebView * pCaller, const Awesomium::JSArray & args)
{
	for (int i = 0; i < args.size(); i++)
	{
		Awesomium::JSValue a = args[i];
	}

}

void CWebListener::OnChangeHeuristic(Awesomium::WebView * pCaller, const Awesomium::JSArray & args)
{
}

void CWebListener::OnChangePathfinding(Awesomium::WebView * pCaller, const Awesomium::JSArray & args)
{
	//PathfindingData* pData = new PathfindingData();

	for (int i = 0; i < args.size(); i++)
	{
		Awesomium::JSValue a = args[i];
		auto temp = ToString(a.ToString());

	}
}

void CWebListener::OnChangeBrush(Awesomium::WebView * pCaller, const Awesomium::JSArray & args)
{
	/*BrushData* pData = new BrushData();
	Awesomium::JSValue a = args[0];
	auto temp = ToString(a.ToString());
	if (temp == "Grass")
	{
		pData->type = TT_WALKABLE;
	}
	else if (temp == "Water")
	{
		pData->type = TT_WATER;
	}
	g_MESSAGE()->PostMsg(new CMessage(MSG_TOOLDATA_CHANGE, (void*)pData, 0));*/
}

void CWebListener::Load()
{
	if (!Awesomium::WebCore::instance())
	{
		m_pWebCore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
	}
	else
	{
		m_pWebCore = Awesomium::WebCore::instance();
	}

	m_pWebView = m_pWebCore->CreateWebView(m_SizeX, m_SizeY);
	m_pWebView->Focus();
	m_pWebView->SetTransparent(true);

	Awesomium::WebURL url(Awesomium::WSLit(m_pAdress));

	m_pWebView->LoadURL(url);

	while (m_pWebView->IsLoading()) {
		m_pWebCore->Update();					//! update the webcore until the webview loads completely
	}

	OnLoaded();	// this can also go after setting transparency????
}

