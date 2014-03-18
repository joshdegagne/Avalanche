#include <typeinfo>

#include "IViewModel.h"

enum class EntityType;

class ViewModelBase : public IViewModel
{
public:
	virtual ~ViewModelBase() {};
	
	//virtual bool InitializeTextures(TextureManager* texMan) = 0;
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice) = 0;
	virtual bool Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader) = 0;

	EntityType	GetAssociatedType();

	const virtual std::type_info& GetType() = 0;
	virtual void cleanUpArrayMemory() = 0;

protected:
	ViewModelBase(EntityType);

protected:
	EntityType		associatedEntity;
};