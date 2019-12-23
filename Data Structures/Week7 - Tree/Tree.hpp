#pragma once

template <class T>
struct TreeNode
{
    T m_data;
    TreeNode* m_siblings;
    TreeNode* m_successor;

    TreeNode(const T& data, TreeNode* sib = nullptr, TreeNode* succ = nullptr)
        : m_data(data),
        m_siblings(sib),
        m_successor(succ)
    { }
};

template <class T>
class Tree
{
private:
    TreeNode<T>* m_root;

    TreeNode<T>* copy(const TreeNode<T>* rhs_node);

    void del(const TreeNode<T>* node);

    bool find(const TreeNode<T>* node, const T& key) const;

    // Not very good for complex data types because of the data type "path".
    // The root must not be in the path.
    bool insert(const T& elem, TreeNode<T>*& node, const T* path, size_t path_length);

    size_t size(const TreeNode<T>* node) const;

    T* get(TreeNode<T>* node, T* path, size_t path_lenght);

    void print(const TreeNode<T>* node) const;

public:
    Tree();

    Tree(const Tree& rhs);

    Tree& operator=(const Tree& rhs);

    ~Tree();

    bool find(const T& key) const
    {
        return find(m_root, key);
    }

    bool insert(const T& element, const T* path, size_t pathlen)
    {
        return insert(element, m_root, path, pathlen);
    }

    size_t size() const
    {
        return size(m_root);
    }

    T* get(T* path, size_t len)
    {
        return get(m_root, path, len);
    }

    void print() const
    {
        print(m_root);
    }
};

template <class T>
TreeNode<T>* Tree<T>::copy(const TreeNode<T>* rhs_node)
{
    if (!rhs_node)
    {
        return nullptr;
    }

    TreeNode<T>* node = new TreeNode<T>(rhs_node->m_data);

    node->m_siblings = copy(rhs_node->m_siblings);
    node->m_successor = copy(rhs_node->m_successor);

    return node;
}

template<class T>
inline void Tree<T>::del(const TreeNode<T>* node)
{
    if (!node)
    {
        return;
    }

    del(node->m_siblings);
    del(node->m_successor);

    delete node;
}

template<class T>
inline bool Tree<T>::find(const TreeNode<T>* node, const T& key) const
{
    if (!node)
    {
        return false;
    }

    if (node->m_data == key)
    {
        return true;
    }

    return find(node->m_successor, key) || find(node->m_siblings, key);
}

template<class T>
inline bool Tree<T>::insert(const T& elem, TreeNode<T>*& node, const T* path, size_t path_length)
{
    if (!node && path_length)
    {
        return false;
    }

    if (!node && !path_length)
    {
        node = new TreeNode<T>(elem);
        return true;
    }

    if (!path_length)
    {
        TreeNode<T>* n = new TreeNode<T>(elem);
        n->m_siblings = node->m_successor;
        node->m_successor = n;
        return true;
    }

    TreeNode<T>* n = node->m_successor;
    while (n && n->m_data != *path)
    {
        n = n->m_siblings;
    }
    if (n)
    {
        return insert(elem, n, path + 1, path_length - 1);
    }

    return false;
}

template<class T>
inline size_t Tree<T>::size(const TreeNode<T>* node) const
{
    if (!node)
    {
        return 0;
    }

    return 1 + size(node->m_siblings) + size(node->m_successor);
}

template<class T>
inline T* Tree<T>::get(TreeNode<T>* node, T* path, size_t path_lenght)
{
    if (path_lenght == 0)
    {
        return &node->m_data;
    }

    TreeNode<T>* n = node->m_successor;

    while (n)
    {
        if (n->m_data == *path)
        {
            T* res = get(n, path + 1, path_lenght - 1);
            if (res)
            {
                return res;
            }
        }
        n = n->m_siblings;
    }

    return nullptr;
}

template<class T>
inline void Tree<T>::print(const TreeNode<T>* node) const
{
    if (!node)
    {
        return;
    }

    std::cout << " { " << node->m_data;
    print(node->m_successor);
    std::cout << " }";
    print(node->m_siblings);
}

template<class T>
inline Tree<T>::Tree()
    : m_root(nullptr)
{ }

template<class T>
inline Tree<T>::Tree(const Tree& rhs)
{
    m_root = copy(rhs.m_root);
}

template<class T>
inline Tree<T>& Tree<T>::operator=(const Tree& rhs)
{
    if (this != &rhs)
    {
        del(m_root);
        m_root = copy(rhs.m_root);
    }
    return *this;
}

template<class T>
inline Tree<T>::~Tree()
{
    del(m_root);
}