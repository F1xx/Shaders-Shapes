#pragma once
#include "Constants.h"

class Event;

class InputEvent : public Event
{
public:
	InputEvent(DeviceType atype, unsigned char akeyID, KeyState astate, ivec2 acoords);
	~InputEvent();

	EventTypes GetEventType();
	DeviceType GetDeviceType();
	KeyState GetInputState();
	unsigned char GetKeyID();
	ivec2 GetCoordinates();

private:
	DeviceType m_DeviceType;
	unsigned char m_KeyID;
	KeyState m_State;
	ivec2 m_coords;
};