/**********************************************************************************************//**
 * @file	Graphics\Sprite.h
 *
 * @brief	Declares the sprite class.
 **************************************************************************************************/

#pragma once
#include "Renderer.h"

namespace aeCore
{
	class aeRenderer;
	class aeSprite;

	/**********************************************************************************************//**
	 * @class	aeFont
	 *
	 * @brief	An ae font.
	 **************************************************************************************************/

	class LIBRARY_EXPORT aeFont
	{
	public:
		aeFont();
		aeFont(aeString &FilePath, aeString & Name, int Size);
		~aeFont();
	public:
		int Init(aeString &FilePath, aeString & Name,  int Size);
		void Destroy();

		int GetSize();
		aeString &GetName();
		void ChangeSize(int Size);
	private:
		TTF_Font * m_pFont;
		aeString m_pszFilePath;
		aeString m_pszName;
		int m_nSize;
		friend class aeSprite;
	};

	/**********************************************************************************************//**
	 * @class	aeSprite
	 *
	 * @brief	This class reads and displays images given by the user.
	 **************************************************************************************************/

	class LIBRARY_EXPORT aeSprite
	{
	private:
		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		aePoint m_rSourceSize;
		SDL_Texture* m_pTexture;
		int ID;

		friend class aeRenderer;
	public:
		aeString Name;

		/************************************************************************************************************************/
		/* Constructors  declaration                                                      										*/
		/************************************************************************************************************************/
		aeSprite();
		~aeSprite();

		/************************************************************************************************************************/
		/* Functions declaration                                            													*/
		/************************************************************************************************************************/

		/**********************************************************************************************//**
		 * @fn	static aeSprite* aeSprite::CreateSprite(aeString pszPath, aeString pszName, aeRenderer* pRenderer, int ID);
		 *
		 * @brief	Creates a sprite.
		 *
		 * @param	pszPath			 	Path of the file.
		 * @param	pszName			 	The name.
		 * @param [in,out]	pRenderer	If non-null, the renderer.
		 * @param	ID				 	The identifier.
		 *
		 * @return	The new sprite.
		 **************************************************************************************************/

		static aeSprite* CreateSprite(aeString pszPath, aeString pszName, aeRenderer* pRenderer, int ID);

		/**********************************************************************************************//**
		 * @fn	static aeSprite* aeSprite::CreateTargetRenderer(aeRenderer* pRenderer, int w, int h);
		 *
		 * @brief	Creates target renderer.
		 *
		 * @param [in,out]	pRenderer	If non-null, the renderer.
		 * @param	w				 	The width.
		 * @param	h				 	The height.
		 *
		 * @return	null if it fails, else the new target renderer.
		 **************************************************************************************************/

		static aeSprite* CreateTargetRenderer(aeRenderer* pRenderer, int w, int h);

		/**********************************************************************************************//**
		 * @fn	static aeSprite* aeSprite::CreateTextImage(aeRenderer* pRenderer, aeFont* pFont, aeString &pszText, int Size);
		 *
		 * @brief	Creates an image from text.
		 *
		 * @param [in,out]	pRenderer	If non-null, the renderer.
		 * @param [in,out]	pFont	 	If non-null, the font.
		 * @param [in,out]	pszText  	The text.
		 * @param	Size			 	The size.
		 *
		 * @return	null if it fails, else the new text image.
		 **************************************************************************************************/

		static aeSprite* CreateTextImage(aeRenderer* pRenderer, aeFont* pFont, aeString &pszText, aeRGB & Color);

		/**********************************************************************************************//**
		 * @fn	bool aeSprite::LoadImageFromFile(aeString pszFileName, aeRenderer* pRenderer);
		 *
		 * @brief	Loads image from file.
		 *
		 * @param	pszFileName		 	Filename of the file.
		 * @param [in,out]	pRenderer	If non-null, the renderer.
		 *
		 * @return	true if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool LoadImageFromFile(aeString pszFileName, aeRenderer* pRenderer);

		/**********************************************************************************************//**
		 * @fn	bool aeSprite::LoadImageFromText(aeRenderer * pRenderer, aeFont * pFont, aeString & pszText, int Size);
		 *
		 * @brief	Loads image from text.
		 *
		 * @param [in,out]	pRenderer	If non-null, the renderer.
		 * @param [in,out]	pFont	 	If non-null, the font.
		 * @param [in,out]	pszText  	The text.
		 * @param	Size			 	The size.
		 *
		 * @return	true if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool LoadImageFromText(aeRenderer * pRenderer, aeFont * pFont, aeString & pszText, aeRGB & Color);

		/**********************************************************************************************//**
		 * @fn	void aeSprite::Free();
		 *
		 * @brief	Frees this object.
		 **************************************************************************************************/

		void Free();

		/**********************************************************************************************//**
		 * @fn	void aeSprite::SetColor(aeRGB rgbColor);
		 *
		 * @brief	Sets a color modifier.
		 *
		 * @param	rgbColor	The RGB color.
		 **************************************************************************************************/

		void SetColor(aeRGB rgbColor);	

		/**********************************************************************************************//**
		 * @fn	void aeSprite::SetBlendMode(int blending);
		 *
		 * @brief	Sets blend mode.
		 *
		 * @param	blending	The blending.
		 **************************************************************************************************/

		void SetBlendMode(int blending);			

		/**********************************************************************************************//**
		 * @fn	void aeSprite::SetAlpha(uint8 alpha);
		 *
		 * @brief	Sets an alpha.
		 *
		 * @param	alpha	The alpha.
		 **************************************************************************************************/

		void SetAlpha(uint8 alpha);

		/**********************************************************************************************//**
		 * @fn	void aeSprite::Render(aeRenderer *Renderer, int x, int y, aePoint* pSize = NULL, aeRect* pRectSource = NULL);
		 *
		 * @brief	Renders this object.
		 *
		 * @param [in,out]	Renderer   	If non-null, the renderer.
		 * @param	x				   	The x coordinate.
		 * @param	y				   	The y coordinate.
		 * @param [in,out]	pSize	   	(Optional) If non-null, the size.
		 * @param [in,out]	pRectSource	(Optional) If non-null, the rectangle source.
		 **************************************************************************************************/

		void Render(aeRenderer *Renderer, int x, int y, aePoint* pSize = NULL, aeRect* pRectSource = NULL);

		/**********************************************************************************************//**
		 * @fn	void aeSprite::RenderEx(aeRenderer *Renderer, int x, int y, aePoint* pSize = NULL, aeRect* pRectSource = NULL, int Flip = 0, aePoint* pCenter = NULL, float Angle = 0.0f );
		 *
		 * @brief	Renders this object.
		 *
		 * @param [in,out]	Renderer   	If non-null, the renderer.
		 * @param	x				   	The x coordinate.
		 * @param	y				   	The y coordinate.
		 * @param [in,out]	pSize	   	(Optional) If non-null, the size.
		 * @param [in,out]	pRectSource	(Optional) If non-null, the rectangle source.
		 * @param	Flip			   	The flip.
		 * @param [in,out]	pCenter	   	(Optional) If non-null, the center.
		 * @param	Angle			   	The angle.
		 **************************************************************************************************/

		void RenderEx(aeRenderer *Renderer, int x, int y, aePoint* pSize = NULL, aeRect* pRectSource = NULL, int Flip = 0, aePoint* pCenter = NULL, float Angle = 0.0f );

		/**********************************************************************************************//**
		 * @fn	int aeSprite::Height();
		 *
		 * @brief	Gets the height.
		 *
		 * @return	An int.
		 **************************************************************************************************/

		int Height();

		/**********************************************************************************************//**
		 * @fn	int aeSprite::Width();
		 *
		 * @brief	Gets the width.
		 *
		 * @return	An int.
		 **************************************************************************************************/

		int Width();

		/**********************************************************************************************//**
		 * @fn	aePoint aeSprite::GetSize();
		 *
		 * @brief	Gets the size.
		 *
		 * @return	The size.
		 **************************************************************************************************/

		aePoint GetSize();

		/**********************************************************************************************//**
		 * @fn	int aeSprite::GetID();
		 *
		 * @brief	Gets the identifier.
		 *
		 * @return	The identifier.
		 **************************************************************************************************/

		int GetID();

		/**********************************************************************************************//**
		 * @fn	void aeSprite::SetAsRenderTarget(aeRenderer* pRenderer, int w, int h);
		 *
		 * @brief	Sets as render target.
		 *
		 * @param [in,out]	pRenderer	If non-null, the renderer.
		 * @param	w				 	The width.
		 * @param	h				 	The height.
		 **************************************************************************************************/

		void SetAsRenderTarget(aeRenderer* pRenderer, int w, int h);
	};
}

typedef std::vector<aeCore::aeSprite*> LIBRARY_EXPORT SpriteList;



