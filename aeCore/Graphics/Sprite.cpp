/**********************************************************************************************//**
 * @file	Graphics\Sprite.cpp
 *
 * @brief	Implements the sprite class.
 **************************************************************************************************/
#include "aeCoreStd.h"
#include "Sprite.h"

namespace aeCore
{
	/**********************************************************************************************//**
	 * @fn	aeSprite::aeSprite()
	 *
	 * @brief	Default constructor.
	 **************************************************************************************************/

	aeSprite::aeSprite()
	{
		m_pTexture = nullptr;
	}

	/**********************************************************************************************//**
	 * @fn	aeSprite::~aeSprite()
	 *
	 * @brief	Destructor.
	 **************************************************************************************************/

	aeSprite::~aeSprite()
	{
		//Empty the object
		Free();
	}

	/**********************************************************************************************//**
	 * @fn	aeSprite* aeSprite::CreateSprite(aeString pszPath, aeString pszName, aeRenderer* pRenderer, int ID)
	 *
	 * @brief	Creates a sprite.
	 *
	 * @param	pszPath			 	Path of the file.
	 * @param	pszName			 	The name.
	 * @param [in,out]	pRenderer	If non-null, the renderer.
	 * @param	ID				 	If non-null, the transaction color.
	 *
	 * @return	The new sprite.
	 **************************************************************************************************/

	aeSprite* aeSprite::CreateSprite(aeString pszPath, aeString pszName, aeRenderer* pRenderer, int ID)
	{
		aeSprite* NewSprite = new aeSprite();
		NewSprite->ID = ID;
		if (NewSprite->LoadImageFromFile(pszPath, pRenderer))
		{
			NewSprite->Name = pszName;
			return NewSprite;
		}
		NewSprite->Free();
		return nullptr;
	}

	/**********************************************************************************************//**
	 * @fn	aeSprite * aeSprite::CreateTargetRenderer(aeRenderer * pRenderer, int w, int h)
	 *
	 * @brief	Creates target renderer.
	 *
	 * @param [in,out]	pRenderer	If non-null, the renderer.
	 * @param	w				 	The width.
	 * @param	h				 	The height.
	 *
	 * @return	null if it fails, else the new target renderer.
	 **************************************************************************************************/

	aeSprite * aeSprite::CreateTargetRenderer(aeRenderer * pRenderer, int w, int h)
	{
		aeSprite* NewSprite = new aeSprite();
		NewSprite->SetAsRenderTarget(pRenderer, w, h);
		return NewSprite;
	}

	/**********************************************************************************************//**
	 * @fn	bool aeSprite::LoadImageFromFile(aeString pszFileName, aeRenderer* pRenderer)
	 *
	 * @brief	Loads image from file.
	 *
	 * @param	pszFileName		 	Filename of the file.
	 * @param [in,out]	pRenderer	If non-null, the renderer.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	aeSprite * aeSprite::CreateTextImage(aeRenderer * pRenderer, aeFont * pFont, aeString & pszText, aeRGB & Color)
	{
		aeSprite* NewSprite = new aeSprite();
		if (NewSprite->LoadImageFromText(pRenderer,pFont,pszText, Color))
		{
			NewSprite->Name = pszText;
			return NewSprite;
		}
		NewSprite->Free();
		return nullptr;
	}

	bool aeSprite::LoadImageFromFile(aeString pszFileName, aeRenderer* pRenderer)
	{
		//Making sure the object is empty
		Free();
		//Change the Name
		Name = pszFileName;

		//Create texture
#if PLATFORM_TCHAR_IS_1_BYTE == 1
		m_pTexture = IMG_LoadTexturepRenderer->m_pRenderer, (path.c_str());
#else
		m_pTexture = IMG_LoadTexture(pRenderer->m_pRenderer, ws2s(pszFileName).c_str());
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		if (m_pTexture == NULL)
		{
#if PLATFORM_TCHAR_IS_1_BYTE == 1
			printf("Unable to create texture from %s! SDL Error: %s\n", pszFileName.c_str(), SDL_GetError());
#else
			printf("Unable to create texture from %s! SDL Error: %s\n", ws2s(pszFileName).c_str(), SDL_GetError());
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		}
		else
		{
			//Get the size of the image
			SDL_QueryTexture(m_pTexture, NULL, NULL, &m_rSourceSize.w, &m_rSourceSize.h);
		}
		return m_pTexture != NULL;

	}

	/**********************************************************************************************//**
	 * @fn	void aeSprite::Free()
	 *
	 * @brief	Frees this object.
	 **************************************************************************************************/

	bool aeSprite::LoadImageFromText(aeRenderer * pRenderer, aeFont * pFont, aeString & pszText, aeRGB & Color)
	{
		SDL_Surface* NewText;
#if PLATFORM_TCHAR_IS_1_BYTE == 1
		NewText = TTF_RenderText_Solid(pFont->m_pFont, pszText.c_str(), SDL_Color{ Color.r,Color.g,Color.b });
#else
		NewText = TTF_RenderText_Solid(pFont->m_pFont, ws2s(pszText).c_str(), SDL_Color{ Color.r,Color.g,Color.b });
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		
		m_pTexture = SDL_CreateTextureFromSurface(pRenderer->m_pRenderer, NewText);

		SDL_FreeSurface(NewText);

		if (m_pTexture)
			return true;

		return false;
	}

	void aeSprite::Free()
	{
		if (m_pTexture != nullptr)
		{
			//Free loaded image
			SDL_DestroyTexture(m_pTexture);
			m_pTexture = nullptr;
		}
	}

	/**********************************************************************************************//**
	 * @fn	void aeSprite::SetColor(aeRGB rgbColor)
	 *
	 * @brief	Sets a color.
	 *
	 * @param	rgbColor	The RGB color.
	 **************************************************************************************************/

	void aeSprite::SetColor(aeRGB rgbColor)
	{
		SDL_SetTextureColorMod(m_pTexture, rgbColor.r, rgbColor.g, rgbColor.b);
	}

	/**********************************************************************************************//**
	 * @fn	void aeSprite::SetBlendMode(int blending)
	 *
	 * @brief	Sets blend mode.
	 *
	 * @param	blending	The blending.
	 **************************************************************************************************/

	void aeSprite::SetBlendMode(int blending)
	{
		SDL_SetTextureBlendMode(m_pTexture, (SDL_BlendMode)blending);
	}

	/**********************************************************************************************//**
	 * @fn	void aeSprite::SetAlpha(uint8 alpha)
	 *
	 * @brief	Sets an alpha.
	 *
	 * @param	alpha	The alpha.
	 **************************************************************************************************/

	void aeSprite::SetAlpha(uint8 alpha)
	{
		SDL_SetTextureAlphaMod(m_pTexture, alpha);
	}

	/**********************************************************************************************//**
	 * @fn	void aeSprite::Render(aeRenderer & Renderer, int x, int y, aePoint* pSize, aeRect* pRectSource)
	 *
	 * @brief	Renders this object.
	 *
	 * @param [in,out]	Renderer   	The renderer.
	 * @param	x				   	The x coordinate.
	 * @param	y				   	The y coordinate.
	 * @param [in,out]	pSize	   	If non-null, the size.
	 * @param [in,out]	pRectSource	If non-null, the rectangle source.
	 **************************************************************************************************/

	void aeSprite::Render(aeRenderer * Renderer, int x, int y, aePoint* pSize, aeRect* pRectSource)
	{
		SDL_Rect rSource;
		SDL_Rect rDest;

		if (pRectSource)
			rSource = { pRectSource->x,pRectSource->y,pRectSource->w,pRectSource->h };
		else
			rSource = { 0,0,m_rSourceSize.w,m_rSourceSize.h };

		if (pSize)
			rDest = { x,y,pSize->w,pSize->h };
		else
			rDest = { x,y,m_rSourceSize.w,m_rSourceSize.h };

		SDL_RenderCopy(Renderer->m_pRenderer,m_pTexture, &rSource, &rDest);
	}

	/**********************************************************************************************//**
	 * @fn	void aeSprite::RenderEx(aeRenderer &Renderer, int x, int y, aePoint* pSize, aeRect* pRectSource, aePoint* pCenter, int Flip, float Angle)
	 *
	 * @brief	Renders this object.
	 *
	 * @param [in,out]	Renderer   	The renderer.
	 * @param	x				   	The x coordinate.
	 * @param	y				   	The y coordinate.
	 * @param [in,out]	pSize	   	If non-null, the size.
	 * @param [in,out]	pRectSource	If non-null, the rectangle source.
	 * @param [in,out]	pCenter	   	If non-null, the center.
	 * @param	Flip			   	The flip.
	 * @param	Angle			   	The angle.
	 **************************************************************************************************/

	void aeSprite::RenderEx(aeRenderer *Renderer, int x, int y, aePoint* pSize, aeRect* pRectSource, int Flip, aePoint* pCenter, float Angle)
	{
		SDL_Rect rSource;
		SDL_Rect rDest;
		SDL_Point pointCenter;

		if(pRectSource)
			rSource = { pRectSource->x,pRectSource->y,pRectSource->w,pRectSource->h };
		else
			rSource = { 0,0,m_rSourceSize.w,m_rSourceSize.h };		

		if(pSize)
			rDest = { x,y,pSize->w,pSize->h };
		else
			rDest = { x,y,m_rSourceSize.w,m_rSourceSize.h };

		if (Flip || pCenter || Angle)
		{
			if (pCenter)
				pointCenter = { pCenter->x,pCenter->x };
			else
				pointCenter = { rDest.w >> 1,rDest.h >> 1 };

			SDL_RenderCopyEx(Renderer->m_pRenderer, m_pTexture, &rSource, &rDest, Angle, &pointCenter, static_cast<SDL_RendererFlip>(Flip));
		}
		else
			SDL_RenderCopy(Renderer->m_pRenderer, m_pTexture, &rSource, &rDest);
	}

	/**********************************************************************************************//**
	 * @fn	int aeSprite::Height()
	 *
	 * @brief	Gets the height.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	int aeSprite::Height() {
		return m_rSourceSize.h;

	}

	/**********************************************************************************************//**
	 * @fn	int aeSprite::Width()
	 *
	 * @brief	Gets the width.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	int aeSprite::Width() {
		return m_rSourceSize.w;
	}
	aePoint aeSprite::GetSize()
	{
		return m_rSourceSize;
	}
	int aeSprite::GetID()
	{
		return ID;
	}

	void aeSprite::SetAsRenderTarget(aeRenderer* pRenderer, int w, int h)
	{
		Free();
		Name = TEXT("RenderTarget");
		m_pTexture = SDL_CreateTexture(pRenderer->m_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		if (m_pTexture == NULL)
		{
#if PLATFORM_TCHAR_IS_1_BYTE == 1
			printf("Unable to create Render Target! SDL Error: %s\n", SDL_GetError());
#else
			printf("Unable to create Render Target! SDL Error: %s\n", SDL_GetError());
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		}
		else
		{
			//Get the size of the image
			SDL_QueryTexture(m_pTexture, NULL, NULL, &m_rSourceSize.w, &m_rSourceSize.h);
		}
	}
	aeFont::aeFont()
	{
	}
	aeFont::aeFont(aeString & FilePath, aeString & Name, int Size)
	{
		Init(FilePath, Name, Size);
	}
	aeFont::~aeFont()
	{
	}
	int aeFont::Init(aeString & FilePath, aeString & Name, int Size)
	{
		m_nSize = Size;
		m_pszFilePath = FilePath;
		m_pszName = Name;
#if PLATFORM_TCHAR_IS_1_BYTE == 1
		m_pFont = TTF_OpenFont(FilePath.c_str(), m_nSize);
#else
		m_pFont = TTF_OpenFont(ws2s(FilePath).c_str(), m_nSize);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		return 0;
	}
	void aeFont::Destroy()
	{
		TTF_CloseFont(m_pFont);
	}
	int aeFont::GetSize()
	{
		return m_nSize;
	}
	aeString & aeFont::GetName()
	{
		return m_pszName;
	}
	void aeFont::ChangeSize(int Size)
	{
		Destroy();
#if PLATFORM_TCHAR_IS_1_BYTE == 1
		m_pFont = TTF_OpenFont(m_pszFilePath.c_str(), m_nSize);
#else
		m_pFont = TTF_OpenFont(ws2s(m_pszFilePath).c_str(), m_nSize);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
	}
}