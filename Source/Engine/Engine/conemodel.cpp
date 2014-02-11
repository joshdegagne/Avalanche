#include "gamemodel.h"
#include "modelclass.h"
#include "conemodel.h"

ConeModel::ConeModel(float height, float radius, int nFaces, XMFLOAT4 * pColors) : GameModel()
{
	InitializeModel(height, radius, nFaces, pColors);
}

ConeModel::~ConeModel(void)
{ 
}


void ConeModel::InitializeModel(float height, float radius, int nFaces, XMFLOAT4 * pColors)
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



 	XMFLOAT3 topVertex;
 	XMFLOAT3* bottomVertices = new XMFLOAT3[numberOfFaces + 1];



    XMFLOAT3 v0bottom(radius, -height/2, 0);

    XMFLOAT3 topCenter(0, height/2, 0);
    XMFLOAT3 bottomCenter(0, -height/2, 0);

    topVertex = topCenter;
    bottomVertices[0] = v0bottom;
    bottomVertices[numberOfFaces] = v0bottom;


    //define the vertices around the bottom of cone

    XMFLOAT4X4 rotationMatrix;
    for (int i = 1; i < numberOfFaces; i++)
    {
		XMStoreFloat4x4(&rotationMatrix, XMMatrixRotationY(angle * i));
	    XMStoreFloat3( &bottomVertices[i],  XMVector3Transform( XMLoadFloat3(&v0bottom), XMLoadFloat4x4(&rotationMatrix) ));

    }

    m_vertexCount = numberOfFaces * 6;
	m_indexCount = m_vertexCount;

	m_colorVertices = new ColorVertexType[m_vertexCount];
	m_textureVertices = 0;
	m_indices = new unsigned long[m_indexCount];

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

		   //top slope triangles
		   m_colorVertices[6*i+0].position = topVertex; 
	       m_colorVertices[6*i+0].color = vertexColor;	
	       m_colorVertices[6*i+1].position = bottomVertices[i + 1]; 
	       m_colorVertices[6*i+1].color = vertexColor;
	       m_colorVertices[6*i+2].position = bottomVertices[i];  
	       m_colorVertices[6*i+2].color = vertexColor;

		   vertexColor = vertexEndColor;

		   //bottom slice triangle
		   m_colorVertices[6*i+3].position = bottomCenter; 
	       m_colorVertices[6*i+3].color = vertexColor;	
	       m_colorVertices[6*i+4].position = bottomVertices[i];  
	       m_colorVertices[6*i+4].color = vertexColor;
	       m_colorVertices[6*i+5].position = bottomVertices[i + 1];  
	       m_colorVertices[6*i+5].color = vertexColor;


     }

	//release memory for temporary arrays
 	delete [] bottomVertices;


    //---------------------------------------------
	

	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.
	for(int i=0; i<m_indexCount; i++)
	     m_indices[i] = i;  // map vertices directly to indices




	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline
	m_VertexModel = new ModelClass(GetColorVertices(), GetVertexCount(), GetIndices(), GetIndexCount(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}



void ConeModel::Shutdown()
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
