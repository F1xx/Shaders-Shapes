#pragma once

enum EventTypes
{
	EventType_NotSet = -1,
	EventType_Input = 0,
	EventType_TimeStart,
	EventType_TimeEnd,
	EventType_Collision,
	EventType_Death,
	EventType_Win,
};

class Event
{
public:
	virtual EventTypes GetEventType() = 0;
};