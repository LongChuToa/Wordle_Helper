#include "util.h"

//////////////////////////////////////
//         BEGIN DEFINITION			//
//////////////////////////////////////

/// WordList class
//MAIN FUNCTION
WordList::WordList(string filename)
{
	fstream file;
	file.open(filename);
	if (file.is_open()) {
		string w;
		while (!file.eof())
		{
			file >> w;
			list.push_back(w);
			for (int i = 0; i < 5; i++) {
				wordIndex[i].addWord(w[i], w);
			}
		};
	}
	else {
		cerr << "File not found: " << filename << endl;
		exit(1);
	}
	file.close();
}

vector<string> WordList::getList(int idx, char wordIdx)
{
	return wordIndex[idx].get(wordIdx);
}

vector<string> WordList::getFullList()
{
	return list;
}

/// Word class
//MAIN FUNCTION
void Word::addWord(char w, string words) {
	if (word.find(w) == word.end()) {
		word[w] = vector<string>();
	}
	word[w].push_back(words);
}

vector<string> Word::get(char w) {
	return word[w];
}


//////////////////////////////////////
//         END DEFINITION			//
//////////////////////////////////////