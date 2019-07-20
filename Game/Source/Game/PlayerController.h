#pragma once

class Event;
class Framework;

class PlayerController
{
public:
    PlayerController(Framework* aFramework);

    void SetFlag(Event* aevent);

	int GetPressedKeys();
	void ClearKeys();
protected:
	int m_KeyStates; //1 = down (check bits)

	Framework* m_pFramework;
};