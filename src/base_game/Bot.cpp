#include "BaseGame/Bot.h"

//////////////////////////////////////
//         BEGIN DEFINITION			//
//////////////////////////////////////

Bot::Bot()
{
}

Bot::~Bot()
{

}

void Bot::play(BaseGame& game, string mode)
{
	if (mode == "naive")
	{
		naivePlay(game);
	}
	else
	{
		cout << "Bot mode not recognized: " << mode << endl;
	}
}

/* Get a random word from the word list, and if the support list is not
empty, it will return a random word from the support list
*/
string Bot::getWord(BaseGame& game)
{
	if (game.getRound() == 1) {
		return game.randomWord(time(0));
	}
	else {
		vecS support = game.getSupport();
		if (!support.empty()) {
			return support[rand() % support.size()];
		}
		else {
			//Error check
			cout << "Support list is empty, returning empty string." << endl;
		}
	}
}

// PRIVATE FUNCTIONS
/* What a naive bot do?
- First, it will play the first word randomly
- From the second word, it will play random on the support list
- Mode is default by random, and support is true
*/
void Bot::naivePlay(BaseGame& game)
{
	game.playWithRandomWord(0, 0);
}


//////////////////////////////////////
//         END DEFINITION			//
//////////////////////////////////////