#pragma once
#include <iostream>
#include <set>

using namespace std;

template <class K, class V>
class KeyValuePair {
private:
	K key;
	V value;
public:
	using key_type = K;
	using value_type = V;

	//Constructors
	KeyValuePair() : key(), value() {} //default constructor empty
	KeyValuePair(K k, V v) : key(k), value(v) {} //constructor with parameters

	//Getters
	K getKey() const { return key; }
	V& getValue() { return value; } //returninng by reference which allows for change
	const V& getValue() const { return value; }

	//Setters
	void setKey(K k) { key = k; }
	void setValue(V v) { value = v; }

	//Overload operators based on key value 
	bool operator==(const KeyValuePair& other) const {
		return key == other.key;
	}

	bool operator<(const KeyValuePair& other) const {
		return key < other.key;
	}

	bool operator>(const KeyValuePair& other) const {
		return key > other.key;
	}

	//declaration friend function for printing what is inside this class
	template <class K, class V>
	friend ostream& operator<<(ostream& os, const KeyValuePair<K, V>& kv);
};

template <class K, class V> //implementtaion for friend function 
ostream& operator<<(ostream& os, const KeyValuePair<K, V>& kv) {
	os << kv.key << ": " << kv.value;
	return os;
}

//overloading operator for set, this will allow to print the set of strings
template <typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
	os << "{ ";
	for (const auto& element : s) {
		os << element << ", ";
	}
	os << "}";
	return os;
}
