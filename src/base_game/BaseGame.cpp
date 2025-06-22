#include "BaseGame/BaseGame.h"

//////////////////////////////////////
//         BEGIN DEFINITION			//
//////////////////////////////////////

BaseGame::BaseGame(string filename)
{
	wordList = WordList(filename);
	sup = Support();
	sup.setWordList(wordList);
}

void BaseGame::input(string s)
{
	vecS arg = stringsplit(s, ' ');
	if (arg[0] == "random") {
		playWithRandomWord(stoi(arg[1]), is_true(arg[2]));
	}
	else if (arg[0] == "choice") {
		playWithChoiceWord(arg[1], is_true(arg[2]));
	}
	else if (arg[0] == "custom") {
		playWithCustomWord(arg[1]);
	}
	else if (arg[0] == "reponse") {
		playWithReponse();
	}
	else {
		cout << "Invalid input!!\n";
	}
}

void BaseGame::wordInput(string& w)
{
	if (w == "") {
		cin >> w;
	}
}

void BaseGame::gameWorking(string w)
{
	//START THE GAME
	Guesses guess = Guesses(w);
	while (guess.turn != 0) {		//GUESS LOOP
		bool pass = false;
		while (!pass) {		//Check the word if size = 5 && it is valid
			guessWord = "";
			cout << "\nGuesses number " << 7 - guess.turn << " : ";
			if (guessWord == "") {
				cin >> guessWord;
			}
			pass = valid_word(guessWord, w.size());
			if (!pass) {
				cout << "Word is invalid!!\n";
			}
		}
		guessed.push_back(guessWord);
		guess.guess(guessWord);
		if (guess.winner) break;
		else if (supportMode) {
			sup.add(guessWord, guess.info());
			sup.print();
		}
	}
	//END THE GAME
	if (guess.winner) {
		cout << "\nGame finish!! You are winner\n";
	}
	else {
		cout << "\nYou are lose!! The word is: " << green << guess.finishWord << reset << endl;
	}
	gameReset(); // Reset the game state for next play
}

/*
Play with random word:
1. Create a word from seed (maybe your choice or another layer of random)
2. Guess the word
*/
void BaseGame::playWithRandomWord(int seed, bool supportMode)
{
	if (seed == 0) {
		seed = (rand() % 2162 + 1000) * (rand() % 2162 + 1000);
	}
	if (supportMode == 0) {
		supportMode = true;
	}
	cout << "Random mode is running...\n";
	cout << "The word has been choice!! (Seed: " << seed << ")\n";
	//RUN GAME
	this->supportMode = supportMode;
	gameWorking(randomWord(seed));
}

/* Play with choice word:
1. Choose the word that appear in word list (for using the support mode)
2. Guess the word
Note: using when demo or testing
*/
void BaseGame::playWithChoiceWord(string choice, bool supportMode)
{
	if (!is_word(choice)) {
		cout << "Invalid word!!\n";
		return;
	}
	if (!valid_word(choice)) {
		cout << "Word is not existed in word list!!\n";
		return;
	}
	cout << "Choice mode is running...\n";
	this->supportMode = supportMode;
	gameWorking(choice);
}

/* Play with custom word:
1. Write down the word, any size, any word in it
2. Guess without any support (cause there is no limit with final word)
Note: play for fun
*/
void BaseGame::playWithCustomWord(string custom)
{
	if (!is_word(custom)) {
		cout << "Invalid word!!\n";
		return;
	}
	cout << "Custom mode is running...\n";
	customMode = true;
	cout << "Word size is " << custom.size() << endl;
	gameWorking(custom);
}

/* Play with reponse:
1. You guess the word, and write the reponse for this word.
2. Game will auto run, support mode is set to true default
Note: use in Wordle today for help.
WARNING: This function must be using correctly, because most of invalid check function is gone (for simply the code)
*/
void BaseGame::playWithReponse()
{
	cout << "Reponse mode is running...\n";
	int count = 6, win = 0;
	string i_info;
	vecI info = vecI(5, 2);
	sup.setMaxSize(100);

	//GUESS LOOP
	while (count != 0) {
		win = 0;
		cout << "\nGuesses number " << 7 - count << " : ";
		cin >> guessWord;
		cout << "Reponse (0 for Green, 1 for Yellow, 2 for Red): ";
		cin >> i_info;
		for (int i = 0; i < 5; i++) {
			info[i] = i_info[i] - '0';
			if (info[i] == GREEN) {
				cout << green << guessWord[i] << reset;
				win++;
			}
			else if (info[i] == YELLOW) {
				cout << yellow << guessWord[i] << reset;
			}
			else if (info[i] == RED) {
				cout << red << guessWord[i] << reset;
			}
		}
		sup.add(guessWord, info);
		sup.print();
		count--;
		if (win == 5) { break; }
	}
	//END THE GAME
	if (win == 5) {
		cout << "\nYou are win the game!!!\n";
	}
	else {
		cout << "\nYou are lose!!\n";
	}
	gameReset(); // Reset the game state for next play	
}

void BaseGame::gameReset()
{
	guessed.clear();
	supportMode = false;
	customMode = false;
	sup.clear(); // Reset the support data if needed
	sup.setWordList(wordList);
}

string BaseGame::randomWord(int seed)
{
	srand(seed);
	int random_idx = rand() % 5;
	int randomWord = rand() % 26;
	vecS word = wordList.getList(random_idx, randomWord + 'a');
	return word[rand() % word.size()];
}

vecS BaseGame::getSupport()
{
	return vecS(sup.getList().begin(), sup.getList().end());
}


/* What valid_word doing?
* 1. It checks if the word have not existed in word list
* 2. It will make UPPERCASE word become lowercase word
* 3. It also prevent any not-5-length-word
* 4. And last it will reject any guessed word before.
*/
bool BaseGame::valid_word(string& w, int size)
{
	//Prevent any n-length word		
	if (w.size() != size) return false;
	//Transform UPPERCASE to lowercase
	for (int i = 0; i < w.size(); i++) {
		if (65 <= w[i] && w[i] <= 90) {
			w[i] += 32;
		}
		if (w[i] < 65 || w[i] > 122) return false;
	}
	// Find word that existed before in any last guessed 
	// and not existed in word list
	if (!customMode) {
		auto word_finder = wordList.getList(0, w[0]);
		for (string word : guessed) {
			if (w == word) {
				return false;
			}
		}
		for (string word : word_finder) {
			if (w == word) {
				return true;
			}
		}
	}
	return customMode;
}


//////////////////////////////////////
//         END DEFINITION			//
//////////////////////////////////////