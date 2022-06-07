#include <iostream>
#include <string>
using namespace std;


template<typename T>
class Node {  //узел
public:
	Node* pNext;
	T data;

	Node(T data = T(), Node* pNext = nullptr) {
		this->data = data;
		this->pNext = pNext;
	}
};

template<typename T>
class List {
public:
	List();
	~List();

	void push_back(T data);  //добавление в конец списка
	void pop_front();
	void clear();
	int GetSize() { return Size; }
	void push_front(T data);   //добавление в начало
	void insert(T value, int index);
	void removeAt(int index);

	T& operator[](const int index);
	T& operator*(const int v);
	bool operator ==(List<T>& a);
	//private:
	int Size; //колличество элементов
	Node<T>* head;

};


template<typename T>
List<T>::List() {
	Size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List() {
	//clear();
}

template<typename T>
void List<T>::push_back(T data) {
	if (head == nullptr) {
		head = new Node<T>(data);
	}
	else {
		Node<T>* current = this->head;

		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}
	Size++;
}

template<typename T>
void List<T>::pop_front() {
	Node<T>* tmp = head;
	head = head->pNext;
	delete tmp;
	Size--;
}

template<typename T>
void List<T>::clear() {
	while (Size) {
		pop_front();
	}
}

template<typename T>
void List<T>::push_front(T data) {
	head = new Node<T>(data, head);
	Size++;
}

template<typename T>
void List<T>::insert(T value, int index) {


	if (index == 0)
		push_front(value);

	else {
		Node<T>* previous = this->head;
		for (size_t i = 0; i < index - 1; i++) {
			previous - previous->pNext;
		}
		Node<T>* newNode = new Node<T>(value, previous->pNext);
		previous->pNext = newNode;
	}
	Size++;
}

template<typename T>
void List<T>::removeAt(int index) {
	if (index == 0)
		pop_front();
	else {
		Node<T>* prevous = this->head;
		for (size_t i = 0; i < index - 1; i++)
			prevous = prevous->pNext;
		Node<T>* toDelete = prevous->pNext;
		prevous->pNext = toDelete->pNext;

		delete toDelete;
		Size--;
	}
}

template<typename T>
T& List<T>::operator[](const int index) {
	int count = 0;
	Node<T>* current = this->head;
	while (current != nullptr) {
		if (count == index)
			return current->data;
		current = current->pNext;
		count++;
	}
}

template<typename T>
inline T& List<T>::operator*(const int v)
{
	Node<T>* current = this->head;
	while (current != nullptr) {
		return current->data * v;
		current = current->pNext;
	}

}



struct Monom {
	double Value = 1;
	int degree = 111;
};

class Polinoms {
public:
	string key = "Unnamed";
	List<Monom> polinom;
	int PolinomSize = 1;
	Polinoms() {};
	void setPolinom(int k);
	void setTestPolinom(double value1, int degree1);  //реализация аналогичная, как и в первом setPolinom, но полином состоит из двух мономов
	void printPolinom();
	void setKey(){
		string k;
		cin >> k;
		key = k;
	}
	string GetKey() { return key; }
	~Polinoms() {};
	Polinoms operator + (Polinoms v);
	Polinoms operator - (Polinoms v) {
		return (*this + v * (-1));
	}
	Polinoms operator * (Polinoms v);
	Polinoms operator *(double v);
	Polinoms& operator=(const Polinoms& v);
	bool operator <(Polinoms& v);
	bool operator >(Polinoms& v);
	bool operator ==(Polinoms v);
	friend ostream& operator<<(ostream& os, const Polinoms& p);
};