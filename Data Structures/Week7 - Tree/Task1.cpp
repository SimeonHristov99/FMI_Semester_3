#include "pch.h"
#include "gtest/gtest.h"
#include "../Tree/Tree.hpp"

TEST(TreeTest, Insert)
{
    Tree<int> t;
    int arr[1] = { };

    t.insert(5, arr, 0);
    ASSERT_EQ(t.size(), 1);
}

TEST(TreeTest, OperatorEq)
{
    Tree<int> t1;
    int arr[1] = { };

    t1.insert(5, arr, 0);
    t1.insert(10, arr, 0);
    t1.insert(20, arr, 0);

    Tree<int> t2;

    t2 = t1;

    ASSERT_EQ(t2.size(), 3);
}

TEST(TreeTest, find)
{
    Tree<int> t;
    int arr[1] = { 2 };

    t.insert(1, arr, 0);
    t.insert(2, arr, 0);
    t.insert(5, arr, 1);
    ASSERT_TRUE(t.find(5));
}

TEST(TreeTest, get)
{
    Tree<int> t;
    int arr[3] = { 2, 5 };

    t.insert(1, arr, 0);
    t.insert(2, arr, 0);
    t.insert(5, arr, 1);
    t.insert(6, arr, 1);

    int* ptr2 = t.get(arr, 2);

    *ptr2 = 600;

    ASSERT_TRUE(t.find(600));
}