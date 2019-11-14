#include "gramatica.h"
#include<fstream>
#include<iostream>
#include<string>
#include"Rules.h"
#include<time.h>

gramatica::gramatica()
{
}


//gramatica::gramatica(std::string Vn, std::string Vt, char s, std::vector<std::string> ProdLeft, std::vector<std::string> ProdRight, uint16_t number) :
//	m_Vn(Vn), m_Vt(Vt), m_s(s), m_ProdLeft(ProdLeft), m_ProdRight(ProdRight), m_number(number)
//{
//	//Empty
//};
void gramatica::read() {
	std::fstream fin;
	fin.open("Input.txt");
	fin >> m_Vn >> m_Vt >> m_s;
	for (int index = 0; index < rulesNumber; ++index) {
		fin >> rules[index];
	}
	
}
void gramatica::print()
{
	std::cout << "NonTerminal :" << m_Vn<<std::endl;;
	std::cout << "Temrinal :" << m_Vt<<std::endl;
	std::cout << "start simbol:" << m_s << std::endl;
	std::cout << "Rules number:" << rulesNumber << std::endl;
	for (int i = 0; i  < rulesNumber; i++)
	{
		rules[i].print();
	}
}

bool gramatica::upperCase(std::string word)
{
	char letter;
	for (int i = 0; i < word.size(); i++) {
		letter = word[i];
		if (islower(letter)) return true;
	}
	return false;
}

bool gramatica::lowerCase(std::string word)
{
	char letter;
	for (int i = 0; i < word.size(); i++)
	{
		letter = word[i];
		if (isupper(letter)) return true;
	}
	return false;
}

bool gramatica::intersection(std::string firstWord, std::string secondWord)
{
	for (int i = 0; i < firstWord.length(); i++)
	{
		if (secondWord.find(firstWord[i] != std::string::npos)) return true;
	}
	return false;
}

bool gramatica::startInNonTerminals()
{
	if (m_Vn.find(m_s) != std::string::npos) return true;
	return false;
}

bool gramatica::checkLefttMember()
{
	for (int i = 0; i < rulesNumber; i++)
	{
		if (m_Vn.find(rules[i].leftMember) == std::string::npos)return false;
	}
	return true;
}
bool gramatica::checkRightMemeber()
{
	for (int i = 0; i < rulesNumber; i++)
	{
		for (int j = 0; j < rules[i].rightMember.length(); j++)
		{
			if (m_Vn.find(rules[i].rightMember[j]) == std::string::npos)
				if (m_Vt.find(rules[i].rightMember[j]) == std::string::npos)
					return false;
		}
	}
	return true;
}

bool gramatica::checkStartSymbolExistence()
{
	for(int i=0;i<rulesNumber;i++)
		if(rules[i].leftMember==m_s)
			return true;
	return false;

}

bool gramatica::ckeckAll()
{
	int check = 0;
	if (!lowerCase(m_Vn))
		check = 1;
	if (!upperCase(m_Vt))
		check = 2;
	if (!intersection(m_Vn,m_Vt))
		check = 3;
	if (!startInNonTerminals())
		check = 4;
	if (!checkStartSymbolExistence())
		check = 5;
	if (!checkLefttMember())
		check = 6;
	if (!checkRightMemeber())
		check = 7;
	switch (check)
	{
	case 1:
		std::cout << "Termianl error!" << "\n";
		return false;
	case 2:
		std::cout << "Nonterminal error!" << "\n";
		return false;
	case 3:
		std::cout << "there are common elemnt between Vn&Vt" << "\n";
		return false;
	case 4:
		std::cout << "Start symbol is in Vn" << "\n";
		return false;
	case 5:
		std::cout << "Start symbol isn't in left member!" << "\n";
		return false;
	case 6:
		std::cout << "Invalid left member" << "\n";
		return false;
	case 7:
		std::cout << "Invalid right member!" << "\n";
		return false;

	}
	return true;
}

bool gramatica::findChar(std::string myString, char chToFind)
{
	if (myString.find(chToFind) != std::string::npos)
		return true;
	return false;
}

Rules gramatica::getRandomRule(std::vector<int>)
{
	int getRule = rand() % pickedRule.size();
	return rules[pickedRule[getRule]];
}

void gramatica::selectRule()
{
	for (int i = 0; i < rulesNumber; i++)
	{
		if (findChar(word, rules[i].leftMember))
			pickedRule.push_back(i);
	}
}

std::string gramatica::generateWord(int isOK)
{
	word = m_s;
	while (true)
	{
		selectRule();
		if (pickedRule.size() == 0)
			return word;
		Rules currentRule = getRandomRule(pickedRule);
		int position = word.find(currentRule.leftMember);
		word = word.replace(position, currentRule.rightMember.length() - 1, currentRule.rightMember);
		if (isOK == 1)
		{
			currentRule.print();
			std::cout << word << "\n\n";
		}
		pickedRule.clear();
	}
	
}




		