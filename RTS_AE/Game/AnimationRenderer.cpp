#include "stdafx.h"
#include "AnimationRenderer.h"


CAnimationRenderer::CAnimationRenderer()
{
	m_nClassID = ClassId::AddOn;
	m_nAddOnID = AddOnId::Scripts;
	m_nScriptID = ScriptId::AnimationRenderer;
	OrderOfRender = 0;
	MirrorX = false;
	MirrorY = false;
}


CAnimationRenderer::~CAnimationRenderer()
{
}

int CAnimationRenderer::Init(aeBaseClass * pParent)
{
	m_pParent = pParent;
	bRender = true;
	return 0;
}

void CAnimationRenderer::Update(float fDelta)
{
	CurrentTime += fDelta;
}

void CAnimationRenderer::Render(aeRenderer * pRenderer)
{
	if(bRender)
	if(m_pAnimation)
		m_pAnimation->Render(pRenderer, ((aeGameObject*)GetParent())->Transform,CurrentTime,MirrorX,Booleans);
}

void CAnimationRenderer::Destroy()
{
}

void CAnimationRenderer::SetObject(void* Object, bool Mirrorx)
{
	m_pAnimation = (CAnimation*)Object;
	MirrorX = Mirrorx;
	m_pAnimation->Set(CurrentTime,Booleans);
}