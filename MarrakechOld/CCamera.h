#pragma once
#include "../Utilities/utilities.h"

class CCamera
{
public:
	CCamera();

	void SetSpeed(float moveSpeed, float rotateSpeed);
	void SetPosition(const Vector3& pos);
	void SetLook(const Vector3& look);
	void SetWorldUp(const Vector3& wup);
	void SetVisibleArea(float FOV, float nearZ, float farZ);
	void SetRotAngle(float angle);

	const Vector3& GetPosition() const { return m_position; }
	const Matrix& GetResultMatrix() const { return m_resultMatrix; } // returning result of (View_matrix * projection_matrix)

	inline const float GetNearZ() const { return m_nearZ; }
	inline const float GetFarZ() const { return m_farZ; }

	void ComputeMatrices();

	const Matrix& GetViewMatrix() const { return m_viewMatrix; };
	const Matrix& GetProjMatrix() const { return m_projMatrix; };

	void Walk(char direction);
	void Strafe(char direction);
	void Fly(char direction);
	void Pitch(char direction);
	void Yaw(char direction);

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

	Vector3 m_position;
	Vector3 m_look;
	Vector3 m_up;
	Vector3 m_right;
	Vector3 m_WorldUp;

	Matrix m_viewMatrix;
	Matrix m_projMatrix;
	Matrix m_resultMatrix; //View_matrix * projection_matrix

	float m_camSpeed;
	float m_rotateSpeed;
	float m_rotateAngle;
	float m_fov;
	float m_aspect;
	float m_nearZ;
	float m_farZ;
};