#include <iostream>

//We use the implementation of linked list (we only have the AddLast(T) and RemoveFirst()) 

template <typename T>
class LinkedQueue
{
	struct Node
	{
		Node(T data)
		{
			this->data = data;
			next = nullptr;
		}
		T data;
		Node* next;
	};

	Node* head;
	Node* tail;

	void free();
	void copyFrom(const LinkedQueue& other);

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue& other);
	LinkedQueue operator=(const LinkedQueue& other);
	~LinkedQueue();

	void enqueue(const T&); // O(1)
	T dequeue(); //O(1)
	const T& peek() const; //O(1)

	bool isEmpty() const;

};

template <typename T>
void LinkedQueue<T>::free()
{
	Node* iter = head;
	while (iter!=nullptr)
	{
		Node* prev = iter;
		iter = iter->next;
		delete prev;
	}
}

template <typename T>
void LinkedQueue<T>::copyFrom(const LinkedQueue& other)
{
	Node* iter = other.head;
	while (iter != nullptr)
	{
		enqueue(iter->data);
		iter = iter->next;
	}
	
}

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	head = nullptr;
	tail = nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& other)
{
	copyFrom(other);
}

template <typename T>
LinkedQueue<T> LinkedQueue<T>::operator=(const LinkedQueue& other)
{
	if (this!=&other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& el)
{
	Node* newNode = new Node(el);
	if (head == nullptr && tail == nullptr)//if its empty
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
}



template <typename T>
T LinkedQueue<T>::dequeue()
{
	if (isEmpty())
		throw std::runtime_error("The list is empty!");
	else if (head == tail)
	{
		T el = head->data;
		delete head;

		head = nullptr;
		tail = nullptr;

		return el;
	}
	else
	{
		T el = head->data;
		Node* temp = head->next;
		
		delete head;
		
		head = temp;
		return el;
	}

}
template <typename T>
const T& LinkedQueue<T>::peek() const
{
	if(isEmpty())
		throw std::runtime_error("The list is empty!");

	return head->data;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	free();
}