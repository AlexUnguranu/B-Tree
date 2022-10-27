
#include <iostream>
#include "B_Arbori.h"
#include <fstream>
#include <string>
template<class T>
void citireDate(std::vector<T>& vect)
{
	std::ifstream inp("B_Arbori.in");
	if (inp.is_open())
	{
		T ch;
		while (!inp.eof())
		{
			inp >> ch;
			vect.push_back(ch);
		}
	}
	inp.close();
}
void menu()
{
	bool exit = false;
	std::vector<std::string> ve;
	citireDate(ve);

	B_Arbori<std::string> tree(3);
	for (auto el : ve)
	{
		tree.BTree_Insert(el);
	}
	while (!exit)
	{
		int alegere;
		std::cout << "0. Exit menu\n1. Insert\n2. Find\n3. delete\n4. Elementul minim\n5. Elementul maxim\n6. Afisare\n7. Clear consola";
		std::cout << "\n Alegere: ";
		std::cin >> alegere;
		std::cout << "\n";
		switch (alegere)
		{
		case 1:
		{
			std::cout << "Valoarea de inserat :";
			std::string val;
			std::cin >> val;
			tree.BTree_Insert(val);
			break;
		}
		case 2:
		{
			std::pair<Node<std::string>*, int> nou;
			std::string val;
			std::cout << "Cheia nodului cautat :";
			std::cin >> val;
			nou = tree.B_search(val);
			if (nou.first == nullptr)
				std::cout << "Nodul nu exista\n";
			else std::cout << "Nodul exista: " << nou.first->key_vector[nou.second] << "\n";
			break;
		}
		case 3:
		{
			std::cout << "Cheia de sters: ";
			std::string val;
			std::cin >> val;
			tree.Delete(val);
			break;
		}
		case 4:
		{
			std::string max;
			max = tree.getMax();
			std::cout << "Nodul exista: " << max << "\n";
			break;
		}
		case 5:
		{
			std::string max;
			max = tree.getMin();
			std::cout << "Nodul exista: " << max << "\n";
			break;
		}
		case 6:
		{
			tree.Niveluri();
			break;
		}
		case 7:
		{
			system("cls");
			break;
		}
		case 0:
		{
			exit = true;
			break;
		}
		default:
			break;
		}
	}
}
int main()
{

	menu();
	//arb.Niveluri();
	//B_Arbori<int> ar1;
	//std::vector<int> vi = { 1 ,2 , 3 , 6 , 8 , 16 , 10 ,9 ,4 ,7,17 };
	//for (auto el : vi)
	//	ar1.BTree_Insert(el);
	//std::cout << std::endl << ar1.getMin() << std::endl;
	//if (arb.B_search("57").first != nullptr)
	//	std::cout << std::endl << arb.getMaxNodeX(arb.B_search("57")) << std::endl;
	//else std::cout << "Nodul nu exista\n";
	//std::cout << std::endl << arb.getMax();
	//std::cout << std::endl << arb.getMin();
	//std::cout << std::endl << arb.succesor(arb.B_search("H"))->key_vector[0] << "\n\n";
	//arb.BTree_Insert("5");
	//arb.Niveluri();
	//std::cout << "Inaltimea arborelui este <= " << arb.getHeight() << "\n";
	//std::cout << "\n\n" << arb.predecesor(arb.B_search("H"))->key_vector[arb.predecesor(arb.B_search("H"))->key_number - 1];
	//arb.Delete("H");
	//arb.Niveluri();
	//arb.Delete("Y");
	//arb.Niveluri();
	//arb.Delete("X");
	//arb.Niveluri();
	//arb.Delete("W");
	//arb.Niveluri();
	//arb.Delete("L");
	//arb.Niveluri();
	//arb.Delete("L");
	//arb.Niveluri();
	//arb.Delete("R");
	//arb.Niveluri();
	//arb.Delete("O");
	//arb.Niveluri();
	//arb.Delete("N");
	//arb.Niveluri();
	//arb.Delete("M");
	//arb.Niveluri();
	//arb.Delete("J");
	//arb.Niveluri();
	//arb.Delete("S");
	//arb.Niveluri();
	//arb.Delete("E");
	//arb.Niveluri();
	//arb.Delete("H");
	//arb.Niveluri();
	//arb.Delete("G");
	//arb.Niveluri();
	//arb.Delete("T");
	//arb.Niveluri();
	//arb.Delete("A");
	//arb.Niveluri();
	//arb.Delete("V");
	//arb.Niveluri();
	//arb.Delete("D");
	//arb.Niveluri();
	//arb.Delete("U");
	//arb.Niveluri();
	//arb.BTree_Insert("A");
	//arb.Niveluri();
	//std::cout << "Inaltimea arborelui este <= " << arb.getHeight() << "\n";

}
