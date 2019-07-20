#include "GamePCH.h"
#include "PlayerController.h"

PlayerController::PlayerController(Framework* aFramework)
{
	m_pFramework = aFramework;

	m_KeyStates = 0;
}

void PlayerController::SetFlag(Event* aevent)
{
	InputEvent* pInputEvent = (InputEvent*)aevent;

	//ALL KEYBOARD EVENTS HERE
	if (pInputEvent->GetDeviceType() == DeviceType_Keyboard)
	{
		//if Pressed
		if (pInputEvent->GetInputState() == KeyState_Down)
		{
			//MOVEMENT
			if (pInputEvent->GetKeyID() == Key_W || pInputEvent->GetKeyID() == Key_ArrowUp)
			{
				m_KeyStates = m_KeyStates | KeyValue_Up;
			}
			if (pInputEvent->GetKeyID() == Key_S || pInputEvent->GetKeyID() == Key_ArrowDown)
			{
				m_KeyStates = m_KeyStates | KeyValue_Down;
			}
			if (pInputEvent->GetKeyID() == Key_A || pInputEvent->GetKeyID() == Key_ArrowLeft)
			{
				m_KeyStates = m_KeyStates | KeyValue_Left;
			}
			if (pInputEvent->GetKeyID() == Key_D || pInputEvent->GetKeyID() == Key_ArrowRight)
			{
				m_KeyStates = m_KeyStates | KeyValue_Right;
			}

			//ROTATION
			if (pInputEvent->GetKeyID() == Key_E)
			{
				m_KeyStates = m_KeyStates | KeyValue_RotLeft;
			}
			if (pInputEvent->GetKeyID() == Key_Q)
			{
				m_KeyStates = m_KeyStates | KeyValue_RotRight;
			}

			//Modifier Keys
			if (pInputEvent->GetKeyID() == Key_LShift)
			{
				m_KeyStates = m_KeyStates | KeyValue_Sprint;
			}
			if (pInputEvent->GetKeyID() == Key_LCTRL)
			{
				m_KeyStates = m_KeyStates | KeyValue_Walk;
			}
			if (pInputEvent->GetKeyID() == Key_R)
			{
				m_KeyStates = m_KeyStates | KeyValue_Reset;
			}
			if (pInputEvent->GetKeyID() == Key_Space)
			{
				m_KeyStates = m_KeyStates | KeyValue_Grow;
			}
		}
		//if released
		if (pInputEvent->GetInputState() == KeyState_Up)
		{
			//MOVEMENT
			if (pInputEvent->GetKeyID() == Key_W || pInputEvent->GetKeyID() == Key_ArrowUp)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_Up;
			}
			if (pInputEvent->GetKeyID() == Key_S || pInputEvent->GetKeyID() == Key_ArrowDown)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_Down;
			}
			if (pInputEvent->GetKeyID() == Key_A || pInputEvent->GetKeyID() == Key_ArrowLeft)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_Left;
			}
			if (pInputEvent->GetKeyID() == Key_D || pInputEvent->GetKeyID() == Key_ArrowRight)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_Right;
			}
			//ROTATION
			if (pInputEvent->GetKeyID() == Key_E)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_RotLeft;
			}
			if (pInputEvent->GetKeyID() == Key_Q)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_RotRight;
			}
			//Modifier Keys
			if (pInputEvent->GetKeyID() == Key_LShift)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_Sprint;
			}
			if (pInputEvent->GetKeyID() == Key_LCTRL)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_Walk;
			}
			if (pInputEvent->GetKeyID() == Key_R)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_Reset;
			}
			if (pInputEvent->GetKeyID() == Key_Space)
			{
				m_KeyStates = m_KeyStates ^ KeyValue_Grow;
			}
		}
	}
	//ALL GAMEPAD EVENTS HERE
	if (pInputEvent->GetDeviceType() == DeviceType_Gamepad)
	{
		if (pInputEvent->GetInputState() == KeyState_Down)
		{
			//Gamepad Direction pad
			if (pInputEvent->GetKeyID() == VK_GAMEPAD_DPAD_UP)
			{

			}
			if (pInputEvent->GetKeyID() == VK_GAMEPAD_DPAD_DOWN)
			{

			}
			if (pInputEvent->GetKeyID() == VK_GAMEPAD_DPAD_LEFT)
			{

			}
			if (pInputEvent->GetKeyID() == VK_GAMEPAD_DPAD_RIGHT)
			{

			}
		}
	}
	m_pFramework->GetEventManager()->PopEvent();
}

int PlayerController::GetPressedKeys()
{
	return m_KeyStates;
}

void PlayerController::ClearKeys()
{
	m_KeyStates = 0;
}
