#pragma once

template <class T>
class Queue
{
private:
	size_t m_capacity;

	// The % operation should not get a negative number.
	size_t m_first;
	size_t m_last;

	T* m_data;

	void resize();
	unsigned next(unsigned index);

public:
	Queue();
	Queue(const Queue& rhs) = delete;
	Queue& operator=(const Queue& rhs) = delete;
	~Queue();

	bool is_empty();
	bool is_full();

	void enqueue(const T& element);
	void dequeue();

	T peek() const;
};

template<class T>
inline void Queue<T>::resize()
{
	T* data = new T[m_capacity * 2];

	for (size_t i = 0; i < m_capacity; i++)
	{
		data[i] = m_data[m_first];

		m_first = next(m_first);
	}

	delete[] m_data;
	m_data = data;

	m_first = 0;
	m_last = m_capacity - 1; // Indexes the free cell.

	m_capacity *= 2;
}

template<class T>
inline unsigned Queue<T>::next(unsigned index)
{
	return (index + 1) % m_capacity;
}

template<class T>
inline Queue<T>::Queue()
	: m_capacity(8),
	m_first(0),
	m_last(0),
	m_data(new T[m_capacity])
{ }

template<class T>
inline Queue<T>::~Queue()
{
	delete[] m_data;
}

template<class T>
inline bool Queue<T>::is_empty()
{
	return m_first == m_last;
}

template<class T>
inline bool Queue<T>::is_full()
{
	return (m_last + 1) % m_capacity == m_first;
}

template<class T>
inline void Queue<T>::enqueue(const T& element)
{
	if (is_full())
	{
		resize();
	}

	m_data[m_last] = element;

	m_last = next(m_last);
}

template<class T>
inline void Queue<T>::dequeue()
{
	m_first = next(m_first);
}

template<class T>
inline T Queue<T>::peek() const
{
	return m_data[m_first];
}