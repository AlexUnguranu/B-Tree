#pragma once
#include <vector>
template<class T>
class Node
{
public:
	int key_number = NULL;
	bool leaf = false;
	std::vector <T>key_vector;
	std::vector<Node<T>*> link_vector;
};

