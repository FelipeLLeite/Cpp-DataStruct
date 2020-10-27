/**
I have decided to implement all the codes for my container in one file, in this case the header.
*/

//#pragma once
#ifndef SMARTARRAY_H
#define SMARTARRAY_H

#include <iostream>

template<typename T>
class SmartArray {
private:
	size_t len = 0;	// The amount of element in the array
	size_t cap = 8; // Real cpaacity of the array. Default value as 8 (is that menas bytes? Maybe.)
	T* arr;	// My real contiguous container in memory
public:
	// Explicitly 
	SmartArray() {
		this->arr = new T[this->cap];
	}
	// Set the initial capacity of the array
	SmartArray(size_t initCap) {
		if (initCap > 1) {
			this->cap = initCap;
			this->arr = new T[initCap];
		}
		else {
			std::cout << "\nInvalid value for capacity.\nThe SmartArray Capacity will be set as 8." << std::endl;
			this->arr = new T[this->cap];
		}
	}
	
	// Resize the array with the new 
	void resize(size_t newCap) {
		if (newCap > 0) {
			// Create a new array with the new capacity and copy the elems from the original array
			T* new_arr = new T[newCap];
			for (size_t i = 0; i < newCap; i++)
				new_arr[i] = this->arr[i];
			// Free the space allocated
			delete[] this->arr;
			// Realocate the memory with the new array
			this->arr = new_arr;
			this->len = newCap < this->len ? newCap : this->len;
		}
		else
			std::cout << "\nInvalid capacity.\nThe array will not be changed." << std::endl;
	}
	// Add at the end of the array
	void add_at_end(T const& elem) {
		// Resize the array by calling the resize method
		if (this->len + 1 > this->cap){
			// Double the capacity
			this->cap *= 2;
			// Create a new array with the new capacity and copy the elems from the original array
			T* new_arr = new T[this->cap];
			for (size_t i = 0; i <this->len; i++)
				new_arr[i] = this->arr[i];
			// Free the space allocated
			delete[] this->arr;
			// Realocate the memory with the new array
			this->arr = new_arr;
		}
		// Add to the resized array and increment the length
		this->arr[this->len++] = elem;
	}
	// Return an elem at sartain index
	T get_at(size_t idx) const {
		if (idx > this->len - 1) {
			std::cout << "Index out of bound. It should throw error" << std::endl;
		}
		return this->arr[idx];
	}
	// Return the real size of the array
	size_t size() const { return this->len; }
	size_t get_capacity() const { return this->cap; }
	// Check if array is empty
	bool is_empty() const { return this->len == 0; }
	// Clear the array by deleting each 
	void clear() {
		for (size_t i = 0; i < this->len; i++)
			this->arr[i].~T();
		this->len = 0;
		std::cout << "Array cleared" << std::endl;
	}
	// print the smart array
	void print_sarray() {
		if (!(this->len == 0)) {
			for (size_t i = 0; i < this->len; i++)
				std::cout << this->arr[i] << std::endl;
			std::cout << std::endl;
		}
		else
			std::cout << "Array is empty" << std::endl;
	}
};

#endif // !SMARTARRAY_H