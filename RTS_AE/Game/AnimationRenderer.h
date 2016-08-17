#pragma once
#include "SpriteRenderer.h"
#include "Animation.h"

class CAnimationRenderer : public aeScript
{
private:
	CAnimation * m_pAnimation;
	
public:
	CAnimationRenderer();
	virtual ~CAnimationRenderer();

	virtual int Init(aeBaseClass* pParent);
	virtual void Update(float fDelta);
	virtual void Render(aeRenderer * pRenderer);
	virtual void Destroy();
	virtual void SetObject(void* Object, bool Mirrorx);
	bool bRender;

	uint8 Booleans;
	float CurrentTime;

	int OrderOfRender;
	bool MirrorX;
	bool MirrorY;
	aeRect RenderRect;
	aeRect SourceRect;
};

