/*
Name: Jeffery Knudson
Program: Assignment 5 - DoublyLinkedList
Part: Implementation
Date: 11/8/19
*/
#pragma once
#include <ostream>
#include <exception>

using namespace std;

template <typename T>
struct listNode
{
public:
	listNode* previous;
	listNode* next;
	T value;
	listNode(T value)
	{
		this->value = value;
	}
};

template <typename T>
class DoublyLinkedListIterator
{
public:
	// Write your own constructor:
	DoublyLinkedListIterator(listNode<T> const* start) : current{ start }
	{

	}

	// pre-increment
	DoublyLinkedListIterator<T>& operator ++ ()
	{
		current = current->next;
		return *this;
	}

	// post-increment
	void operator ++ (int)
	{
		current = current->next;
	}

	// pre-decrement
	DoublyLinkedListIterator<T>& operator -- ()
	{
		current = current->previous;
		return *this;
	}

	// post-decrement
	void operator -- (int)
	{
		current = current->previous;
	}

	bool operator == (const DoublyLinkedListIterator<T>& other) const
	{
		return this->current == other.current;
	}

	bool operator != (const DoublyLinkedListIterator<T>& other) const
	{
		return !(*this == other);
	}

	T const& operator * () const
	{
		return current->value;
	}

	T const* operator -> () const
	{
		return &(current->value);
	}

private:
	// Add any private variables you need:
	listNode<T> const* current = nullptr;
};

template <class T>
class MutableDoublyLinkedListIterator
{
public:
	// Write your own constructor:
	MutableDoublyLinkedListIterator(listNode<T>* start) : current{ start }
	{

	}

	// pre-increment
	MutableDoublyLinkedListIterator<T>& operator ++ ()
	{
		current = current->next;
		return *this;
	}

	// post-increment
	void operator ++ (int)
	{
		current = current->next;
	}

	// pre-decrement
	MutableDoublyLinkedListIterator<T>& operator -- ()
	{
		current = current->previous;
		return *this;
	}

	// post-decrement
	void operator -- (int)
	{
		current = current->previous;
	}

	bool operator == (const MutableDoublyLinkedListIterator<T>& other) const
	{
		return this->current == other.current;
	}
	bool operator != (const MutableDoublyLinkedListIterator<T>& other) const
	{
		return !(*this == other);
	}

	T& operator * ()
	{
		return current->value;
	}
	T* operator -> ()
	{
		return &(current->value);
	}

private:
	// Add any private variables you need:
	listNode<T>* current = nullptr;
};

template <typename T>
class ReverseDoublyLinkedListIterator
{
public:
	// Write your own constructor that initializes "base":
	ReverseDoublyLinkedListIterator(listNode<T> const* start) : base{ start }
	{

	}


	// pre-increment
	ReverseDoublyLinkedListIterator<T>& operator ++ ();

	// post-increment
	void operator ++ (int);

	// pre-decrement
	ReverseDoublyLinkedListIterator<T>& operator -- ();

	// post-decrement
	void operator -- (int);

	bool operator == (const ReverseDoublyLinkedListIterator<T>& other) const;
	bool operator != (const ReverseDoublyLinkedListIterator<T>& other) const;

	T const& operator * () const;
	T const* operator -> () const;

private:
	DoublyLinkedListIterator<T> base;
};

template <class T>
class MutableReverseDoublyLinkedListIterator
{
public:
	// Write your own constructor that initializes "base":
	MutableReverseDoublyLinkedListIterator(listNode<T> start) : base{ start }
	{

	}


	// pre-increment
	MutableReverseDoublyLinkedListIterator<T>& operator ++ ();

	// post-increment
	void operator ++ (int);

	// pre-decrement
	MutableReverseDoublyLinkedListIterator<T>& operator -- ();

	// post-decrement
	void operator -- (int);

	bool operator == (const MutableReverseDoublyLinkedListIterator<T>& other) const;
	bool operator != (const MutableReverseDoublyLinkedListIterator<T>& other) const;

	T& operator * ();
	T* operator -> ();

private:
	MutableDoublyLinkedListIterator<T> base;
};

template <typename T>
class DoublyLinkedList
{
public:

	// Use default constructor
	DoublyLinkedList() = default; //used

	// Implement destructor but disable copy constructor and copy assignment (for now)
	//DoublyLinkedList(const DoublyLinkedList<T>& original) = delete;
	~DoublyLinkedList();
	/*
	DoublyLinkedList<T>& operator= (
		const DoublyLinkedList<T>& original) = delete;
		*/

	// Get the size of the list
	unsigned int getSize() const //used
	{
		return listSize;
	}

	// Is there anything in the list?
	bool isEmpty() const //used
	{
		return listSize <= 0;
	}

	// get the first element of the list
	const T& getFirst() const //used
	{
		return firstNode->value;
	}

	// gets the first element of the list, mutable
	T& getFirst() //used
	{
		return firstNode->value;
	}

	// get the last element of the list
	const T& getLast() const //used
	{
		return lastNode->value;
	}

	// gets the last element of the list, mutable
	T& getLast() //used
	{
		return lastNode->value;
	}

	// Add an item to the front of the list
	void addFirst(T value) //used
	{
		listNode<T>* newNode = new listNode<T>(value);
		if (firstNode == nullptr)
		{
			lastNode = newNode;
		}
		else
		{
			firstNode->previous = newNode;
			newNode->next = firstNode;
		}
		firstNode = newNode;
		listSize++;
	}

	// Remove an item from the front of the list
	void removeFirst() //used
	{
		if (!isEmpty())
		{
			if (listSize == 1)
			{
				lastNode = nullptr;
				delete firstNode;
				firstNode = nullptr;
			}
			else
			{
				firstNode->next->previous = nullptr;
				listNode<T>* temp = firstNode->next;
				delete firstNode;
				firstNode = temp;
			}
			listSize--;
		}
		else
		{
			throw exception("No nodes to remove in list");
		}
	}

	// Add an item to the end of the list
	void addLast(T value) //used
	{
		listNode<T>* newNode = new listNode<T>(value);
		if (firstNode == nullptr)
		{
			firstNode = newNode;
		}
		else
		{
			lastNode->next = newNode;
			newNode->previous = lastNode;
		}
		lastNode = newNode;
		listSize++;
	}

	// Remove an item from the end of the list
	void removeLast() //used
	{
		if (!isEmpty())
		{
			if (lastNode->previous == nullptr)
			{
				firstNode = nullptr;
				delete lastNode;
				lastNode = nullptr;
			}
			else
			{
				lastNode->previous->next = nullptr;
				listNode<T>* temp = lastNode->previous;
				delete lastNode;
				lastNode = temp;
			}
			listSize--;
		}
		else
		{
			throw exception("No nodes to remove in list");
		}
	}

	// Remove all items from the list
	void clear() //used
	{
		while (!isEmpty())
		{
			removeFirst();
		}
	}

	template <typename T2> //used
	friend std::ostream& operator << (
		std::ostream& os,
		const DoublyLinkedList<T2>& list)
	{
		bool needToRemove = false;
		const DoublyLinkedList<int>* cList = &list;
		os << "[";
		for (auto i = cList->begin(); i != cList->end(); i++)
		{
			needToRemove = true;
			os << *i << ", ";
		}
		os << (needToRemove ? "\b\b]" : "]");
		return os;
	}

	// Gets an iterator for use with range-based for loop
	DoublyLinkedListIterator<T> begin() const
	{
		return DoublyLinkedListIterator<T>{firstNode};
	}

	DoublyLinkedListIterator<T> end() const
	{
		return (lastNode != nullptr ? DoublyLinkedListIterator<T>{lastNode->next} : 
			DoublyLinkedListIterator<T>{ lastNode });
	}

	// Gets an iterator that allows modifying values
	MutableDoublyLinkedListIterator<T> begin()
	{
		return DoublyLinkedList<T>{firstNode};
	}

	MutableDoublyLinkedListIterator<T> end()
	{
		return (lastNode != nullptr ? DoublyLinkedListIterator<T>{lastNode->next} :
			DoublyLinkedListIterator<T>{ lastNode });
	}

	// Gets a reverse iterator
	ReverseDoublyLinkedListIterator<T> rbegin() const
	{
		return DoublyLinkedList<T>{lastNode};
	}
	ReverseDoublyLinkedListIterator<T> rend() const
	{
		return (firstNode != nullptr ? DoublyLinkedListIterator<T>{firstNode->previous} :
			DoublyLinkedListIterator<T>{ firstNode });
	}

	// Gets a reverse iterator that allows modifying values
	MutableReverseDoublyLinkedListIterator<T> rbegin()
	{
		return DoublyLinkedList<T>{lastNode};
	}
	MutableReverseDoublyLinkedListIterator<T> rend()
	{
		return (firstNode != nullptr ? DoublyLinkedListIterator<T>{firstNode->previous} :
			DoublyLinkedListIterator<T>{ firstNode });
	}

private:
	// Add any private variables you need:
	listNode<T>* firstNode;
	listNode<T>* lastNode;
	int listSize = 0;
};

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();
}

template<typename T>
ReverseDoublyLinkedListIterator<T>& ReverseDoublyLinkedListIterator<T>::operator++()
{
	--base;
	return *this;
}

template<typename T>
void ReverseDoublyLinkedListIterator<T>::operator++(int)
{
	base--;
}

template<typename T>
ReverseDoublyLinkedListIterator<T>& ReverseDoublyLinkedListIterator<T>::operator--()
{
	++base;
	return *this;
}

template<typename T>
void ReverseDoublyLinkedListIterator<T>::operator--(int)
{
	base++;
}

template<typename T>
bool ReverseDoublyLinkedListIterator<T>::operator==(const ReverseDoublyLinkedListIterator<T>& other) const
{
	return base == other.base;
}

template<typename T>
bool ReverseDoublyLinkedListIterator<T>::operator!=(const ReverseDoublyLinkedListIterator<T>& other) const
{
	return base != other.base;
}

template<typename T>
T const& ReverseDoublyLinkedListIterator<T>::operator*() const
{
	return *base;
}

template<typename T>
T const* ReverseDoublyLinkedListIterator<T>::operator->() const
{
	return &(*base);
}

template<class T>
MutableReverseDoublyLinkedListIterator<T>& MutableReverseDoublyLinkedListIterator<T>::operator++()
{
	--base;
	return *this;
}

template<class T>
void MutableReverseDoublyLinkedListIterator<T>::operator++(int)
{
	base--;
}

template<class T>
MutableReverseDoublyLinkedListIterator<T>& MutableReverseDoublyLinkedListIterator<T>::operator--()
{
	++base;
	return *this;
}

template<class T>
void MutableReverseDoublyLinkedListIterator<T>::operator--(int)
{
	base++;
}

template<class T>
bool MutableReverseDoublyLinkedListIterator<T>::operator==(const MutableReverseDoublyLinkedListIterator<T>& other) const
{
	return base == other.base;
}

template<class T>
bool MutableReverseDoublyLinkedListIterator<T>::operator!=(const MutableReverseDoublyLinkedListIterator<T>& other) const
{
	return base != other.base;
}

template<class T>
T& MutableReverseDoublyLinkedListIterator<T>::operator*()
{
	return *base;
}

template<class T>
T* MutableReverseDoublyLinkedListIterator<T>::operator->()
{
	return &(*base);
}