#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include <iostream>
#include <ostream>



template <typename T>
class node {
public:
	node* prev = nullptr;	// Access the previous node of the list
	node* next = nullptr;	// Access the next node of the list
	T data;		// Acces the node of the list at a certain index
};


template <typename T>
class DLinkedList {
private:
	unsigned int _len = 0;
	node<T>* _head = nullptr;	// The first block of the linked list
	node<T>* _cur = this->_head;	// The _current obj from the list
	node<T>* _tail = this->_head;	// The last block of the linked list
public:
	DLinkedList() = default;
	constexpr DLinkedList(T elem);
	//~DLinkedList();

	// Remove methods
	void remove_at(size_t idx);
	void remove_head();
	void remove_tail();

	// Insert functions at the end of the linked list
	void insert_at_begin(T elem);
	void insert_at_end(T elem);
	void insert_before_cur(T elem);
	void insert_after_cur(T elem);
	void insert_at(T elem, size_t idx); // implement in the future. Is there any reason to do this insert? Practice maybe?

	inline void move_to_prev();
	inline void move_to_next();
	inline void move_to_head();
	inline void move_to_tail();


	// Get the _current node
	T get_cur_data() const { return this->_cur->data; }
	T get_head_data() const { return this->_head->data; }
	T get_tail_data() const { return this->_tail->data; }
	T get_at(size_t idx);
	// Get size
	unsigned size() const { return this->_len; }
	// chack if it is empty
	bool is_empty() { return this->_len == 0; }

	// Print List
	void print_list();
};






//template <typename T>
//inline DLinkedList<T>::DLinkedList() : _head(nullptr), _cur(nullptr), _tail(nullptr) {}

template <typename T>
constexpr DLinkedList<T>::DLinkedList(T elem) {
	this._head->data = elem;
	this._head->next = nullptr;
	this._head->prev = nullptr;
	this->_cur = this->_head;
	this->_tail = nullptr;
}


template<typename T>
inline void DLinkedList<T>::remove_at(size_t idx) {
	if (idx >= 0 && idx < this->_len) {
		size_t count = 0;
		if (this->_head == nullptr)
			std::cerr << "List is empty." << std::endl;
		else if (idx == 0)
			this->remove_head();
		else if (idx == this->_len - 1)
			this->remove_tail();
		else {
			this->_cur = this->_head;
			while (count != idx) {
				count++;
				this->_cur = this->_cur->next;
			}
			this->_cur->prev->next = this->_cur->next;
			this->_cur->next->prev = this->_cur->prev;
			delete this->_cur;
			this->_cur = this->_head;
			this->_len--;
		}
	}
	else
		std::cerr << "Out of Bound" << std::endl;
}

template <typename T>
inline void DLinkedList<T>::remove_head() {
	if (this->_head != nullptr) {
		if (this->_len == 1) {
			this->_tail = this->_head;
			this->_cur = this->_head;
			delete this->_head;
			this->_head = nullptr;
			this->_tail = this->_head;
			this->_cur = this->_head;
		}
		else {
			this->_cur = this->_head->next;
			this->_cur->prev = nullptr;
			delete this->_head;
			this->_head = this->_cur;
		}
		
	}
	else
		std::cout << "List is empty." << std::endl;
	this->_len--;
}

template <typename T>
inline void DLinkedList<T>::remove_tail() {
	if (this->_head != nullptr) {
		if (this->_len == 1) {
			this->_tail = this->_head;
			this->_cur = this->_head;
			delete this->_head;
			this->_head = nullptr;
			this->_tail = this->_head;
			this->_cur = this->_head;
		}
		else {
			this->_cur = this->_tail->prev;
			this->_cur->next = nullptr;
			delete this->_tail;
			this->_tail = this->_cur;
		}

	}
	else
		std::cout << "List is empty." << std::endl;
	this->_len--;
}

// Insert methods
template <typename T>
void DLinkedList<T>::insert_at_begin(T elem) {
	this->_cur = this->_head;
	this->insert_before_cur(elem);
}
template <typename T>
void DLinkedList<T>::insert_at_end(T elem) {
	this->_cur = this->_tail;
	this->insert_after_cur(elem);
}
template <typename T>
void DLinkedList<T>::insert_before_cur(T elem) {
	node<T>* temp = new node<T>();
	temp->data = elem;
	temp->next = nullptr;
	temp->prev = nullptr;
	if (this->_head == nullptr) {
		this->_head = temp;
		this->_tail = this->_head;
		this->_cur = this->_head;
	}
	else if (this->_cur == this->_head) {
		temp->next = this->_head;
		this->_head->prev = temp;
		this->_head = temp;
		this->_cur = this->_head;
	}
	else {
		temp->next = this->_cur;
		temp->prev = this->_cur->prev;
		this->_cur->prev->next = temp;
		this->_cur->prev = temp;
		this->_cur = temp;
	}
	temp = nullptr;
	delete temp;
	this->_len++;
}
template <typename T>
void DLinkedList<T>::insert_after_cur(T elem) {
	node<T>* temp = new node<T>();
	temp->data = elem;
	temp->next = nullptr;
	temp->prev = nullptr;
	if (this->_head == nullptr) {
		this->_head = temp;
		this->_tail = this->_head;
		this->_cur = this->_head;
	}
	else if (this->_cur == this->_tail) {
		temp->prev = this->_tail;
		this->_tail->next = temp;
		this->_tail = temp;
		this->_cur = this->_tail;
	}
	else {
		temp->prev = this->_cur;
		temp->next = this->_cur->next;
		this->_cur->next->prev = temp;
		this->_cur->next = temp;
		this->_cur = temp;
	}
	temp = nullptr;
	delete temp;
	this->_len++;
}
template <typename T>
void DLinkedList<T>::insert_at(T elem, size_t idx) {
	if (idx >= 0 && idx < this->_len) {
		node<T>* temp = new node<T>();
		temp->data = elem;
		temp->next = nullptr;
		temp->prev = nullptr;
		size_t count = 0;
		if (this->_head == nullptr) {
			this->_head = temp;
			this->_tail = this->_head;
			this->_cur = this->_head;
		}
		else {
			this->_cur = this->_head;
			while (count != idx) {
				count++;
				this->_cur = this->_cur->next;
			}
			this->insert_before_cur(elem);
		}
	}
	else
		std::cerr << "Invalid index. Please enter a index in the valid interval [0, " << this->size() << "].";
}


// Move _current node methods
template <typename T>
inline void DLinkedList<T>::move_to_prev() {
	if (this->_cur != nullptr) {
		if (this->_cur->prev != nullptr)
			this->_cur = this->_cur->prev;
		else
			std::cout << "You are in the beginning of the list (head).\nThere is no previous node." << std::endl;
	}
	else
		std::cout << "There are not elements in this list." << std::endl;
}

template <typename T>
inline void DLinkedList<T>::move_to_next() {
	if (this->_cur != nullptr) {
		if (this->_cur->next != nullptr)
			this->_cur = this->_cur->next;
		else
			std::cout << "You are at the end of the list (tail).\nThere is no next node." << std::endl;
	}
	else
		std::cout << "There are not elements in this list." << std::endl;
}

template <typename T>
inline void DLinkedList<T>::move_to_head() { this->_cur = this->_head; }
template <typename T>
inline void DLinkedList<T>::move_to_tail() { this->_cur = this->_tail; }

template<typename T>
inline T DLinkedList<T>::get_at(size_t idx) {
	if (idx >= 0 && idx < this->_len) {
		//node<T>* temp = this->_head;
		size_t count = 0;
		if (this->_head == nullptr)
			std::cerr << "the list is empty" << std::endl;
		else if (idx == 0)
			return this->_head->data;
		else if (idx == this->_len - 1)
			return this->_tail->data;
		else {
			this->_cur = this->_head;
			while (count != idx) {
				this->_cur = this->_cur->next;
				//temp = temp->next;
				count++;
			}
		}
		return this->_cur->data;
		//return temp->data;
	}
	else
		std::cerr << "Out of Bound" << std::endl;
	return T();
}

template <typename T>
inline void DLinkedList<T>::print_list() {
	if (this->_head == nullptr)
		std::cerr << "the list is empty" << std::endl;
	else {
		this->_cur = this->_head;
		std::cout << "*****************************" << std::endl;
		while (this->_cur != nullptr) {
			std::cout << this->get_cur_data() << std::endl;
			this->_cur = this->_cur->next;
		}
		this->_cur = this->_head;
	}
}






#endif // !DLINKEDLIST_H