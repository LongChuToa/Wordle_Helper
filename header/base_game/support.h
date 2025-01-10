#ifndef SUPPORT
#define SUPPORT

//SET UP
#include <functional>
enum TrueColor {GREEN, YELLOW, RED };
using vec_s = vector<string>;
using vec_i = vector<int>;

//SUPPORT CLASS
class Support
{
public:
	Support(int max_size = 30) :max_size(max_size) {}

	// VECTOR SUPPORT FUNCTION
	void vector_concat(vec_s& a, vec_s b);
	void vector_filter(vec_s& a, vec_s b, bool positive = true);
	void vector_erase(vec_s& vec, const function<bool(const string&)>& condition);
	void vector_erase(vec_s& vec, string del);
	vec_s vector_merge(vec_s* vec_list);

	// MAIN FUNCTION
	void first_add(string guess, vec_i word, Word_List word_list);
	void add(string guess, vec_i word);
	void print();
	bool empty();
private:
	int max_size;
	vector <string> sup_list;
	vector <pair<char, int>> green_list;
};

//////////////////////////////////////
//          BEGIN SUPPORT			//
//////////////////////////////////////

inline void Support::vector_concat(vec_s& a, vec_s b)
{
	a.insert(a.end(), b.begin(), b.end());
}

inline void Support::vector_filter(vec_s& a, vec_s b, bool positive)
{
	vec_s new_list;
	for (string i : a) {
		for (string j : b) {
			// Using XNOR !(a ^ b)
			if (!((i == j) ^ positive)) {
				new_list.push_back(i);
			}
		}
	}
	a = new_list;
}

inline void Support::vector_erase(vec_s& vec, const function<bool(const string&)>& condition)
{
	for (int j = 0; j < vec.size(); j++) {
		if (condition(vec[j])) {
			vec.erase(vec.begin() + j);
			j--;
		}
	}
}

inline void Support::vector_erase(vec_s& vec, string del)
{
	for (int i = 0; i < vec.size(); i++) {
		if (del == vec[i]) {
			vec.erase(vec.begin() + i);
			break;
		}
	}
}

/* Vector merge:
* 1. In first loop, new_list = first list
* 2. Until end, using negative filter (it mean what is diffrent can be choice)
* 3. Return merged list
*/
inline vec_s Support::vector_merge(vec_s* vec_list)
{
	vec_s new_list;
	for (int i = 0; i < 5; i++) {
		if (new_list.empty()) {
			new_list = vec_list[0];
		}
		else {
			vector_filter(new_list, vec_list[i], false);
		}
		vec_list++;
	}
}


//////////////////////////////////////
//			 END SUPPORT			//
//////////////////////////////////////


//////////////////////////////////////
//         BEGIN DEFINITION			//
//////////////////////////////////////
inline void Support::first_add(string guess, vec_i word, Word_List word_list)
{
	// Search for green word first
	for (int i = 0; i < 5; i++) {
		if (word[i] == GREEN) {
			if (empty()) {		//If empty, create a new sup_list
				sup_list = word_list.get_list(i, guess[i] - 'a');
			}
			// If not, traverse through two list and
			// take all the words are the same into new list
			else {
				auto compare_list = word_list.get_list(i, guess[i] - 'a');
				vector_filter(sup_list, compare_list);
			}
			green_list.push_back(make_pair(guess[i], i));
		}
	}
	// Search for yellow word second
	for (int i = 0; i < 5; i++) {
		if (word[i] == YELLOW) {
			/* If empty, it take all the word that DIFFERENT with the
			* index of the yellow word.
			* If not empty, traverse through two list and take all the words
			* are the same, keep in mind that it will take from 4 other
			* words list, except the index of the yellow word.
			*/
			if (empty()) {
				for (int j = 0; j < 5; j++) {
					if (i != j) {
						auto add_list = word_list.get_list(j, guess[i] - 'a');
						vector_concat(sup_list, add_list);
					}
				}
			}
			else {
				for (int j = 0; j < 5; j++) {
					if (i != j) {
						auto compare_list = word_list.get_list(j, guess[i] - 'a');
						vector_filter(sup_list, compare_list);
					}
				}
			}
		}
	}
	// Search for the red word
	for (int i = 0; i < 5; i++) {
		if (word[i] == RED) {
			/* Only execute in not empty list situation, it will delete all word
			* that has a red word in it.
			*/
			if (!empty()) {
				for (int j = 0; j < sup_list.size(); j++) {
					if (sup_list[j].find(guess[i]) != string::npos) {
						sup_list.erase(sup_list.begin() + j);
					}
				}
			}
		}
	}
}

inline void Support::add(string guess, vec_i word)
{
	bool condition = false;
	for (int i = 0; i < 5; i++) {
		// For Green word, erase all word that not have Green word at index
		if (word[i] == GREEN) {
			vector_erase(sup_list, [i, &guess](const string& s) {
				return s[i] != guess[i];
				});
		}
		// For Red word, erase all word that exist a Red word (except an 
		// existed word before)
		else if (word[i] == RED) {
			vector_erase(sup_list, [&word, i, &guess](const string& s) {
				int idx = s.find(guess[i]);
				if (idx != -1 && word[idx] == GREEN) return false;
				return s.find(guess[i]) != string::npos;
				});
		}
		// For Yellow word, erase all word have Yellow word at the index i
		// or word that not exist the Yellow word
		else if (word[i] == YELLOW) {
			vector_erase(sup_list, [i, &guess](const string& s) {
				return (s.find(guess[i]) == string::npos) || s[i] == guess[i];
				});
		}
	}
	vector_erase(sup_list, guess);
}

inline void Support::print()
{
	cout << "\nSupport list: [";
	if (sup_list.size() <= max_size) {
		for (string i : sup_list) {
			cout << i << "; ";
		}
	}
	cout << "...]\n";
}

inline bool Support::empty()
{
	return sup_list.empty();
}

//////////////////////////////////////
//         END DEFINITION			//
//////////////////////////////////////

#endif // !SUPPORT

