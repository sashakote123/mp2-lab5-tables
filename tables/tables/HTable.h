#include <iostream>
#include <list>
#include <string>
using namespace std;


class HashTable
{
    Polinoms array[50];
    
public:
    HashTable() {
        for (size_t i = 0; i < 50; i++){
            array[i].setTestPolinom(1, 111);
            array[i].PolinomSize = 1;
        }
    }

    void insertItem(string key, Polinoms data){
        
        int index = hashFunction(key);
        array[index].PolinomSize = data.PolinomSize;
        array[index] = data;
    }
  

    int search(string name){
        return hashFunction(name);
    }

    int hashFunction(string key){
        int sum = 0;
        for (int j = 0; j < key.length(); j++)
            sum += int(key[j]);
        int h = sum + 2 * sum + 3 * sum * sum;
        return abs(h % 50);
    }
    Polinoms GetHash(string number){
        return array[search(number)];
    }
};




