#ifndef VECTOR_H
#define VECTOR_H

const int  START_VECTOR_SIZE = 2;

template<class T> class Vector {
public:
	Vector() {
		arr = new T[START_VECTOR_SIZE];
		capacity = START_VECTOR_SIZE;
		size = 0;
	};

	Vector(const Vector<T>& v)
	{
		size = v.size;
		capacity = v.capacity;
		arr = new T[size];
		for (int i = 0; i < size; i++)
			arr[i] = v.arr[i];
	}

	~Vector() {
		delete[] arr;
	};

	void push(T data) {
		if (size == capacity) {
			doubleCapacity();
		}
		arr[size] = data;
		size++;
	};

	int getSize() {
		return size;
	};

	void insert(int pos, T val) {
		if (pos<0 || pos>size) pos = size;
		if (size == capacity) {
			doubleCapacity();
		}
		for (int i = size - 1; i >= pos; i--) {
			swap(arr[i], arr[i + 1]);
		}
		arr[pos] = val;
		size++;
	};

	void remove(int pos) {
		if (pos<0 || pos>size) return;
		for (int i = pos; i < size - 1; i++) {
			swap(arr[i], arr[i + 1]);
		}
		size--;
	}

	T& operator[](unsigned int index) {
		return arr[index];
	};

	Vector<T>& operator=(const Vector<T>& v) {
		delete[] arr;
		size = v.size;
		capacity = v.capacity;
		arr = new T[capacity];
		for (int i = 0; i < size; i++)
			arr[i] = v.arr[i];
		return *this;
	};

private:
	T* arr;
	int size, capacity;
	void doubleCapacity() {
		T* newArr = new T[2 * capacity];
		for (int i = 0; i < capacity; i++) {
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
		capacity *= 2;
	};
};

#endif