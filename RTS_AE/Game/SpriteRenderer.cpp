#include "stdafx.h"
#include "SpriteRenderer.h"


aeSpriteRenderer::aeSpriteRenderer() : aeScript()
{
	m_nScriptID = ScriptId::SpriteRenderer;
	OrderOfRender = 0;
	Rect = aeVector4{0,0,1,1};
	MirrorX = false;
	MirrorY = false;
}


aeSpriteRenderer::~aeSpriteRenderer()
{
	Destroy();
}

int aeSpriteRenderer::Init(aeBaseClass * pParent)
{
	m_pParent = pParent;
	return 0;
}

void aeSpriteRenderer::Update(float fDelta)
{
}

void aeSpriteRenderer::Render(aeRenderer * pRenderer)
{
	m_pSprite->RenderEx(pRenderer, (int)((float)WindowSize.x * Rect.x), (int)((float)WindowSize.y * Rect.y), &aePoint{ (int)((float)WindowSize.w* Rect.z),  (int)((float)WindowSize.h* Rect.w) }, &SourceRect, MirrorX ? SDL_FLIP_HORIZONTAL : 0);
}

void aeSpriteRenderer::Destroy()
{
	m_pSprite = nullptr;
}

void aeSpriteRenderer::SetSprite(aeSprite * pSprite)
{
	m_pSprite = pSprite;
	SourceRect = aeRect{ 0,0,m_pSprite->Width(),m_pSprite->Height() };
}