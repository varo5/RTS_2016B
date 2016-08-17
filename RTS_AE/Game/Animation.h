#pragma once
#include <vector>

class CAnimation
{
private:
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

	struct CFrame 
	{ 
		float FinishTime; 
		aeRect SourceRect; 
		bool MirrorX;
	};

	std::vector<CFrame> m_vFrames;

	aeSprite* m_pSprite;
	float m_tCurrentTime;
	float m_tFrameTime;
	float m_tMaxTime;

	aeRect* m_pCameraRect;
	aeVector2* m_pCameraPos;
	bool* m_pIsometric;
public:
	CAnimation(aeRect* pCameraRect,aeVector2* pCameraPos, bool* pIsometric);
	~CAnimation();

	void Delete();
	void Play();
	void Stop();
	void Pause();
	void Set(float CurrentTime, uint8 Booleans);
	void Render(aeRenderer * pRenderer, aeTransform UpperTransform, float CurrentTime, bool MirrorX, uint8 Booleans);
	void LoadSprite(aeSprite* pImage);
	void InsertFrame(aeRect SourceRect, float FinishTime, bool MirrorX );
	void SetLoop();

	bool MirrorX;

	aeTransform Transform;
};

