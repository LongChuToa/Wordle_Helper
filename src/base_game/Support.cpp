#include "BaseGame/Support.h"

//////////////////////////////////////
//         BEGIN DEFINITION			//
//////////////////////////////////////
void Support::add(string guess, vecI word) {
	greenadd(guess, word);
	for (int i = 0; i < 5; i++) {
		if (empty()) {
			if (word[i] == GREEN) {
				//Create a new supList
				supListAdd(wordList.getList(i, guess[i]));
			}
			else if (word[i] == YELLOW) {
				/* It take all the word that DIFFERENT with the
				* index of the yellow word.
				*/
				for (int j = 0; j < 5; j++)
				{
					if (j != i) {
						supListAdd(wordList.getList(j, guess[i]));
					}
				}
			}
			else if (word[i] == RED) {
				//Take a full list then erase all word that exist
				// a Red word (except an existed word before)
				for (string j : wordList.getFullList()) {
					if (j.find(guess[i]) == string::npos && !greencheck(guess[i])) {
						supList.insert(j);
					}
				}
			}
			continue;
		}
		else {
			// For Green word, erase all word that not have Green word at index
			sSet tempList;
			if (word[i] == GREEN) {
				for (string j : supList) {
					if (j[i] == guess[i]) {
						tempList.insert(j);
					}
				}
			}
			// For Red word, erase all word that exist a Red word (except an 
			// existed word before)
			else if (word[i] == RED) {
				for (string j : supList) {
					if (j.find(guess[i]) == string::npos && !greencheck(guess[i])) {
						tempList.insert(j);
					}
				}
			}
			// For Yellow word, erase all word have Yellow word at the index i
			// or word that not exist the Yellow word
			else if (word[i] == YELLOW) {
				for (string j : supList) {
					if (j[i] != guess[i] && j.find(guess[i]) != string::npos) {
						tempList.insert(j);
					}
				}
			}
			supList = tempList; // Update supList
		}
	}
}

void Support::print()
{
	cout << "\nSupport list: [";
	if (supList.size() <= maxSize) {
		for (string i : supList) {
			cout << i << "; ";
		}
	}
	cout << "...]\n";
}

bool Support::empty()
{
	return supList.empty();
}

sSet Support::getList()
{
	return supList;
}

void Support::setMaxSize(int maxSize)
{
	this->maxSize = maxSize;
}

void Support::setWordList(WordList wordList)
{
	this->wordList = wordList;
}

void Support::clear()
{
	supList.clear();
	greenList.clear();
}

//SUPPORT FUNCTIONS
void Support::supListAdd(vecS supportList) {
	for (string i : supportList) {
		supList.insert(i);
	}
}

// Set greenlist with a green word
void Support::greenadd(string guess, vecI word) {
	for (int i = 0; i < 5; i++) {
		if (word[i] == GREEN) {
			greenList.insert(guess[i]);
		}
	}
}

// Check if a character is in the green list
bool Support::greencheck(char c) {
	for (char i : greenList) {
		if (i == c) {
			return true;
		}
	}
	return false;
}

//////////////////////////////////////
//         END DEFINITION			//
//////////////////////////////////////