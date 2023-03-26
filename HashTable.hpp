# include <vector>
# include "RB_Tree.h"
# include <functional>

template <typename T, typename H = std::hash<T>>
class HashTable {
public:
	HashTable(int length);
	void Insert(T data);
	bool Delete(T data);
	bool isPrime(int num);
	bool Find(T data);
	size_t getHash(T data);
private:
	//哈希表的长度以及小于表长的最大素数
	int length, maxPrime;
	std::vector<RB_Tree<T> > Nodes;
};


template <typename T, typename H = std::hash<T>>
HashTable<T, H>::HashTable(int length) {
	this->length = length;
	Nodes.resize(this->length);
	for (int i = this->length - 1; i >= 2; i--) {
		if (this->isPrime(i)) {
			this->maxPrime = i;
			break;
		}
	}
}

//判断是否是素数
template <typename T, typename H = std::hash<T>>
bool HashTable<T, H>::isPrime(int num) {
	bool flag = true;
	if (num <= 1) {
		flag = false;
	}
	else if (num == 2) {
		flag = true;
	}
	else {
		for (int i = 2; i < num - 1; i++) {
			//num能被i整除 
			if (num % i == 0) {
				flag = false;
				break;
			}
		}
	}
	return flag;
}

template <typename T, typename H = std::hash<T>>
bool HashTable<T, H>::Find(T data) {
	int hash_code = getHash(data) % this->maxPrime;
	return this->Nodes[hash_code].Find(data);
}

template <typename T, typename H = std::hash<T>>
void HashTable<T, H>::Insert(T data) {
	int hash_code = getHash(data) % this->maxPrime;
	this->Nodes[hash_code].Insert(data);
}

template <typename T, typename H = std::hash<T>>
size_t HashTable<T, H>::getHash(T data) {
	return H()(data);
}

template <typename T, typename H = std::hash<T>>
bool HashTable<T, H>::Delete(T data) {
	int hash_code = getHash(data) % this->maxPrime;
	return this->Nodes[hash_code].Delete(data);
}
