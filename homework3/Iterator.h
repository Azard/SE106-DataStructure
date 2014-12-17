#ifndef MY_ITERATOR_H
#define MY_ITERATOR_H

/**
*   Homework 3:
*/

// Student ID:5120379076
// Name: 熊伟伦

template<typename T>
class Iterator {
	private:
		T* p;
		int index;

	public:
		Iterator(T* _p, int _index);
		Iterator(const Iterator& x);
		Iterator& operator++();
		Iterator operator++(int);
		bool operator==(const Iterator& that);
		bool operator!=(const Iterator& that);
		T& operator*();
};

template<typename T>
Iterator<T>::Iterator(T* _p, int _index) {
	p = _p;
	index = _index;
}
		
template<typename T>
Iterator<T>::Iterator(const Iterator& x) {
	this->p = x.p;
	this->index = x.index;
}
		
template<typename T>
Iterator<T>& Iterator<T>::operator++() {
	index++;
	return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator++(int) {
	Iterator copy(*this);
	operator++();
	return copy;
}

template<typename T>
bool Iterator<T>::operator==(const Iterator& that) {
	return p==that.p && index==that.index;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator& that) {
	return !(*this == that);
}

template<typename T>
T& Iterator<T>::operator*() {
	return *(p+index) ;		
}

#endif
