#pragma once

//Macro to do the whole "if nullptr" check when deleting
#define SafeDelete(p) while(p){if(p != nullptr){delete p; p = nullptr;}}

const enum DeviceType
{
	DeviceType_NONE = -1,
	DeviceType_Keyboard = 0,
	DeviceType_Mouse,
	DeviceType_Gamepad
};

const enum KeyState
{
	KeyState_NONE = -1,
	KeyState_Up = 0,
	KeyState_Down,
	KeyState_Held
};

//Check what keys are pressed against these values.
//Values are functional, IE Up could be done by the down arrow but will functionally be UP
const enum KeyValues
{
	KeyValue_NONE = 0,

	//Movement
	KeyValue_Up = 0x0001,
	KeyValue_Down = 0x0002,
	KeyValue_Left = 0x0004,
	KeyValue_Right = 0x0008,

	//Rotation
	KeyValue_RotLeft = 0x0010,
	KeyValue_RotRight = 0x0020,

	//Scale
	KeyValue_Grow = 0x0040,

	//Movement Modification
	KeyValue_Sprint = 0x0100,
	KeyValue_Walk = 0x0200,

	KeyValue_Reset = 0x8000,

	KeyValue_MAX


};

const enum KeyNames
{
	Key_W = 87,
	Key_S = 83,
	Key_A = 65,
	Key_D = 68,
	Key_R = 82,
	Key_E = 69,
	Key_Q = 81,

	Key_LShift = 16,
	Key_LCTRL = 17,
	Key_Space = 32,


	Key_ArrowUp = VK_UP,
	Key_ArrowDown = VK_DOWN,
	Key_ArrowLeft = VK_LEFT,
	Key_ArrowRight = VK_RIGHT
};