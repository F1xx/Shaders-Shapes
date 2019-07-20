#include "FrameworkPCH.h"
#include "DeathEvent.h"

DeathEvent::DeathEvent(EventTypes atype)
{
	m_Type = atype;
}

DeathEvent::~DeathEvent()
{
}

EventTypes DeathEvent::GetEventType()
{
	return m_Type;
}
