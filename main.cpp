#include "base_game/base_game.h"
#include <ctime>

int main() {
	Base_Game demo = Base_Game("wordlist.txt");
	srand(time(0));
	int seed = (rand() % 682 + 317) * (rand() % 682 + 317);
	demo.play_with_choice_word("crawl", true);
}