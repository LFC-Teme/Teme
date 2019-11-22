#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <iostream>

class AFD
{

private:
	std::vector<std::string> states;
	std::string alphabet;
	std::tuple<std::string, std::string, std::string>** table; 
	std::string initialState;
	std::vector<std::string> finalStates;

public:
	AFD();
	~AFD();
	void read();
	void print();
	bool checkWord(const std::string word);
	void verifyWord(const std::string word);
	void verifyWords(const std::vector<std::string> words);

};
