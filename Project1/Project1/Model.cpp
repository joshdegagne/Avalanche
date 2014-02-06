#include "Model.h"
#include "ModelUtil.h"

Model::Model()
{

	//initialize all matrices to identity matrix
	XMStoreFloat4x4(&m_orientRotateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_orientTranslateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_dimensionScaleMatrix, XMMatrixIdentity());

	XMStoreFloat4x4(&m_worldRotateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_worldTranslateMatrix, XMMatrixIdentity());

}

Model::~Model(void)
{
	Shutdown();
}





void Model::Shutdown()
{
	if(m_colorVertices)
	{
		delete[] m_colorVertices;
		m_colorVertices = 0;
	}

	if(m_textureVertices)
	{
		delete[] m_textureVertices;
		m_textureVertices = 0;
	}


	if(m_indices)
	{
		delete[] m_indices;
		m_indices = 0;
	}

	if(m_VertexModel)
	{
		delete m_VertexModel;
		m_VertexModel = 0;
	}


}

bool Model::isColorVertexModel(){
	if(m_colorVertices) return true;
	else return false;
}
bool Model::isTextureVertexModel(){
	if(m_textureVertices) return true;
	else return false;

}

bool Model::initializeTextures(ID3D11Device* device){
	//subclasses who have textures are expected to overide this method
	return false;
}
ID3D11ShaderResourceView* Model::GetTexture(){
	//subclasses who have textures are expected to overide this method
	return 0;
}



ColorVertexType* Model::GetColorVertices()
{
	return m_colorVertices;
}

TextureVertexType* Model::GetTextureVertices()
{
	return m_textureVertices;
}

unsigned long* Model::GetIndices()
{
	return m_indices;
}

int Model::GetVertexCount() {
	return m_vertexCount;
}

int Model::GetIndexCount() {
	return m_indexCount;
}


ModelUtil* Model::GetVertexModel() {return m_VertexModel; }

XMFLOAT4X4 Model::GetWorldMatrix(){
    
	//Build the world matrix to give to the graphis system
	XMFLOAT4X4 worldMatrix; 
	XMStoreFloat4x4(&worldMatrix, 
		XMLoadFloat4x4(&m_orientRotateMatrix) * 
		XMLoadFloat4x4(&m_orientTranslateMatrix) * 
		XMLoadFloat4x4(&m_worldRotateMatrix) * 
		XMLoadFloat4x4(&m_worldTranslateMatrix)

		);

	return worldMatrix;

}

XMFLOAT4X4 Model::GetWorldRotateMatrix(){
	return m_worldRotateMatrix;
}

void Model::orientRotateX(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_orientRotateMatrix, XMLoadFloat4x4(&m_orientRotateMatrix) * XMMatrixRotationX(radianAngle));

}
void Model::orientRotateY(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_orientRotateMatrix, XMLoadFloat4x4(&m_orientRotateMatrix) * XMMatrixRotationY(radianAngle));

}
void Model::orientRotateZ(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_orientRotateMatrix, XMLoadFloat4x4(&m_orientRotateMatrix) * XMMatrixRotationZ(radianAngle));

}

void Model::orientTranslate(float deltaX, float deltaY, float deltaZ){
		XMStoreFloat4x4(&m_orientTranslateMatrix, XMLoadFloat4x4(&m_orientTranslateMatrix) * XMMatrixTranslation(deltaX, deltaY, deltaZ));

}

void Model::worldRotateX(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_worldRotateMatrix, XMLoadFloat4x4(&m_worldRotateMatrix) * XMMatrixRotationX(radianAngle));

}
void Model::worldRotateY(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_worldRotateMatrix, XMLoadFloat4x4(&m_worldRotateMatrix) * XMMatrixRotationY(radianAngle));

}
void Model::worldRotateZ(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&m_worldRotateMatrix, XMLoadFloat4x4(&m_worldRotateMatrix) * XMMatrixRotationZ(radianAngle));

}

void Model::worldTranslate(float deltaX, float deltaY, float deltaZ){
		XMStoreFloat4x4(&m_worldTranslateMatrix, XMLoadFloat4x4(&m_worldTranslateMatrix) * XMMatrixTranslation(deltaX, deltaY, deltaZ));

}





//User Control Moved Methods

void Model::MoveLeft()
{
	worldTranslate(-TRANSLATION_INCREMENT, 0.0f, 0.0f);
}

void Model::MoveRight()
{
	worldTranslate(TRANSLATION_INCREMENT, 0, 0);
}

void Model::MoveUp()
{
	worldTranslate(0.0f, TRANSLATION_INCREMENT, 0.0f);
}

void Model::MoveDown()
{
	worldTranslate(0.0f, -TRANSLATION_INCREMENT, 0.0f);
}

void Model::RotateLeft()
{
	orientRotateY(-XM_PIDIV4*ROTATION_SPEED);
}

void Model::RotateRight()
{
	orientRotateY(XM_PIDIV4*ROTATION_SPEED);

}