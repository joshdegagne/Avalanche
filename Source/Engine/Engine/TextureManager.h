#include "ArrayList.h"
#include "IManager.h"
#include "ITexture.h"
#include "Texture.h"
#include "SpriteTexture.h"

//class Entity;
//class ViewModelBase;

class TextureManager : public IManager
{
public:
	TextureManager();

	bool initialize();
	void update(float);

	Texture* loadTexture(WCHAR*); // Create new Texture, save pointer, initialize Texture, return pointer to Texture... Ref to D3D device?
	SpriteTexture* loadSpriteTexture(WCHAR*, float); 
	void unloadTexture(ITexture*);

	// initialize texture taking in reference to game?

	//template<class T> void add(T* entity);
private:
	//ArrayList<ViewModelBase>* models;
	//ID3D11Device
};