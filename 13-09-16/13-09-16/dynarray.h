#ifndef __DYNARRAY_H__
#define __DYNARRAY_H__

#define DYNARRAY_BLOCK_SIZE 16

typedef unsigned int uint;

template <class T>

class DynArray {
private:
	T* buffer;
	uint capacity;
	uint num_elements;


public:
	DynArray() :
		capacity(DYNARRAY_BLOCK_SIZE),
		num_elements(0)
	{
		buffer = new T[DYNARRAY_BLOCK_SIZE];
	}

	DynArray(uint n_elements) :
		capacity(DYNARRAY_BLOCK_SIZE * (n_elements / DYNARRAY_BLOCK_SIZE + 1)),
		num_elements(0)
	{
		buffer = new T[capacity];
	}

	DynArray(T* vector) {
		
	}

	DynArray(const DynArray &Tvect) :
		num_elements(Tvect.num_elements),
		capacity(Tvect.capacity)
	{
		buffer = new T[capacity];
		for (int i = 0; i < capacity; i++) {
			buffer[i] = Tvect.buffer[i];
		}

	}

	virtual ~DynArray(){}

public:
	T* GetBuffer() const {
		return buffer;
	}

	void push_back(const T value){

		if (num_elements == capacity){
			T* newbuffer = new T[capacity + 1];

			for (int i = 0; i < num_elements; i++){
				newbuffer[i] = buffer[i];
			}
			delete[] buffer;
			capacity++;
			buffer = newbuffer;
		}

		buffer[num_elements] = value;
		num_elements++;

	}

	void push_front(const T value){

		if (num_elements == capacity){
			capacity++;
		}

		T* newbuffer = new T[capacity];

		for (int i = 0; i< num_elements; i++){
			newbuffer[i + 1] = buffer[i];
		}
		newbuffer[0] = value;
		delete[] buffer;
		buffer = newbuffer;
		num_elements++;


	}
	int operator[](T value)const{
		return buffer[value];

	}
	int operator[](T value){
		return buffer[value];
	}
	void operator=(T value){
		buffer[] = value;

	}

};

#endif