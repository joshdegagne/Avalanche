#include "arraylist.h"
#include "Player.h"
#include "QuadTexturedModel.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: Playfield
// The main encapsulation of the entities and management of said entities
////////////////////////////////////////////////////////////////////////////////
class Playfield
{
	public:
		Playfield();
		~Playfield();
	private:
		//ArrayList<Obstacles> obstacles;	//List of obstacles
		Player* players [4];			//List of players
		QuadTexturedModel* ground;		//Playfield quad
};