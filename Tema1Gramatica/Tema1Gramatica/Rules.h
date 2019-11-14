#pragma once

#include <string>
#include <iostream>

class Rules
{
public:
	char leftMember;
	std::string rightMember;
	friend std::istream& operator>> (std::istream& is, Rules& rule);
	void print();
private:
};

