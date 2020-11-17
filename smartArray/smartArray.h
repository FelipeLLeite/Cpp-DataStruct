/**
Smart Array header that defined and implemented
*/

#pragma once
#ifndef SMARTARRAY_H
#define SMARTARRAY_H

#include <iostream>
#include <exception>

template<typename T>
class SmartArray {
private:
	size_t _len = 0;	// The amount of element in the array
	size_t _cap = 8; // Real cpaacity of the array. Default value as 8 (is that menas bytes? Maybe.)
	T* _arr;	// My real contiguous container in memory
public:
	// Explicitly 
	SmartArray() { this->_arr = new T[this->_cap]; }
	// Set the initial capacity of the array
	SmartArray(size_t initCap);
	
	// Resize the array with the new 
	void resize(size_t newCap);
	
	// Add at the end of the array
	void add_at_end(T const& elem);
	void add_at_end(T* elem);

	void remove_at(size_t idx);
	T get_at(size_t idx) const;

	size_t size() const;
	size_t get_capacity() const;
	bool is_empty() const;
	
	// Clear the array by 
	void clear();
	void print_sarray();
};






#endif // !SMARTARRAY_H

template<typename T>
inline SmartArray<T>::SmartArray(size_t initCap) {
	if (initCap > 1) {
		this->_cap = initCap;
		this->_arr = new T[initCap];
	}
	else {
		std::cerr << "\nInvalid value for capacity.\nThe SmartArray Capacity will be set as 8." << std::endl;
		this->_arr = new T[this->_cap];
	}
}

template<typename T>
inline void SmartArray<T>::resize(size_t newCap) {
	if (newCap > 0) {
		// Create a new array with the new capacity and copy the elems from the original array
		T* new_arr = new T[newCap];
		for (size_t i = 0; i < this->_len; i++)
			new_arr[i] = this->_arr[i];
		// Free the space allocated
		delete[] this->_arr;
		// Realocate the memory with the new array
		this->_arr = new_arr;
		this->_len = newCap < this->_len ? newCap : this->_len;
		new_arr = nullptr;
		delete[] new_arr;
	}
	else
		std::cerr << "\nInvalid capacity.\nThe array will not be changed." << std::endl;
}

template<typename T>
inline void SmartArray<T>::add_at_end(T const& elem) {
	// Resize the array by calling the resize method
	if (this->_len + 1 > this->_cap) {
		this->_cap *= 2;
		this->resize(this->_cap);
	}
	// Add to the resized array and increment the length
	this->_arr[this->_len++] = elem;
}

template<typename T>
inline void SmartArray<T>::add_at_end(T* elem) {
	// Resize the array by calling the resize method
	if (this->_len + 1 > this->_cap) {
		this->_cap *= 2;
		this->resize(this->_cap);
	}
	// Add to the resized array and increment the length
	this->_arr[this->_len++] = *elem;
}

template<typename T>
inline void SmartArray<T>::remove_at(size_t idx) {
	try {
		if (idx >= 0 && idx < this->_len) {
			T* new_arr = new T[this->_cap];
			for (size_t i = 0, j = 0; i < this->_len; i++) {
				if (i != idx) { new_arr[j] = this->_arr[i]; }
				else { j--; }
				j++;
			}
			// Free the space allocated
			delete[] this->_arr;
			// Realocate the memory with the new array
			this->_arr = new_arr;
			this->_len--;
			new_arr = nullptr;
			delete[] new_arr;
		}
	}
	catch (std::out_of_range ex) {
		std::cout << ex.what() << std::endl;
	}
}

template<typename T>
inline T SmartArray<T>::get_at(size_t idx) const {
	if (idx < 0 || idx > this->_len - 1)
		std::cerr << "Index out of bound. It should throw error" << std::endl;
	return this->_arr[idx];
}

template<typename T>
inline size_t SmartArray<T>::size() const { return this->_len; }

template<typename T>
inline size_t SmartArray<T>::get_capacity() const { return this->_cap; }

template<typename T>
inline bool SmartArray<T>::is_empty() const { return this->_len == 0; }

template<typename T>
inline void SmartArray<T>::clear() {
	for (size_t i = 0; i < this->_len; i++)
		this->remove_at(i);
	this->_len = 0;
	std::cout << "Array cleared" << std::endl;
}

template<typename T>
inline void SmartArray<T>::print_sarray() {
	if (!(this->_len == 0)) {
		for (size_t i = 0; i < this->_len; i++)
			std::cout << this->_arr[i] << std::endl;
		std::cout << std::endl;
	}
	else
		std::cout << "Array is empty" << std::endl;
}
