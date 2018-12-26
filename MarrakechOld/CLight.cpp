#include "stdafx.h"
#include "CLight.h"
#include "Globals.h"
#include <cmath>

CLight::CLight():
	m_color(0.0f, 0.0f, 0.0f),
	m_position(0.0f,0.0f,0.0f),
	m_speed(0.0f),
	m_radius(0.0f)
{

}

void CLight::SetPosition(const Vector3& position)
{
	m_position = position;
}

void CLight::SetColor(const Vector3& color)
{
	m_color = color;
}

void CLight::SetSpeed(float speed)
{
	m_speed = speed;
}

void CLight::SetRadius(float radius)
{
	m_radius = radius;
}


void CLight::SetType(GLuint type)
{
	if (type <= LightType::POINT)
	{
		m_eMoveType = (MoveType)type;
	}
}

void CLight::SetMoveType(GLuint movetype)
{
	if (movetype <= MoveType::CIRCLE)
	{
		m_eMoveType = (MoveType)movetype;
	}
}

void CLight::Move(const Vector3& center)
{
	if (m_eMoveType == MoveType::CIRCLE)
	{
		m_position.x = center.x + m_radius * cos(m_speed * Globals::m_time);
		m_position.y = center.y;
		m_position.z = center.z + m_radius * sin(m_speed * Globals::m_time);
	}
}