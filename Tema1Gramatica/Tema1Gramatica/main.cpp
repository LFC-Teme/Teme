#include"gramatica.h"
#include<time.h>

int main()
{
	Rules rule;
	gramatica gramar;
	gramar.read();
	srand(time(NULL));
	
	
	if (gramar.ckeckAll())
	{
		gramar.print();
		std::cout << '\n';
		int numberToGenerate;
		std::cout << "How many words do you want to generate ? \n";
		std::cin >> numberToGenerate;
		std::vector <std::string > generatedWords;

		while (numberToGenerate != 0)
		{
			bool everithingOk = true;

			std::string wordToGenerate = gramar.generateWord(1);
			for (int i = 0; i < generatedWords.size(); i++)
				if (wordToGenerate == generatedWords[i])
					break;
			if (everithingOk == true)
			{
				generatedWords.push_back(wordToGenerate);
				--numberToGenerate;
			}
		}
		std::cout << "Here are the generated words :) :\n";
		for (int i = 0; i < generatedWords.size(); i++)
			std::cout << generatedWords[i] << '\n';
	}
	return 0;
}