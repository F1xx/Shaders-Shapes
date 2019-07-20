#pragma once

class DeathEvent : public Event 
{
public:
	DeathEvent(EventTypes atype);
	~DeathEvent();

	EventTypes GetEventType();


private:
	EventTypes m_Type;
};