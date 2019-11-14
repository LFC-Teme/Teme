#include "Rules.h"


std::istream & operator>>(std::istream & is, Rules &rule){
	is >> rule.leftMember >> rule.rightMember;
	return is;
}

void Rules::print() {
	std::cout << this->leftMember << "->" << this->rightMember << "\n";
}
