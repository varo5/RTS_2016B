#pragma once


#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>

#include <SDL.h>
class MethodDispatcher;

/* tutorial
stuff in the main application class:
	CWebApplication::CWebListener* g_WebListener;
stuff in the init:
	g_WebListener = new CWebApplication::CWebListener();
	g_WebListener->m_pWebApp->Init(m_pRenderer, "file:///UI/UI.html", g_ResolutionX, g_ResolutionY);

stuff in your update:
	g_WebListener->m_pWebView->InjectMouseMove(e.motion.x, e.motion.y);
	
	if(mousebuttonLDown)
		g_WebListener->m_pWebView->InjectMouseDown(Awesomium::kMouseButton_Left);
	if(mousebuttonRDOwn)
		g_WebListener->m_pWebView->InjectMouseDown(Awesomium::kMouseButton_Right);
	if(mousebuttonLUP)
		g_WebListener->m_pWebView->InjectMouseUp(Awesomium::kMouseButton_Left);
	if(mousebuttonRUP)
		g_WebListener->m_pWebView->InjectMouseUp(Awesomium::kMouseButton_Right);

		g_WebListener->Update();

stuff in your render:
		g_Weblistener->Render();	

stuff in your destroy:
		g_Weblistener->Destroy();
*/

/*! \brief manages the true mastermind behind everything, the webapplication class. Also holds the webview awesomium stuff, instance this class instead of CWebApplication
*/
class CWebListener
{
public:
	CWebListener();
	virtual ~CWebListener();

	//! events fired when app and webcore do stuff
	virtual void OnLoaded();
	virtual void OnUpdate();//! Event fired of each run loop
	virtual void OnShutdown();//! event fired when app is shutting down 

	void Init(SDL_Renderer* pRenderer, const char * pAdress, int X, int Y, int sizeX, int sizeY);
	void Update();
	void Render();
	void Destroy();

	/*!\brief binds functions in the html to this class methods
	*/
	void BindMethods(Awesomium::WebView* pWebView);

	/*! Bound methods section, pcaller is the webview that calls the method args holds the parameter data from the js method*/
	/* Main Buttons*/
	void OnBrushClick(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);
	void OnGeneratorClick(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);
	void OnPathfindingClick(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);
	void OnInfluenceClick(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);

	void OnStart(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);
	void OnStop(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);
	void OnReset(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);

	void OnChangeHeuristic(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);
	void OnChangePathfinding(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);
	void OnChangeBrush(Awesomium::WebView* pCaller, const Awesomium::JSArray& args);

public:
	Awesomium::WebView* m_pWebView;					//! pointer to the webView
	MethodDispatcher* m_pMethodDispatcher;			//! pointer to the js methods dispatcher

protected:
	/*! initializes the webcore if needed and creates the webview, sets the focus to it and tells the listener that the webpage was loaded formethod binding
	*/
	virtual void Load();

	SDL_Texture* m_pTexture;		//! texture to 
	SDL_Renderer* m_pRenderer;		//! sdl renderer
	SDL_Rect m_DstRect;				//! the Destination size and position
	Awesomium::Surface* m_pSurface;	//! Surface to render to
	Awesomium::WebCore* m_pWebCore;	//! pointer to the webcore, awesomium manages its own memory, so eh, doesn't matter if you don't delete it
	

	int m_SizeX;			//! webview/image dimensions
	int m_SizeY;
private:
	const char* m_pAdress;	//! Adress of the webpage
};

