#pragma once
#include "Constants.h"

class Event;

class TimedEvent : public Event
{
public:
	TimedEvent(EventTypes atype);
	~TimedEvent();

	EventTypes GetEventType();


private:
	EventTypes m_Type;
};