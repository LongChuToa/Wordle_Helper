#ifndef BASE_GAME
#define BASE_GAME

#include "word_list.h"
#include <cstdlib>
#include <stdlib.h>

#define red "\033[31m"
#define reset "\033[0m"
#define green "\033[32;1m"
#define yellow "\033[33;1m"

class Base_Game
{
public:
	//CONSTRUCTOR AND DESTRUCTOR
	Base_Game(string filename);
	~Base_Game();

	//PLAY FUNCTION
	void play_with_random_word(int seed, bool support_mode);
	void play_with_custom_word(string custom);
	void play_with_choice_word(string choice);

	//GUESS FUNCTION
	class Guesses
	{
	public:
		Guesses(string word) : finish_word(word) {}

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
			for (int i = 0; i < 5; i++) {
				bool printed = false;
				for (int j = 0; j < 5; j++) {
					if (_word[i] == finish_word[i]) {
						_green(_word[i]);
						printed = true;
						break;
					}
					else if (_word[i] == finish_word[j]) {
						_yellow(_word[i]);
						printed = true;
						break;
					}
				}
				if (!printed) {
					_red(_word[i]);
				}
			}
			if (_word == finish_word) {
				cout << "\n You have guess the right word: " << finish_word;
				count = 0;
				winner = true;
			}
			count--;
		}
		void _green(char _word){
			cout << green << _word << reset;
		}
		void _yellow(char _word) {
			cout << yellow << _word << reset;
		}
		void _red(char _word) {
			cout << red << _word << reset;
		}
	private:
		friend class Base_Game;
		int count = 6;
		string finish_word;
		bool winner = false;
	};

	//SUPPORT MODE FUNCTION
	class SupportMode
	{
	public:
		SupportMode()
		{
		}
	private:
		vector<string> support_list;
	};


	//OTHER SUPPORT FUNCTION
	bool valid_word(string _word);
private:
	Word_List word_list;
};

//////////////////////////////////////
//         BEGIN DEFINITION			//
//////////////////////////////////////

Base_Game::Base_Game(string filename)
{
	word_list = Word_List(filename);
}

Base_Game::~Base_Game()
{
	word_list.allclear();
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
	cout << "The word has been choice!! (Seed: " << seed <<")\n";

	//START THE GAME
	Guesses guess = Guesses(word[random_word_idx]);
	string guess_word;
	while (guess.count != 0) {		//GUESS LOOP
		bool pass = false;
		while (!pass) {		//Check the word if size = 5 && it is valid
			cout << "\nGuesses number " << 7 - guess.count << " : ";
			cin >> guess_word;
			pass = (guess_word.size() == 5) && (valid_word(guess_word));
			if (!pass) {
				cout << "Word is invalid!!\n";
			}
		}
		guess.guess(guess_word);
		if (guess.winner) break;
	}

	//END THE GAME
	if (guess.winner) {
		cout << "\nGame finish!! You are winner";
	}
	else {
		cout << "\nYou are lose!! The word is: " << guess.finish_word;
	}
}

inline bool Base_Game::valid_word(string _word)
{
	int num = _word[0] - 'a';
	auto word_finder = word_list.get_list(0, num);
	for (auto w : word_finder) {
		if (w == _word) {
			return true;
		}
	}
	return false;
}



//////////////////////////////////////
//         END DEFINITION			//
//////////////////////////////////////

#endif // !BASE_GAME
