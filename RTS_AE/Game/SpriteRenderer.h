#pragma once
#include "Scripts.h"
#include "AddOn.h"

class aeSpriteRenderer : public aeScript
{
private:
	aeSprite* m_pSprite;
public:
	aeSpriteRenderer();
	virtual ~aeSpriteRenderer();

	virtual int Init(aeBaseClass* pParent);
	virtual void Update(float fDelta);
	virtual void Render(aeRenderer * pRenderer);
	virtual void Destroy();
	virtual void SetSprite(aeSprite* pSprite);

	int OrderOfRender;
	bool MirrorX;
	bool MirrorY;
	aePoint WindowSize;
	aeRect SourceRect;

	aeVector4 Rect;
};

