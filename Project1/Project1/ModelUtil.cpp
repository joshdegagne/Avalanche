////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ModelUtil.h"


ModelUtil::ModelUtil()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ModelUtil::ModelUtil(ColorVertexType* vertices, int numvertices, unsigned long* indices, int numindices, D3D_PRIMITIVE_TOPOLOGY topology)
{
	//initialize model as colored vertices
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_colorVertices = vertices;
	m_textureVertices = 0;
	m_indices = indices;
	m_vertexCount = numvertices;
	m_indexCount = numindices;
	m_primitive_topology = topology;
}
ModelUtil::ModelUtil(TextureVertexType* vertices, int numvertices, unsigned long* indices, int numindices, D3D_PRIMITIVE_TOPOLOGY topology)
{
	//initialize model as textured vertices
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_colorVertices = 0;
	m_textureVertices = vertices;
	m_indices = indices;
	m_vertexCount = numvertices;
	m_indexCount = numindices;
	m_primitive_topology = topology;
}


ModelUtil::ModelUtil(const ModelUtil& other)
{
}


ModelUtil::~ModelUtil()
{
    m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_colorVertices = 0;
	m_textureVertices = 0;
	m_indices = 0;
	m_vertexCount = 0;
	m_indexCount = 0;

}

bool ModelUtil::Initialize(ID3D11Device* device)
{
	bool result;


	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelUtil::Shutdown()
{
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}


void ModelUtil::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelUtil::GetIndexCount()
{
	return m_indexCount;
}


bool ModelUtil::InitializeBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc; // d`escriptions of our buffers
    D3D11_SUBRESOURCE_DATA vertexData, indexData; // buffer data
	HRESULT result; // for error checking

    unsigned int vertexTypeSize = 0;
	if(m_colorVertices) vertexTypeSize = sizeof(ColorVertexType);
	else if(m_textureVertices) vertexTypeSize = sizeof(TextureVertexType);


	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = vertexTypeSize * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.

	if(m_colorVertices) vertexData.pSysMem = m_colorVertices;
	else if(m_textureVertices) vertexData.pSysMem = m_textureVertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = m_indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	if(m_colorVertices) stride = sizeof(ColorVertexType);
	else if(m_textureVertices) stride = sizeof(TextureVertexType);

	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(m_primitive_topology);

	return;
}