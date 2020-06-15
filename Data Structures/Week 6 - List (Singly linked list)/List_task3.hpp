#pragma once

template <class T>
class List
{
private:
	struct Node
	{
		T m_data;
		Node* m_next;

		Node(const T& data, Node* next = nullptr)
			: m_data(data),
			m_next(next)
		{ }
	};
	
	Node* m_first;
	Node* m_last;

	size_t m_size;

public:
	List();
	List(const List& rhs) = delete;
	List& operator=(const List& rhs) = delete;
	~List();

	bool is_empty() const; // Checks whether there are zero elements.
	size_t size() const; // Returns the number of elements.

	void insert_front(const T& element); // Inserts an element in the beginning.
	void insert_last(const T& element); // Inserts an element in the end.
	void insert_after(Node* ptr, const T& element); // Inserts element after the node that ptr holds.

	T remove_first(); // Removes the first element.
	T remove(const T& key); // Removes the first element that matches the key. Linear time complexity!
	T remove(Node* ptr); // Removes the node that ptr is holding. Linear time complexity!

	Node* find(const T& key); // The key is a "quality" - in this case: a value. Linear time complexity!
	Node* get_at(size_t index); // Returns the element that is on that index.

	template <class Functor>
	void map(Functor f) // Takes a function and applies it to all the elements in the list. Depending on what the function is time complexity >= O(n).
	{
		for (Node* current = m_first; current != nullptr; current = current->m_next)
		{
			f(current->m_data);
		}
	}

	void reverse();
};

template<class T>
inline List<T>::List()
	: m_first(nullptr),
	m_last(nullptr),
	m_size(0)
{ }

template<class T>
inline List<T>::~List()
{
	while (m_first != nullptr)
	{
		Node* current = m_first;
		m_first = m_first->m_next;
		delete[] current;
	}
}

template<class T>
inline bool List<T>::is_empty() const
{
	return m_size == 0;
}

template<class T>
inline size_t List<T>::size() const
{
	return m_size;
}

template<class T>
inline void List<T>::insert_front(const T& element)
{
	Node* n = new Node(element);

	if (m_first == nullptr)
	{
		m_last = m_first = n;
	}
	else
	{
		n->m_next = m_first;
		m_first = n;
	}

	++m_size;
}

template<class T>
inline void List<T>::insert_last(const T& element)
{
	Node* n = new Node(element);

	if (m_first == nullptr)
	{
		m_last = m_first = n;
	}
	else
	{
		m_last->m_next = n;
		m_last = n;
	}

	++m_size;
}

template<class T>
inline void List<T>::insert_after(Node* ptr, const T& element)
{
	if (ptr == nullptr)
	{
		return insert_front(element);
	}

	if (ptr == m_last)
	{
		return insert_last(element);
	}

	Node* n = new Node(element, ptr->m_next);

	ptr->m_next = n;

	++m_size;
}

template<class T>
inline T List<T>::remove_first()
{
	Node* first = m_first;
	T data = first->m_data;

	m_first = m_first->m_next;

	if (m_size == 1)
	{
		delete[] m_last;
	}
	else
	{
		delete[] first;
	}

	--m_size;

	return data;
}

template<class T>
inline typename List<T>::Node* List<T>::find(const T& key)
{
	Node* current = m_first;

	while (current != nullptr && current->m_data != key)
	{
		current = current->m_next;
	}

	return current;
}

template<class T>
inline typename List<T>::Node* List<T>::get_at(size_t index)
{
	if (index >= m_size)
	{
		return nullptr;
	}

	if (index == 0)
	{
		return m_first;
	}

	if (index == m_size - 1)
	{
		return m_last;
	}

	Node* current = m_first->m_next;

	while (index != 1)
	{
		current = current->m_next;
		--index;
	}

	return current;
}

template<class T>
inline void List<T>::reverse()
{
	if (m_size < 2)
	{
		return;
	}

	if (m_size == 2)
	{
		m_last->m_next = m_first;
		m_first->m_next = nullptr;
		m_first = m_last;
		m_last = m_last->m_next;
		return;
	}

	Node* ptr1 = m_first;
	Node* ptr2 = m_first->m_next;
	Node* ptr3 = ptr2->m_next;

	ptr1->m_next = nullptr;

	while (ptr2 != nullptr)
	{
		ptr2->m_next = ptr1;

		if (ptr3 == nullptr)
		{
			m_first = ptr2;
			break;
		}

		ptr1 = ptr3->m_next;
		ptr3->m_next = ptr2;

		if (ptr1 == nullptr)
		{
			m_first = ptr3;
			break;
		}

		ptr2 = ptr1->m_next;
		ptr1->m_next = ptr3;

		if (ptr2 == nullptr)
		{
			m_first = ptr1;
			break;
		}

		ptr3 = ptr2->m_next;
	}

	while (m_last->m_next != nullptr)
	{
		m_last = m_last->m_next;
	}
}

template<class T>
inline T List<T>::remove(const T& key)
{
	// List must not be empty.
	if (m_first->m_data == key)
	{
		return remove_first();
	}

	Node* current = m_first;

	// Key has to be present in list.
	while (current->m_next)
	{
		if (current->m_next->m_data == key)
		{
			Node* n = current->m_next;
			current->m_next = n->m_next;

			T x = n->m_data;

			delete n;

			if (!current->m_next)
			{
				m_last = current;
			}

			--m_size;

			return x;
		}

		current = current->m_next;
	}
}

template<class T>
inline T List<T>::remove(Node* ptr)
{
	if (m_first == ptr)
	{
		return remove_first();
	}

	Node* current = m_first;

	while (current->m_next != ptr)
	{
		current = current->m_next;
	}

	// Key must be present. Ptr must not be nulptr.
	current->m_next = ptr->m_next;

	T data = ptr->m_data;

	delete[] ptr;
	
	--m_size;

	return data;
}
