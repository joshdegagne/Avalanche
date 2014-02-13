////////////////////////////////////////////////////////////////////////////////
// Filename: OldCamera.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"






////////////////////////////////////////////////////////////////////////////////
// Class name: OldCamera
////////////////////////////////////////////////////////////////////////////////
class OldCamera
{
public:
	OldCamera();
	OldCamera(const OldCamera&);
	~OldCamera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMFLOAT4X4&);
	void GetProjectionMatrix(XMFLOAT4X4&);
	void SetProjectionMatrix(float, float, float, float);

private:
	float positionX, positionY, positionZ;
	float rotationX, rotationY, rotationZ;

	//quantities to create projection matrix
	float fieldOfView;
	float screenAspect;
	float screenNear;
	float screenDepth;

	XMFLOAT4X4 viewMatrix;
	XMFLOAT4X4 projectionMatrix;

};