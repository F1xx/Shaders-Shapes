#include "FrameworkPCH.h"
#include "InputEvent.h"

InputEvent::InputEvent(DeviceType atype, unsigned char akeyID, KeyState astate, ivec2 acoords)
{
	m_DeviceType = atype;
	m_KeyID = akeyID;
	m_State = astate;
	m_coords = acoords;
}

InputEvent::~InputEvent()
{

}

EventTypes InputEvent::GetEventType()
{
	return EventType_Input;
}

DeviceType InputEvent::GetDeviceType()
{
	return m_DeviceType;
}

KeyState InputEvent::GetInputState()
{
	return m_State;
}

unsigned char InputEvent::GetKeyID()
{
	return m_KeyID;
}

ivec2 InputEvent::GetCoordinates()
{
	return m_coords;
}
