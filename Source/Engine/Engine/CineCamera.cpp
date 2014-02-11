////////////////////////////////////////////////////////////////////////////////
// Filename: CineCamera.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cinecamera.h"


CineCamera::CineCamera(int screenWidth, int screenHeight)
{
	position = XMFLOAT3(0.0f, 0.0f, -10.0f); //location of camera in 3D space
	direction = XMFLOAT3(0.0f, 0.0f, 1.0f); //direction camera is facing
	upDirection = XMFLOAT3(0.0f, 1.0f, 0.0f); //up direction of vector

	screenAspectRatio = ((float) screenWidth) / ((float) screenHeight);
	fieldOfView = NOMINAL_FIELD_OF_VIEW;

	/* note direction and up direction should be initialized to be
	   orthogonal to each others
	*/


}


CineCamera::CineCamera(const CineCamera& other)
{
}


CineCamera::~CineCamera()
{
}


void CineCamera::SetPosition(float x, float y, float z)
{
	position = XMFLOAT3(x, y, z);
}
void CineCamera::SetDirection(float x, float y, float z)
{
	XMFLOAT3 newDirection = XMFLOAT3(x, y, z);
	XMStoreFloat3(&direction, XMVector3Normalize(XMLoadFloat3(&newDirection)));

}
void CineCamera::SetUpDirection(float x, float y, float z)
{
	XMFLOAT3 newUpDirection = XMFLOAT3(x, y, z);
	XMStoreFloat3(&upDirection, XMVector3Normalize(XMLoadFloat3(&newUpDirection)));

}
void CineCamera::MoveForward()
{
	wchar_t* outstring = L"CineCamera::Move Forward\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	/*
	Modify the position of the camera by moving it along its
	direction vector at a rate based on the constant CAMERA_DOLLY_SPEED

	You can adjust the constant CAMERA_DOLLY_SPEED to get a nice
	smooth motion
	*/
	position.x += direction.x * CAMERA_DOLLY_SPEED;
	position.y += direction.y * CAMERA_DOLLY_SPEED;
	position.z += direction.z * CAMERA_DOLLY_SPEED;
	return;
}
void CineCamera::MoveBackward()
{
	wchar_t* outstring = L"CineCamera::Move Backward\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	position.x -= direction.x * CAMERA_DOLLY_SPEED;
	position.y -= direction.y * CAMERA_DOLLY_SPEED;
	position.z -= direction.z * CAMERA_DOLLY_SPEED;
	return;
}

void CineCamera::CraneUp()
{
	wchar_t* outstring = L"CineCamera::Crane Up\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	/*TO DO
	Modify the camera position by moving it along it's up vector based on
	the constant CAMERA_CRANE_SPEED. You can adjust this constant to get a
	nice smooth crane speed.

	Note the camera up vector will not always be pointing in the world vertical
	(that is along a y-axis). If the camera is tilted up or down that will affect
	the up vector. See the implementation of the camera tilt method below.
	*/
	position.x += upDirection.x * CAMERA_CRANE_SPEED;
	position.y += upDirection.y * CAMERA_CRANE_SPEED;
	position.z += upDirection.z * CAMERA_CRANE_SPEED;
	return;
}
void CineCamera::CraneDown()
{

	wchar_t* outstring = L"CineCamera::Crane Down\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	/*TO DO
	Modify the camera position by moving it along it's up vector based on
	the constant CAMERA_CRANE_SPEED. You can adjust this constant to get a
	nice smooth crane speed.

	Note the camera up vector will not always be pointing in the world vertical
	(that is along a y-axis). If the camera is tilted up or down that will affect
	the up vector. See the implementation of the camera tilt method below.
	*/

	position.x -= upDirection.x * CAMERA_CRANE_SPEED;
	position.y -= upDirection.y * CAMERA_CRANE_SPEED;
	position.z -= upDirection.z * CAMERA_CRANE_SPEED;
	return;
}
void CineCamera::StrafeLeft()
{
	wchar_t* outstring = L"CineCamera::Strafe Left\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	/*TO DO
	Modify the camera position by moving it along it's sideways vector based on
	the constant CAMERA_STRAFE_SPEED. You can adjust this constant to get a
	nice smooth crane speed. The sideways vector is the vector that is
	perpendicular to the plane formed by the camera direction vector and
	up vectors. See the implementation of the camera tilt operation to see how
	you can obtain this.

	*/

	XMVECTOR sideWaysVector = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&upDirection), XMLoadFloat3(&direction) ));

	position.x -= XMVectorGetX(sideWaysVector) * CAMERA_STRAFE_SPEED;
	position.y -= XMVectorGetY(sideWaysVector) * CAMERA_STRAFE_SPEED;
	position.z -= XMVectorGetZ(sideWaysVector) * CAMERA_STRAFE_SPEED;
	return;
}
void CineCamera::StrafeRight()
{

	/*TO DO
	Modify the camera position by moving it along it's sideways vector based on
	the constant CAMERA_STRAFE_SPEED. You can adjust this constant to get a
	nice smooth crane speed. The sideways vector is the vector that is
	perpendicular to the plane formed by the camera direction vector and
	up vectors. See the implementation of the camera tilt operation to see how
	you can obtain this.
	*/

	wchar_t* outstring = L"CineCamera::Strafe Right\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	XMVECTOR sideWaysVector = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&upDirection), XMLoadFloat3(&direction) ));

	position.x += XMVectorGetX(sideWaysVector) * CAMERA_STRAFE_SPEED;
	position.y += XMVectorGetY(sideWaysVector) * CAMERA_STRAFE_SPEED;
	position.z += XMVectorGetZ(sideWaysVector) * CAMERA_STRAFE_SPEED;
	return;
} 

void CineCamera::TiltDown()
{
	//NOTE: currently the argument delta is not used
	wchar_t* outstring = L"CineCamera::TiltDown\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	//Compute the sideways vector of the camera.
	//The sideways vector is the vector cross product of the up vector and the
	//direction vector of the camera

	XMVECTOR sideWaysVector = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&upDirection), XMLoadFloat3(&direction) ));

	//Tilt the camera downwards rotating about the sideways direction vector

	//Create a Rotaton Quaternion that represents a rotation about the
	//Sideways vector.
	//A Quaternion is created by supplying a vector and an angle and
	//represents a rotation of that angle about the vector

	//create the quaternion the rotates about the sideways vector of the camera
	XMVECTOR tiltRotationQuaternion = XMQuaternionRotationAxis(sideWaysVector, XM_PIDIV4/100*CAMERA_TILT_SPEED);

	//Modify both the camera's direction vector and its up vector using the
	//rotation quaternion. Note we want the camera's direction vector and up vector
	//to always be orthogonal so we rotate both of them by the same amount
	//around the sideways vector

	XMStoreFloat3(&direction, XMVector3Rotate( XMLoadFloat3(&direction), tiltRotationQuaternion));
	XMStoreFloat3(&upDirection, XMVector3Rotate( XMLoadFloat3(&upDirection), tiltRotationQuaternion));

} 
void CineCamera::TiltUp()
{
	//NOTE: currently the argument delta is not used
	wchar_t* outstring = L"CineCamera::TiltUp\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	//Tilt the camera upwards rotating about the sideways direction vector

	XMVECTOR sideWaysVector = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&upDirection), XMLoadFloat3(&direction) ));
	XMVECTOR tiltRotationQuaternion = XMQuaternionRotationAxis(sideWaysVector, -XM_PIDIV4/100*CAMERA_TILT_SPEED);

	XMStoreFloat3(&direction, XMVector3Rotate( XMLoadFloat3(&direction), tiltRotationQuaternion));
	XMStoreFloat3(&upDirection, XMVector3Rotate( XMLoadFloat3(&upDirection), tiltRotationQuaternion));

} 
void CineCamera::PanLeft()
{
	//NOTE: currently the argument delta is not used
	wchar_t* outstring = L"CineCamera::PanLeft\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	/*TO DO
	Pan the camera left rotating CCW about the up vector direction vector

	Create a Rotaton Quaternion that represents a rotation about the
	camera's up vector.
	A Quaternion is created by supplying a vector and an angle and
	represents a rotation of that angle about the vector
	See how this is done for the tilt operation
	*/

	XMVECTOR panRotationQuaternion = XMQuaternionRotationAxis(XMLoadFloat3(&upDirection), -XM_PIDIV4/100*CAMERA_PAN_SPEED);
	XMStoreFloat3(&direction, XMVector3Rotate( XMLoadFloat3(&direction), panRotationQuaternion));
} 
void CineCamera::PanRight()
{
	//NOTE: currently the argument delta is not used
	wchar_t* outstring = L"CineCamera::PanRight\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	/*TO DO
	Pan the camera left rotating CW about the up vector direction vector

	Create a Rotaton Quaternion that represents a rotation about the
	camera's up vector.
	A Quaternion is created by supplying a vector and an angle and
	represents a rotation of that angle about the vector
	See how this is done for the tilt operation
	*/

	//Pan the camera right rotating CW about the up vector direction vector
	XMVECTOR panRotationQuaternion = XMQuaternionRotationAxis(XMLoadFloat3(&upDirection), XM_PIDIV4/100*CAMERA_PAN_SPEED);
	XMStoreFloat3(&direction, XMVector3Rotate( XMLoadFloat3(&direction), panRotationQuaternion));
}
void CineCamera::RollLeft()
{
	//NOTE: currently the argument delta is not used
	wchar_t* outstring = L"CineCamera::RollLeft\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	//create the quaternion the rotates about the direction vector of the camera
	XMVECTOR rollRotationQuaternion = XMQuaternionRotationAxis(XMLoadFloat3(&direction), XM_PIDIV4/100*CAMERA_ROLL_SPEED);

	//Modify both the camera's up vector using the
	//rotation quaternion. 

	XMStoreFloat3(&upDirection, XMVector3Rotate( XMLoadFloat3(&upDirection), rollRotationQuaternion));

}

void CineCamera::RollRight()
{
	//NOTE: currently the argument delta is not used
	wchar_t* outstring = L"CineCamera::RollRight\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	//Rotate the Camera counter clockwise about its direction vector

	//create the quaternion the rotates about the direction vector of the camera
	XMVECTOR rollRotationQuaternion = XMQuaternionRotationAxis(XMLoadFloat3(&direction), -XM_PIDIV4/100*CAMERA_ROLL_SPEED);

	//Modify both the camera's up vector using the
	//rotation quaternion. 

	XMStoreFloat3(&upDirection, XMVector3Rotate( XMLoadFloat3(&upDirection), rollRotationQuaternion));

}
void CineCamera::ZoomIn()
{
	//NOTE: currently the argument delta is not used
	wchar_t* outstring = L"CineCamera::Zoom In\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);
 
	/*TO DO
	  Modify the fieldOfView to reduce the view angle based on the
	  camera's CAMERA_ZOOM_IN_FACTOR. You can adjust this constant to
	  make the zoom in smooth and comfortable to operate
       
	  Do not exceed the camera's MIN_CAMERA_FIELD_OF_VIEW or MAX_CAMERA_FIELD_OF_VIEW
	  field of view range
	*/

	   if( fieldOfView * CAMERA_ZOOM_IN_FACTOR >= MIN_CAMERA_FIELD_OF_VIEW)
	   fieldOfView = fieldOfView * CAMERA_ZOOM_IN_FACTOR;

}
void CineCamera::ZoomOut()
{
	//NOTE: currently the argument delta is not used
	wchar_t* outstring = L"CineCamera::Zoom Out\n";
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), outstring, wcslen(outstring), NULL, NULL);

	/*TO DO
	  Modify the fieldOfView to increase the view angle based on the
	  camera's CAMERA_ZOOM_OUT_FACTOR. You can adjust this constant to
	  make the zoom in smooth and comfortable to operate
       
	  Do not exceed the camera's MIN_CAMERA_FIELD_OF_VIEW or MAX_CAMERA_FIELD_OF_VIEW
	  field of view range
	*/
    if( fieldOfView * CAMERA_ZOOM_OUT_FACTOR <= MAX_CAMERA_FIELD_OF_VIEW)
	   fieldOfView = fieldOfView * CAMERA_ZOOM_OUT_FACTOR;

} 


XMFLOAT3 CineCamera::GetPosition()
{
	return position;
}


void CineCamera::Render()
{

   //Create a view matrix based on direction camera is looking
	XMStoreFloat4x4(&viewMatrix, XMMatrixLookToLH( XMLoadFloat3(&position), XMLoadFloat3(&direction), XMLoadFloat3(&upDirection)));

	//Create the projection matrix for 3D rendering.
	XMStoreFloat4x4(&projectionMatrix, XMMatrixPerspectiveFovLH(fieldOfView, screenAspectRatio, CAMERA_SCREEN_NEAR, CAMERA_SCREEN_DEPTH));

	return;
}


void CineCamera::GetViewMatrix(XMFLOAT4X4& returnMatrix)
{
	returnMatrix = viewMatrix;
	return;
}
void CineCamera::GetProjectionMatrix(XMFLOAT4X4& returnMatrix)
{
	returnMatrix = projectionMatrix;
	return;
}