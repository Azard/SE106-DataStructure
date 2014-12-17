/**
* Homework 3
**/

// Student ID: 5120379076
// Name: 熊伟伦
//

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cstdlib>
#include "Iterator.h"

template <typename T>
class Vector {
private:
/* Private variables */

	T* elements;	/* array of the elements			*/
	int capacity;	/* allocated size of the array		*/
	int count;		/* the number of elements in use	*/

/* Private methods */
	void deepCopy(const Vector & src);	// for operator= and copy constructor


public:
  // Do NOT modify following interfaces
  Vector();
  Vector(int size, const T& val = T());
  Vector(const Vector& x);
  ~Vector();
  Vector<T>& operator=(const Vector<T>& x);
  int size() const;
  bool empty() const;
  T& operator [](int pos) const;
  void resize(size_t n, T val = T());
  void push_back(const T& val);

  Iterator<T> begin();
  Iterator<T> end();
};

//=====================deepCopy=================================

template<typename T>
void Vector<T>::deepCopy(const Vector & src) {
	count = capacity = src.count;
	elements = (capacity == 0) ? NULL : new T[capacity];
	for (int i = 0; i < count; i++) {
		elements[i] = src.elements[i];
	}
}

//==============================================================


// (default constructor)
// Constructs an empty container, with no elements.
template <typename T>
Vector<T>::Vector() {
	count = capacity = 0;
	elements = NULL;
}

// (fill constructor)
// Constructs a container with n elements.
// Each element is a copy of val.
template <typename T>
Vector<T>::Vector(int size, const T& val) {
	count = capacity = size;
	elements = (size == 0) ? NULL : new T[size];
	for (int i = 0; i < size; i++) {
		elements[i] = val;
	}
}

// (copy constructor)
// Constructs a container with a copy of each of the
// elements in x, in the same order.
template <typename T>
Vector<T>::Vector(const Vector& x) {
	deepCopy(x);
}

// (destructor)
// Destroys the container object.
template <typename T>
Vector<T>::~Vector() {
	if (elements != NULL)
		delete[] elements;
}

// operator=
// Assigns new contents to the container, replacing its
// current contents, and modifying its size accordingly.
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& x) {
	if (this != &x) {
		if (elements != NULL) 
			delete[] elements;
		deepCopy(x);
	}
	return *this;
}

// size
// Returns the number of elements in the vector.
// This is the number of actual objects held in the
// vector, which is not necessarily equal to its
// storage capacity.
template <typename T>
int Vector<T>::size() const {
	return count;
}

// empty
// Returns whether the vector is empty
template <typename T>
bool Vector<T>::empty() const {
	return count == 0;
}

// operator[]
// Returns a reference to the element at position n
// in the vector container.
// if the requested position is out of range, the
// behavior is undefined
template <typename T>
T& Vector<T>::operator[](int pos) const {
	if (pos < 0 || pos >= count)
		return elements[0];
	return elements[pos];
}

// resize
// Resizes the container so that it contains n elements.
// If n is smaller than the current container size, the 
// content is reduced to its first n elements, removing 
// those beyond (and destroying them).
// If n is greater than the current container size, the 
// content is expanded by inserting at the end as many 
// elements as needed to reach a size of n. If val is 
// specified, the new elements are initialized as copies 
// of val, otherwise, they are value-initialized.
template <typename T>
void Vector<T>::resize(size_t n, T val) {
	T* array = NULL;
	if (n != 0) {
		array = new T[n];
		for (int i = 0; i < n; i++)
			array[i] = (i < count)? elements[i] : val;
	}
	if (elements != NULL)
		delete[] elements;
	count = capacity = n;
	elements = array;
}

// push_back
// Adds a new element at the end of the vector, after its
// current last element. The content of val is copied (or
// moved) to the new element.
template <typename T>
void Vector<T>::push_back(const T& val) {
	int save_count = count;
	if (count == capacity)
		resize(2*capacity);
	elements[save_count] = val;
	count = save_count + 1;
}

//homework3 for vector
template <typename T>
Iterator<T> Vector<T>::begin() {
	return Iterator<T>(elements, 0);
}

template <typename T>
Iterator<T> Vector<T>::end() {
	return Iterator<T>(elements, count);
}

#endif

