/**********************************************************************************************//**
 * @file	AppWindow.cpp
 *
 * @brief	Implements the application Windows Form.
 **************************************************************************************************/
#include "aeCoreStd.h"
#include "AppWindow.h"

/**********************************************************************************************//**
 * @namespace	aeCore
 *
 * @brief	.
 **************************************************************************************************/

namespace aeCore
{
	/**********************************************************************************************//**
	 * @fn	aeAppWindow::aeAppWindow()
	 *
	 * @brief	Default constructor.
	 **************************************************************************************************/

	aeAppWindow::aeAppWindow()
	{
		m_pSDLWindow = nullptr;
	}

	/**********************************************************************************************//**
	 * @fn	aeAppWindow::~aeAppWindow()
	 *
	 * @brief	Destructor.
	 **************************************************************************************************/

	aeAppWindow::~aeAppWindow()
	{
	}

	/**********************************************************************************************//**
	 * @fn	int aeAppWindow::Init(OnLoad& OnLoadVariables, aeRenderer* pRenderer)
	 *
	 * @brief	Starts SDL and creates a window. Gets 0 if it was initialized correctly, otherwise,
	 * 			 it will get an error number.
	 *
	 * @param [in,out]	OnLoadVariables	The on load variables.
	 * @param [in,out]	pRenderer	   	If non-null, the renderer.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	int aeAppWindow::Init(OnLoad& OnLoadVariables, aeRenderer* pRenderer)
	{
		int Succeed = 0;
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			MessageBox(NULL, TEXT("SDL couldn't initialize."), TEXT("SDL error"), MB_ICONERROR);
			Succeed = -1;
		}
		else
		{
			
#ifdef _DEBUG
			GetNumofDrivers();
#endif
			
#if PLATFORM_TCHAR_IS_1_BYTE == 1
			int nDriver = GetNumOfDriver(OnLoadVariables.pszDriverName.c_str());
			m_pSDLWindow = SDL_CreateWindow(
				OnLoadVariables.pszWindowName.c_str(), 
				OnLoadVariables.X, 
				OnLoadVariables.Y, 
				OnLoadVariables.Width, 
				OnLoadVariables.Height, 
				OnLoadVariables.WindowFlag);
#else
			int nDriver = GetNumOfDriver((char*)ws2s(OnLoadVariables.pszDriverName).c_str());
			m_pSDLWindow = SDL_CreateWindow(
				ws2s(OnLoadVariables.pszWindowName).c_str(), 
				OnLoadVariables.X, 
				OnLoadVariables.Y, 
				OnLoadVariables.Width, 
				OnLoadVariables.Height, 
				OnLoadVariables.WindowFlag);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
			if (m_pSDLWindow != NULL)
			{
				SDL_SysWMinfo wmInfo;
				SDL_VERSION(&wmInfo.version);
				SDL_GetWindowWMInfo(m_pSDLWindow, &wmInfo);
				HWND hwnd = wmInfo.info.win.window;
				RECT temp;
				GetWindowRect(hwnd, &temp);
				m_nX = temp.left + (OnLoadVariables.X - temp.left);
				m_nY = temp.top + (OnLoadVariables.Y - temp.top);
				m_nWidth = OnLoadVariables.Width;
				m_nHeight = OnLoadVariables.Height;
				/*m_nX = OnLoadVariables.X;
				m_nY = OnLoadVariables.Y;
				m_nWidth = OnLoadVariables.Width;
				m_nHeight = OnLoadVariables.Height;*/
				pRenderer->m_pRenderer = SDL_CreateRenderer(m_pSDLWindow, nDriver, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
				if (pRenderer->m_pRenderer != NULL)
				{
					SDL_SetRenderDrawColor(pRenderer->m_pRenderer, 0, 0, 0, 255);
					//Initialize PNG loading
					if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
					{
						MessageBox(NULL, TEXT("SDL_Image could not initialize."), TEXT("SDL error"), MB_ICONERROR);
						Succeed = -1;
					}
					if (TTF_Init() == -1)
					{
						MessageBox(NULL, TEXT("SDL_TTF could not initialize."), TEXT("SDL error"), MB_ICONERROR);
						Succeed = -1;
					}
				}
				else
				{
					Succeed = -1;
				}
			}
			else
			{
				MessageBox(NULL, TEXT("SDL couldn't create a new window."), TEXT("SDL error"), MB_ICONERROR);
				Succeed = -1;
			}
		}
		return Succeed;
	}

	/**********************************************************************************************//**
	 * @fn	void aeAppWindow::Render()
	 *
	 * @brief	Renders this object.
	 **************************************************************************************************/

	void aeAppWindow::Render(aeRenderer* pRenderer)
	{
		SDL_RenderPresent(pRenderer->m_pRenderer);
	}

	/**********************************************************************************************//**
	 * @fn	void aeAppWindow::Destroy()
	 *
	 * @brief	Destroys the Window.
	 **************************************************************************************************/

	void aeAppWindow::Destroy()
	{
		SDL_DestroyWindow(m_pSDLWindow);
	}

	/**********************************************************************************************//**
	 * @fn	int aeAppWindow::GetWidth()
	 *
	 * @brief	Gets the width.
	 *
	 * @return	The width.
	 **************************************************************************************************/

	int aeAppWindow::GetWidth()
	{
		return m_nWidth;
	}

	/**********************************************************************************************//**
	 * @fn	int aeAppWindow::GetHeight()
	 *
	 * @brief	Gets the height.
	 *
	 * @return	The height.
	 **************************************************************************************************/

	int aeAppWindow::GetHeight()
	{
		return m_nHeight;
	}

	/**********************************************************************************************//**
	 * @fn	int aeAppWindow::GetPosX()
	 *
	 * @brief	Gets position x coordinate.
	 *
	 * @return	The position x coordinate.
	 **************************************************************************************************/

	int aeAppWindow::GetPosX()
	{
		return m_nX;
	}

	/**********************************************************************************************//**
	 * @fn	int aeAppWindow::GetPosY()
	 *
	 * @brief	Gets position y coordinate.
	 *
	 * @return	The position y coordinate.
	 **************************************************************************************************/

	int aeAppWindow::GetPosY()
	{
		return m_nY;
	}

	void aeAppWindow::ProcessWindowEvents()
	{
		if (SDL_PollEvent(&m_EventManager))
		{
			switch (m_EventManager.type)
			{
			case SDL_QUIT:
			{
				aeQuitEvent* Quit = new aeQuitEvent();
				Quit->Type = static_cast<uint8>(EventTypes::QuitEvent);
				Quit->Priority = static_cast<uint8>(EventPriority::High);
				PostEvent(Quit);
			}
				break;
			case SDL_WINDOWEVENT_RESIZED:
			{
				aeResizeEvent* Resize = new aeResizeEvent();
				Resize->Type = static_cast<uint8>(EventTypes::ResizeEvent);
				Resize->Priority = static_cast<uint8>(EventPriority::High);
				Resize->w = m_EventManager.window.data1;
				Resize->h = m_EventManager.window.data2;
				PostEvent(Resize);
			}
			break;
			case SDL_WINDOWEVENT_MOVED:
			{
				aeMoveEvent* Move = new aeMoveEvent();
				Move->Type = static_cast<uint8>(EventTypes::MoveEvent);
				Move->Priority = static_cast<uint8>(EventPriority::High);
				Move->x = m_EventManager.window.data1;
				Move->y = m_EventManager.window.data2;
				PostEvent(Move);
			}
			break;
			default:
				break;
			}
		}
	}

	int aeAppWindow::GetNumOfDriver(char* pszDriverName)
	{
		int numdrivers = SDL_GetNumRenderDrivers();
		int nDriver = -1;
		for (int i = 0; i < numdrivers; i++)
		{
			SDL_RendererInfo drinfo;
			SDL_GetRenderDriverInfo(i, &drinfo);
			if (drinfo.name == pszDriverName)
			{
				return i;
			}
		}
		return nDriver;
	}

#ifdef _DEBUG
	void aeAppWindow::GetNumofDrivers()
	{
		using namespace std;
		int numdrivers = SDL_GetNumRenderDrivers();
		cout << "Render driver count: " << numdrivers << endl;
		for (int i = 0; i < numdrivers; i++) {
			SDL_RendererInfo drinfo;
			SDL_GetRenderDriverInfo(i, &drinfo);
			cout << "Driver name (" << i << "): " << drinfo.name << endl;
			if (drinfo.flags & SDL_RENDERER_SOFTWARE) cout << " the renderer is a software fallback" << endl;
			if (drinfo.flags & SDL_RENDERER_ACCELERATED) cout << " the renderer uses hardware acceleration" << endl;
			if (drinfo.flags & SDL_RENDERER_PRESENTVSYNC) cout << " present is synchronized with the refresh rate" << endl;
			if (drinfo.flags & SDL_RENDERER_TARGETTEXTURE) cout << " the renderer supports rendering to texture" << endl;
		}
	}
#endif // _DEBUG
}