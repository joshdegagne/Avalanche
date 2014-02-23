#include "gamemodel.h"
#include "Model.h"
#include "cubeTexturedModel.h"
#include "ColorShader.h"
#include "TextureShader.h"

CubeTexturedModel::CubeTexturedModel(float lengthX, float lengthY, float lengthZ, WCHAR** pTextureFileNames) : GameModel()
{
	InitializeModel(lengthX, lengthY, lengthZ, pTextureFileNames);
}

CubeTexturedModel::~CubeTexturedModel(void)
{
}


void CubeTexturedModel::InitializeModel(float lengthX, float lengthY, float lengthZ, WCHAR** pTextureFileNames)
{

	/*
	pTextures is expected to be an array[6] which holds the textures files names for the faces of the cube as follows:
	pTextures[0] frontFace
	pTextures[1] backFace
	pTextures[2] rightFace
	pTextures[3] leftFace
	pTextures[4] topFace
	pTextures[5] bottomFace
	*/


	int vertexCountPerFace = 4; 
	int indexCountPerFace = 6;  

	//m_textureVertices = new TextureVertexType[vertexCount];
	m_textureVerticesFront = new TextureVertexType[vertexCountPerFace];
	m_textureVerticesBack = new TextureVertexType[vertexCountPerFace];
	m_textureVerticesRight = new TextureVertexType[vertexCountPerFace];
	m_textureVerticesLeft = new TextureVertexType[vertexCountPerFace];
	m_textureVerticesTop = new TextureVertexType[vertexCountPerFace];
	m_textureVerticesBottom = new TextureVertexType[vertexCountPerFace];

	m_quadTextures = 0; 

	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline

	m_VertexModelArray = new Model*[NUMBER_OF_CUBE_FACES]; 


	m_textureFileNames = new WCHAR*[NUMBER_OF_CUBE_FACES]; //file names of 6 face .dds texture files
    for(int i=0; i<NUMBER_OF_CUBE_FACES; i++){
		m_textureFileNames[i] = pTextureFileNames[i]; //record the file names of the six cube face texture files
	}

	m_indicesFront = new unsigned long[indexCountPerFace];
	m_indicesBack = new unsigned long[indexCountPerFace];
	m_indicesRight = new unsigned long[indexCountPerFace];
	m_indicesLeft = new unsigned long[indexCountPerFace];
	m_indicesTop = new unsigned long[indexCountPerFace];
	m_indicesBottom = new unsigned long[indexCountPerFace];
	
	/*
	The index locations are all hard-coded to better illustrate the 
	structure. Alternatively we could use for-loops to contruct the models
	*/

	//Front Face
	m_textureVerticesFront[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, -lengthZ/2); // Front Bottom left.
	m_textureVerticesFront[0].texture = XMFLOAT2(0.0f, 1.0f);
	
	m_textureVerticesFront[1].position = XMFLOAT3(-lengthX/2, lengthY/2, -lengthZ/2);  // Front Top left.
	m_textureVerticesFront[1].texture = XMFLOAT2(0.0f, 0.0f);

	m_textureVerticesFront[2].position = XMFLOAT3(lengthX/2, -lengthY/2, -lengthZ/2);  // Front Bottom right.
	m_textureVerticesFront[2].texture = XMFLOAT2(1.0f, 1.0f);
	
	m_textureVerticesFront[3].position = XMFLOAT3(lengthX/2, lengthY/2, -lengthZ/2);   // Front Top right.
	m_textureVerticesFront[3].texture = XMFLOAT2(1.0f, 0.0f);

	//Front Face
	m_indicesFront[0] = 0;  // Front Bottom left.
	m_indicesFront[1] = 1;  // Front Top left.
	m_indicesFront[2] = 2;  // Front Bottom right.
	m_indicesFront[3] = 1;  // Front Top left.
	m_indicesFront[4] = 3;  // Front Top right.  
	m_indicesFront[5] = 2;  // Front Bottom right.

	m_VertexModelArray[0] = new Model(
			     m_textureVerticesFront, 
				 vertexCountPerFace,  //vertex count
				 m_indicesFront, 
				 indexCountPerFace, //index count
				 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Back Face

	m_textureVerticesBack[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, lengthZ/2); // Back Bottom Left.
	m_textureVerticesBack[0].texture = XMFLOAT2(1.0f, 1.0f);
	
	m_textureVerticesBack[1].position = XMFLOAT3(-lengthX/2, lengthY/2, lengthZ/2);  // Back Top Left.
	m_textureVerticesBack[1].texture = XMFLOAT2(1.0f, 0.0f);

	m_textureVerticesBack[2].position = XMFLOAT3(lengthX/2, -lengthY/2, lengthZ/2);  // Back Bottom Right.
	m_textureVerticesBack[2].texture = XMFLOAT2(0.0f, 1.0f);
	
	m_textureVerticesBack[3].position = XMFLOAT3(lengthX/2, lengthY/2, lengthZ/2);   // Back Top Right.
	m_textureVerticesBack[3].texture = XMFLOAT2(0.0f, 0.0f);

	//Back Face
	m_indicesBack[0] = 3;  // Top Back Right
	m_indicesBack[1] = 1;  // Top Back Left
	m_indicesBack[2] = 0;  // Bottom Back Left
	m_indicesBack[3] = 3;  // Top Back Right
	m_indicesBack[4] = 0;  // Bottom Back Left
	m_indicesBack[5] = 2;  // Bottom Back Right

	m_VertexModelArray[1] = new Model(
			     m_textureVerticesBack, 
				 vertexCountPerFace,  
				 m_indicesBack, 
				 indexCountPerFace, 
				 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//Right Side

	m_textureVerticesRight[0].position = XMFLOAT3(lengthX/2, lengthY/2, -lengthZ/2);   // Front Top right.
	m_textureVerticesRight[0].texture = XMFLOAT2(1.0f, 0.0f);

	m_textureVerticesRight[1].position = XMFLOAT3(lengthX/2, -lengthY/2, -lengthZ/2);  // Front Bottom right.
	m_textureVerticesRight[1].texture = XMFLOAT2(1.0f, 1.0f);

	m_textureVerticesRight[2].position = XMFLOAT3(lengthX/2, lengthY/2, lengthZ/2);   // Back Top right.
	m_textureVerticesRight[2].texture = XMFLOAT2(0.0f, 0.0f);

	m_textureVerticesRight[3].position = XMFLOAT3(lengthX/2, -lengthY/2, lengthZ/2);  // Back Bottom right.
	m_textureVerticesRight[3].texture = XMFLOAT2(0.0f, 1.0f);

	//Right Side
	m_indicesRight[0] = 1;  // Front Bottom right.
	m_indicesRight[1] = 0;  // Front Top right.
	m_indicesRight[2] = 3;  // Back Bottom right.
	m_indicesRight[3] = 0;  // Front Top right.
	m_indicesRight[4] = 2;  // Back Top right.
	m_indicesRight[5] = 3;  // Back Bottom right.

    m_VertexModelArray[2] = new Model(
			     m_textureVerticesRight, 
				 vertexCountPerFace,  
				 m_indicesRight, 
				 indexCountPerFace, 
				 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);



	//Left Side

	m_textureVerticesLeft[0].position = XMFLOAT3(-lengthX/2, lengthY/2, -lengthZ/2);   // Front Top Left.
	m_textureVerticesLeft[0].texture = XMFLOAT2(1.0f, 0.0f);

	m_textureVerticesLeft[1].position = XMFLOAT3(-lengthX/2, -lengthY/2, -lengthZ/2);  // Front Bottom Left.
	m_textureVerticesLeft[1].texture = XMFLOAT2(1.0f, 1.0f);

	m_textureVerticesLeft[2].position = XMFLOAT3(-lengthX/2, lengthY/2, lengthZ/2);   // Back Top Left.
	m_textureVerticesLeft[2].texture = XMFLOAT2(0.0f, 0.0f);

	m_textureVerticesLeft[3].position = XMFLOAT3(-lengthX/2, -lengthY/2, lengthZ/2);  // Back Bottom Left.
	m_textureVerticesLeft[3].texture = XMFLOAT2(0.0f, 1.0f);

	//Left Side 
	m_indicesLeft[0] = 0;  // Top Front Left.
	m_indicesLeft[1] = 1;  // Bottom Front Left.
	m_indicesLeft[2] = 3;  // Bottom Back Left.
	m_indicesLeft[3] = 0;  // Top Front Left.
	m_indicesLeft[4] = 3;  // Bottom Back Left.
	m_indicesLeft[5] = 2;  // Top Back Left.

	 m_VertexModelArray[3] = new Model(
			     m_textureVerticesLeft, 
				 vertexCountPerFace,  
				 m_indicesLeft, 
				 indexCountPerFace, 
				 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//Top Face

	m_textureVerticesTop[0].position = XMFLOAT3(-lengthX/2, lengthY/2, -lengthZ/2);   // Front Top Left.
	m_textureVerticesTop[0].texture = XMFLOAT2(0.0f, 1.0f);

	m_textureVerticesTop[1].position = XMFLOAT3(lengthX/2, lengthY/2, -lengthZ/2);  // Front Top Right.
	m_textureVerticesTop[1].texture = XMFLOAT2(1.0f, 1.0f);

	m_textureVerticesTop[2].position = XMFLOAT3(-lengthX/2, lengthY/2, lengthZ/2);   // Back Top Left.
	m_textureVerticesTop[2].texture = XMFLOAT2(0.0f, 0.0f);

	m_textureVerticesTop[3].position = XMFLOAT3(lengthX/2, lengthY/2, lengthZ/2);  // Back Top Right.
	m_textureVerticesTop[3].texture = XMFLOAT2(1.0f, 0.0f);

	//Top Face
	m_indicesTop[0] = 1;  // Top Front Right
	m_indicesTop[1] = 0;  // Top Front Left
	m_indicesTop[2] = 2;  // Top Back Left
	m_indicesTop[3] = 1;  // Top Front Right
	m_indicesTop[4] = 2;  // Top Back Left
	m_indicesTop[5] = 3;  // Top Back Right.

	m_VertexModelArray[4] = new Model(
			     m_textureVerticesTop, 
				 vertexCountPerFace,  
				 m_indicesTop, 
				 indexCountPerFace, 
				 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Bottom Face

	m_textureVerticesBottom[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, -lengthZ/2);   // Front Bottom Left.
	m_textureVerticesBottom[0].texture = XMFLOAT2(0.0f, 0.0f);

	m_textureVerticesBottom[1].position = XMFLOAT3(lengthX/2, -lengthY/2, -lengthZ/2);  // Front Bottom Right.
	m_textureVerticesBottom[1].texture = XMFLOAT2(1.0f, 0.0f);

	m_textureVerticesBottom[2].position = XMFLOAT3(-lengthX/2, -lengthY/2, lengthZ/2);   // Back Bottom Left.
	m_textureVerticesBottom[2].texture = XMFLOAT2(0.0f, 1.0f);

	m_textureVerticesBottom[3].position = XMFLOAT3(lengthX/2, -lengthY/2, lengthZ/2);  // Back Bottom Right.
	m_textureVerticesBottom[3].texture = XMFLOAT2(1.0f, 1.0f);

	//Bottom Face
	m_indicesBottom[0] = 0;  // Bottom Front Left
	m_indicesBottom[1] = 3;  // Bottom Back Right
	m_indicesBottom[2] = 2;  // Bottom Back Left
	m_indicesBottom[3] = 0;  // Bottom Front Left
	m_indicesBottom[4] = 1;  // Bottom Front Right
	m_indicesBottom[5] = 3;  // Bottom Back Right

	m_VertexModelArray[5] = new Model(
			     m_textureVerticesBottom, 
				 vertexCountPerFace,  
				 m_indicesBottom, 
				 indexCountPerFace, 
				 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.



}

bool CubeTexturedModel::InitializeVertexModels(ID3D11Device* d3dDevice){

	//Initialize the vertex model and textures for the  rendering to d3dDevice

	bool result = false;

	for(int i=0;i<NUMBER_OF_CUBE_FACES; i++){
	    result = m_VertexModelArray[i]->Initialize(d3dDevice);
		if(!result) return false;
	}

	result = initializeTextures(d3dDevice); //initialize the textures

	return result;



}

bool CubeTexturedModel::initializeTextures(ID3D11Device* d3dDevice){
	
	bool result;

	// Create quad texture object.
	m_quadTextures = new Texture*[NUMBER_OF_CUBE_FACES];
	if(!m_quadTextures)
	{
		return false;
	}
	// Initialize the textures on six faces of the cube model.
	for(int i=0; i<NUMBER_OF_CUBE_FACES; i++){
		  m_quadTextures[i] = new Texture;
	      result = m_quadTextures[i]->Initialize(d3dDevice, m_textureFileNames[i]);
	      if(!result)
	      {
		     return false;
	      }
	}

	return true;
}

ID3D11ShaderResourceView* CubeTexturedModel::GetTexture(int i){

	return m_quadTextures[i]->GetTexture();
}


bool CubeTexturedModel::Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader){
	
	if(!textureShader) return false; //we were not provided with a shader


	for(int i=0; i<NUMBER_OF_CUBE_FACES; i++){
	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	 m_VertexModelArray[i]->Render(deviceContext);

	 //render the game model
	 //render the game model
	 bool result = textureShader->Render(deviceContext, 
		                                  m_VertexModelArray[i]->GetIndexCount(), 
								          GetWorldMatrix(), 
								          viewMatrix, 
								          projectionMatrix,
										  GetTexture(i) //get the texture to render
										  ); 

	 if(!result) return false;
	
	}
	return true;

}



void CubeTexturedModel::Shutdown()
{


	if(m_textureVerticesTop)
	{
		delete[] m_textureVerticesTop;
		m_textureVerticesTop = 0;
	}

	if(m_textureVerticesBottom)
	{
		delete[] m_textureVerticesBottom;
		m_textureVerticesBottom = 0;
	}

	if(m_textureVerticesRight)
	{
		delete[] m_textureVerticesRight;
		m_textureVerticesRight = 0;
	}
	
	if(m_textureVerticesLeft)
	{
		delete[] m_textureVerticesLeft;
		m_textureVerticesLeft = 0;
	}
	
	if(m_textureVerticesFront)
	{
		delete[] m_textureVerticesFront;
		m_textureVerticesFront = 0;
	}
	
	if(m_textureVerticesBack)
	{
		delete[] m_textureVerticesBack;
		m_textureVerticesBack = 0;
	}


	if(m_indicesFront)
	{
		delete[] m_indicesFront;
		m_indicesFront = 0;
	}
	if(m_indicesBack)
	{
		delete[] m_indicesBack;
		m_indicesBack = 0;
	}

	if(m_indicesRight)
	{
		delete[] m_indicesRight;
		m_indicesRight = 0;
	}

	if(m_indicesLeft)
	{
		delete[] m_indicesLeft;
		m_indicesLeft = 0;
	}

	if(m_indicesTop)
	{
		delete[] m_indicesTop;
		m_indicesTop = 0;
	}

	if(m_indicesBottom)
	{
		delete[] m_indicesBottom;
		m_indicesBottom = 0;
	}


	if(m_VertexModelArray)
	{
		for(int i=0; i<NUMBER_OF_CUBE_FACES; i++) 
			delete m_VertexModelArray[i];
		delete [] m_VertexModelArray;
		m_VertexModelArray = 0;
	}

	if(m_textureFileNames)
	{
		delete [] m_textureFileNames;
		m_textureFileNames = 0;
	}

	if(m_quadTextures)
	{
		for(int i=0; i<NUMBER_OF_CUBE_FACES; i++)
			delete m_quadTextures[i]; //delete individual face textures

		delete [] m_quadTextures; //delete the texture array
		m_quadTextures = 0;
	}	


}
