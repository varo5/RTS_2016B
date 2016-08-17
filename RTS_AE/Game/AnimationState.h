#pragma once
#include "State.h"
#include "EnumDeclarations.h"
#include "World.h"

class CAnimationState : public CState
{
protected:	
	union
	{
		struct
		{
			bool m_bPlaying : 1;
			bool m_bStopped : 1;
			bool m_bPaused : 1;
			bool m_bCiclic : 1;
		};
		uint8 m_byteBooleans;
	};

	aeWorld* m_pWorldReference;
public:
	CAnimationState();
	virtual ~CAnimationState();

	inline void SetWorldReference(aeWorld* pWorldReference)
	{
		m_pWorldReference = pWorldReference;
	}
};

