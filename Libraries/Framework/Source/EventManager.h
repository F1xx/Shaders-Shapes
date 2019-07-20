#pragma once

//class Event;

class EventManager
{
public:
	EventManager();
	~EventManager();
	void AddEvent(Event *aevent);

    EventManager* GetInstance();

protected:
	void ClearEvents();
private:
	std::queue<Event*> m_InputEvents; //make pointer to be on heap
public:
    void PopEvent();
    Event* GetNextEvent();
    bool IsEmpty();
    int GetEventCount();
    void DispatchEvents();
};