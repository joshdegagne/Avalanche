////////////////////////////////////////////////////////////////////////////////
// Filename: OldCamera.cpp
////////////////////////////////////////////////////////////////////////////////
#include "OldCamera.h"



OldCamera::OldCamera()
{
	positionX = 0.0f;
	positionY = 0.0f;
	positionZ = 0.0f;

	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;
}


OldCamera::OldCamera(const OldCamera& other)
{
}


OldCamera::~OldCamera()
{
}


void OldCamera::SetPosition(float x, float y, float z)
{
	positionX = x;
	positionY = y;
	positionZ = z;
	return;
}






void OldCamera::SetRotation(float x, float y, float z)
{
	rotationX = x;
	rotationY = y;
	rotationZ = z;
	return;
}




XMFLOAT3 OldCamera::GetPosition()
{
	return XMFLOAT3(positionX, positionY, positionZ);
}


XMFLOAT3 OldCamera::GetRotation()
{
	return XMFLOAT3(rotationX, rotationY, rotationZ);
}


void OldCamera::Render()
{
	XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	XMFLOAT4X4 rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = positionX;
	position.y = positionY;
	position.z = positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = rotationX * 0.0174532925f;
	yaw   = rotationY * 0.0174532925f;
	roll  = rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	XMStoreFloat4x4( &rotationMatrix, XMMatrixRotationRollPitchYaw (pitch, yaw, roll) );

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	XMStoreFloat3( &lookAt, XMVector3TransformCoord( XMLoadFloat3(&lookAt), XMLoadFloat4x4(&rotationMatrix)) );
	XMStoreFloat3( &up, XMVector3TransformCoord( XMLoadFloat3(&up), XMLoadFloat4x4(&rotationMatrix) ));

	// Translate the rotated camera position to the location of the viewer.
	XMStoreFloat3( &lookAt, XMLoadFloat3(&position) + XMLoadFloat3(&lookAt) );

	// Finally create the view matrix from the three updated vectors.
	XMStoreFloat4x4( &viewMatrix, XMMatrixLookAtLH( XMLoadFloat3(&position), XMLoadFloat3(&lookAt), XMLoadFloat3(&up)) );

	return;
}


void OldCamera::GetViewMatrix(XMFLOAT4X4& viewMatrix)
{
	viewMatrix = viewMatrix;
	return;
}
void OldCamera::GetProjectionMatrix(XMFLOAT4X4& projectionMatrix)
{
	projectionMatrix = projectionMatrix;
	return;
}
void OldCamera::SetProjectionMatrix(
	float aFieldOfView,
	float anAspectRatio,
	float aScreenNearField,
	float aScreenFarField)
{
	fieldOfView = aFieldOfView;
	screenAspect = anAspectRatio;
	screenNear = aScreenNearField;
	screenDepth = aScreenFarField;
	// Create the projection matrix for 3D rendering.
	XMStoreFloat4x4(&projectionMatrix, XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth));

	return;
}