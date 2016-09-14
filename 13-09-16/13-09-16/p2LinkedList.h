#ifndef __P2LINJEDLIST_H__
#define __P2LINKEDLIST_H__

#define NULL 0

#include "c3vector.h"

typedef unsigned int uint;

template<class T>

class List {
// Node implementation ---
	struct node {
	public:
		mutable T data;
		node* next = nullptr;

	public:
		node(){}
		node(const T& data) : data(data) {}

	};
// -----

public:
	List(){
		iterator = root;
	}
	virtual ~List(){}

	node* root;
	node* iterator;

public:
	// Erase --- 
	/*void Erase(uint n) {
		for (int i = 0; i < n - 1 && iterator->next != nullptr; i++) {
			iterator = iterator->next;
		}
		node* aux;
		aux = iterator->next;

		if (aux->next == nullptr) {
			iterator->next = nullptr;
		}
		else {
			iterator->next = aux->next;
		}

		delete aux;
	}
*/
	// Insert --- (WIP)
/*	void insert(const T& data, int n){
		node* newnode = new node(data);
		n-= 2;
		iterator = root;
		while (n > 0 && iterator->next != nullptr) {
			iterator = iterator->next;
			n--;
		}
		newnode->next = iterator->next;	
		iterator = newnode;
	}
	*/


	// Clear ---
	void Clear() {
		while (root != nullptr) {
			node* aux = root->next;
			delete root;
			root = aux;
		}
	}

	// First ---
	node first() {
		return *root;
	}

	// Last ---
	node last() {
		return *end();
	}

	// Push_Back ---
	void Push_Back(const T& value) {
		node* newnode = new node(value);
		if (root == nullptr) {
			root = newnode;
		}
		else {
			node* last = end();
			last->next = newnode;
		}
	}

	// Push_Front ---
	void Push_Front(const T& value) {
		node* newnode = new node(value);
		newnode->next = root;
		root = newnode;
	}

	// End ---
	node* end() {
		if (root == nullptr)
			return root;
		else 

		iterator = root;
 		while (iterator->next != nullptr) {
			iterator = iterator->next;
		}
		return iterator;
	}
	const node* end() const {
		if (root == nullptr)
			return root;
		else

		iterator = root;
		while (iterator->next != nullptr) {
			iterator = iterator->next;
		}
		return iterator;
	}

	// Size ---
	const uint size() {
		int size = 0;
		if (root != nullptr) {
			size = 1;
			iterator = root;
			while (iterator->next != nullptr) {
				iterator = iterator->next;
				size++;
			}
		}

		return size;
	}

	// Empty ---
	bool Empty() {
		return root == nullptr;
	}

	// toVect ---
	c3vector<T> toVect() {
		c3vector<T> vector;

		if (root != nullptr) {
			iterator = root;
			while (iterator != nullptr) {
				vector.PushBack(iterator->data);
				iterator = iterator->next;
			}
		}
		return vector;
	}

};

#endif