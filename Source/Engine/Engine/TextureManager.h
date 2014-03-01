
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

	void initialize();
	void update(float);

	Texture* loadTexture(WCHAR*);
	SpriteTexture* loadSpriteTexture(WCHAR*, float);
	void unloadTexture(ITexture*);

	//template<class T> void add(T* entity);
private:
	//ArrayList<ViewModelBase>* models;
};