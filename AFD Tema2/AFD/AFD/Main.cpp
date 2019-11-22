#include "AFD.h"

int main()
{
	AFD AFD;
	AFD.read();
	AFD.print();

	std::string word;
	std::vector<std::string> words;
	std::ifstream file("Words.txt");
	while (!file.eof())
	{
		file >> word;
		words.push_back(word);
	}
	AFD.verifyWords(words);

	system("pause");
	return 0;
}