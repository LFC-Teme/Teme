#pragma once
#include <string>
#include <vector>
#include <tuple>

class AFN
{
public:
	AFN();
	~AFN();
	void read();
	void print();
	void verify(const std::string);
	void verify(const std::string, std::string, int, bool&);
	void verify(const std::vector<std::string>);
	bool checkValidation(const std::string);
private:
	std::vector<std::string> states;
	std::string alphabet;
	std::tuple<std::string, std::string, std::vector<std::string>> ** table; // matrix of tuples
	std::string initialState;
	std::vector<std::string> finals;
};

