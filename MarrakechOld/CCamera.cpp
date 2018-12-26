#include "stdafx.h"
#include "CCamera.h"
#include "Globals.h"

#define _USE_MATH_DEFINES
#include <math.h>

CCamera::CCamera() :
	m_position(0.0f,0.0f,0.0f),
	m_look(0.0f, 0.0f, 0.0f),
	m_up(0.0f, 0.0f, 0.0f),
	m_right(0.0f, 0.0f, 0.0f),
	m_WorldUp(0.0f, 0.0f, 0.0f),
	m_viewMatrix(0),
	m_projMatrix(0),
	m_resultMatrix(0),
	m_camSpeed(0.0f),
	m_rotateSpeed(0.0f),
	m_rotateAngle(0.0f),
	m_fov(0.0f),
	m_aspect(0.0f),
	m_nearZ(0.0f),
	m_farZ(0.0f)
{

}


void CCamera::SetWorldUp(const Vector3& wup)
{
	m_WorldUp = wup;
}

void CCamera::SetVisibleArea(float FOV, float nearZ, float farZ)
{
	m_fov = FOV;
	m_nearZ = nearZ;
	m_farZ = farZ;
	m_aspect = Globals::screenWidth / Globals::screenHeight;
}

void CCamera::SetSpeed(float moveSpeed, float rotateSpeed)
{
	m_camSpeed = moveSpeed;
	m_rotateSpeed = rotateSpeed;
}

void CCamera::SetRotAngle(float angle)
{
	angle = angle * M_PI / 180.0;
	m_rotateAngle = tan(angle);
}


void CCamera::SetPosition(const Vector3& pos)
{
	m_position = pos;
}

void CCamera::SetLook(const Vector3& look)
{
	m_look = look;
}

void CCamera::Walk(char direction)
{
	Vector3 f = m_look - m_position;
	f.Normalize();

	if (direction == CM_FORWARD)
	{
		m_position += f * m_camSpeed;
		m_look += f * m_camSpeed;
	}
	else if (direction == CM_BACKWARD)
	{
		m_position -= f * m_camSpeed;
		m_look -= f * m_camSpeed;
	}
}

void CCamera::Strafe(char direction)
{
	Vector3 f = m_look - m_position;
	f.Normalize();

	if (direction == CM_RIGHT)
	{
		Vector3 r = f.Cross(m_up);
		m_position += r * m_camSpeed;
		m_look += r * m_camSpeed;
	}
	else if (direction == CM_LEFT)
	{
		Vector3 l = m_up.Cross(f);
		m_position += l * m_camSpeed;
		m_look += l * m_camSpeed;
	}
}

void CCamera::Fly(char direction)
{
	Vector3 u = Vector3(0.0f, 1.0f, 0.0f);

	if (direction == CM_UP)
	{
		m_position += u * m_camSpeed;
		m_look += u * m_camSpeed;
	}
	else if (direction == CM_DOWN)
	{
		m_position -= u * m_camSpeed;
		m_look -= u * m_camSpeed;
	}
}

void CCamera::Pitch(char direction)
{
	Vector3 dir = m_look - m_position;
	Vector3 f;

	if (direction == CR_UP)
	{
		f = dir * cos(m_rotateAngle) + m_right.Cross(dir)*sin(m_rotateAngle) + m_right * m_right.Dot(dir)*(1 - cos(m_rotateAngle));
	}
	else if (direction == CR_DOWN)
	{
		f = dir * cos(-m_rotateAngle) + m_right.Cross(dir)*sin(-m_rotateAngle) + m_right * m_right.Dot(dir)*(1 - cos(-m_rotateAngle));
	}

	f.Normalize();
	m_look = m_position + f * m_rotateSpeed;
	m_up = m_right.Cross(m_look);
}

void CCamera::Yaw(char direction)
{

	Vector3 dir = m_look - m_position;
	Vector3 f;
	f.Normalize();

	if (direction == CR_RIGHT)
	{
		f = dir * cos(-m_rotateAngle) + m_up.Cross(dir)*sin(-m_rotateAngle) + m_up * m_up.Dot(dir)*(1 - cos(-m_rotateAngle));
	}
	else if (direction == CR_LEFT)
	{
		f = dir * cos(m_rotateAngle) + m_up.Cross(dir)*sin(m_rotateAngle) + m_up * m_up.Dot(dir)*(1 - cos(m_rotateAngle));
	}

	f.Normalize();
	m_look = m_position + f * m_rotateSpeed;
	m_right = m_look.Cross(m_up);
}

void CCamera::ComputeViewMatrix()
{
	Vector3 f = m_look - m_position;
	f.Normalize();
	Vector3 u = m_WorldUp.Normalize();
	Vector3 s = f.Cross(u);
	s.Normalize();
	u = s.Cross(f);
	m_up = u;
	m_right = s;

	Matrix result;
	result.SetIdentity();

	result.m[0][0] = s.x;
	result.m[1][0] = s.y;
	result.m[2][0] = s.z;

	result.m[0][1] = u.x;
	result.m[1][1] = u.y;
	result.m[2][1] = u.z;

	result.m[0][2] = -f.x;
	result.m[1][2] = -f.y;
	result.m[2][2] = -f.z;

	result.m[3][0] = -s.Dot(m_position);
	result.m[3][1] = -u.Dot(m_position);
	result.m[3][2] = f.Dot(m_position);

	m_viewMatrix = result;
}

void CCamera::ComputeProjMatrix()
{
	m_projMatrix.SetIdentity();
	m_projMatrix.SetPerspective(m_fov, m_aspect, m_nearZ, m_farZ);
}

void CCamera::ComputeMatrices()
{
	ComputeViewMatrix();
	ComputeProjMatrix();
	m_resultMatrix = m_viewMatrix * m_projMatrix;
}