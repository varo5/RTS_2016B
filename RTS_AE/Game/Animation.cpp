#include "stdafx.h"
#include "Animation.h"


CAnimation::CAnimation(aeRect* pCameraRect, aeVector2* pCameraPos, bool* pIsometric)
{
	m_bPlaying = false;
	m_bStopped = false;
	m_bPaused = false;
	m_bCiclic = false;
	m_tCurrentTime = 0;
	m_pCameraRect = pCameraRect;
	m_pCameraPos = pCameraPos;
	m_pIsometric = pIsometric;
}

CAnimation::~CAnimation()
{
}

void CAnimation::Delete()
{
}

void CAnimation::Play()
{
	m_bPlaying = true;
	m_bStopped = false;
	m_bPaused = false;
}

void CAnimation::Stop()
{
	m_bPlaying = false;
	m_bStopped = true;
	m_bPaused = false;
}

void CAnimation::Pause()
{
	m_bStopped = false;
	m_bPaused = !m_bPaused;
	m_bPlaying = !m_bPaused;
}

void CAnimation::Set(float CurrentTime, uint8 Booleans)
{
	m_tCurrentTime = CurrentTime;
	m_byteBooleans = Booleans;
}

void CAnimation::Render(aeRenderer * pRenderer, aeTransform UpperTransform, float CurrentTime, bool MirrorX, uint8 Booleans)
{
	m_byteBooleans = Booleans;
	if (m_bPlaying)
	{
		if (m_bCiclic)
		{
			m_tFrameTime = fmodf(CurrentTime, m_tMaxTime);
		}
		else if (!m_bPaused && CurrentTime < m_tMaxTime)
		{
			m_tFrameTime = fmodf(CurrentTime, m_tMaxTime);
		}
		else
		{
			m_tFrameTime = m_tMaxTime - 0.01f;
		}
	}
	else if (m_bStopped)
	{
		m_tFrameTime = 0;
	}
	for (int i = 0; i < m_vFrames.size(); i++)
	{
		if (m_tFrameTime < m_vFrames[i].FinishTime)
		{
			aeVector2 DisplacedPosition;
			aePoint DestSize;
			DestSize.w = m_vFrames[i].SourceRect.w * Transform.Scale.x;
			DestSize.h = m_vFrames[i].SourceRect.h * Transform.Scale.y;
			DisplacedPosition.x = UpperTransform.Position.x + Transform.Position.x + (DestSize.w >> 1);
			DisplacedPosition.y = UpperTransform.Position.y + Transform.Position.y + (DestSize.h >> 1);
			aePoint ScreenPosition = GetMapToScreenCoords(DisplacedPosition, *m_pCameraPos, *m_pCameraRect, *m_pIsometric);

			m_pSprite->RenderEx(pRenderer, ScreenPosition.x, ScreenPosition.y, &DestSize, &m_vFrames[i].SourceRect, MirrorX ? SDL_FLIP_HORIZONTAL : 0);
			return;												   
		}														   
	}															   
}

void CAnimation::LoadSprite(aeSprite * pImage)
{
	m_pSprite = pImage;
}



void CAnimation::InsertFrame(aeRect SourceRect, float FinishTime, bool MirrorX)
{
	CFrame Temp = CFrame{ FinishTime , SourceRect, MirrorX };
	m_vFrames.push_back(Temp);
	if (Temp.FinishTime > m_tMaxTime)
		m_tMaxTime = Temp.FinishTime;
}


void CAnimation::SetLoop()
{
	m_bCiclic = !m_bCiclic;
}
