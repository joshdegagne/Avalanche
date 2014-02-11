////////////////////////////////////////////////////////////////////////////////
// Filename: Model.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Model.h"


Model::Model()
{
	vertexBuffer = 0;
	indexBuffer = 0;
}

Model::Model(ColorVertexType* vertices, int numvertices, unsigned long* indicesParam, int numindices, D3D_PRIMITIVE_TOPOLOGY topology)
{
	//initialize model as colored vertices
	vertexBuffer = 0;
	indexBuffer = 0;
	colorVertices = vertices;
	textureVertices = 0;
	indices = indicesParam;
	vertexCount = numvertices;
	indexCount = numindices;
	primitive_topology = topology;
}
Model::Model(TextureVertexType* vertices, int numvertices, unsigned long* indicesParam, int numindices, D3D_PRIMITIVE_TOPOLOGY topology)
{
	//initialize model as textured vertices
	vertexBuffer = 0;
	indexBuffer = 0;
	colorVertices = 0;
	textureVertices = vertices;
	indices = indicesParam;
	vertexCount = numvertices;
	indexCount = numindices;
	primitive_topology = topology;
}


Model::Model(const Model& other)
{
}


Model::~Model()
{
    vertexBuffer = 0;
	indexBuffer = 0;
	colorVertices = 0;
	textureVertices = 0;
	indices = 0;
	vertexCount = 0;
	indexCount = 0;

}

bool Model::Initialize(ID3D11Device* device)
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


void Model::Shutdown()
{
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}


void Model::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int Model::GetIndexCount()
{
	return indexCount;
}


bool Model::InitializeBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc; // d`escriptions of our buffers
    D3D11_SUBRESOURCE_DATA vertexData, indexData; // buffer data
	HRESULT result; // for error checking

    unsigned int vertexTypeSize = 0;
	if(colorVertices) vertexTypeSize = sizeof(ColorVertexType);
	else if(textureVertices) vertexTypeSize = sizeof(TextureVertexType);


	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = vertexTypeSize * vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.

	if(colorVertices) vertexData.pSysMem = colorVertices;
	else if(textureVertices) vertexData.pSysMem = textureVertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void Model::ShutdownBuffers()
{
	// Release the index buffer.
	if(indexBuffer)
	{
		indexBuffer->Release();
		indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(vertexBuffer)
	{
		vertexBuffer->Release();
		vertexBuffer = 0;
	}

	return;
}


void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	if(colorVertices) stride = sizeof(ColorVertexType);
	else if(textureVertices) stride = sizeof(TextureVertexType);

	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(primitive_topology);

	return;
}