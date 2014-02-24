#include "gamemodel.h"
#include "Model.h"
#include "cubemodel.h"
#include "ColorShader.h"

CubeModel::CubeModel(float lengthX, float lengthY, float lengthZ, XMFLOAT4 * pColors) : GameModel()
{
	InitializeModel(lengthX, lengthY, lengthZ, pColors);
}

CubeModel::~CubeModel(void)
{
}


void CubeModel::InitializeModel(float lengthX, float lengthY, float lengthZ, XMFLOAT4 * pColors)
{

	/*
	1x1 reference cube
	This model provides a nominal dimension 1x1 reference cube centered about the origin
	Each face of the cube is a different color so you can tell which side you are looking
	at.
	Vertices and Indices are hard code for easy modification and experimentation.

	Exercise: can you build these vertices and indices with a for-loop instead of
	hard coding there values?
	*/
	int vertexCount = 24;
	int indexCount = 36;

	m_colorVertices = new ColorVertexType[vertexCount];
	m_indices = new unsigned long[indexCount];
	

	XMFLOAT4 vertexColor;
	vertexColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); //red
	if(pColors) vertexColor = pColors[0];

	//Front Face
	m_colorVertices[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, -lengthZ/2); // Front Bottom left.
	m_colorVertices[0].color = vertexColor;
	
	m_colorVertices[1].position = XMFLOAT3(-lengthX/2, lengthY/2, -lengthZ/2);  // Front Top left.
	m_colorVertices[1].color = vertexColor;

	m_colorVertices[2].position = XMFLOAT3(lengthX/2, -lengthY/2, -lengthZ/2);  // Front Bottom right.
	m_colorVertices[2].color = vertexColor;
	
	m_colorVertices[3].position = XMFLOAT3(lengthX/2, lengthY/2, -lengthZ/2);   // Front Top right.
	m_colorVertices[3].color = vertexColor;

	//Back Face
	vertexColor = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f); //magenta
	if(pColors) vertexColor = pColors[1];

	m_colorVertices[4].position = XMFLOAT3(-lengthX/2, -lengthY/2, lengthZ/2); // Back Bottom Left.
	m_colorVertices[4].color = vertexColor;
	
	m_colorVertices[5].position = XMFLOAT3(-lengthX/2, lengthY/2, lengthZ/2);  // Back Top Left.
	m_colorVertices[5].color = vertexColor;

	m_colorVertices[6].position = XMFLOAT3(lengthX/2, -lengthY/2, lengthZ/2);  // Back Bottom Right.
	m_colorVertices[6].color = vertexColor;
	
	m_colorVertices[7].position = XMFLOAT3(lengthX/2, lengthY/2, lengthZ/2);   // Back Top Right.
	m_colorVertices[7].color = vertexColor;

	//Right Side
	vertexColor = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f); //blue
	if(pColors) vertexColor = pColors[2];

	m_colorVertices[8].position = XMFLOAT3(lengthX/2, lengthY/2, -lengthZ/2);   // Front Top right.
	m_colorVertices[8].color = vertexColor;

	m_colorVertices[9].position = XMFLOAT3(lengthX/2, -lengthY/2, -lengthZ/2);  // Front Bottom right.
	m_colorVertices[9].color = vertexColor;

	m_colorVertices[10].position = XMFLOAT3(lengthX/2, lengthY/2, lengthZ/2);   // Back Top right.
	m_colorVertices[10].color = vertexColor;

	m_colorVertices[11].position = XMFLOAT3(lengthX/2, -lengthY/2, lengthZ/2);  // Back Bottom right.
	m_colorVertices[11].color = vertexColor;

	//Left Side
	vertexColor = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f); //green
	if(pColors) vertexColor = pColors[3];

	m_colorVertices[12].position = XMFLOAT3(-lengthX/2, lengthY/2, -lengthZ/2);   // Front Top Left.
	m_colorVertices[12].color = vertexColor;

	m_colorVertices[13].position = XMFLOAT3(-lengthX/2, -lengthY/2, -lengthZ/2);  // Front Bottom Left.
	m_colorVertices[13].color = vertexColor;

	m_colorVertices[14].position = XMFLOAT3(-lengthX/2, lengthY/2, lengthZ/2);   // Back Top Left.
	m_colorVertices[14].color = vertexColor;

	m_colorVertices[15].position = XMFLOAT3(-lengthX/2, -lengthY/2, lengthZ/2);  // Back Bottom Left.
	m_colorVertices[15].color = vertexColor;


	//Top Face
	vertexColor = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f); //yellow
	if(pColors) vertexColor = pColors[4];

	m_colorVertices[16].position = XMFLOAT3(-lengthX/2, lengthY/2, -lengthZ/2);   // Front Top Left.
	m_colorVertices[16].color = vertexColor;

	m_colorVertices[17].position = XMFLOAT3(lengthX/2, lengthY/2, -lengthZ/2);  // Front Top Right.
	m_colorVertices[17].color = vertexColor;

	m_colorVertices[18].position = XMFLOAT3(-lengthX/2, lengthY/2, lengthZ/2);   // Back Top Left.
	m_colorVertices[18].color = vertexColor;

	m_colorVertices[19].position = XMFLOAT3(lengthX/2, lengthY/2, lengthZ/2);  // Back Top Right.
	m_colorVertices[19].color = vertexColor;

	//Bottom Face
	vertexColor = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f); //cyan
	if(pColors) vertexColor = pColors[5];

	m_colorVertices[20].position = XMFLOAT3(-lengthX/2, -lengthY/2, -lengthZ/2);   // Front Bottom Left.
	m_colorVertices[20].color = vertexColor;

	m_colorVertices[21].position = XMFLOAT3(lengthX/2, -lengthY/2, -lengthZ/2);  // Front Bottom Right.
	m_colorVertices[21].color = vertexColor;

	m_colorVertices[22].position = XMFLOAT3(-lengthX/2, -lengthY/2, lengthZ/2);   // Back Bottom Left.
	m_colorVertices[22].color = vertexColor;

	m_colorVertices[23].position = XMFLOAT3(lengthX/2, -lengthY/2, lengthZ/2);  // Back Bottom Right.
	m_colorVertices[23].color = vertexColor;


	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.

	//Front Face
	m_indices[0] = 0;  // Front Bottom left.
	m_indices[1] = 1;  // Front Top left.
	m_indices[2] = 2;  // Front Bottom right.
	m_indices[3] = 1;  // Front Top left.
	m_indices[4] = 3;  // Front Top right.  
	m_indices[5] = 2;  // Front Bottom right.

	//Right Side
	m_indices[6] = 9;  // Front Bottom right.
	m_indices[7] = 8;  // Front Top right.
	m_indices[8] = 11;  // Back Bottom right.
	m_indices[9] = 8;  // Front Top right.
	m_indices[10] = 10;  // Back Top right.
	m_indices[11] = 11;  // Back Bottom right.

	//Left Side
	m_indices[12] = 12;  // Top Front Left.
	m_indices[13] = 13;  // Bottom Front Left.
	m_indices[14] = 15;  // Bottom Back Left.
	m_indices[15] = 12;  // Top Front Left.
	m_indices[16] = 15;  // Bottom Back Left.
	m_indices[17] = 14;  // Top Back Left.

	//Top Face
	m_indices[18] = 17;  // Top Front Right
	m_indices[19] = 16;  // Top Front Left
	m_indices[20] = 18;  // Top Back Left
	m_indices[21] = 17;  // Top Front Right
	m_indices[22] = 18;  // Top Back Left
	m_indices[23] = 19;  // Top Back Right.

	//Bottom Face
	m_indices[24] = 20;  // Bottom Front Left
	m_indices[25] = 23;  // Bottom Back Right
	m_indices[26] = 22;  // Bottom Back Left
	m_indices[27] = 20;  // Bottom Front Left
	m_indices[28] = 21;  // Bottom Front Right
	m_indices[29] = 23;  // Bottom Back Right

   //Back Face
	m_indices[30] = 7;  // Top Back Right
	m_indices[31] = 5;  // Top Back Left
	m_indices[32] = 4;  // Bottom Back Left
	m_indices[33] = 7;  // Top Back Right
	m_indices[34] = 4;  // Bottom Back Left
	m_indices[35] = 6;  // Bottom Back Right


	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline
	m_VertexModel = new Model(m_colorVertices, vertexCount, m_indices, indexCount, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

bool CubeModel::InitializeVertexModels(ID3D11Device* d3dDevice){
	//subclasses who have vertices are expected to overide this method
	return m_VertexModel->Initialize(d3dDevice);

}

bool CubeModel::Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader){
	
	if(!colorShader) return false; //we were not provided with a shader

	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	 m_VertexModel->Render(deviceContext);

	 //render the game model
	 bool result = colorShader->Render(deviceContext, 
		                                  m_VertexModel->GetIndexCount(), 
								          GetWorldMatrix(), 
								          viewMatrix, 
								          projectionMatrix);
	
	return result; 

}



void CubeModel::Shutdown()
{
	if(m_colorVertices)
	{
		delete[] m_colorVertices;
		m_colorVertices = 0;
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
