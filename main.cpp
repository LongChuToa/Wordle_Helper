#include "all_header.h"
#include <ctime>

int main() {
	Base_Game demo = Base_Game("wordlist.txt");
	srand(time(0));
	int seed = (rand() % 682 + 317) * (rand() % 682 + 317);
	demo.play_with_random_word(seed, true);
}