#pragma once

class Framework;
class Event;

class Timer
{
public:
	Timer(float length);

	void Update(float adelta);

	void Start();
	void Stop();

	bool IsComplete();

	void Reset();

private:
	float m_Length;
	float m_Complete;

	bool m_IsStarted;
};