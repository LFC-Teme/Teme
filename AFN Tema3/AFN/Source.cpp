#include "AFN.h"
#include <conio.h>
#include <fstream>
#include <iostream>

int main() {
	AFN AFN;
	AFN.read();
	AFN.print();
	std::string word;
	std::ifstream fin("Input.txt");
	std::vector<std::string>words;
	while (!fin.eof()) {
		fin >> word;
		words.push_back(word);
	}
	AFN.verify(words);
	_getch();
}
