#ifndef WORD_LIST
#define WORD_LIST

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Word;				//Forward declaration
class Word_List
{
public:
	//MAIN FUNCTION
	Word_List() = default;
	Word_List(string filename);

	vector<string> get_list(int idx, int _word_idx);
	void allclear();
private:
	Word* word_idx;
};

//SUPPORT CLASS
class Word
{
public:
	Word() { word = new vector<string>[26]; }

	void add_word(char _word, string words) {
		int idx = _word - 'a';
		this->word[idx].push_back(words);
	}
	vector<string> get(char _word) {
		return word[int(_word - 'a')];
	}
	vector<string> get(int _word_idx) {
		return word[_word_idx];
	}
	void clear() {
		delete[] word;
	}
private:
	vector<string>* word;
};

//////////////////////////////////////
//         BEGIN DEFINITION			//
//////////////////////////////////////

//MAIN FUNCTION
Word_List::Word_List(string filename)
{
	word_idx = new Word[5];
	fstream file;
	file.open(filename);
	if (file.is_open()) {
		string _word;
		while (!file.eof())
		{
			file >> _word;
			for (int i = 0; i < 5; i++) {
				word_idx[i].add_word(_word[i], _word);
			}
		};
	}
	file.close();
}

inline vector<string> Word_List::get_list(int idx, int _word_idx)
{
	return word_idx[idx].get(_word_idx);
}

inline void Word_List::allclear()
{
	for (int i = 0; i < 5; i++) {
		word_idx[i].clear();
	}
	delete[] word_idx;
}


//////////////////////////////////////
//         END DEFINITION			//
//////////////////////////////////////


#endif // ! WORD_LIST
