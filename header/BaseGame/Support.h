#ifndef SUPPORT
#define SUPPORT

//SET UP
#include "util.h"
#include <functional>
enum TrueColor {GREEN, YELLOW, RED };


//SUPPORT CLASS
class Support
{
public:
	Support(int maxSize = 30) :maxSize(maxSize) {
		supList.reserve(15000);
	}
	~Support() {};
	
	// SUPPORT FUNCTION
	// Set support list
	void supListAdd(vecS supportList);
	// Set greenlist with a green word
	void greenadd(string guess, vecI word);
	// Check if a character is in the green list
	bool greencheck(char c);

	// MAIN FUNCTION
	void add(string guess, vecI word);
	void print();
	bool empty();
	sSet getList();
	void setMaxSize(int maxSize);
	void setWordList(WordList wordList);
	void clear();
private:
	int maxSize;
	WordList wordList;
	sSet supList; // For unique set
	cSet greenList;
};

#endif // !SUPPORT

