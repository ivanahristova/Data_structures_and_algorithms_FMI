#pragma once
#include <iostream>

//Implementation without iterators (for now)
template <typename T> 
class DoublyLinkedList 
{
	size_t count = 0;

	struct Node
	{
		Node(T data) : data(data) {}
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	void copyFrom(const DoublyLinkedList& other);
	void free();

public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>& other);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
	~DoublyLinkedList();

	void pushBack(const T& el); //O(1)
	void pushFront(const T& el); //O(1)

	T popBack(); // O(1)
	T popFront(); // O(1)

	void print() const;
	size_t getSize() const;

	bool isEmpty() const;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), count(0)
{}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T& el)
{
	Node* added = new Node(el);
	count++;
	if (isEmpty())
		head = tail = added;
	else
	{
		tail->next = added;
		added->prev = tail;
		tail = added;
	}
}
template <typename T>
void DoublyLinkedList<T>::pushFront(const T& el)
{
	Node* added = new Node(el);
	if (isEmpty())
	{
		head = tail = added;
	}
	else
	{
		added->next = head;
		head->prev = added;
		head = added;
	}
	count++;
}

template<typename T>
T DoublyLinkedList<T>::popBack()
{
	if (isEmpty())
		throw std::runtime_error("The list is empty!");
	else if (head == tail)
	{
		T data = head->data;
		delete head;
		head = tail = nullptr;
		return data;
	}
	else
	{
		T data = tail->data;
		tail->prev->next = nullptr;

		Node* toDelete = tail;
		tail = tail->prev;

		delete toDelete;

		count--;
		return data;
	}
}

template<typename T>
T DoublyLinkedList<T>::popFront()
{
	if (isEmpty())
		throw std::runtime_error("The list is empty!");
	else if (head == tail)
	{
		T data = head->data;
		delete head;

		head = tail = nullptr;
		
		count--;
		return data;
	}
	else
	{
		T data = head->data;
		head->next->prev = nullptr;

		Node* toDelete = head;
		head = head->next;
		
		delete toDelete;
		
		count--;
		return data;
	}
}

template<typename T>
void DoublyLinkedList<T>::print() const
{
	Node* iter = head;
	while (iter != nullptr)
	{
		std::cout << iter->data;
		if (iter != tail)
			std::cout << "<->";
		iter = iter->next;
	}
	std::cout << std::endl;
}
template<typename T>
size_t DoublyLinkedList<T>::getSize() const
{
	return count;
}


template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
{
	copyFrom(other);
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	free();
}

template <typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList<T>& other)
{
	Node* otherIter = other.head;
	while (otherIter != nullptr)
	{
		pushBack(otherIter->data);
		otherIter = otherIter->next;
	}
}

template<typename T>
void DoublyLinkedList<T>::free()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}
