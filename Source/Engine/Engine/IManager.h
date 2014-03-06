
class Game;

class IManager
{
public:
	virtual bool initialize(Game&)= 0;
	virtual void update(float)	= 0;
};