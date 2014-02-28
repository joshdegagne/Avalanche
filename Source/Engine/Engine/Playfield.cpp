#include "Playfield.h"
#include "DebugConsole.h"

////////////////////////
#include "PlayerViewModel.h"
#include "LogViewModel.h"
#include "ViewModel.cpp"
////////////////////////


Playfield::Playfield() : fieldLength(20.0f), fieldWidth(6.0f)
{
	//Initialize arraylist of game models
	models = new ArrayList<GameModel>;
	viewModels = new ArrayList<IViewModel>;

	entities = new ArrayList<Entity>();
	activePlayers = new ArrayList<Player>();
	obstacles = new ArrayList<Obstacle>();
}

Playfield::~Playfield()
{
	for (int i = 0; i , models->size(); ++i)
	{
		delete models->elementAt(i);
	}
	delete models;
	models = 0;
}

ArrayList<GameModel>* Playfield::getGameModels() { return models; }
ArrayList<IViewModel>* Playfield::getViewModels() { return viewModels; }

void Playfield::initialize(Game* game)
{
	populateEntityList(game);
	populateViewModels();
	associateEntitiesAndModels();
	
	placeObstacle(obstacles->elementAt(0));
	placeObstacle(obstacles->elementAt(1), 3);

	writeLabelToConsole(L"Number of players connected: ", activePlayers->size());

	//Ground Texture. (could have an enum and a switch statement for different levels)
	WCHAR* fieldTexture = L"textures/tempsnow2.dds";
	ground = new QuadTexturedModel (fieldLength, fieldWidth, fieldTexture);
	ground->worldTranslate(fieldLength/2, 3.0f, -0.1f);
	models->add(ground);
}
void Playfield::update(float elapsed) 
{
	for (int i = 0; i < entities->size(); ++i){
		entities->elementAt(i)->update(elapsed);
	}
	for (int i = 0; i < obstacles->size(); ++i)
	{
		obstacles->elementAt(i)->update(elapsed);
	}
}


//Creates obstacles and places them in the obstacles arraylist
void Playfield::populateEntityList(Game* game)
{
	for(int i = 0; i < game->GetPlayers()->size(); ++i)
	{
			Player* player = game->GetPlayers()->elementAt(i);
			activePlayers->add(player);
			entities->add(player); //Unused right now
	}
	for (int i = 0; i < 3; ++i)
	{
		obstacles->add(new LogObstacle);
		entities->add(obstacles->elementAt(i)); //unused right now
	}
}
//Creates the view models and places them in the viewModels arraylist
void Playfield::populateViewModels()
{
	viewModels->add(new PlayerViewModel);
	viewModels->add(new LogViewModel);
}
//Connects entities to their view models.
void Playfield::associateEntitiesAndModels()
{
	//Technically we should be able to loop through the viewModels, but we can't right now
	PlayerViewModel* pView = (PlayerViewModel*)(viewModels->elementAt(0));
	LogViewModel*	 lView = (LogViewModel*)(viewModels->elementAt(1));

	for (int i = 0; i < entities->size(); ++i)
	{
		Obstacle*	   currObstacle  = ((Obstacle*)(entities->elementAt(i)));

		if (pView->GetAssociatedType() == currObstacle->getEntityType())
			pView->Add((Player*)currObstacle);
		else if (lView->GetAssociatedType() == currObstacle->getEntityType())
			lView->Add((LogObstacle*)currObstacle);
	}
}


//Places input obstacle at the "beginning" of the playfield. Optional: Specific lane input
void Playfield::placeObstacle(Obstacle* obstacle, int lane)
{
	if (lane == -1) //Then randomize based on algorithm! :D
		lane = 0;	//This should be the randomization call (temp value for testing)

	float laneLength = fieldWidth/6;
	obstacle->moveBy(fieldLength, (laneLength)*(lane) + (laneLength)*1.5f);
	obstacle->setProgress(fieldLength);
	writeTextToConsole(L"Moved log to end of lane");

}