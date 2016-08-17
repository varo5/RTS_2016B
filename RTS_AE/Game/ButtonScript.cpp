#include "stdafx.h"
#include "ButtonScript.h"

aeButtonScript::aeButtonScript() : aeScript()
{
	m_nScriptID = ScriptId::ButtonScript;
}

aeButtonScript::aeButtonScript(aeBaseClass * pParent) : aeButtonScript()
{
	Init(pParent);
}

aeButtonScript::~aeButtonScript()
{
	Destroy();
}

int aeButtonScript::Init(aeBaseClass * pParent)
{
	m_pParent = pParent;

	Angle = 0;
	OrderOfRender = 0;
	m_nFlip = 0;

	m_fTimeForDblClick = 2;
	m_fCounter = 0;

	return 0;
}

void aeButtonScript::Update(float fDelta)
{
}

void aeButtonScript::Render(aeRenderer * pRenderer)
{
	m_pSprite->RenderEx(pRenderer, RenderRect.x, RenderRect.y, &aePoint{ RenderRect.w, RenderRect.h }, &SourceRect, m_nFlip);
}

void aeButtonScript::Destroy()
{
	m_pSprite = nullptr;
}

void aeButtonScript::SetSprite(aeSprite * pSprite)
{
	m_pSprite = pSprite;
	RenderRect = aeRect{ 0,0,m_pSprite->Width(),m_pSprite->Height() };
	SourceRect = aeRect{ 0,0,m_pSprite->Width(),m_pSprite->Height() };
}

ButtonState aeButtonScript::GetState()
{
	if (m_bDblClick)
		return ButtonState::DoubleClick;

	return static_cast<ButtonState>(ButtonStateMachine[m_bLastState ? 1 : 0][m_bCurrentState ? 1 : 0]);
}

void aeButtonScript::ClickOn(aePoint Point)
{
	m_bLastState = m_bCurrentState;
	//m_bCurrentState = m_Rect.HitTest(Point.x, Point.y);
}

void aeButtonScript::SetFunction(std::function<void(void)> Function, ButtonState ExecState)
{
	if (m_aFunction.empty())
	{
		std::vector<std::function<void(void)>> List = std::vector<std::function<void(void)>>();
		List.push_back(Function);
		m_aFunction.insert(make_pair(ExecState,List));
	}
	else
	{
		auto search = m_aFunction.find(ExecState);
		if (search != m_aFunction.end()) 
		{
			search->second.push_back(Function);
		}
		else 
		{
			std::vector<std::function<void(void)>> List = std::vector<std::function<void(void)>>();
			List.push_back(Function);
			m_aFunction.insert(make_pair(ExecState, List));
		}
	}
}

void aeButtonScript::MirrorX(bool Flip)
{
	m_bMirrorX = Flip;
	m_nFlip = (m_bMirrorX ? SDL_FLIP_HORIZONTAL : 0) | (m_bMirrorY ? SDL_FLIP_VERTICAL : 0);
}

void aeButtonScript::MirrorY(bool Flip)
{
	m_bMirrorY = Flip;
	m_nFlip = (m_bMirrorX ? SDL_FLIP_HORIZONTAL : 0) | (m_bMirrorY ? SDL_FLIP_VERTICAL : 0);
}
