#include <iostream>
#include "list/list.h"
#include "tables/HTable.h"
#include "tables/RBTable.h"
#include "tables/UOTable.h"
using namespace std;
const int SIZE_POLINOMS = 100;

int GetNumber(string name, Polinoms* p, RBTree<string> t, int itt) {
	for (int i = 0; i < itt; i++)
		if (p[i].key == t.search(name)->key)
			return i;
}

int main() {

	Polinoms polinoms[SIZE_POLINOMS];
	Polinoms result;
	int choice = 0;
	bool a = 1;
	int b = 0;
	int NumberOfMonoms = 0;
	string  NameOfFirstPolynom;
	string NameOfSecondPolynom;

	int itter = 0;
	int startitter = 0;

	UOTable<string> table;
	RBTree<string> tree2;
	HashTable hash;



	
	/*
	
	for (int i = 0; i < 3; i++) {
		polinoms[i].setPolinom(2);
		hash.insertItem(polinoms[i].GetKey(), polinoms[i]);
	}
	

	//hash.displayHash();
	for (int i = 0; i < 3; i++)
		hash.hashFunction(polinoms[i].GetKey());
	string name;
	cout << "what name?\n";
	cin >> name;
	cout << hash.GetHash(name) + hash.GetHash(name);
	//cout << polinoms[hash.hashFunction(polinoms[0].GetKey())];

	*/
ptr:
	if (itter == 0)
		cout << "No polinoms in memory...\nPlease, add polinoms...:" << endl;
	else {
		cout << "\nIn memory:\n";
		for (int i = 0; i < itter; i++) {
			cout << i + 1 << ')';
			cout << "Polinom " << polinoms[i] << " with key: " << polinoms[i].GetKey() << endl;
		}
	}
	
	cout << "\n1. Add polinom\n2. Add two polynoms\n3. Subctruct two polynoms\n4. Multiply two polynoms\n5. Multiply by a scalar\n6. Exit\n... ";

	
	while (choice > 7 || choice < 1 || itter == 0) {
		cin >> choice;
		if (choice > 7 || choice < 1 || itter == 0) {
			if (choice == 1)
				break;
			cout << "Wrong choice, or no polinoms in memory!\n";
		}
		
	}

	
	switch (choice) {

	case 1: {
		startitter = itter;
		while (a == true) {
			cout << "enter size:" << endl;
			cin >> NumberOfMonoms;
			cout << "enter polinom:" << endl;
			polinoms[itter].setPolinom(NumberOfMonoms);
			itter++;
			cout << "continue?" << endl;
			cin >> a;
		}
		
		for (startitter; startitter < itter; startitter++) {
			table.insert(polinoms[startitter].GetKey());
			tree2.insert(polinoms[startitter].GetKey());
			hash.insertItem(polinoms[startitter].GetKey(), polinoms[startitter]);
		}
		choice = 0;
		a = 1;
		goto ptr;
	}
		  break;
	case 2: {
		cout << "Polynoms addition.\nEnter, what polynoms you want to add:\nName of first polynom: ";
		cin >> NameOfFirstPolynom;
		cout << "\nName of second polynom: ";
		cin >> NameOfSecondPolynom;
		cout << "\nAdditional is:\n";
		cout << polinoms[GetNumber(NameOfFirstPolynom, polinoms, tree2, itter)] + polinoms[GetNumber(NameOfSecondPolynom, polinoms, tree2, itter)] << " on tree\n";
		cout << polinoms[table.find(NameOfFirstPolynom)] + polinoms[table.find(NameOfSecondPolynom)] << " on table\n";
		cout << (hash.GetHash(NameOfFirstPolynom) + hash.GetHash(NameOfSecondPolynom)) << " on hash table\n";
		cout << "\nSave result?\n1 - yes\n2 - no\n";
		cin >> b;
		if (b == 1) {
			polinoms[itter].PolinomSize = (polinoms[table.find(NameOfFirstPolynom)] + polinoms[table.find(NameOfSecondPolynom)]).PolinomSize;
			polinoms[itter] = (polinoms[table.find(NameOfFirstPolynom)] + polinoms[table.find(NameOfSecondPolynom)]);
			cout << "Enter name: ";
			polinoms[itter].setKey();
			table.insert(polinoms[itter].GetKey());
			tree2.insert(polinoms[itter].GetKey());
			hash.insertItem(polinoms[itter].GetKey(), polinoms[itter]);
			itter++;
		}
		choice = 0;
		goto ptr;


	}
		  break;
	case 3: {
		cout << "Polynoms substruct.\nEnter, what polynoms you want to subrtract:\nName of first polynom: ";
		cin >> NameOfFirstPolynom;
		cout << "\nName of second polynom: ";
		cin >> NameOfSecondPolynom;
		cout << "\nSubstruct is:\n";
		cout << polinoms[GetNumber(NameOfFirstPolynom, polinoms, tree2, itter)] - polinoms[GetNumber(NameOfSecondPolynom, polinoms, tree2, itter)] << " on tree\n";
		cout << polinoms[table.find(NameOfFirstPolynom)] - polinoms[table.find(NameOfSecondPolynom)] << " on table";
		cout << (hash.GetHash(NameOfFirstPolynom) - hash.GetHash(NameOfSecondPolynom)) << " on hash table\n";
		cout << "\nSave result?\n1 - yes\n2 - no\n";
		cin >> b;
		if (b == 1) {
			polinoms[itter].PolinomSize = (polinoms[table.find(NameOfFirstPolynom)] + polinoms[table.find(NameOfSecondPolynom)]).PolinomSize;
			polinoms[itter] = (polinoms[table.find(NameOfFirstPolynom)] - polinoms[table.find(NameOfSecondPolynom)]);
			cout << "Enter name: ";
			polinoms[itter].setKey();
			table.insert(polinoms[itter].GetKey());
			tree2.insert(polinoms[itter].GetKey());
			hash.insertItem(polinoms[itter].GetKey(), polinoms[itter]);
			itter++;
		}
		choice = 0;
		goto ptr;

	}
		  break;
	case 4: {
		cout << "Polynoms multiply.\nEnter, what polynoms you want to multiply:\nName of first polynom: ";
		cin >> NameOfFirstPolynom;
		cout << "\nName of second polynom: ";
		cin >> NameOfSecondPolynom;
		cout << "\nMyltiply is:\n";
		cout << polinoms[GetNumber(NameOfFirstPolynom, polinoms, tree2, itter)] * polinoms[GetNumber(NameOfSecondPolynom, polinoms, tree2, itter)] << " on tree\n";
		cout << polinoms[table.find(NameOfFirstPolynom)] * polinoms[table.find(NameOfSecondPolynom)] << " on table";
		cout << (hash.GetHash(NameOfFirstPolynom) * hash.GetHash(NameOfSecondPolynom)) << " on hash table\n";
		cout << "\nSave result?\n1 - yes\n2 - no\n";
		cin >> b;
		if (b == 1) {
			polinoms[itter].PolinomSize = (polinoms[table.find(NameOfFirstPolynom)] * polinoms[table.find(NameOfSecondPolynom)]).PolinomSize;
			polinoms[itter] = (polinoms[table.find(NameOfFirstPolynom)] * polinoms[table.find(NameOfSecondPolynom)]);
			cout << "Enter name: ";
			polinoms[itter].setKey();
			table.insert(polinoms[itter].GetKey());
			tree2.insert(polinoms[itter].GetKey());
			hash.insertItem(polinoms[itter].GetKey(), polinoms[itter]);
			itter++;
		}
		choice = 0;
		goto ptr;

	}
		  break;
	case 5: {
		double scalar;
		cout << "Multiply by a scalar\nEnter scalar:\n";
		cin >> scalar;
		cout << "Enter, what polynom you want to multiply:\n";
		cin >> NameOfFirstPolynom;
		cout << "\nMyltiply is:\n";
		cout << polinoms[GetNumber(NameOfFirstPolynom, polinoms, tree2, itter)] * scalar << " on tree\n";
		cout << polinoms[table.find(NameOfFirstPolynom)] * scalar << " on table";
		cout << (hash.GetHash(NameOfFirstPolynom) * scalar) << " on hash table\n";
		cout << "\nSave result?\n1 - yes\n2 - no\n";
		cin >> b;
		if (b == 1) {
			polinoms[itter].PolinomSize = (polinoms[table.find(NameOfFirstPolynom)] * scalar).PolinomSize;
			polinoms[itter] = (polinoms[table.find(NameOfFirstPolynom)] * scalar);
			cout << "Enter name: ";
			polinoms[itter].setKey();
			table.insert(polinoms[itter].GetKey());
			tree2.insert(polinoms[itter].GetKey());
			hash.insertItem(polinoms[itter].GetKey(), polinoms[itter]);
			itter++;
		}
		choice = 0;
		goto ptr;
	}
		  break;
	case 6: {
		return 0;
	}
	}
}

