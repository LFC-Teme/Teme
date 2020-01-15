#include "Analizator.h"

bool Analizator::isID(const std::string& str)
{
	if (std::isdigit(str[0]))
		return false;
	int counter = 0;
	if (str[0] == '_')
		counter++;

	for (; counter < str.size(); counter++)
		if (!(isalnum(str[counter])))
			return false;

	return true;
}

bool Analizator::isComment(const std::string& str)
{
	return str == "/*" || str == "//";
}

bool Analizator::isDigit(const std::string& str)
{
	return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool Analizator::isString(const std::string& str)
{
	return str[0] == '"' && str[str.size() - 1] == '"';
}

bool Analizator::isBool(const std::string& str)
{
	return str == "true" || str == "false";
}

bool Analizator::isLiteral(const std::string& str)
{
	return isDigit(str) || isString(str) || isBool(str);
}

bool Analizator::isKeyword(const std::string& str)
{
	const std::vector<std::string> keywords{ "int", "float", "auto", "double", "do", "switch", "return" };
	for (const auto& keyword : keywords)
		if (keyword == str)
			return true;

	return false;
}

bool Analizator::isStatement(const std::string& str)
{
	const std::vector<std::string> statements{ "for", "while" };
	for (const auto& statement : statements)
		if (statement == str)
			return true;

	return false;
}

bool Analizator::isOperator(const std::string& str)
{
	const std::vector<std::string> operators{ "<", ">", "<=", ">=", "*", "+", "-", "/", "=", "-=", "*=", "+=", "/=", "++", "--", "==" };
	for (const auto& op : operators)
		if (op == str)
			return true;

	return false;
}

bool Analizator::isSeparator(const std::string& str)
{
	const std::vector<std::string> Separators{ "{", "}", ",", "(", ")", ";" };
	for (const auto& separate : Separators)
		if (separate == str)
			return true;

	return false;
}

bool Analizator::isNotLegal(const std::string& str)
{
	return str == " " || str == "\n";
}

void Analizator::printRoleOfToken(const std::string& token)
{
    if (isOperator(token))
        std::cout << "(operator, " << token << ")" << std::endl;
    else if (isSeparator(token))
        std::cout << "(separator, " << token << ")" << std::endl;
    else if (isKeyword(token))
        std::cout << "(keyword, " << token << ")" << std::endl;
	else if (isStatement(token))
		std::cout << "(statement, " << token << ")"<<std::endl;
	else if (isLiteral(token))
		std::cout << "(literal, " << token << ")"<<std::endl;
	else if (isID(token))
		std::cout << "(identifier, " << token << ")"<<std::endl;
	else if (isComment(token))
		std::cout << "(comment, " << token << ")"<<std::endl;
	else
		throw std::runtime_error(token);
}

void Analizator::lexicalAnalyze(const std::string& nameOfFile)
{
	char ch;
	std::string buffer;
	std::fstream file(nameOfFile, std::fstream::in);

	if (!file.is_open())
	{
		std::cout << "error while opening the file\n";
		exit(0);
	}
}