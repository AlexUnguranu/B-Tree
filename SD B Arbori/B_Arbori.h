
#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "Node.h"
#include <queue>
template<class T>
class B_Arbori
{
	Node<T>* root;
	int t;
	int total_keys;


	void rotDr(std::pair<Node<T>*, int> x)
	{
		if (x.first->leaf == true || x.first->link_vector[x.second + 1]->key_number == 2 * this->t - 1)
		{
			std::cout << "\nRotatia DR nu se poate efectua!\n";
			return;
		}
		Node<T>* y1 = x.first->link_vector[x.second];
		Node<T>* y2 = x.first->link_vector[x.second + 1];

		Node<T>* curent = x.first;
		T val = y1->key_vector[y1->key_number - 1];
		y1->key_vector.pop_back();
		y2->key_vector.push_back(y2->key_vector[y2->key_number - 1]);
		T valy2;
		for (int k = y2->key_number - 2; k >= 0; k--)
		{
			y2->key_vector[k + 1] = y2->key_vector[k];
			//tranlatam cheile
		}
		//inseram cheia lui x in y2
		y2->key_vector[0] = curent->key_vector[x.second];
		// schimbam val din x cu cea din y1
		curent->key_vector[x.second] = val;
		if (y2->leaf == false)
		{
			//daca y nu e frunza , schimbam si copii acestora 
			y2->link_vector.push_back(y2->link_vector[y2->key_number]);
			for (int k = y2->key_number - 1; k >= 0; k--)
			{
				y2->link_vector[k + 1] = y2->link_vector[k];
			}
			y2->link_vector[0] = y1->link_vector[y1->key_number];
			y1->link_vector.pop_back();
		}
		y2->key_number++;
		y1->key_number--;
	}
	void rotSt(std::pair<Node<T>*, int>x)
	{
		if (x.first->leaf == true || x.first->link_vector[x.second + 1]->key_number == 2 * this->t - 1)
		{
			std::cout << "\nRotatia DR nu se poate efectua!\n";
			return;
		}
		Node<T>* y1 = x.first->link_vector[x.second];
		Node<T>* y2 = x.first->link_vector[x.second + 1];
		Node<T>* curent = x.first;
		T val = y2->key_vector[0];
		for (int k = 0; k < y2->key_number - 1; k++)
		{
			y2->key_vector[k] = y2->key_vector[k + 1];
			//translatie chei
		}
		y2->key_vector.pop_back();
		y1->key_vector.push_back(curent->key_vector[x.second]);
		curent->key_vector[x.second] = val;
		if (y1->leaf == false)
		{
			y1->link_vector.push_back(y2->link_vector[0]);
			for (int k = 0; k < y2->key_number; k++)
			{
				y2->link_vector[k] = y2->link_vector[k + 1];
				//translatie legaturi
			}
			y2->link_vector.pop_back();
		}
		y1->key_number++;
		y2->key_number--;
	}
	void fusion(std::pair<Node<T>*, int> x)
	{
		Node<T>* curent = x.first;
		Node<T>* y1 = curent->link_vector[x.second];
		Node<T>* y2 = curent->link_vector[x.second + 1];
		if (y1->key_number != this->t - 1 || y2->key_number != this->t - 1)
		{
			std::cout << "\nNu se poate realiza fuziunea!\n";
			return;
		}
		int del_root = 0;
		if (curent->key_number < this->t && curent != this->root)
		{
			std::cout << "\nNu se poate realiza fuziunea!\n";
			return;
		}

		else if (curent->key_number == 1 && curent == this->root)
		{
			del_root = 1;
		}
		//nodul rezultat va fi y1 ( copilul stang)
		y1->key_vector.push_back(curent->key_vector[x.second]);
		curent->key_vector.erase(curent->key_vector.begin() + x.second);
		for (int i = 0; i < y2->key_number; i++)
		{
			y1->key_vector.push_back(y2->key_vector[i]);
		}
		if (y1->leaf == false)
		{
			for (int i = 0; i < y2->key_number + 1; i++)
			{
				y1->link_vector.push_back(y2->link_vector[i]);
			}
		}
		y1->key_number = 2 * this->t - 1;
		curent->key_number--;
		curent->link_vector.erase(curent->link_vector.begin() + x.second + 1);
		if (del_root == 1)
		{
			this->root = y1;
			delete curent;
		}
		delete y2;
	}
	void DelereRec(Node<T>* x, T key)
	{
		if (x == nullptr || x->key_number == 0)
		{
			std::cout << "EEE\n";
			return;
		}
		int ok = 0;//verif cazul in care x este radacina si trebuie facuta o fuziune , caz in care , radacina se modifica , si inaltimea la arbore scade 
		if (x == this->root)
			ok = 1;
		int index = 0;
		while (index < x->key_number)// test
		{
			if (key >= x->key_vector[index])
				index++;
			else break;
		}if (index > 0)
			index--;
		if (x->leaf == true)
		{
			if (x->key_vector[index] == key)
			{
				x->key_number--;
				x->key_vector.erase(x->key_vector.begin() + index);
				this->total_keys--;
			}
			else std::cout << "\n Cheia nu exista!\n";
			// STOP
			return;
		}
		else if (x->key_vector[index] == key)
		{
			Node<T>* y = x->link_vector[index];
			if (y->key_number >= this->t)
			{
				Node<T>* k1 = predecesor({ x, index });
				x->key_vector[index] = k1->key_vector[k1->key_number - 1];
				DelereRec(y, k1->key_vector[k1->key_number - 1]);
			}
			else
			{
				y = x->link_vector[index + 1];
				if (y->key_number >= this->t)
				{
					Node<T>* k1 = succesor({ x, index });
					x->key_vector[index] = k1->key_vector[0];
					DelereRec(y, k1->key_vector[0]);
				}
				else
				{
					fusion({ x, index });
					if (ok)
						x = this->root;
					DelereRec(x, key);
				}
			}
		}
		else if (x->leaf == false && key < x->key_vector[index])
		{
			if (x->link_vector[index]->key_number >= this->t)
				DelereRec(x->link_vector[index], key);
			else if (x->link_vector[index]->key_number == this->t - 1)
			{
				if (/*index > 0 &&*/ x->link_vector[index]->key_number >= this->t)
				{
					rotDr({ x, index });
					DelereRec(x, key);
				}
				else if (index < x->key_number && x->link_vector[index + 1]->key_number >= this->t)
				{
					rotSt({ x, index });
					DelereRec(x, key);
				}
				else if (index > 0 && x->link_vector[index - 1]->key_number == this->t - 1)
				{
					fusion({ x, index - 1 });
					if (ok)
						x = this->root;
					DelereRec(x, key);
				}
				else if (x->link_vector[index]->key_number == this->t - 1)
				{
					fusion({ x, index });
					if (ok)
						x = this->root;
					DelereRec(x, key);
				}
			}
		}
		else if (x->leaf == false && x->key_vector[index] < key)
		{
			if (x->link_vector[index + 1]->key_number >= this->t)
				DelereRec(x->link_vector[index + 1], key);
			else if (x->link_vector[index + 1]->key_number == this->t - 1)
			{
				if (x->link_vector[index]->key_number >= this->t)
				{
					rotDr({ x, index });
					DelereRec(x, key);
				}
				else if (index <= x->key_number && x->link_vector[index + 1]->key_number >= this->t)
				{
					rotSt({ x, index });
					DelereRec(x, key);
				}
				else if (x->link_vector[index]->key_number == this->t - 1)
				{
					fusion({ x, index });
					if (ok)
						x = this->root;
					DelereRec(x, key);
				}
				else if (x->link_vector[index + 1]->key_number == this->t - 1)
				{
					fusion({ x, index + 1 });
					if (ok)
						x = this->root;
					DelereRec(x, key);
				}
			}
		}

	}
	std::pair<Node<T>*, int> B_SearchRec(Node<T>* nod, T key)// nod+ pozitia in vect
	{
		int i = 0;
		while (i < nod->key_number && nod->key_vector[i] < key)
		{
			i++;
		}
		if (i < nod->key_number&& nod->key_vector[i] == key)
		{
			return { nod, i };
		}
		else
		{
			if (nod->leaf == true)
				return { nullptr,0 };
			else
			{
				return B_SearchRec(nod->link_vector[i], key);
			}
		}
	}
	void Split(Node<T>* x, int i)
	{
		// y = copil care se va imparti in 2 noduri 
		Node<T>* y = x->link_vector[i];
		// adaugam o noua cheie si copil  in nodul x(parinte )
		x->link_vector.push_back(x->link_vector[x->key_number]);
		for (int k = x->key_number - 1; k > i; k--)
		{
			x->link_vector[k + 1] = x->link_vector[k];
		}
		if (x->key_number > 0)
			x->key_vector.push_back(x->key_vector[x->key_number - 1]);
		else
		{
			x->key_vector.push_back(y->key_vector[t - 1]);
		}
		for (int k = x->key_number - 2; k >= i; k--)
		{
			x->key_vector[k + 1] = x->key_vector[k];
		}
		x->key_vector[i] = y->key_vector[t - 1];
		//cream un nou nod , copil dreapta al lui x(parinte)
		Node<T>* z = new Node<T>;
		z->key_number = this->t - 1;
		z->key_vector.reserve(2 * this->t - 1);
		z->link_vector.reserve(2 * this->t);
		y->key_number = this->t - 1;
		int cnt = 1;
		for (int k = 0; k < this->t - 1; k++)
		{
			z->key_vector.push_back(y->key_vector[t]);
			y->key_vector.erase(y->key_vector.begin() + this->t);
			//
			cnt++;
		}
		y->key_vector.erase(y->key_vector.begin() + this->t - 1);
		if (y->leaf == false)
		{
			for (int k = 0; k < this->t; k++)
			{
				z->link_vector.push_back(y->link_vector[t]);
				y->link_vector.erase(y->link_vector.begin() + this->t);
			}
		}
		z->leaf = y->leaf;
		x->link_vector[i + 1] = z;
		x->key_number++;
	}
	void B_Insert_Rec(Node<T>* nod, T key)
	{
		int i;
		i = nod->key_number;// ?
		if (nod->leaf == true)
		{
			// adaugam un nou element in vectorul de key
			if (i > 0)
				nod->key_vector.push_back(nod->key_vector[i - 1]);
			else nod->key_vector.push_back(key);
			while (i > 0 && key < nod->key_vector[i - 1])
			{
				nod->key_vector[i] = nod->key_vector[i - 1];
				// tranlatez cheile
				i--;
			}
			//punem cheia pe pozitia corecta 
			nod->key_vector[i] = key;
			nod->key_number++;
		}
		else
		{
			while (i >= 1 && key < nod->key_vector[i - 1])
			{
				i--;
			}
			i++;
			if (nod->link_vector[i - 1]->key_number == 2 * this->t - 1)
			{
				Split(nod, i - 1);
				if (key > nod->key_vector[i - 1])
					i++;
			}
			B_Insert_Rec(nod->link_vector[i - 1], key);
		}
	}

public:
	B_Arbori(int t = 2)
	{
		this->root = new Node<T>;
		this->root->key_vector.reserve(2 * t - 1);
		this->root->link_vector.reserve(2 * t);
		this->t = t;
		this->root->leaf = true;
		this->total_keys = 0;
	}
	int getHeight()
	{
		return log2((this->total_keys + 1) / 2) / log2(this->t);
	}
	std::pair<Node<T>*, int> B_search(T key)
	{
		return B_SearchRec(this->root, key);
	}
	void BTree_Insert(T key)
	{
		this->total_keys++;
		if (this->root->key_number == 2 * this->t - 1)
		{
			Node<T>* nod_nou = new Node<T>;
			//creem o noua radacina 
			nod_nou->key_vector.reserve(2 * this->t - 1);
			nod_nou->link_vector.reserve(2 * this->t);
			nod_nou->leaf = false;
			nod_nou->key_number = 0;
			//adaugam in vectorul de noduri radacina anterioara 
			nod_nou->link_vector.push_back(this->root);
			this->root = nod_nou;
			Split(this->root, 0);
		}
		B_Insert_Rec(this->root, key);
	}
	void Niveluri()
	{
		if (this->total_keys == 0)
		{
			std::cout << "\nArborele este gol!\n";
			return;
		}
		std::queue<Node<T>*> qu;
		qu.push(this->root);
		std::cout << std::endl;
		int cnt1 = 0, cnt2 = 0, cnt3 = 0;
		cnt1 = this->root->key_number;
		while (!qu.empty())
		{
			Node<T>* front = qu.front();
			qu.pop();
			for (int i = 0; i < front->key_number; i++)
			{
				std::cout << front->key_vector[i] << ' ';
				cnt2++;
			}
			for (int i = 0; i <= front->key_number && front->leaf == false; i++)
			{
				qu.push(front->link_vector[i]);
				cnt3 += front->link_vector[i]->key_number;
			}
			std::cout << "	";
			if (cnt1 == cnt2)
			{
				std::cout << std::endl;
				cnt2 = 0;
				cnt1 = cnt3;
			}
		}
		std::cout << std::endl;
	}
	T getMin()
	{
		Node<T>* curent = this->root;
		while (curent->leaf == false)
		{
			curent = curent->link_vector[0];
		}
		return curent->key_vector[0];
	}
	T getMinNodeX(std::pair<Node<T>*, int> x)
	{
		Node<T>* curent = x.first;
		if (curent->leaf == true)
			return curent->key_vector[x.second];
		curent = curent->link_vector[x.second + 1];
		while (curent->leaf == false)
		{
			curent = curent->link_vector[0];
		}
		return curent->key_vector[0];
	}
	T getMax()
	{
		Node<T>* curent = this->root;
		while (curent->leaf == false)
		{
			curent = curent->link_vector[curent->key_number];
		}
		return curent->key_vector[curent->key_number - 1];
	}
	T getMaxNodeX(std::pair<Node<T>*, int> x)
	{

		Node<T>* curent = x.first;
		if (curent->leaf == true)
			return curent->key_vector[x.second];
		curent = curent->link_vector[x.second + 1];
		while (curent->leaf == false)
		{
			curent = curent->link_vector[curent->key_number];
		}
		return curent->key_vector[curent->key_number - 1];
	}
	Node<T>* predecesor(std::pair<Node<T>*, int> x)
	{
		Node<T>* curent = x.first;
		if (curent->leaf == true)
			return nullptr;
		curent = curent->link_vector[x.second];
		while (curent->leaf == false)
		{
			curent = curent->link_vector[curent->key_number];
		}
		return curent;
	}
	Node<T>* succesor(std::pair<Node<T>*, int> x)
	{
		Node<T>* curent = x.first;
		if (curent->leaf == true)
			return nullptr;
		curent = curent->link_vector[x.second + 1];
		while (curent->leaf == false)
		{
			curent = curent->link_vector[0];
		}
		return curent;
	}
	void Delete(T key)
	{
		DelereRec(this->root, key);
	}
};