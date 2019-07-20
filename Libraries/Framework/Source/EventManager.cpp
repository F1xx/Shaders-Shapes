#include "FrameworkPCH.h"

EventManager::EventManager()
{
    //m_InputEvents = new std::queue<Event*>;
}

EventManager::~EventManager()
{
	ClearEvents();
}

//wipes the entire Event Queue, calling the pointer destructors.
void EventManager::ClearEvents()
{
	//call all destructors and properly clear
	int size = m_InputEvents.size();
	for (int x = 0; x < size; x++)
	{
		Event *deletionEvent = m_InputEvents.front();
        m_InputEvents.pop();
		delete deletionEvent;
	}

	//free the memory by swapping to an empty queue
	//std::queue<Event*>().swap(m_InputEvents);
}

void EventManager::PopEvent()
{
	assert(!m_InputEvents.empty());

	Event *deletionEvent = m_InputEvents.front();
	delete deletionEvent;
	m_InputEvents.pop();
}

void EventManager::AddEvent(Event * aevent)
{
	m_InputEvents.push(aevent);
}

EventManager* EventManager::GetInstance()
{
    return this;
}

Event* EventManager::GetNextEvent()
{
    return m_InputEvents.front();
}

bool EventManager::IsEmpty()
{
    return m_InputEvents.empty();
}

int EventManager::GetEventCount()
{
    return m_InputEvents.size();
}

void EventManager::DispatchEvents()
{
	//Call Game's OnEvent?
}