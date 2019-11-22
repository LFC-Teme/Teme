#include "AFD.h"

AFD::AFD()
{
}

AFD::~AFD()
{
	for (int index = 0; index < alphabet.length(); ++index)
		delete[] table[index];
	delete[] table;
}

void AFD::read()
{
	std::ifstream file("AFD.txt");
	int size;
	std::string info;

	file >> size;
	for (int index = 0; index < size; ++index)
	{
		file >> info;
		states.push_back(info);
	}

	file >> alphabet;

	table = new std::tuple<std::string, std::string, std::string> * [states.size()];
	for (int index = 0; index < states.size(); ++index)
	{
		table[index] = new std::tuple<std::string, std::string, std::string>[alphabet.length()];
	}

	for (int i=0; i<states.size(); ++i)
		for (int j = 0; j < alphabet.size(); ++j)
		{
			file >> info;
			table[i][j] = std::make_tuple(states[i], alphabet[j], info);
		}

	file >> initialState;

	file >> size;
	for (int index = 0; index < size; ++index)
	{
		file >> info;
		finalStates.push_back(info);
	}
}

void AFD::print()
{
	std::cout << "States: ";
	for (int index = 0; index < states.size(); ++index)
		std::cout << states[index] << " ";
	std::cout << std::endl;

	std::cout << "Alphabet: " << alphabet << std::endl;

	for (int i = 0; i < states.size(); ++i)
		for (int j = 0; j < alphabet.length(); ++j) 
			std::cout << "<" << std::get<0>(table[i][j]) << ", " << std::get<1>(table[i][j]) << ", " << std::get<2>(table[i][j]) << "> \n";

	std::cout << "Initial state: " << initialState << std::endl;

	std::cout << "Final states: ";
	for (int index = 0; index < finalStates.size(); ++index)
		std::cout << finalStates[index] << " ";
	std::cout << std::endl << std::endl << std::endl;
}

bool AFD::checkWord(const std::string word)
{
	for (char c : word) {
		if (alphabet.find(c) == std::string::npos)
			return false;
	}
	return true;
}

void AFD::verifyWord(const std::string word)
{
	std::string currentState = initialState;
	int stateIndex;

	if (!checkWord(word))
	{
		std::cout << "Invalid word!";
		return;
	}

	for (char c : word) {
		for (int index = 0; index < states.size(); ++index) {
			if (std::get<0>(table[index][0]) == currentState)
				stateIndex = index;
		}

		for (int index = 0; index < alphabet.length(); ++index) {
			if (std::get<1>(table[stateIndex][index]).find(c) != std::string::npos) {
				currentState = std::get<2>(table[stateIndex][index]);

				std::cout << "<" << std::get<0>(table[stateIndex][index]) << ", " << std::get<1>(table[stateIndex][index]) << ", " << std::get<2>(table[stateIndex][index]) << "> \n";

				if (currentState == "-1") {
					std::cout << "Word " << word << ": Blockage state!\n";
					return;
				}
			}
		}
	}
	if (std::find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end())
		std::cout << "Word " << word << ": Word accepted!\n";
	else
		std::cout << "Word " << word << ": Word not accepted!\n";
}

void AFD::verifyWords(const std::vector<std::string> words)
{
	for (const std::string& word : words) {
		verifyWord(word);
	}
}
