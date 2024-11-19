#pragma once
#include <iostream>

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
	KeyValuePair() : key(""), value(0) {} //default constructor empty
	KeyValuePair(K k, V v) : key(k), value(v) {} //constructor with parameters

	//Getters
	K getKey() const { return key; }
	V getValue() const { return value; }

	//Setters
	void setKey(K k) { key = k; }
	void setValue(V v) { value = v; }

	//Overload operators 
	bool operator==(const KeyValuePair& other) const {
		return key == other.key;
	}

	bool operator<(const KeyValuePair& other) const {
		return key < other.key;
	}

	bool operator>(const KeyValuePair& other) const {
		return key > other.key;
	}
};
