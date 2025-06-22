#ifndef BASEGAME
#define BASEGAME

#include "Support.h"
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>

#define red "\033[31m"
#define reset "\033[0m"
#define green "\033[32;1m"
#define yellow "\033[33;1m"

enum MODE {random, choice, custom, reponse};


/////////////////BASE GAME CLASS/////////////////
class BaseGame
{
public:
	//CONSTRUCTOR
	BaseGame() = default;
	BaseGame(string filename);

	//PLAY FUNCTION
	void input(string s);
	void wordInput(string& w);
	void gameWorking(string w);
	void playWithRandomWord(int seed, bool supportMode = false);
	void playWithChoiceWord(string choice, bool supportMode = false);
	void playWithCustomWord(string custom);
	void playWithReponse();
	void gameReset();

	//OTHER SUPPORT FUNCTION
	string randomWord(int seed);
	int getRound() { return guessed.size() + 1; }
	void setGuess(string word) { guessWord = word; }
	vecS getSupport();
private:
	WordList wordList;
	Support sup;
	vecS guessed;
	string guessWord = "";
	bool supportMode = false, customMode = false;

private:
	//PRIVATE SUPPORT FUNCTION
	bool valid_word(string& w, int size = 5);
	vecS stringsplit(const string& s, char delimiter) {
		vecS result;
		size_t start = 0;
		size_t pos;

		while ((pos = s.find(delimiter, start)) != string::npos) {
			result.push_back(s.substr(start, pos - start));
			start = pos + 1;
		}
		result.push_back(s.substr(start));
		while (result.size() < 3) {	//Ensure at least 3 arguments
			result.push_back("0");
		}
		if (!is_number(result[1])) {
			result[2] = result[1]; // Ensure the second argument is a number
			result[1] = "0"; // Default to 0 if not a number
		}
		return result;
	}

	bool is_number(const string& s) {
		return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
	}

	bool is_true(const string& s) {
		return s == "true" || s == "t";
	}

	bool is_word(const string& s) {
		for (char c : s) {
			if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
				return false;
			}
		}
		return true;
	}
};

/////////////////GUESS CLASS/////////////////
class Guesses
{
public:
	Guesses(string word) : finishWord(word) {
		lastGuess = vecI(word.size(), RED);
		isColored = vector<bool>(word.size(), false);
	}

	/*
	Guess the word:
	 1. Traverse through the word.
	 2. Compare with finish word, by traverse and check in finish word.
	 3a. If word is same index, print it with green color.
	 3b. If word is not at same index, print it with yellow color.
	 3c. If word not exist, print it with red color.
	*/
	void guess(string word) {
		cout << "Result: ";
		for (int i = 0; i < word.size(); i++) {
			char w = word[i];
			lastGuess[i] = RED;		//Reset color here
			if (w == finishWord[i]) {
				lastGuess[i] = GREEN;
				isColored[i] = true;
			}
			else {
				for (int j = 0; j < word.size(); j++) {
					if (w == finishWord[j] && !isColored[j] && (word[j] != finishWord[j])) {
						lastGuess[i] = YELLOW;
						isColored[j] = true;
						break;
					}
				}
			}
			_print(i, w);
		}
		colored_reset();			//Reset colored here
		if (word == finishWord) {
			cout << "\n You have guess the right word: " << finishWord;
			turn = 0;
			winner = true;
		}
		turn--;
	}

private:
	//FUNCTIONS
	void _print(int idx, char word) {
		if (lastGuess[idx] == GREEN) {
			cout << green << word << reset;
		}
		else if (lastGuess[idx] == YELLOW) {
			cout << yellow << word << reset;
		}
		else if (lastGuess[idx] == RED) {
			cout << red << word << reset;
		}
	}
	void colored_reset() {
		isColored.assign(finishWord.size(), false);
	}
	vecI info() {
		return lastGuess;
	}

	//VARIABLES
	friend class BaseGame;
	int turn = 6;
	string finishWord;
	vector <int> lastGuess;
	vector <bool> isColored;
	bool winner = false;
};



#endif // !BASEGAME
