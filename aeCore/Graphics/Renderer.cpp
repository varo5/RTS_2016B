#include "aeCoreStd.h"
#include "Renderer.h"

namespace aeCore
{
	aeRenderer::aeRenderer()
	{
		m_RenderColor = aeRGBQuad{ 0,0,0,255 };
	}


	aeRenderer::~aeRenderer()
	{
	}

	void aeRenderer::Clear()
	{
		SDL_RenderClear(m_pRenderer);
	}

	void aeRenderer::Destroy()
	{
		SDL_DestroyRenderer(m_pRenderer);
	}

	aeRGBQuad aeRenderer::SetRenderDrawColor(aeRGBQuad Color)
	{
		SDL_SetRenderDrawColor(m_pRenderer, Color.r, Color.g, Color.b, Color.a);
		aeRGBQuad Temp = m_RenderColor;
		m_RenderColor = Color;
		return Temp;
	}

	void aeRenderer::DrawLine(aePoint Start, aePoint End)
	{
		SDL_RenderDrawLine(m_pRenderer, Start.x, Start.y, End.x, End.y);
	}

	void aeRenderer::DrawRect(aeRect Rectangle)
	{
		SDL_Rect Temp = SDL_Rect{ Rectangle.x,Rectangle.y,Rectangle.w,Rectangle.h };
		SDL_RenderDrawRect(m_pRenderer, &Temp);
	}

	void aeRenderer::DrawPoint(aePoint Point)
	{

		SDL_RenderDrawPoint(m_pRenderer, Point.x, Point.y);
	}

	void aeRenderer::RenderTarget(aeSprite * Target)
	{
		if(Target)
			SDL_SetRenderTarget(m_pRenderer, Target->m_pTexture);
		else
			SDL_SetRenderTarget(m_pRenderer, NULL);
	}
}