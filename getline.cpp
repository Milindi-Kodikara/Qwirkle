#include <iostream>

void getline(std::istream& is, std::string& str)
{
	std::getline(is, str);
	if (str[str.size() - 1] == '\r') str.pop_back();
}