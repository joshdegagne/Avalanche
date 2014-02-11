////////////////////////////////////////////////////////////////////////////////
// Filename: CineCamera.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CINECAMERA_H_
#define _CINECAMERA_H_


//////////////
// INCLUDES //
//////////////
#include <windows.h> //needed to create and destroy windows and call Win32 functions

#include <DirectXMath.h>

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: CineCamera
////////////////////////////////////////////////////////////////////////////////
/*
CineCamearClass provides a camera that responds to tradional cinematography camera moves:
Pan-Tilt_Strafe-Dolly-Crane-Zooom
*/
	//these constants can be adjusted to provide smooth feel for the 
	//camera moves

	const float CAMERA_TILT_SPEED = 1.0f; //up and down rotation about the sideways vector direction
	const float CAMERA_PAN_SPEED = 1.0f; //left and right rotation about the up vector
	const float CAMERA_ROLL_SPEED = 1.0f; //left and right rotation about the camera direction vector
	const float CAMERA_DOLLY_SPEED = 0.1f;; //used for forward and backward travel along the camera direction vector
	const float CAMERA_STRAFE_SPEED = 0.1f; //sideways translation along the sideways vector direction
	const float CAMERA_CRANE_SPEED = 0.1f; //up and down translatoin along the up vector direction
	const float CAMERA_ZOOM_IN_FACTOR = 0.9f; //field of view mult. factor to zoom in
	const float CAMERA_ZOOM_OUT_FACTOR = 1.1f; //field of view mult. factor to zoom out

	const float	NOMINAL_FIELD_OF_VIEW = (float)XM_PI / 4.0f;

	const float MAX_CAMERA_FIELD_OF_VIEW = NOMINAL_FIELD_OF_VIEW * 3;
	const float MIN_CAMERA_FIELD_OF_VIEW = NOMINAL_FIELD_OF_VIEW / 3;

	const float CAMERA_SCREEN_DEPTH = 1000.0f;
    const float CAMERA_SCREEN_NEAR = 0.1f;

class CineCamera
{
public:
	CineCamera(int screenWidth, int screenHeight); //constructor
	CineCamera(const CineCamera&); //copy const/cructor
	~CineCamera(); //destructor

	void SetPosition(float, float, float);
	void SetDirection(float, float, float);
	void SetUpDirection(float, float, float);

	void MoveForward(); //translate forward along camera direction vector
	void MoveBackward(); //translate backwards along camera direction vector
	void StrafeLeft(); //translate left along camera sideways vector
	void StrafeRight(); //translate right along camera sideways vector
	void CraneUp(); //translate up along camera up vector
	void CraneDown(); //translate down along camera up vector
	void TiltUp(); //rotate lens, or view, upwards around camera sideways vector
	void TiltDown(); //rotate lens, or view, downwards around camera sideways vector
	void PanLeft(); //rotate left around camera up vector
	void PanRight(); //rotate right around cameara up vector
	void RollLeft(); //rotate left around camera direction vector
	void RollRight(); //rotate right around cameara direction vector
	void ZoomIn(); //increase the effective focal length for camera lens (smaller field of view angle)
	void ZoomOut(); //decrease the effectigve focal length of the camera lens (greater field of view angle)

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetDirection();
	XMFLOAT3 GetUpDirection();

	void Render();
	void GetViewMatrix(XMFLOAT4X4&);
	void GetProjectionMatrix(XMFLOAT4X4&);

private:

	XMFLOAT3 position; //position in 3-space of the camera
	XMFLOAT3 direction; //direction the camera is pointing
	XMFLOAT3 upDirection; //up direction of the camera

	float screenAspectRatio; // screen width / screen height
	float fieldOfView; //view angle of the lens in radians

	//These are the matrices the camera provides to the graphics
	//system when it is time to render
	XMFLOAT4X4 viewMatrix;
	XMFLOAT4X4 projectionMatrix;

};

#endif