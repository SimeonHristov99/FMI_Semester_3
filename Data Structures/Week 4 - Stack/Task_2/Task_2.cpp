#include <iostream>
#include <vector>

size_t max_chunks(std::vector<int>& input)
{
    if (input.size() < 2)
    {
        return 1;
    }

    size_t j = 0;

    std::vector<int>::iterator left = input.begin();
    std::vector<int>::iterator right = input.begin();

    while (right != input.end())
    {
        if (*right > *left)
        {
            ++j;
            left = right - 1;
        }

        ++right;

        if (right != input.end() && *right > * left)
        {
            ++j;
            left = right - 1;
        }

        if (right != input.end())
        {
            ++right;
        }
    }

    if (j == 0)
    {
        return 1;
    }

    return j;
}

int main()
{
    std::vector<int> input = { 4, 3, 2, 1, 0 }; // 1
    std::vector<int> input1 = { 1, 0, 2, 3, 4 }; // 4
    std::vector<int> input2 = { 2, 0, 1 }; // 1
    std::vector<int> input3 = { 1, 2, 0, 3 }; // 2

    std::cout << max_chunks(input) << '\n';
    std::cout << max_chunks(input1) << '\n';
    std::cout << max_chunks(input2) << '\n';
    std::cout << max_chunks(input3) << '\n';

    return 0;
}