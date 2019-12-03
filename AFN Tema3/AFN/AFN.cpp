#include "AFN.h"
#include <fstream>
#include <iostream>



AFN::AFN()
{
}


AFN::~AFN()
{
	for (int index = 0; index < alphabet.length(); ++index)
		delete table[index];
	delete table;
}

void AFN::read() {
	std::ifstream fin("AFN.txt");
	int counter; // range of the reading
	std::string c; // auxilliary variable which will contain elements from the file

	// reads states
	fin >> counter;
	for (int index = 0; index < counter; ++index) {
		fin >> c;
		states.push_back(c);
	}

	// reads alphabet
	fin >> alphabet;

	// allocates memory for table
	table = new std::tuple<std::string, std::string, std::vector<std::string>>*[states.size()];
	for (int index = 0; index < states.size(); ++index) {
		table[index] = new std::tuple<std::string, std::string, std::vector<std::string>>[alphabet.length()];
	}

	// reads table
	std::vector<std::string> readStates;
	for (int lineCounter = 0; lineCounter < states.size(); ++lineCounter) {
		for (int colCounter = 0; colCounter < alphabet.length(); ++colCounter) {
			fin >> c;
			for (char aux : c) {
				if (aux != ',') {
					readStates.push_back(std::string(1, aux));
				}
			}
			table[lineCounter][colCounter] = std::make_tuple(states[lineCounter], alphabet[colCounter], readStates);
			readStates.clear();
		}
	}

	fin >> initialState;

	//reads finals
	fin >> counter;
	for (int index = 0; index < counter; ++index) {
		fin >> c;
		finals.push_back(c);
	}
}

void AFN::print() {
	for (int index = 0; index < states.size(); ++index) {
		std::cout << states[index] << " ";
	}
	std::cout << "\n\n";

	std::cout << alphabet << "\n\n";


	for (int lineCounter = 0; lineCounter < states.size(); ++lineCounter) {
		for (int colCounter = 0; colCounter < alphabet.length(); ++colCounter) {
			std::cout << "<" << std::get<0>(table[lineCounter][colCounter]) << ", " << std::get<1>(table[lineCounter][colCounter]) << ", [";
			for (std::string state : std::get<2>(table[lineCounter][colCounter])) {
				std::cout << state;
			}
			std::cout << "]>\n";
		}
	}
	std::cout << "\n\n";
}

//checks if a given word is valid
bool AFN::checkValidation(const std::string word) {
	for (char c : word) {
		if (alphabet.find(c) == std::string::npos)
			return false;
	}
	return true;
}

void AFN::verify(const std::string word, std::string currentState, int letterIndex, bool & condition) {
	
	if (word[letterIndex] == '\0') {
		//breakpoint; word is accepted
		std::cout << word << " is accepted!\n";
		condition = false;
		return;
	}

	for (int iterator = 0; iterator < states.size(); ++iterator) {
		//searches for the current state in the table
		if (states[iterator] == currentState) {
			for (int index = 0; index < alphabet.size(); ++index) {
				if (word[letterIndex] == alphabet[index]) {
					if (std::get<2>(table[iterator][index])[0] == "-") {
						condition = false;
						//breakpoint; no available path to continue
						std::cout << "Blockage detected in point: " << "<" << currentState << ", " << word[letterIndex] << ", -" << ">\n";
						return;
					}
					else {
						for (std::string c : std::get<2>(table[iterator][index])) {
							condition = true;
							std::cout << "<" << currentState << ", " << word[letterIndex] << ", " << c << ">\n";
							verify(word, c, letterIndex + 1, condition);
							if(condition == true){
								//breakpoint
								return;
							}
						}
					}
				}
			}
		}
	}
}

void AFN::verify(const std::vector<std::string> words) {
	bool condition;
	for (const std::string& word : words) {
		condition = false;
		if (!checkValidation(word)) {
			std::cout << "Invalid word!\n" << word;
		}
		std::cout << word << "\n";
		verify(word, initialState, 0, condition);
		std::cout << "\n";
	}
}

void AFN::verify(const std::string word) {
	bool condition = false;
	verify(word, initialState, 0, condition);
}
