#include "GamePCH.h"
#include "Timer.h"

Timer::Timer(float length)
{
	m_Length = length;
	m_Complete = 0.0f;
}

void Timer::Update(float adelta)
{
	if(m_IsStarted)
	m_Complete += adelta;
}

void Timer::Start()
{
	m_IsStarted = true;
}

void Timer::Stop()
{
	m_IsStarted = false;
}

bool Timer::IsComplete()
{
	if (m_Complete >= m_Length)
		return true;

	return false;
}

void Timer::Reset()
{
	m_Complete = 0.0f;
}
