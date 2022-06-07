
using namespace std;
const int SIZE = 100;

template<typename T>
class UOTable {
public:
	
	T keys[SIZE];
	int itter = 0;
	void insert(T element);
	void erase();
	int find();
	int find(T NameOfKey);
	void printKeys();
};

template<typename T>
inline void UOTable<T>::insert(T element){
	keys[itter] = element;
	itter++;
}

template<typename T>
inline void UOTable<T>::erase(){
	T NameOfKey;
	cin >> NameOfKey;
	for (int i = 0; i < itter; i++)
		if (keys[i] == NameOfKey) {
			for (int j = i; j < itter; j++) {
				swap(keys[j], keys[j + 1]);
			}
		}
	itter--;
}

template<typename T>
inline int UOTable<T>::find(){
	T NameOfKey;
	cin >> NameOfKey;
	for (int i = 0; i < itter; i++) {
		if (keys[i] == NameOfKey) {
			return i;
		}
	}
}
template<typename T>
inline int UOTable<T>::find(T NameOfKey) {
	
	for (int i = 0; i < itter; i++) {
		if (keys[i] == NameOfKey) {
			return i;
		}
	}
}

template<typename T>
inline void UOTable<T>::printKeys(){
	for (int i = 0; i < itter; i++){
		cout << i + 1 << ')' << keys[i] << endl;
	}
}


