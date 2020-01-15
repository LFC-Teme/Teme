#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
class Analizator
{
public:
	bool isID(const std::string& str);
	bool isComment(const std::string& str);
	bool isDigit(const std::string& str);
	bool isString(const std::string& str);
	bool isBool(const std::string& str);
	bool isLiteral(const std::string& str);
	bool isKeyword(const std::string& str);
	bool isStatement(const std::string& str);
	bool isOperator(const std::string& str);
	bool isSeparator(const std::string& str);
	bool isNotLegal(const std::string& str);
	void printRoleOfToken(const std::string& token);
	void lexicalAnalyze(const std::string& nameOfFile);
};

