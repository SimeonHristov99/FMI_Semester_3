#pragma once

template <class T>
struct TreeNode
{
	T m_data;
	TreeNode* m_left;
	TreeNode* m_right;

	TreeNode(const T& data, TreeNode* left = nullptr, TreeNode* right = nullptr)
		: m_data(data),
		m_left(left),
		m_right(right)
	{ }
};

template <class T>
class BST
{
private:
	TreeNode<T>* m_root;

	TreeNode<T>* copy(const TreeNode<T>* rhs) const;
	void del(TreeNode<T>* node);

	bool find(const TreeNode<T>* node, const T& key) const;

	///
	/// Inserts only unique elements.
	///
	void insert(TreeNode<T>*& node, const T& key);

	///
	/// Creates a binary search tree from a sorted array.
	///
	TreeNode<T>* create(const T* arr, const size_t left_index, const size_t right_index);

	size_t size(const TreeNode<T>* r) const;
	void print(const TreeNode<T>* node) const;
	T* to_arrayHlp(T* arr, TreeNode<T>* node) const;
	TreeNode<T>* get_min(TreeNode<T>* node);
	bool remove(TreeNode<T>*& node, const T& key);

public:
	BST();
	BST(const T* arr, const size_t size);
	BST(const BST& rhs);
	BST& operator=(const BST& rhs);
	~BST();

	bool find(const T& key) const
	{
		return find(m_root, key);
	}

	void insert(const T& key)
	{
		insert(m_root, key);
	}

	size_t size() const
	{
		return size(m_root);
	}

	void print() const
	{
		print(m_root);
	}

	size_t to_array(T* arr) const
	{
		return to_arrayHlp(arr, m_root) - arr;
	}

	bool remove(const T& key)
	{
		return remove(m_root, key);
	}
};

template<class T>
inline TreeNode<T>* BST<T>::copy(const TreeNode<T>* rhs) const
{
	if (!rhs.m_root)
	{
		return nullptr;
	}

	return new TreeNode<T>(rhs->m_data, copy(rhs->m_left), copy(rhs->m_right));
}

template<class T>
inline void BST<T>::del(TreeNode<T>* node)
{
	if (node)
	{
		del(node->m_left);
		del(node->m_right);
		delete node;
	}
}

template<class T>
inline TreeNode<T>* BST<T>::create(const T* arr, const size_t left_index, const size_t right_index)
{
	if (left_index >= right_index)
	{
		return nullptr;
	}

	size_t median = (left_index + right_index) / 2;

	return new TreeNode<T>(arr[0], create(arr, left_index, median), create(arr, median + 1, right_index));
}

template<class T>
inline BST<T>::BST()
	: m_root(nullptr)
{ }

template<class T>
inline BST<T>::BST(const T * arr, const size_t size)
{
	m_root = create(arr, 0, size);
}

template<class T>
inline BST<T>::BST(const BST& rhs)
{
	copy(rhs.m_root);
}

template<class T>
inline BST<T>& BST<T>::operator=(const BST& rhs)
{
	if (this != &rhs)
	{
		del(m_root);
		copy(rhs.m_root);
	}
	return *this;
}

template <class T>
inline BST<T>::~BST()
{
	del(m_root);
}

template<class T>
inline bool BST<T>::find(const TreeNode<T>* node, const T& key) const
{
	if (!node)
	{
		return false;
	}

	if (node->m_data == key)
	{
		return true;
	}

	return node->m_data > key ? find(node->m_left, key) : find(node->m_right, key);
}

template<class T>
inline void BST<T>::insert(TreeNode<T>*& node, const T& key)
{
	if (!node)
	{
		node = new TreeNode<T>(key);
		return;
	}

	if (node->m_data == key)
	{
		return;
	}

	node->m_data > key ? insert(node->m_left, key) : insert(node->m_right, key);
}

template<class T>
inline size_t BST<T>::size(const TreeNode<T>* r) const
{
	if (!r)
	{
		return 0;
	}
	return 1 + size(r->m_left) + size(r->m_right);
}

template<class T>
inline void BST<T>::print(const TreeNode<T>* node) const
{
	if (node)
	{
		print(node->m_left);
		std::cout << node->m_data << ' ';
		print(node->m_right);
	}
}

template<class T>
inline T* BST<T>::to_arrayHlp(T* arr, TreeNode<T>* node) const
{
	if (!node)
	{
		return arr;
	}

	T* left = to_arrayHlp(arr, node->m_left);

	left[0] = node->m_data;

	return to_arrayHlp(left + 1, node->m_right);
}

template<class T>
inline TreeNode<T>* BST<T>::get_min(TreeNode<T>* node)
{
	if (node)
	{
		if (!node->m_left)
		{
			TreeNode<T>* current = node;
			node = node->m_right;
			return current;
		}

		return get_min(node->m_left);
	}
	return nullptr;
}

template<class T>
inline bool BST<T>::remove(TreeNode<T>*& node, const T& key)
{
	if (!node)
	{
		return false;
	}

	if (node->m_data < key)
	{
		return remove(node->m_right, key);
	}

	if (node->m_data > key)
	{
		return remove(node->m_left, key);
	}

	TreeNode<T>* current = node;

	if (!node->m_left)
	{
		node = node->m_right;
	}
	else if (!node->m_right)
	{
		node = node->m_left;
	}
	else
	{
		current = get_min(node->m_right);
		node->m_data = current->m_data;
	}

	delete current;
	return true;
}