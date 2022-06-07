#include "list/list.h"
using namespace std;



void Polinoms::setPolinom(int k) {
	Monom m;
	PolinomSize = k;
	for (int i = 0; i < k; i++) {
		cout << "Enter " << i + 1 << "`st " << "value: ";
		cin >> m.Value;
		cout << "Enter " << i + 1 << "`st " << "degree: ";
		cin >> m.degree;
		if (m.Value == 0)
			throw "value cannot be zero!";
		if (m.degree > 1000)
			throw "degree is too high!";
		if (m.degree < 0)
			throw "degree cannot be negative!";
		if (m.degree < 100)
			throw "too low degree!";
		polinom.push_back(m);
	}
	for (int i = 0; i < PolinomSize; i++)
		for (int j = i + 1; j < PolinomSize; j++) {
			if (polinom[i].degree == polinom[j].degree) {
				polinom[i].Value += polinom[j].Value;
				polinom.removeAt(j);
				PolinomSize--;
				j--;
			}
		}
	cout << "Enter the name of polinom: ";
	setKey();
}

void Polinoms::setTestPolinom(double value1, int degree1) {
	Monom m;
	PolinomSize = 2;
	m.degree = degree1;
	m.Value = value1;
	if (m.Value == 0)
		throw "value cannot be zero!";
	if (m.degree > 1000)
		throw "degree is too high!";
	if (m.degree < 0)
		throw "degree cannot be negative!";
	if (m.degree < 100)
		throw "too low degree!";
	polinom.push_back(m);

}

void Polinoms::printPolinom() {
	for (int i = 0; i < PolinomSize; i++) {
		cout << polinom[i].Value << "*X^" << polinom[i].degree / 100 << "*Y^" << (polinom[i].degree / 10) - (polinom[i].degree / 100) * 10 << "*Z^" << polinom[i].degree % 10;
		if (i != PolinomSize - 1)
			cout << "+";
	}
}

Polinoms Polinoms::operator + (Polinoms v) {
	Polinoms result;
	result.PolinomSize = PolinomSize + v.PolinomSize;
	Monom m;
	for (int i = 0; i < PolinomSize; i++) {
		m.Value = polinom[i].Value;
		m.degree = polinom[i].degree;
		result.polinom.push_back(m);
	}
	for (int i = 0; i < v.PolinomSize; i++) {
		m.Value = v.polinom[i].Value;
		m.degree = v.polinom[i].degree;
		result.polinom.push_back(m);
	}
	for (int i = 0; i < result.PolinomSize; i++)
		for (int j = i + 1; j < result.PolinomSize; j++) {
			if (result.polinom[i].degree == result.polinom[j].degree) {
				result.polinom[i].Value += result.polinom[j].Value;
				result.polinom.removeAt(j);
				result.PolinomSize--;
				j--;
			}
			//если степень итого монома равна степени житого монома, сложить сзачени€ коэфициентов и записать как новый моном, понизить размер монома на 1
		}
	for (int i = 0; i < result.PolinomSize; i++)
		if (result.polinom[i].Value == 0) {
			result.polinom.removeAt(i);
			result.PolinomSize--;
			i--;
		}


	return result;
}

Polinoms Polinoms::operator * (Polinoms v) {
	Polinoms result;
	result.PolinomSize = PolinomSize * v.PolinomSize;
	Monom m;

	for (int i = 0; i < PolinomSize; i++)
		for (int j = 0; j < v.PolinomSize; j++) {
			m.Value = polinom[i].Value * v.polinom[j].Value;
			m.degree = polinom[i].degree + v.polinom[j].degree;
			if (m.degree > 1000)
				throw("degree is too high!");
			result.polinom.push_back(m);
		}

	return result;

}

Polinoms Polinoms::operator*(double v) {
	Polinoms result;
	result.PolinomSize = PolinomSize;
	Monom m;
	for (int i = 0; i < PolinomSize; i++) {
		m.Value = polinom[i].Value * v;
		m.degree = polinom[i].degree;
		result.polinom.push_back(m);
	}
	return result;
}

Polinoms& Polinoms::operator=(const Polinoms& v) {
	polinom = v.polinom;
	return *this;
}




bool Polinoms::operator<(Polinoms& v) {
	int a = 0;
	if (polinom.GetSize() < v.polinom.GetSize())
		return true;
	else {
		for (size_t i = 0; i < polinom.GetSize(); i++) {
			if (polinom[i].degree == v.polinom[i].degree) {
				a++;
				continue;
			}
			if (polinom[i].degree < v.polinom[i].degree)
				return true;
			if (polinom[i].degree > v.polinom[i].degree)
				return false;
		}
		if (a == polinom.GetSize()) {
			for (size_t i = 0; i < polinom.GetSize(); i++) {
				if (polinom[i].Value == v.polinom[i].Value)
					continue;
				if (polinom[i].Value < v.polinom[i].Value)
					return true;
				if (polinom[i].Value > v.polinom[i].Value)
					return false;
			}
		}

	}
}

bool Polinoms::operator>(Polinoms& v) {
	int a = 0;
	if (polinom.GetSize() > v.polinom.GetSize())
		return true;
	else {
		for (size_t i = 0; i < polinom.GetSize(); i++) {
			if (polinom[i].degree == v.polinom[i].degree)
				continue;
			if (polinom[i].degree > v.polinom[i].degree)
				return true;
			if (polinom[i].degree < v.polinom[i].degree)
				return false;
		}
		if (a == polinom.GetSize()) {
			for (size_t i = 0; i < polinom.GetSize(); i++) {
				if (polinom[i].Value == v.polinom[i].Value)
					continue;
				if (polinom[i].Value > v.polinom[i].Value)
					return true;
				if (polinom[i].Value < v.polinom[i].Value)
					return false;
			}
		}

	}
}




bool Polinoms::operator==(Polinoms v) {
	int a = 0;
	if (polinom.GetSize() != v.polinom.GetSize())
		return false;
	else {
		for (size_t i = 0; i < polinom.GetSize(); i++) {
			if (polinom[i].degree == v.polinom[i].degree && polinom[i].Value == v.polinom[i].Value)
				a++;
		}
		if (a == polinom.GetSize())
			return true;
		else
			return false;
	}
}



ostream& operator<<(ostream& os, const Polinoms& p)
{
	List<Monom> pol = p.polinom;
	for (int i = 0; i < p.PolinomSize; i++) {
		os << pol[i].Value << "*X^" << pol[i].degree / 100 << "*Y^" << (pol[i].degree / 10) - (pol[i].degree / 100) * 10 << "*Z^" << pol[i].degree % 10;
		if (i != p.PolinomSize - 1)
			cout << "+";
	}
	return os;
}
