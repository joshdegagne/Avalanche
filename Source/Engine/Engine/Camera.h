////////////////////////////////////////////////////////////////////////////////
// Filename: Camera.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERA_H_
#define _CAMERA_H_


//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: Camera
////////////////////////////////////////////////////////////////////////////////
class Camera
{
public:
	Camera(int, int);
	Camera(const Camera&);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void SetUpDirection(float, float, float);
	void SetTarget(float, float, float);
	void SetTarget(XMFLOAT3);

	XMFLOAT3 GetPosition();

	void Render();
	void GetViewMatrix(XMFLOAT4X4&);
	void GetProjectionMatrix(XMFLOAT4X4&);
	void SetProjectionMatrix(float, float, float, float);

private:
	XMFLOAT3 up;
	XMFLOAT3 position;
	XMFLOAT3 target;

	//quantities to create projection matrix
	float m_fieldOfView;
	float m_screenAspect;
	float m_screenNear;
	float m_screenDepth;

	XMFLOAT4X4 m_viewMatrix;
	XMFLOAT4X4 m_projectionMatrix;

};

const float	NOMINAL_FIELD_OF_VIEW = (float)XM_PI / 4.0f;
const float CAMERA_SCREEN_DEPTH = 1000.0f;
const float CAMERA_SCREEN_NEAR = 0.1f;

#endif