#include<iostream>
#include<string>
#include<map>

int main() {
	std::map<char, int, std::greater<char>> myMap;
	std::string sir = "structuri";
	for (unsigned int i = 0; i < sir.length(); i++) {
		myMap[sir[i]] = i;
	}
	for (auto x : myMap) {
		std::cout << "(" << x.first << "," << x.second << ")";
	}
	std::cout << std::endl;
	return 0;

}