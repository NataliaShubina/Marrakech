#pragma once
#include "../Utilities/utilities.h"

class CLight
{
public:
	CLight();
	~CLight() {}

	void SetPosition(const Vector3& position);
	void SetColor(const Vector3& color);
	void SetSpeed(float speed);
	void SetRadius(float radius);

	void SetType(GLuint type);
	void SetMoveType(GLuint movetype);

	const Vector3& GetColor() const { return m_color; };
	const Vector3& GetPosition() const { return m_position; };
	const float GetSpeed() const { return m_speed; };
	const float GetRadius() const { return m_radius; };
	
	const GLuint GetLightType() const  { return (GLuint)m_eType; }
	const GLuint GetMoveType() const { return (GLuint)m_eMoveType; }

	void Move(const Vector3& center);

private:
	enum LightType
	{
		DIRECTIONAL,
		POINT
	}m_eType;

	enum MoveType
	{
		STATIC,
		CIRCLE
	}m_eMoveType;

	Vector3 m_position;
	Vector3 m_color;
	float m_speed;
	float m_radius;
};

