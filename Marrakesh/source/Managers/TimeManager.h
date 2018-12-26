#pragma once

#include "../../Util/include/Singleton.h"
#include "../../Util/include/Defines.h"


class TimeManager : public Singleton<TimeManager>
{
public:

	TimeManager();

	float GetTime() const { return m_time; }
	float GetDeltaTime() const { return m_deltaTime; }
	void Update(float deltatime);

private:
	float m_deltaTime;
	float m_time;
};