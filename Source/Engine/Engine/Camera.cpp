////////////////////////////////////////////////////////////////////////////////
// Filename: Camera.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Camera.h"



Camera::Camera(int screenWidth, int screenHeight)
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	target.x = 0.0f;
	target.y = 1.0f;
	target.z = 0.0f;

	up.x = 0.0f;
	up.y = 0.0f;
	up.z = 1.0f;

	m_screenAspect = ((float) screenWidth) / ((float) screenHeight);
	m_fieldOfView = NOMINAL_FIELD_OF_VIEW;
	m_screenNear = CAMERA_SCREEN_NEAR;
	m_screenDepth = CAMERA_SCREEN_DEPTH;
}

Camera::Camera(const Camera& other)
{
	m_viewMatrix = XMFLOAT4X4();
	m_projectionMatrix = XMFLOAT4X4();

	position = other.position;

	target = other.target;

	up = other.up;

	m_screenAspect = other.m_screenAspect;
	m_fieldOfView = other.m_fieldOfView;
	m_screenNear = CAMERA_SCREEN_NEAR;
	m_screenDepth = CAMERA_SCREEN_DEPTH;
}

void Camera::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	return;
}

void Camera::SetRotation(float x, float y, float z)
{
	float yaw, pitch, roll;

	XMFLOAT4X4 rotationMatrix;

	target.x = 0.0f;
	target.y = 1.0f;
	target.z = 0.0f;

	pitch = x * 0.0174532925f;
	yaw   = y * 0.0174532925f;
	roll  = z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	XMStoreFloat4x4( &rotationMatrix, XMMatrixRotationRollPitchYaw (pitch, yaw, roll) );

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	XMStoreFloat3( &target, XMVector3TransformCoord( XMVector3Normalize( XMLoadFloat3(&target)), XMLoadFloat4x4(&rotationMatrix)) );

	// Translate the rotated camera position to the location of the viewer.
	XMStoreFloat3( &target, XMLoadFloat3(&position) + XMLoadFloat3(&target) );

	return;
}

void Camera::SetUpDirection(float x, float y, float z)
{
	up.x = x;
	up.y = y;
	up.z = z;
}

void Camera::SetTarget(float x, float y, float z)
{
	target.x = x;
	target.y = y;
	target.z = z;
}

void Camera::SetTarget(XMFLOAT3 target)
{
	SetTarget(target.x, target.y, target.z);
}

XMFLOAT3 Camera::GetPosition()
{
	return position;
}


void Camera::Render()
{
	XMVECTOR direction = XMLoadFloat3( &position ) - XMLoadFloat3( &target );

	XMVECTOR tempUp = XMVector3Cross( XMVector3Cross( direction , XMLoadFloat3(&up)), direction );

	// Create View Matrix
	XMStoreFloat4x4( &m_viewMatrix, XMMatrixLookAtLH( XMLoadFloat3(&position), XMLoadFloat3(&target), tempUp) );

	// Create Projection Matrix
	XMStoreFloat4x4(&m_projectionMatrix, XMMatrixPerspectiveFovLH(m_fieldOfView, m_screenAspect, m_screenNear, m_screenDepth));

	//float height = CAMERA_HEIGHT;
	//float width = CAMERA_HEIGHT * m_screenAspect;

	//XMStoreFloat4x4(&m_projectionMatrix, XMMatrixOrthographicLH(width, height, m_screenNear, m_screenDepth));
										

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

void Camera::SetProjectionMatrix(float aFieldOfView, float anAspectRatio, float aScreenNearField, float aScreenFarField)
{
	m_fieldOfView = aFieldOfView;
	m_screenAspect = anAspectRatio;
	m_screenNear = aScreenNearField;
	m_screenDepth = aScreenFarField;
	// Create the projection matrix for 3D rendering.
	XMStoreFloat4x4(&m_projectionMatrix, XMMatrixPerspectiveFovLH(m_fieldOfView, m_screenAspect, m_screenNear, m_screenDepth));

	return;
}

XMFLOAT3 Camera::GetNormalVector()
{
	XMFLOAT3 normal;
	XMStoreFloat3( &normal, XMLoadFloat3( &position ) - XMLoadFloat3( &target ));
	return normal;
}