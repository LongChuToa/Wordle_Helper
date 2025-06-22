#ifndef util
#define util

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using vecS = vector<string>;
using vecI = vector<int>;
using sSet = unordered_set<string>;
using cSet = unordered_set<char>;

class Word;				//Forward declaration
class WordList
{
public:
	//MAIN FUNCTION
	WordList() = default;
	WordList(string filename);

	vector<string> getList(int idx, char wordIdx);
	vector<string> getFullList();
private:
	vector<Word> wordIndex = vector<Word>(5);
	vector<string> list;
};

//SUPPORT CLASS
/* Data structure using here is Map and vector, with map to store 26 char
* of alphabet and vector to store each alphabet word
*/
class Word
{
public:
	Word() = default;
	void addWord(char w, string words);
	vector<string> get(char w);
	
private:
	unordered_map<char, vector<string>> word;
};


#endif // ! util
