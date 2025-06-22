#ifndef BOT
#define BOT

#include <sstream>
#include <ctime>
#include "BaseGame.h"

/////////////////BOT CLASS/////////////////
class Bot
{
public:
	//CONSTRUCTOR AND DESTRUCTOR
	Bot();
	~Bot();

	//MAIN FUNCTION
	void play(BaseGame& game, string mode);

	//SUPPORT FUNCTION
	static string getWord(BaseGame& game);
private:
	//FUNCTIONS
	void naivePlay(BaseGame& game);
	//VARIABLES
	BaseGame game;
};


#endif // !BOT
