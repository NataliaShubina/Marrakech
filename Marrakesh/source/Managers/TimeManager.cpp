#include "TimeManager.h"

TimeManager::TimeManager():
	m_time(0.f),
	m_deltaTime(0.f)
{

}

void TimeManager::Update(float deltatime)
{
	m_deltaTime = deltatime;
	m_time += deltatime;
}