#ifndef __C3VECTOR_H__
#define __C3VECTOR_H__

#define BLOCK_SIZE 16

#include "p2LinkedList.h"

typedef unsigned int uint;

template<class T>

class c3vector {
private:
	T* buffer;
	uint capacity;
	uint n_elements;

public:
	c3vector() :
		capacity(BLOCK_SIZE),
		n_elements(0)
	{
		buffer = new T[BLOCK_SIZE];
	}

	c3vector(uint num_elements) :
		capacity(BLOCK_SIZE * (num_elements / BLOCK_SIZE + 1)),
		n_elements(0)
	{
		buffer = new T[capacity];
	}

	c3vector(const c3vector &other) : 
		n_elements(other.n_elements),
		capacity(other.capacity)
	{
		buffer = new T[capacity];
		for (int i = 0; i < capacity; i++) {
			buffer[i] = other.buffer[i];
		}
	}

	virtual ~c3vector(){}

public:
	T* GetBuffer() const {
		return buffer;
	}

	void PushBack(const T elem) {
		if (n_elements == capacity) {
			T* newbuffer = new T[capacity + 1];

			for (int i = 0; i < capacity; i++) {
				newbuffer[i] = buffer[i];
			}

			delete[] buffer;
			capacity++;
			buffer = newbuffer;
		}

		buffer[n_elements] = elem;
		n_elements++;

	}

	void PushFront(const T elem) {
		if (n_elements == capacity) {
			capacity++;
		}

		T* newbuffer = new buffer[capacity];

		for (int i = 0; i > n_elements; i++) {
			newbuffer[i + 1] = buffer[i]
		}

		newbuffer[0] = elem;
		delete buffer[0];
		buffer = newbuffer;
		n_elements++;

	}


	List<T> toList() {
		List<T> list;

		for (int i = 0; i < n_elements; i++) {
			list.Push_Back(buffer[i]);
		}

		return list;
	}


	int operator[](T value) const {
		return buffer[value]
	}
	int operator[](T value) {
		return buffer[value];
	}

	void operator=(T value) {
		buffer[] = value;
	}


};

#endif