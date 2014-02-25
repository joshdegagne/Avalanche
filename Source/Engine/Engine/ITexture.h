
#include <d3d11.h>

class ITexture
{
public:
	virtual ID3D11ShaderResourceView* GetTexture() = 0;
};