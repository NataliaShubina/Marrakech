#pragma once
#include "../../Util/Math.h"

class Camera
{

public:

	Camera();

	void SetSpeed(float moveSpeed, float rotateSpeed);
	void SetPosition(const math::vec3 & pos);
	void SetLook(const math::vec3 & look);
	void SetWorldUp(const math::vec3 & wup);
	void SetVisibleArea(float FOV, float nearZ, float farZ);
	void SetRotAngle(float angle);

	const math::vec3& GetPosition() const { return m_position; }
	const math::Matrix& GetResultMatrix() const { return m_resultMatrix; } // returning result of (View_matrix * projection_matrix)

	const float GetNearZ() const { return m_nearZ; }
	const float GetFarZ() const { return m_farZ; }

	void ComputeMatrices();

	math::Matrix GetViewMatrix() const { return m_viewMatrix; };
	math::Matrix GetProjMatrix() const { return m_projMatrix; };

	void Walk(char direction, float timeDelta);
	void Strafe(char direction, float timeDelta);
	void Fly(char direction, float timeDelta);
	void Pitch(char direction, float timeDelta);
	void Yaw(char direction, float timeDelta);

	enum CameraControl
	{
		CM_FORWARD,
		CM_BACKWARD,
		CM_RIGHT,
		CM_LEFT,
		CM_UP,
		CM_DOWN,
		CR_UP,
		CR_DOWN,
		CR_RIGHT,
		CR_LEFT
	};

private:

	void  ComputeViewMatrix();
	void  ComputeProjMatrix();

	math::vec3 m_position;
	math::vec3 m_look;
	math::vec3 m_up;
	math::vec3 m_right;
	math::vec3 m_WorldUp;

	math::Matrix m_viewMatrix;
	math::Matrix m_projMatrix;
	math::Matrix m_resultMatrix; //View_matrix * projection_matrix

	float m_camSpeed;
	float m_rotateSpeed;
	float m_rotateAngle;
	float m_fov;
	float m_aspect;
	float m_nearZ;
	float m_farZ;
};