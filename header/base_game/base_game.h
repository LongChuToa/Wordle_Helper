#ifndef BASE_GAME
#define BASE_GAME

#include "word_list.h"
#include "support.h"
#include <stdlib.h>
#include <cstdlib>

#define red "\033[31m"
#define reset "\033[0m"
#define green "\033[32;1m"
#define yellow "\033[33;1m"


/////////////////BASE GAME CLASS/////////////////
class Base_Game
{
public:
	//CONSTRUCTOR AND DESTRUCTOR
	Base_Game(string filename);
	~Base_Game();

	//PLAY FUNCTION
	void game_working(string _word);
	void play_with_random_word(int seed, bool support_mode = false);
	void play_with_choice_word(string choice, bool support_mode = false);
	void play_with_custom_word(string custom);

	//OTHER SUPPORT FUNCTION
	bool valid_word(string& _word, int size = 5);
private:
	Word_List word_list;
	Support sup;
	vector <string> guessed;
	bool support_mode = false, custom_mode = false;
};

/////////////////GUESS CLASS/////////////////
class Guesses
{
public:
	Guesses(string word) : finish_word(word) {
		last_guess = vector<int>(word.size(), RED);
		is_colored = vector<bool>(word.size(), false);
	}

	/*
	* Guess the word:
	* 1. Traverse through the word.
	* 2. Compare with finish word, by traverse and check in finish word.
	* 3a. If word is same index, print it with green color.
	* 3b. If word is not at same index, print it with yellow color.
	* 3c. If word not exist, print it with red color.
	*/
	void guess(string _word) {
		cout << "Result: ";
		for (int i = 0; i < _word.size(); i++) {
			char word = _word[i];
			last_guess[i] = RED;		//Reset color here
			if (word == finish_word[i]) {
				last_guess[i] = GREEN;
				is_colored[i] = true;
			}
			else {
				for (int j = 0; j < _word.size(); j++) {
					if (word == finish_word[j] && !is_colored[j]) {
						last_guess[i] = YELLOW;
						is_colored[j] = true;
						break;
					}
				}
			}
			_print(i, word);
		}
		colored_reset();			//Reset colored here
		if (_word == finish_word) {
			cout << "\n You have guess the right word: " << finish_word;
			count = 0;
			winner = true;
		}
		count--;
	}

	void _print(int idx, char _word) {
		if (last_guess[idx] == GREEN) {
			cout << green << _word << reset;
		}
		else if (last_guess[idx] == YELLOW) {
			cout << yellow << _word << reset;
		}
		else if (last_guess[idx] == RED) {
			cout << red << _word << reset;
		}
	}
	void colored_reset() {
		is_colored.assign(finish_word.size(), false);
	}
	vector<int> info() {
		return last_guess;
	}
private:
	friend class Base_Game;
	int count = 6;
	string finish_word;
	vector <int> last_guess;
	vector <bool> is_colored;
	bool winner = false;
};

//////////////////////////////////////
//         BEGIN DEFINITION			//
//////////////////////////////////////

Base_Game::Base_Game(string filename)
{
	word_list = Word_List(filename);
	sup = Support();
}

Base_Game::~Base_Game()
{
	word_list.allclear();
}

inline void Base_Game::game_working(string _word)
{
	//START THE GAME
	Guesses guess = Guesses(_word);
	string guess_word;
	while (guess.count != 0) {		//GUESS LOOP
		bool pass = false;
		while (!pass) {		//Check the word if size = 5 && it is valid
			cout << "\nGuesses number " << 7 - guess.count << " : ";
			cin >> guess_word;
			pass = valid_word(guess_word, _word.size());
			if (!pass) {
				cout << "Word is invalid!!\n";
			}
		}
		guessed.push_back(guess_word);
		guess.guess(guess_word);
		if (guess.winner) break;
		else if (support_mode) {
			if (sup.empty()) {
				sup.first_add(guess_word, guess.info(), word_list);
			}
			else {
				sup.add(guess_word, guess.info());
			}
			sup.print();
		}
	}
	//END THE GAME
	if (guess.winner) {
		cout << "\nGame finish!! You are winner";
	}
	else {
		cout << "\nYou are lose!! The word is: " << green << guess.finish_word << reset;
	}
}

/*
* Play with random word:
* 1. Create a word from seed (maybe your choice or another layer of random)
* 2. Guess the word
*/
inline void Base_Game::play_with_random_word(int seed, bool support_mode)
{
	//RANDOM CHOICE
	srand(seed);
	int random_idx = rand() % 5;
	int random_word = rand() % 26;
	auto word = word_list.get_list(random_idx, random_word);
	int random_word_idx = rand() % word.size();
	cout << "The word has been choice!! (Seed: " << seed << ")\n";
	//RUN GAME
	this->support_mode = support_mode;
	game_working(word[random_word_idx]);
}

inline void Base_Game::play_with_choice_word(string choice, bool support_mode)
{
	this->support_mode = support_mode;
	game_working(choice);
}

inline void Base_Game::play_with_custom_word(string custom)
{
	custom_mode = true;
	cout << "Word size is " << custom.size() << endl;
	game_working(custom);
}

/* What valid_word doing?
* 1. It checks if the word have not existed in word list
* 2. It will make UPPERCASE word become lowercase word
* 3. It also prevent any not-5-length-word
* 4. And last it will reject any guessed word before.
*/
inline bool Base_Game::valid_word(string& _word, int size)
{
	//Prevent any n-length word		
	if (_word.size() != size) return false;
	//Transform UPPERCASE to lowercase
	for (int i = 0; i < _word.size(); i++) {			
		if (65 <= _word[i] && _word[i] <= 90) {
			_word[i] += 32;
		}
		if (_word[i] < 65 || _word[i] > 122) return false;	
	}
	// Find word that existed before in any last guessed 
	// and not existed in word list
	if (!custom_mode) {
		auto word_finder = word_list.get_list(0, _word[0] - 'a');
		for (string w : guessed) {				
			if (w == _word) {
				return false;
			}
		}
		for (string w : word_finder) {		
			if (w == _word) {
				return true;
			}
		}
	}
	return custom_mode;
}

//////////////////////////////////////
//         END DEFINITION			//
//////////////////////////////////////

#endif // !BASE_GAME
