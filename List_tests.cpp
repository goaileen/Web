// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_stub)
{
    ASSERT_TRUE(true);
}

TEST(test_list_ctor_and_empty)
{
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(list.size() == 0);
    list.push_back(3);
    ASSERT_FALSE(list.empty());
}
TEST(test_list_size)
{
    List<int> list;
    list.push_back(3);
    ASSERT_TRUE(list.size() == 1);
}

TEST(test_push_front_back)
{
    List<int> list;
    list.push_back(3);
    ASSERT_TRUE(list.front() == 3);
    ASSERT_TRUE(list.back() == 3);
    list.push_back(4);
    ASSERT_TRUE(list.front() == 3);
    ASSERT_TRUE(list.back() == 4);
    list.push_front(2);
    ASSERT_TRUE(list.front() == 2);
    ASSERT_TRUE(list.back() == 4);
    list.insert(++list.begin(), 5);
    ASSERT_TRUE(list.front() == 2);
    ASSERT_TRUE(list.back() == 4);
    ASSERT_TRUE(list.size() == 4);
    
    List<int> list1;
    list1.push_front(3);
    ASSERT_TRUE(list1.front() == 3);
    ASSERT_TRUE(list1.back() == 3);
}
TEST(test_front_back)
{
    List<int> list;
    list.push_back(3);
    list.front() = 8;
    ASSERT_TRUE(*list.begin() == 8);
    ASSERT_TRUE(list.front() == 8);
    ASSERT_TRUE(list.back() == 8);
    list.push_back(5);
    list.back() = 10;
    ASSERT_TRUE(list.back() == 10);
    ASSERT_TRUE(list.front() == 8);
}

TEST(test_pop_front_back)
{
    List<int> list;
    list.push_front(2);
    list.pop_front();
    ASSERT_TRUE(list.empty());
    list.push_back(2);
    list.pop_back();
    ASSERT_TRUE(list.empty());
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.pop_back();
    ASSERT_TRUE(list.back() == 3);
    list.pop_front();
    ASSERT_TRUE(list.front() == 3);
    ASSERT_TRUE(list.size() == 1);
}

TEST(test_clear)
{
    List<int> list;
    list.push_front(2);
    list.push_front(3);
    list.clear();
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(list.size() == 0);
}

TEST(test_assignment)
{
    List<int> lhs;
    List<int> rhs;
    rhs.push_front(2);
    rhs.push_back(5);
    ASSERT_TRUE(lhs.empty());
    lhs = rhs;
    ASSERT_TRUE(lhs.size() == 2);
    lhs.pop_back();
    ASSERT_TRUE(lhs.size() == 1);
    ASSERT_TRUE(rhs.size() == 2);
    ASSERT_FALSE(rhs.size() != 2);
    lhs.clear();
    ASSERT_TRUE(lhs.size() == 0);
    ASSERT_TRUE(rhs.size() == 2);
}

TEST(test_copy_ctor)
{
    List<int> test;
    test.push_back(3);
    test.push_back(5);
    List<int> test1(test);
    ASSERT_TRUE(test1.front() == 3);
    ASSERT_TRUE(test1.back() == 5);
    ASSERT_TRUE(test1.begin() != test.begin());

    test.push_back(7);
    ASSERT_TRUE(test.size() == 3);
    ASSERT_FALSE(test1.size() == 3);
}
TEST(test_iterator_ctor_and_deref)
{
    List<int> list;
    list.push_back(3);
    List<int>::Iterator iter;
    iter = list.begin();
    ASSERT_TRUE(*iter == 3);
    iter = list.end();
    ASSERT_TRUE(iter == list.end());
}

TEST(test_decrement_increment)
{
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    List<int>::Iterator iter;
    iter = list.begin();
    ASSERT_TRUE(*iter == 3);
    ASSERT_TRUE(*(++iter) == 5);
    ASSERT_TRUE(*(--iter) == 3);
    ++iter;
    ASSERT_TRUE((++iter) == list.end());
}
TEST(test_equal)
{
    List<int> list;
    list.push_back(3);
    List<int>::Iterator iter;
    List<int>::Iterator iter1;

    iter = list.begin();
    iter1 = list.begin();
    ASSERT_TRUE(iter == iter1);
    ASSERT_FALSE(iter != iter1);
    ++iter;
    ASSERT_FALSE(iter == iter1);
    ASSERT_TRUE(iter != iter1);
}

TEST(test_erase)
{
    List<int> list;
    list.push_back(3);
    List<int>::Iterator iter;
    iter = list.begin();
    list.erase(iter); // 1elem
    ASSERT_TRUE(list.empty());
    list.push_back(3);
    list.push_back(4);
    iter = list.begin();
    ++iter;
    list.erase(iter);
    ASSERT_TRUE(list.front() == 3); // 2elem
    ASSERT_TRUE(list.back() == 3);
    ASSERT_TRUE(list.size() == 1);
    list.push_back(4);
    iter = list.begin();
    list.erase(iter);
    ASSERT_TRUE(list.front() == 4); // 2elem
    ASSERT_TRUE(list.back() == 4);
    ASSERT_TRUE(list.size() == 1);

    list.push_back(5);
    list.push_back(6);
    iter = list.begin();
    ++iter;
    list.erase(iter);
    ASSERT_TRUE(list.front() == 4); // 3elem
    ASSERT_TRUE(list.back() == 6);
    ASSERT_TRUE(list.size() == 2);
    list.clear();
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.erase(list.begin());
    ASSERT_TRUE(list.front() == 5);
    list.erase(++list.begin());
    ASSERT_TRUE(list.front() == 5);
    ASSERT_TRUE(list.back() == 5);
}

TEST(test_insert)
{
    List<int> list;
    list.push_back(3);
    List<int>::Iterator iter;
    iter = list.begin();
    list.insert(iter, 2);
    ASSERT_TRUE(list.front() == 2); // 1elem
    ASSERT_TRUE(list.back() == 3);
    ASSERT_TRUE(list.size() == 2);
    list.insert(iter, 10);
    ASSERT_TRUE(list.front() == 2); // 1elem
    ASSERT_TRUE(list.back() == 3);
    ASSERT_TRUE(list.size() == 3);

    List<int> list1;
    List<int>::Iterator iter1; //insert to empty list
    list1.insert(iter1, 2);
    ASSERT_TRUE(list1.front() == 2);
    ASSERT_TRUE(list1.back() == 2);

    List<int> list2;
    list2.insert(list2.end(), 3);
    ASSERT_TRUE(list2.front() == 3);
    ASSERT_TRUE(list2.back() == 3);
    ASSERT_TRUE(list2.size() == 1);
    list2.insert(list2.begin(), 2);
    ASSERT_TRUE(list2.front() == 2);
    ASSERT_TRUE(list2.back() == 3);
    ASSERT_TRUE(list2.size() == 2);
    list2.push_back(4);
    ASSERT_TRUE(*++++list2.begin() == 4);
    iter1 = ++++list2.begin();
    ASSERT_TRUE(*----iter1 == 2);
    
    List<int> list3;
    list3.push_back(1);
    list3.push_back(2);
    list3.push_back(4);
    list3.insert(++++list3.begin(), 3);
    int i = 1;
    for (List<int>::Iterator iter = list3.begin();
         iter != list3.end(); ++iter)
    {
        ASSERT_TRUE(*iter == i);
        i++;
        
    }
}

TEST(test_iterator_default_ctor)
{
    List<int> list;
    list.push_back(3);
    List<int>::Iterator initialPos = list.begin();
    List<int>::Iterator iter = list.begin();
    List<int>::Iterator iter1(iter);
    ASSERT_TRUE(iter1 == iter);
    list.insert(iter1, 2);
    ASSERT_TRUE(list.size() == 2);
    ASSERT_TRUE(list.front() == 2);
    ASSERT_TRUE(list.back() == 3);
    ASSERT_TRUE(iter1 == initialPos);
    list.insert(iter, 4);
    ASSERT_TRUE(iter == initialPos);
    ASSERT_TRUE(list.size() == 3);
    ASSERT_TRUE(list.front() == 2);
    ASSERT_TRUE(++iter == list.end());
    ASSERT_TRUE(list.back() == 3);
    ASSERT_TRUE(*++list.begin() == 4);
}

TEST(test_iterator_default_assign)
{
    List<int> list;
    list.push_back(3);
    List<int>::Iterator initialPos = list.begin();
    List<int>::Iterator iter = list.begin();
    List<int>::Iterator iter1;
    iter1 = iter;
    ASSERT_TRUE(iter1 == iter);
    list.insert(iter1, 2);
    ASSERT_TRUE(list.size() == 2);
    ASSERT_TRUE(iter1 == initialPos);
    list.insert(iter, 4);
    ASSERT_TRUE(iter == initialPos);
    ASSERT_TRUE(list.size() == 3);
    iter1 = list.begin();
    iter = iter1;
    ++iter;
    ASSERT_FALSE(iter == iter1);
}

TEST(test_list_compile_check)
{
    List<int> my_list;

    int size = 0;
    my_list.empty();
    my_list.size();
    ASSERT_TRUE(my_list.size() == size);

    my_list.push_front(42);
    my_list.push_back(42);

    my_list.front() = 73;
    my_list.back() = 73;
    ASSERT_TRUE(my_list.front() == 73);
    ASSERT_TRUE(my_list.back() == 73);

    my_list.pop_front();
    my_list.pop_back();

    List<int> list2(my_list);
    list2 = my_list;
    List<int>::Iterator iter = my_list.begin();
    my_list.insert(iter, 42);
    iter = my_list.begin();
    my_list.erase(iter);
    iter = my_list.begin();

    List<int>::Iterator iter2 = my_list.end();
    const List<int>::Iterator iter3 = iter2;

    bool b = iter == iter2;
    ASSERT_TRUE(b);
    b = iter3 == my_list.end();
    ASSERT_TRUE(b);
    b = my_list.end() == iter3;
    ASSERT_TRUE(b);
    my_list.push_front(42);
    my_list.push_back(42);
    iter = my_list.begin();
    b = iter != iter2;
    ASSERT_TRUE(b);
    b = iter3 != my_list.end();
    ASSERT_FALSE(b);
    b = my_list.end() != iter3;
    ASSERT_TRUE(b == 0);
    ++iter;

    ASSERT_TRUE(*iter == 42);

    List<int>::Iterator iter_cpy(iter);
    iter_cpy = iter;

    ASSERT_TRUE(*++--iter == 42);
    ASSERT_TRUE(*--++my_list.begin() == 42);

    my_list.insert(my_list.begin(), 3);
    my_list.erase(my_list.begin());
    ASSERT_TRUE(my_list.front() == 42);

    List<int> list3;
    list3.push_back(3);
    ASSERT_TRUE(*list3.begin() == 3);

    List<int> list4;
    list4.push_back(4);
    ASSERT_TRUE(list4.size() == 1);

    my_list.clear();
}
TEST_MAIN()
