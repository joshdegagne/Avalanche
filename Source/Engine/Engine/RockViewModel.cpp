
#include "EntityType.h"
#include "RockObstacle.h"
#include "RockViewModel.h"
#include "TextureShader.h"
#include "ViewModel.cpp"


RockViewModel::RockViewModel() : ViewModel<RockObstacle>(EntityType::ROCK_SMALL)
{
	/*
	pTextureFileNames is expected to be an array of 3 items
	pTextureFileName[0] is the texture applied to the side faces of the prism
	pTextureFileName[1] is the texture applied to the top end of the prism
	pTextureFileName[2] is the texture applied to the bottom end of the prism
	*/

	int   numberOfFaces = 4;
	float width = 1.0f;
	float radius = 1.0f;
	
	m_textureFileNames = new WCHAR*[3];
	m_textureFileNames[0] = L"textures/temprock1.dds";
	m_textureFileNames[1] = L"textures/temprock1.dds";
	m_textureFileNames[2] = L"textures/temprock1.dds";

	//keep number of faces in a reasonable range
	if(numberOfFaces < 3) numberOfFaces = 3;
	if(numberOfFaces > 24) numberOfFaces = 24;
	
	//changing the sign of angle will affect whether the inside or outside of the prism
	//is visible
	float angle = -XM_PI * 2 / numberOfFaces; //slice angle of each face

	//temporary vertices for top and bottom
 	XMFLOAT3* topVertices = new XMFLOAT3[numberOfFaces + 1];
 	XMFLOAT3* bottomVertices = new XMFLOAT3[numberOfFaces + 1];
	
    XMFLOAT3 v0top(radius, width/2, 0); 
    XMFLOAT3 v0bottom(radius, -width/2, 0);

    XMFLOAT3 topCenter(0, width/2, 0);
    XMFLOAT3 bottomCenter(0, -width/2, 0);

    topVertices[0] = v0top;
    topVertices[numberOfFaces] = v0top;
    bottomVertices[0] = v0bottom;
    bottomVertices[numberOfFaces] = v0bottom;

    //define the vertices around the top and bottom of prism

    XMFLOAT4X4 rotationMatrix;
    for (int i = 1; i < numberOfFaces; i++)
    {
		XMStoreFloat4x4(&rotationMatrix, XMMatrixRotationY(angle * i));
	    XMStoreFloat3( &topVertices[i],  XMVector3Transform( XMLoadFloat3(&v0top), XMLoadFloat4x4(&rotationMatrix) ));
	    XMStoreFloat3( &bottomVertices[i],  XMVector3Transform( XMLoadFloat3(&v0bottom), XMLoadFloat4x4(&rotationMatrix) ));
    }

	int numberOfFaceVertices = numberOfFaces * 6;
	int numberOfTopVertices = numberOfFaces * 3;
	int numberOfBottomVertices = numberOfFaces * 3;

	m_textureVertices = new TextureVertexType[numberOfFaceVertices];
	m_topTextureVertices = new TextureVertexType[numberOfTopVertices];
	m_bottomTextureVertices = new TextureVertexType[numberOfBottomVertices];

	m_faceTextures = 0; 

	m_indices = new unsigned long[numberOfFaceVertices];
	m_topIndices = new unsigned long[numberOfTopVertices];
	m_bottomIndices = new unsigned long[numberOfBottomVertices];

	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline

	m_VertexModelArray = new Model*[NUMBER_OF_TEXTURES]; 

	float faceWidth = 1.0f/numberOfFaces;

	//define the triangle pairs that make up each face
    for (int i = 0; i < numberOfFaces; i++)
    {
           //face vertices -in clockwise render order
 	       m_textureVertices[6*i+0].position = topVertices[i];  //top left
	       m_textureVertices[6*i+0].texture = XMFLOAT2(faceWidth * i, 0.0f);	
	       m_textureVertices[6*i+1].position = topVertices[i+1];   //top right
	       m_textureVertices[6*i+1].texture = XMFLOAT2(faceWidth * (i + 1), 0.0f);
	       m_textureVertices[6*i+2].position = bottomVertices[i];   //bottom left
	       m_textureVertices[6*i+2].texture = XMFLOAT2(faceWidth * i, 1.0f);

		   m_textureVertices[6*i+3].position = bottomVertices[i];  //bottom left
	       m_textureVertices[6*i+3].texture = XMFLOAT2(faceWidth * i, 1.0f);	
	       m_textureVertices[6*i+4].position = topVertices[i + 1];   //top right
	       m_textureVertices[6*i+4].texture = XMFLOAT2(faceWidth * (i + 1), 0.0f);
	       m_textureVertices[6*i+5].position = bottomVertices[i+1];   //bottom right
	       m_textureVertices[6*i+5].texture = XMFLOAT2(faceWidth * (i + 1), 1.0f);

		   //top slice triangle
		   m_topTextureVertices[3*i+0].position = topVertices[i];  
	       m_topTextureVertices[3*i+0].texture = XMFLOAT2((radius + topVertices[i].x)/(2.0f * radius) , (radius - topVertices[i].z)/(2.0f * radius));
	       m_topTextureVertices[3*i+1].position = topCenter;   //center
	       m_topTextureVertices[3*i+1].texture = XMFLOAT2(0.5f , 0.5f);
	       m_topTextureVertices[3*i+2].position = topVertices[i + 1];   
	       m_topTextureVertices[3*i+2].texture = XMFLOAT2((radius + topVertices[i+1].x)/(2.0f * radius), (radius - topVertices[i+1].z)/(2.0f * radius));

		   //bottom slice triangle
		   m_bottomTextureVertices[3*i+0].position = bottomCenter;  //center
	       m_bottomTextureVertices[3*i+0].texture = XMFLOAT2(0.5f , 0.5f);
	       m_bottomTextureVertices[3*i+1].position = bottomVertices[i];  
	       m_bottomTextureVertices[3*i+1].texture = XMFLOAT2((radius + bottomVertices[i].x) /(2.0f * radius) , (radius - bottomVertices[i].z)/(2.0f * radius));
	       m_bottomTextureVertices[3*i+2].position = bottomVertices[i + 1];  
	       m_bottomTextureVertices[3*i+2].texture = XMFLOAT2((radius + bottomVertices[i+1].x)/(2.0f * radius), (radius - bottomVertices[i+1].z)/(2.0f * radius));
     }

	//release memory for temporary arrays
    delete [] topVertices;
 	delete [] bottomVertices;

	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.
	for(int i=0; i<numberOfFaceVertices; i++)
	     m_indices[i] = i;  // map vertices directly to indices

	for(int i=0; i<numberOfTopVertices; i++)
	     m_topIndices[i] = i;  // map vertices directly to indices

	for(int i=0; i<numberOfBottomVertices; i++)
	     m_bottomIndices[i] = i;  // map vertices directly to indices

	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline
    m_VertexModelArray[0] = new Model(
			     m_textureVertices, 
				 numberOfFaceVertices,  //vertex count
				 m_indices, 
				 numberOfFaceVertices, //index count
				 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_VertexModelArray[1] = new Model(
			     m_topTextureVertices, 
				 numberOfTopVertices,  //vertex count
				 m_topIndices, 
				 numberOfTopVertices, //index count
				 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_VertexModelArray[2] = new Model(
			     m_bottomTextureVertices, 
				 numberOfBottomVertices,  //vertex count
				 m_bottomIndices, 
				 numberOfBottomVertices, //index count
				 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	orientRotateY(XM_PIDIV4);
	orientRotateZ(XM_PIDIV2);
	orientTranslate(0.0f, radius/2, radius/2);
}

RockViewModel::~RockViewModel()
{
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

	if(m_VertexModelArray)
	{
		for(int i=0; i<NUMBER_OF_TEXTURES; i++) 
			delete m_VertexModelArray[i];
		delete [] m_VertexModelArray;
		m_VertexModelArray = 0;
	}

	if(m_textureFileNames)
	{
		delete [] m_textureFileNames;
		m_textureFileNames = 0;
	}

	if(m_faceTextures)
	{
		for(int i=0; i<NUMBER_OF_TEXTURES; i++)
			delete m_faceTextures[i]; //delete individual face textures

		delete [] m_faceTextures; //delete the texture array
		m_faceTextures = 0;
	}
}

bool RockViewModel::InitializeVertexModels(ID3D11Device* d3dDevice){

	bool result = false;

	for(int i=0;i<NUMBER_OF_TEXTURES; i++){
	    result = m_VertexModelArray[i]->Initialize(d3dDevice);
		if(!result) return false;
	}

	result = initializeTextures(d3dDevice);

	return result;

}

bool RockViewModel::initializeTextures(ID3D11Device* d3dDevice){
	
	bool result;

	// Create quad texture object.
	const int NUMBER_OF_TEXTURES = 3; //one for the sides and one each for top and bottom
	m_faceTextures = new Texture*[NUMBER_OF_TEXTURES];
	if(!m_faceTextures)
	{
		return false;
	}
	// Initialize the textures on six faces of the cube model.
	for(int i=0; i<NUMBER_OF_TEXTURES; i++){
		  m_faceTextures[i] = new Texture;
	      result = m_faceTextures[i]->Initialize(d3dDevice, m_textureFileNames[i]);
	      if(!result)
	      {
		     return false;
	      }
	}

	return true;
}

bool RockViewModel::RenderEntity(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, RockObstacle* entity){

	if(!textureShader) return false; //we were not provided with a shader

	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation() ) * XMMatrixTranslationFromVector( XMLoadFloat3( &entity->getPosition() )));

	const int NUMBER_OF_TEXTURES = 3; //one for the sides and one each for top and bottom

	for(int i=0; i<NUMBER_OF_TEXTURES; i++){
	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	 m_VertexModelArray[i]->Render(deviceContext);

	 //render the game model
	 //render the game model
	 bool result = textureShader->Render(deviceContext, 
		                                  m_VertexModelArray[i]->GetIndexCount(), 
								          worldMatrix, 
								          viewMatrix, 
								          projectionMatrix,
										  m_faceTextures[i]->GetTexture() //get the texture to render
										  ); 

	 if(!result) return false;
	
	}
	return true;

}