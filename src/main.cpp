#include "BaseGame/BaseGame.h"
#include <ctime>
#include <chrono>

int main() {
	srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
	auto start = std::chrono::high_resolution_clock::now();
	cout << "Configuring game..." << endl;
	BaseGame demo = BaseGame("resource/wordlist.txt");
	string s;
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	cout << "Game configured. (" << duration << " ms)" << endl;
	while (true) {
		cout << "Instruction for input: " << endl;
		cout << "1. Input a mode (random, choice, custom, reponse)." << endl;
		cout << "2. Input a word (optional, only for custom mode), or a seed (optional, only for random mode)." << endl;
		cout << "3. Input t of f for the support mode." << endl;
		cout << "4. Input e, exit, or q to quit." << endl;
		cout << "Input: " << endl;
		getline(cin, s);
		if (s == "e" || s == "exit" || s == "q") {
			cout << "Exiting..." << endl;
			break;
		}
		demo.input(s);
		getline(cin, s);
	}
}