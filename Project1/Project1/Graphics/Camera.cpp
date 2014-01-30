////////////////////////////////////////////////////////////////////////////////
// Filename: Camera.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Camera.h"



Camera::Camera()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}


Camera::Camera(const Camera& other)
{
}


Camera::~Camera()
{
}


void Camera::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}






void Camera::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}




XMFLOAT3 Camera::GetPosition()
{
	return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}


XMFLOAT3 Camera::GetRotation()
{
	return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}


void Camera::Render()
{
	XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	XMFLOAT4X4 rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	XMStoreFloat4x4( &rotationMatrix, XMMatrixRotationRollPitchYaw (pitch, yaw, roll) );

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	XMStoreFloat3( &lookAt, XMVector3TransformCoord( XMLoadFloat3(&lookAt), XMLoadFloat4x4(&rotationMatrix)) );
	XMStoreFloat3( &up, XMVector3TransformCoord( XMLoadFloat3(&up), XMLoadFloat4x4(&rotationMatrix) ));

	// Translate the rotated camera position to the location of the viewer.
	XMStoreFloat3( &lookAt, XMLoadFloat3(&position) + XMLoadFloat3(&lookAt) );

	// Finally create the view matrix from the three updated vectors.
	XMStoreFloat4x4( &m_viewMatrix, XMMatrixLookAtLH( XMLoadFloat3(&position), XMLoadFloat3(&lookAt), XMLoadFloat3(&up)) );

	return;
}


void Camera::GetViewMatrix(XMFLOAT4X4& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}
void Camera::GetProjectionMatrix(XMFLOAT4X4& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
	return;
}
void Camera::SetProjectionMatrix(
	float aFieldOfView,
	float anAspectRatio,
	float aScreenNearField,
	float aScreenFarField)
{
	m_fieldOfView = aFieldOfView;
	m_screenAspect = anAspectRatio;
	m_screenNear = aScreenNearField;
	m_screenDepth = aScreenFarField;
	// Create the projection matrix for 3D rendering.
	XMStoreFloat4x4(&m_projectionMatrix, XMMatrixPerspectiveFovLH(m_fieldOfView, m_screenAspect, m_screenNear, m_screenDepth));

	return;
}