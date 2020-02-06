#include <iostream>

template <class T>
class Stack
{
private:
    size_t m_capacity;
    size_t m_tos;
    T* m_data;

    void copy(const Stack& rhs)
    {
        m_data = new T[rhs.m_capacity];

        m_tos = rhs.m_tos;
        m_capacity = rhs.m_capacity;
        
        for (size_t i = 0; i < m_tos; ++i)
        {
            m_data[i] = rhs.m_data[i];
        }
    }

    void resize()
    {
        T* data = new T[m_capacity * 2];

        for (size_t i = 0; i < m_tos; i++)
        {
            data[i] = m_data[i];
        }

        m_capacity *= 2;
        delete[] m_data;
        m_data = data;
        data = nullptr;
    }

    void del()
    {
        delete[] m_data;
        m_data = nullptr;
    }

public:
    Stack()
        : m_capacity(8),
        m_tos(0),
        m_data(new T[m_capacity])
    { }

    Stack(const Stack& rhs)
        : m_capacity(0),
        m_tos(0)
    {
        copy(rhs);
    }

    Stack& operator=(const Stack& rhs)
    {
        if (this != &rhs)
        {
            del();
            copy(rhs);
        }
        return *this;
    }

    ~Stack()
    {
        del();
    }

    bool is_empty() const
    {
        return m_tos == 0;
    }

    void push(const T& element)
    {
        if (m_tos == m_capacity)
        {
            resize();
        }

        m_data[m_tos++] = element;
    }

    T pop()
    {
        return m_data[--m_tos];
    }

    const T& top()
    {
        return m_data[m_tos - 1];
    }
};

char closing(const char& c)
{
    switch (c)
    {
    case '(':
    {
        return ')';
    }
    case '[':
    {
        return ']';
    }
    default:
        return '}';
    }
}

bool eq_brackets(const std::string& s)
{
    Stack<char> st;

    for (const char& c : s)
    {
        if (c == '(' || c == '[' || c == '{')
        {
            st.push(c);
        }
        else if (st.is_empty() || closing(st.pop()) != c)
        {
            return false;
        }
    }

    return st.is_empty();
}

int main()
{
    std::string input;

    while (true)
    {
        std::cin >> input;

        std::cout << std::boolalpha << eq_brackets(input) << '\n';
    }

    return 0;
}