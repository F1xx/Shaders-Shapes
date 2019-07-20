#include "FrameworkPCH.h"
#include "WinEvent.h"

WinEvent::WinEvent(EventTypes atype)
{
	m_Type = atype;
}

WinEvent::~WinEvent()
{
}

EventTypes WinEvent::GetEventType()
{
	return m_Type;
}
