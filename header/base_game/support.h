#ifndef SUPPORT
#define SUPPORT


//SUPPORT CLASS
class Support
{
public:
	Support(int max_size = 20) :max_size(max_size) {}

	void first_add(string guess, vector<int> word, Word_List word_list);
	void add(string guess, vector<int> word);
	void print();
	bool empty();
private:
	int max_size;
	vector <string> sup_list;
};

//////////////////////////////////////
//         BEGIN DEFINITION			//
//////////////////////////////////////


inline void Support::first_add(string guess, vector<int> word, Word_List word_list)
{
	// Search for green word first
	for (int i = 0; i < 5; i++) {
		if (word[i] = GREEN) {
			if (empty()) {		//If empty, create a new sup_list
				sup_list = word_list.get_list(i, guess[i]);
			}
			// If not, traverse through two list and 
			// take all the words are the same into new list
			else {
				auto compare_list = word_list.get_list(i, guess[i]);
				vector<string> new_list;
				for (string i : sup_list) {
					for (string j : compare_list) {
						if (i == j) {
							new_list.push_back(i);
						}
					}
				}
			}
		}
	}
	// Search for yellow word second
	for (int i = 0; i < 5; i++) {
		if (word[i] = YELLOW) {
			/* If empty, it take all the word that DIFFERENT with the 
			* index of the yellow word.
			* If not empty, traverse through two list and take all the words
			* are the same, keep in mind that it will take from 4 other
			* words list, except the index of the yellow word.
			*/
			if (empty()) {
				for (int j = 0; j < 5; j++) {
					if (i != j) {
						;
					}
				}
			}
		}
	}
}

inline void Support::add(string guess, vector<int> word)
{
}

inline void Support::print()
{
}

inline bool Support::empty()
{
	return sup_list.empty();
}

//////////////////////////////////////
//         END DEFINITION			//
//////////////////////////////////////

#endif // !SUPPORT