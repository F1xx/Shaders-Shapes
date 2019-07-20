#include "FrameworkPCH.h"
#include "TimedEvent.h"

TimedEvent::TimedEvent(EventTypes atype)
{
	m_Type = atype;
}

TimedEvent::~TimedEvent()
{
}

EventTypes TimedEvent::GetEventType()
{
	return m_Type;
}
