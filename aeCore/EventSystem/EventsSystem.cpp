#include "aeCoreStd.h"
#include "EventsSystem.h"

namespace aeCore
{
	aeEventsHandler::aeEventsHandler()
	{
	}

	aeEventsHandler::~aeEventsHandler()
	{
		std::priority_queue<aeEvent*, std::vector<aeEvent*>, EventCompare> emptyQueue;
		std::vector<aeEvent*> emptyVector;
		std::swap(m_aMessagePile, emptyQueue);
		std::swap(m_aHistory, emptyVector);
	}	

	aeEventsHandler* EventHandler = 0;

	void InitEventHandler()
	{
		EventHandler = new aeEventsHandler();
	}

	void PostEvent(aeEvent *Event)
	{
		if (!EventHandler)
			InitEventHandler();

		EventHandler->m_aMessagePile.push(Event);

		if (Event->Priority != static_cast<uint8>(EventPriority::Low))
			EventHandler->m_aHistory.push_back(Event);

	}

	bool PollEvent(aeEvent **Event)
	{
		if (!EventHandler)
			InitEventHandler();

		*Event = nullptr;

		if (!EventHandler->m_aMessagePile.empty())
		{
			*Event = EventHandler->m_aMessagePile.top();

			EventHandler->m_aMessagePile.pop();
		}

		return *Event != nullptr;
	}
}