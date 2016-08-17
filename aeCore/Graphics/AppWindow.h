/**********************************************************************************************//**
 * @file	AppWindow.h
 *
 * @brief	Declares the application Windows Form.
 * 			
 * @author	Alvaro Estrada
 * @date	14/05/2016
 **************************************************************************************************/

#pragma once
 /************************************************************************************************************************/
 /* Inclusion of the necessary header files																				*/
 /************************************************************************************************************************/
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_syswm.h>
#include "Renderer.h"

#include "../BasicClasses.h"
#include "dll_definition.h"

 /************************************************************************************************************************/
 /* Constants definition                                       															*/
 /************************************************************************************************************************/

namespace aeCore
{
	class aeRenderer;
	/**********************************************************************************************//**
	 * @typedef	enum
	 *
	 * @brief	Defines an alias representing the enum.
	 **************************************************************************************************/

	enum struct LIBRARY_EXPORT WindowFlags : uint16
	{
		WINDOW_FULLSCREEN = 0x00000001,         /**< full-screen window */
		WINDOW_OPENGL = 0x00000002,             /**< window usable with OpenGL context */
		WINDOW_SHOWN = 0x00000004,              /**< window is visible */
		WINDOW_HIDDEN = 0x00000008,             /**< window is not visible */
		WINDOW_BORDERLESS = 0x00000010,         /**< no window decoration */
		WINDOW_RESIZABLE = 0x00000020,          /**< window can be resized */
		WINDOW_MINIMIZED = 0x00000040,          /**< window is minimized */
		WINDOW_MAXIMIZED = 0x00000080,          /**< window is maximized */
		WINDOW_INPUT_GRABBED = 0x00000100,      /**< window has grabbed input focus */
		WINDOW_INPUT_FOCUS = 0x00000200,        /**< window has input focus */
		WINDOW_MOUSE_FOCUS = 0x00000400,        /**< window has mouse focus */
		WINDOW_FULLSCREEN_DESKTOP = (WINDOW_FULLSCREEN | 0x00001000),
		WINDOW_FOREIGN = 0x00000800,            /**< window not created by SDL */
		WINDOW_ALLOW_HIGHDPI = 0x00002000,      /**< window should be created in high-DPI mode if supported */
		WINDOW_MOUSE_CAPTURE = 0x00004000       /**< window has mouse captured (unrelated to INPUT_GRABBED) */
	};

	/**********************************************************************************************//**
	 * @class	aeAppWindow
	 *
	 * @brief	This class purpose is to create a client window where the entire program will display.
	 *
	 **************************************************************************************************/

	class LIBRARY_EXPORT aeAppWindow
	{
	protected:
		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		SDL_Window* m_pSDLWindow;
		SDL_Event m_EventManager;
		int m_nX, m_nY, m_nWidth, m_nHeight;
	public:
		/************************************************************************************************************************/
		/* Constructors  declaration                                                      													*/
		/************************************************************************************************************************/
		aeAppWindow();
		~aeAppWindow();
	public:
		struct OnLoad
		{
			aeString pszWindowName, pszDriverName;
			int X, Y, Width, Height, WindowFlag;
		};

		/************************************************************************************************************************/
		/* Functions declaration                                            													*/
		/************************************************************************************************************************/
	public:

		/**********************************************************************************************//**
		 * @fn	int aeAppWindow::Init(OnLoad& OnLoadVariables, aeRenderer* pRenderer);
		 *
		 * @brief	Starts SDL and creates a window. Gets 0 if it was initialized correctly, otherwise,
		 * 			 it will get an error number.
		 *
		 * @param [in,out]	OnLoadVariables	The on load variables.
		 * @param [in,out]	pRenderer	   	If non-null, the renderer.
		 *
		 * @return	An int.
		 **************************************************************************************************/

		int Init(OnLoad& OnLoadVariables, aeRenderer* pRenderer);

		/**********************************************************************************************//**
		 * @fn	void aeAppWindow::Render(aeRenderer* pRenderer);
		 *
		 * @brief	Renders the given renderer pointer.
		 *
		 * @param [in,out]	pRenderer	If non-null, the renderer.
		 **************************************************************************************************/

		void Render(aeRenderer* pRenderer);

		/**********************************************************************************************//**
		 * @fn	void aeAppWindow::Destroy();
		 *
		 * @brief	Closes the SDL window and cleans up the source.
		 **************************************************************************************************/

		void Destroy();

		/**********************************************************************************************//**
		 * @fn	int aeAppWindow::GetWidth();
		 *
		 * @brief	Gets the width.
		 *
		 * @return	The width.
		 **************************************************************************************************/

		int GetWidth();

		/**********************************************************************************************//**
		 * @fn	int aeAppWindow::GetHeight();
		 *
		 * @brief	Gets the height.
		 *
		 * @return	The height.
		 **************************************************************************************************/

		int GetHeight();

		/**********************************************************************************************//**
		 * @fn	int aeAppWindow::GetPosX();
		 *
		 * @brief	Gets position x coordinate.
		 *
		 * @return	The position x coordinate.
		 **************************************************************************************************/

		int GetPosX();

		/**********************************************************************************************//**
		 * @fn	int aeAppWindow::GetPosY();
		 *
		 * @brief	Gets position y coordinate.
		 *
		 * @return	The position y coordinate.
		 **************************************************************************************************/

		int GetPosY();

		/**********************************************************************************************//**
		 * @fn	void aeAppWindow::ProcessWindowEvents();
		 *
		 * @brief	Process the events generated by the window.
		 **************************************************************************************************/

		void ProcessWindowEvents();
	protected:

		/**********************************************************************************************//**
		 * @fn	int aeAppWindow::GetNumOfDriver(char* pszDriverName);
		 *
		 * @brief	Gets number of the given driver name. If the driver is not found, returns -1;
		 *
		 * @param [in,out]	pszDriverName	If non-null, name of the driver.
		 *
		 * @return	The number of driver.
		 **************************************************************************************************/

		int GetNumOfDriver(char* pszDriverName);
#ifdef _DEBUG
		void GetNumofDrivers();
#endif // _DEBUG
		

	};
}
