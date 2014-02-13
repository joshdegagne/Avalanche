#include "gamemodel.h"
#include "Model.h"
#include "prismmodel.h"

PrismModel::PrismModel(float height, float radius, int nFaces, XMFLOAT4 * pColors) : GameModel()
{
	InitializeModel(height, radius, nFaces, pColors);
}

PrismModel::~PrismModel(void)
{ 
}


void PrismModel::InitializeModel(float height, float radius, int nFaces, XMFLOAT4 * pColors)
{



	int numberOfFaces = nFaces;

	//keep number of faces in a reasonable range
	if(numberOfFaces < 3) numberOfFaces = 3;
	if(numberOfFaces > 24) numberOfFaces = 24;
	
	//changing the sign of angle will affect whether the inside or outside of the prism
	//is visible
	float angle = -XM_PI * 2 / nFaces; //slice angle of each face

	float nominal_radius = 2.0f;
    float nominal_height = 2.0f;



 	XMFLOAT3* topVertices = new XMFLOAT3[numberOfFaces + 1];
 	XMFLOAT3* bottomVertices = new XMFLOAT3[numberOfFaces + 1];


	
    XMFLOAT3 v0top(radius, height/2, 0); 
    XMFLOAT3 v0bottom(radius, -height/2, 0);

    XMFLOAT3 topCenter(0, height/2, 0);
    XMFLOAT3 bottomCenter(0, -height/2, 0);

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

    int vertexCount = numberOfFaces * 12;
    int indexCount = vertexCount;

	m_colorVertices = new ColorVertexType[vertexCount];
	m_indices = new unsigned long[indexCount];

	XMFLOAT4 vertexFaceColor;
	vertexFaceColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); //red
	if(pColors) vertexFaceColor = pColors[0];

	XMFLOAT4 vertexEndColor;
	vertexEndColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); //red
	if(pColors) vertexEndColor = pColors[1];

	XMFLOAT4 vertexColor;

	//define the triangle pairs that make up each face
    for (int i = 0; i < numberOfFaces; i++)
    {
		   vertexColor = vertexFaceColor;

           //face vertices -in clockwise render order
 	       m_colorVertices[12*i+0].position = topVertices[i]; 
	       m_colorVertices[12*i+0].color = vertexColor;	
	       m_colorVertices[12*i+1].position = topVertices[i+1];  
	       m_colorVertices[12*i+1].color = vertexColor;
	       m_colorVertices[12*i+2].position = bottomVertices[i];  
	       m_colorVertices[12*i+2].color = vertexColor;

		   m_colorVertices[12*i+3].position = bottomVertices[i]; 
	       m_colorVertices[12*i+3].color = vertexColor;	
	       m_colorVertices[12*i+4].position = topVertices[i + 1];  
	       m_colorVertices[12*i+4].color = vertexColor;
	       m_colorVertices[12*i+5].position = bottomVertices[i+1];  
	       m_colorVertices[12*i+5].color = vertexColor;
	
		   vertexColor = vertexEndColor;

		   //top slice triangle
		   m_colorVertices[12*i+6].position = topVertices[i]; 
	       m_colorVertices[12*i+6].color = vertexColor;	
	       m_colorVertices[12*i+7].position = topCenter;  
	       m_colorVertices[12*i+7].color = vertexColor;
	       m_colorVertices[12*i+8].position = topVertices[i + 1];  
	       m_colorVertices[12*i+8].color = vertexColor;

		   //bottom slice triangle
		   m_colorVertices[12*i+9].position = bottomCenter; 
	       m_colorVertices[12*i+9].color = vertexColor;	
	       m_colorVertices[12*i+10].position = bottomVertices[i];  
	       m_colorVertices[12*i+10].color = vertexColor;
	       m_colorVertices[12*i+11].position = bottomVertices[i + 1];  
	       m_colorVertices[12*i+11].color = vertexColor;


     }

	//release memory for temporary arrays
    delete [] topVertices;
 	delete [] bottomVertices;


    //---------------------------------------------
	

	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.
	for(int i=0; i<indexCount; i++)
	     m_indices[i] = i;  // map vertices directly to indices




	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline
	m_VertexModel = new Model(m_colorVertices, vertexCount, m_indices, indexCount, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

bool PrismModel::InitializeVertexModels(ID3D11Device* d3dDevice){
	//subclasses who have vertices are expected to overide this method
	return m_VertexModel->Initialize(d3dDevice);

}

bool PrismModel::Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader){
	
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


void PrismModel::Shutdown()
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
