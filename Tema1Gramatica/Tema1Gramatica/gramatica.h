#pragma once
#include<string>
#include<vector>
#include<cstdint>
#include<iostream>
#include"Rules.h"


class gramatica
{
public:
	gramatica();

	void read();
	 static const int rulesNumber = 10;
	char m_s;
	std::string word;
	
	void print();
	bool upperCase(std::string);
	bool lowerCase(std::string);
	bool intersection(std::string, std::string);
	bool startInNonTerminals();
	bool checkLefttMember();
	bool checkRightMemeber();
	bool checkStartSymbolExistence();
	bool ckeckAll();
	bool findChar(std::string, char);
	std::vector<int> pickedRule;
	Rules getRandomRule(std::vector<int>);
	void selectRule();
	std::string generateWord(int index);
	Rules rules[rulesNumber];
	


private:
	std::string m_Vn;
	std::string m_Vt;
};

