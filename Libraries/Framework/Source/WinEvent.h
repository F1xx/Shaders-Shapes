#pragma once

class WinEvent : public Event
{
public:
	WinEvent(EventTypes atype);
	~WinEvent();

	EventTypes GetEventType();


private:
	EventTypes m_Type;
};
