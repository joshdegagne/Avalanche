#include "Model.h"
#include "ModelUtil.h"
#include "quadTexturedModel.h"

QuadTexturedModel::QuadTexturedModel(float lengthX, float lengthY, WCHAR* aTextureFileName) : Model()
{
	InitializeModel(lengthX, lengthY, aTextureFileName);
}

QuadTexturedModel::~QuadTexturedModel(void)
{
}


void QuadTexturedModel::InitializeModel(float lengthX, float lengthY, WCHAR* aTextureFileName)
{

	/*
	Create a quad consisting of 4 vertices and 2 triangles
	*/
	m_vertexCount = 4;
	m_indexCount = 6;

	m_colorVertices = 0; 
	m_textureVertices = new TextureVertexType[m_vertexCount];

	m_indices = new unsigned long[m_indexCount];

	//potentially dangerous, we should probably make a copy of the string and
	//release it ourselves later
	m_textureFileName = aTextureFileName;
	


	//Quad Face
	m_textureVertices[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, 0.0f); // Bottom left.
	m_textureVertices[0].texture = XMFLOAT2(0.0f, 1.0f);
	
	m_textureVertices[1].position = XMFLOAT3(-lengthX/2, lengthY/2, 0.0f);  // Top left.
	m_textureVertices[1].texture = XMFLOAT2(0.0f, 0.0f);

	m_textureVertices[2].position = XMFLOAT3(lengthX/2, -lengthY/2, 0.0f);  // Bottom right.
	m_textureVertices[2].texture = XMFLOAT2(1.0f, 1.0f);
	
	m_textureVertices[3].position = XMFLOAT3(lengthX/2, lengthY/2, 0.0f);   // Top right.
	m_textureVertices[3].texture = XMFLOAT2(1.0f, 0.0f);




	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.

	//Quad Face
	m_indices[0] = 0;  // Bottom left.
	m_indices[1] = 1;  // Top left.
	m_indices[2] = 2;  // Bottom right.
	m_indices[3] = 1;  // Top left.
	m_indices[4] = 3;  // Top right.  
	m_indices[5] = 2;  // Bottom right.




	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline
	m_VertexModel = new ModelUtil(GetTextureVertices(), GetVertexCount(), GetIndices(), GetIndexCount(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

bool QuadTexturedModel::initializeTextures(ID3D11Device* device){
	
	bool result;

	// Create quad texture object.
	m_quadTexture = new Texture;
	if(!m_quadTexture)
	{
		return false;
	}
	// Initialize the body texture object.
	result = m_quadTexture->Initialize(device, m_textureFileName);
	if(!result)
	{
		return false;
	}

	return true;
}

ID3D11ShaderResourceView* QuadTexturedModel::GetTexture(){

	return m_quadTexture->GetTexture();
}


void QuadTexturedModel::Shutdown()
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

	// Release the texture objects.
	if(m_quadTexture)
	{
		m_quadTexture->Shutdown();
		delete m_quadTexture;
		m_quadTexture = 0;
	}


}
