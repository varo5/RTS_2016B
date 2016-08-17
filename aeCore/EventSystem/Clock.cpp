#include "aeCoreStd.h"
#include "Clock.h"

namespace aeCore
{
	/************************************************************************************************************************/
	/* Functions implementation                                            													*/
	/************************************************************************************************************************/

	aeClock::aeClock()
	{
		m_fTimeScale = 1;
	}

	aeClock::~aeClock()
	{
	}

	int aeClock::Init()
	{
		m_fTimeSinceInit = 0;
		m_fTimeSinceUpdate = 0;
		m_fVirtualTimeSinceInit = 0;
		m_Timer = std::chrono::high_resolution_clock::now();
		return 0;
	}

	void aeClock::Destroy()
	{
		m_aTimers.clear();
	}

	void aeClock::Update()
	{
		m_Delta = std::chrono::high_resolution_clock::now() - m_Timer;
		m_Timer = std::chrono::high_resolution_clock::now();
		m_fTimeSinceUpdate = m_Delta.count();
		m_fTimeSinceInit += m_fTimeSinceUpdate;
		m_fVirtualTimeSinceInit += m_fTimeScale * m_fTimeSinceUpdate;
		PostCalls(m_fTimeSinceInit);
	}

	void aeClock::SetVirtualTimeScale(float NewTimeScale)
	{
		m_fTimeScale = (NewTimeScale >= 0) ? NewTimeScale : 0;
	}

	float aeClock::VirtualTime()
	{
		return m_fVirtualTimeSinceInit;
	}

	float aeClock::RealTime()
	{
		return m_fTimeSinceInit;
	}

	float aeClock::VirtualDeltaTime()
	{
		return m_fVirtualTimeSinceInit;
	}

	float aeClock::RealDeltaTime()
	{
		return m_fTimeSinceUpdate;
	}

	void aeClock::SetTimer(float Time, uint8 ID)
	{
		m_aTimers.push_back(aeTimer{ Time,0,ID });
	}

	bool aeClock::PollEvents(uint8 * ID)
	{
		if (m_aEventsPile.size())
		{
			*ID = m_aEventsPile.front();
			m_aEventsPile.pop();
			return true;
		}
		return false;
	}

	void aeClock::PostCalls(float RealTime)
	{
		for each (auto Timer in m_aTimers)
		{
			if (RealTime > Timer.fTimer*Timer.Counter)
			{
				Timer.Counter = Trunc(RealTime / Timer.fTimer) + 1;
				m_aEventsPile.push(Timer.ID);
			}
		}
	}

}