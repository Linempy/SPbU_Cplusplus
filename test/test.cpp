#include "../src/stack/Stack.tpp"
#include "../src/queue/Queue.tpp"

#include "gtest/gtest.h"

TEST(StackTest, StackIterator)
{
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    // Константный итератор
    Stack<int>::ConstIterator cit = s.cbegin(), ocit;
    EXPECT_EQ(*cit, 30);
    ocit = ++cit;
    EXPECT_EQ(*cit, 20);
    EXPECT_EQ(*ocit, 20);
    ocit = cit++;
    EXPECT_EQ(*cit, 10);
    EXPECT_EQ(*ocit, 20);
    ++cit;
    EXPECT_EQ(cit, s.cend());

    // Константная ссылка
    const Stack<int>& r = s;
    cit = r.begin();
    EXPECT_EQ(*cit, 30);
    ++cit;
    EXPECT_EQ(*cit, 20);
    cit++;
    EXPECT_EQ(*cit, 10);
    ++cit;
    EXPECT_EQ(cit, r.end());

    // Неконстантный итератор
    Stack<int>::Iterator it = s.begin(), oit;
    EXPECT_EQ(*it, 30);
    oit = ++it;
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*oit, 20);
    oit = it++;
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*oit, 20);
    *oit = 5;
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*oit, 5);
    ++it;
    EXPECT_EQ(it, s.end());

    std::stringstream sout;
    sout << s;
    EXPECT_EQ(sout.str(), "[ 30, 5, 10 ]\n");
}

TEST(StackTest, Stack_For)
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);  // верх = 3

    const Stack<int>& r = s;
    int expected1[] = {3, 2, 1};
    int idx = 0;
    for (auto& v : r) EXPECT_EQ(v, expected1[idx++]);

    int expected2[] = {6, 4, 2};
    idx = 0;
    for (auto& v : s) v *= 2;

    idx = 0;
    for (const auto& v : s) {
        EXPECT_EQ(v, expected2[idx++]);
    }

    int expected3[] = {7, 5, 3};

    for (Stack<int>::Iterator it = s.begin(); it != s.end(); ++it) {
        *it += 1;
    }
    idx = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        EXPECT_EQ(*it, expected3[idx++]);
    }
    idx = 0;
    for (Stack<int>::ConstIterator it = r.begin(); it != r.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);

    idx = 0;
    for (Stack<int>::ConstIterator it = s.cbegin(); it != s.cend(); ++it) {
        EXPECT_EQ(*it, expected3[idx++]);
    }

}

TEST(StackTest, Stack_PushPopCopy)
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    s.pop();
    s.push(10);
    s.push(20);

    Stack<int> copy_s(s);

    int expected_orig[] = {20, 10, 2, 1};
    int idx = 0;
    for (auto v : copy_s) EXPECT_EQ(v, expected_orig[idx++]);

    copy_s.pop();
    copy_s.pop();
    copy_s.push(99);
    copy_s.push(98);
    copy_s.push(97);

    idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy[] = {97, 98, 99, 2, 1};
    idx = 0;
    for (auto v : copy_s) EXPECT_EQ(v, expected_copy[idx++]);

    Stack<int> moved_s(std::move(copy_s));

    int expected_moved[] = {97, 98, 99, 2, 1};
    idx = 0;
    for (auto v : moved_s) EXPECT_EQ(v, expected_moved[idx++]);

    EXPECT_TRUE(copy_s.isEmpty());

    Stack<int> s2;
    s2 = s;
    idx = 0;
    for (auto v : s2) EXPECT_EQ(v, expected_orig[idx++]);

    s2.pop();
    s2.push(42);
    s2.push(99);

    idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy_asgn[] = {99, 42, 10, 2, 1};
    idx = 0;
    for (auto v : s2) EXPECT_EQ(v, expected_copy_asgn[idx++]);


    Stack<int> s3;
    s3 = std::move(s2);
    idx = 0;
    for (auto v : s3) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    EXPECT_TRUE(s2.isEmpty());

    s3.pop();
    s3.push(77);
    int expected_final[] = {77, 42, 10, 2, 1};
    idx = 0;
    for (auto v : s3) EXPECT_EQ(v, expected_final[idx++]);
}

TEST(StackTest, Stack_IO)
{
    Stack<int> s;
    s.push(0);

    std::stringstream sin("1 2 3 4 5");
    sin >> s;

    // Проверим размер
    EXPECT_EQ(s.getSize(), 6);

    int expected[] = {5, 4, 3, 2, 1, 0};
    int idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected[idx++]);

    std::stringstream sout;
    sout << s;

    std::string expected_str = "[ 5, 4, 3, 2, 1, 0 ]\n";
    EXPECT_EQ(sout.str(), expected_str);

    for (auto& v : s) v += 10;  // увеличим каждый элемент на 10

    std::stringstream sout2;
    sout2 << s;
    std::string expected_str2 = "[ 15, 14, 13, 12, 11, 10 ]\n";
    EXPECT_EQ(sout2.str(), expected_str2);
}

TEST(StackTest, Stack_Algs)
{
    Stack<int> s;

    for (int i = 1; i <= 5; ++i) s.push(i);

    auto it = std::find_if(s.begin(), s.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(*it, 4);
    *it = 3;

    const Stack<int>& r = s;
    auto cit = std::find_if(r.begin(), r.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(*cit, 2);

    it = std::find_if(s.begin(), s.end(), [](int v){ return v == 0; });
    EXPECT_EQ(it, s.end());

    auto count_even = std::count_if(s.begin(), s.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(count_even, 1);

    std::replace_if(s.begin(), s.end(), [](int v){ return v % 2 != 0; }, 99);
    int expected_replace[] = {99, 99, 99, 2, 99};
    int idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_replace[idx++]);

    std::for_each(s.begin(), s.end(), [](int& v){ v += 1; });
    int expected_for_each[] = {100, 100, 100, 3, 100};
    idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_for_each[idx++]);
}

TEST(ContainerTest, BaseContainer)
{
    Stack<int> s;
    Queue<int> q;

    // Наполним контейнеры
    s.push(1);
    s.push(2);
    s.push(3);
    q.push(10);
    q.push(20);
    q.push(30);

    Collection<int>& bs = s;
    Collection<int>& bq = q;
    const Collection<int>& cs = s;



    int expected_s_after[] = {3, 2, 1};
    int idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_s_after[idx++]);

    bq = s;
    int expected_q_after[] = {3, 2, 1};
    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_q_after[idx++]);

    idx = 0;
    for (auto& it : bs) EXPECT_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (const auto& it : bs) EXPECT_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (auto& it : cs) EXPECT_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (auto& it : bq) EXPECT_EQ(it, expected_q_after[idx++]);

    idx = 0;
    for (const auto& it : bq) EXPECT_EQ(it, expected_q_after[idx++]);
        
    idx = 0;
    for (auto& it : bq) EXPECT_EQ(it, expected_q_after[idx++]);

}


TEST(QueueTest, QueueIterator)
{
    Queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    // Константный итератор
    Queue<int>::ConstIterator cit = q.cbegin(), ocit;
    EXPECT_EQ(*cit, 10);  // В очереди первый элемент
    ocit = ++cit;
    EXPECT_EQ(*cit, 20);
    EXPECT_EQ(*ocit, 20);
    ocit = cit++;
    EXPECT_EQ(*cit, 30);
    EXPECT_EQ(*ocit, 20);
    ++cit;
    EXPECT_EQ(cit, q.cend());

    // Константная ссылка
    const Queue<int>& r = q;
    cit = r.begin();
    EXPECT_EQ(*cit, 10);
    ++cit;
    EXPECT_EQ(*cit, 20);
    cit++;
    EXPECT_EQ(*cit, 30);
    ++cit;
    EXPECT_EQ(cit, r.end());

    // Неконстантный итератор
    Queue<int>::Iterator it = q.begin(), oit;
    EXPECT_EQ(*it, 10);
    oit = ++it;
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*oit, 20);
    oit = it++;
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(*oit, 20);
    *oit = 5;
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(*oit, 5);
    ++it;
    EXPECT_EQ(it, q.end());

    std::stringstream sout;
    sout << q;
    EXPECT_EQ(sout.str(), "[ 10, 5, 30 ]\n");
}

TEST(QueueTest, Queue_For)
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);  // первый = 1

    const Queue<int>& r = q;
    int expected1[] = {1, 2, 3};
    int idx = 0;
    for (auto& v : r) EXPECT_EQ(v, expected1[idx++]);

    int expected2[] = {2, 4, 6};
    idx = 0;
    for (auto& v : q) v *= 2;

    idx = 0;
    for (const auto& v : q) {
        EXPECT_EQ(v, expected2[idx++]);
    }

    int expected3[] = {3, 5, 7};

    for (Queue<int>::Iterator it = q.begin(); it != q.end(); ++it) {
        *it += 1;
    }
    idx = 0;
    for (auto it = q.begin(); it != q.end(); ++it) {
        EXPECT_EQ(*it, expected3[idx++]);
    }
    idx = 0;
    for (Queue<int>::ConstIterator it = r.begin(); it != r.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);

    idx = 0;
    for (Queue<int>::ConstIterator it = q.cbegin(); it != q.cend(); ++it) {
        EXPECT_EQ(*it, expected3[idx++]);
    }
}

TEST(QueueTest, Queue_PushPopCopy)
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    q.pop();  // удаляем 1
    q.push(10);
    q.push(20);

    Queue<int> copy_q(q);

    int expected_orig[] = {2, 3, 10, 20};
    int idx = 0;
    for (auto v : copy_q) EXPECT_EQ(v, expected_orig[idx++]);

    copy_q.pop();  // удаляем 2
    copy_q.pop();  // удаляем 3
    copy_q.push(99);
    copy_q.push(98);
    copy_q.push(97);

    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy[] = {10, 20, 99, 98, 97};
    idx = 0;
    for (auto v : copy_q) EXPECT_EQ(v, expected_copy[idx++]);

    Queue<int> moved_q(std::move(copy_q));

    int expected_moved[] = {10, 20, 99, 98, 97};
    idx = 0;
    for (auto v : moved_q) EXPECT_EQ(v, expected_moved[idx++]);

    EXPECT_TRUE(copy_q.isEmpty());

    Queue<int> q2;
    q2 = q;
    idx = 0;
    for (auto v : q2) EXPECT_EQ(v, expected_orig[idx++]);

    q2.pop();  // удаляем 2
    q2.push(42);
    q2.push(99);

    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy_asgn[] = {3, 10, 20, 42, 99};
    idx = 0;
    for (auto v : q2) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    Queue<int> q3;
    q3 = std::move(q2);
    idx = 0;
    for (auto v : q3) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    EXPECT_TRUE(q2.isEmpty());

    q3.pop();  // удаляем 3
    q3.push(77);
    int expected_final[] = {10, 20, 42, 99, 77};
    idx = 0;
    for (auto v : q3) EXPECT_EQ(v, expected_final[idx++]);
}

TEST(QueueTest, Queue_IO)
{
    Queue<int> q;
    q.push(0);

    std::stringstream sin("1 2 3 4 5");
    sin >> q;

    EXPECT_EQ(q.getSize(), 6);

    int expected[] = {0, 1, 2, 3, 4, 5};
    int idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected[idx++]);

    std::stringstream sout;
    sout << q;

    std::string expected_str = "[ 0, 1, 2, 3, 4, 5 ]\n";
    EXPECT_EQ(sout.str(), expected_str);

    for (auto& v : q) v += 10;  // увеличим каждый элемент на 10

    std::stringstream sout2;
    sout2 << q;
    std::string expected_str2 = "[ 10, 11, 12, 13, 14, 15 ]\n";
    EXPECT_EQ(sout2.str(), expected_str2);
}

TEST(QueueAlgs, SimpleAlgorithms)
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    auto even_it = std::find_if(q.begin(), q.end(),
                                [](int x) { return x % 2 == 0; });
    EXPECT_NE(even_it, q.end());
    EXPECT_EQ(*even_it, 2);

    int even_count = std::count_if(q.begin(), q.end(),
                                   [](int x) { return x % 2 == 0; });
    EXPECT_EQ(even_count, 2);

    auto three_it = std::find(q.begin(), q.end(), 3);
    EXPECT_NE(three_it, q.end());
    EXPECT_EQ(*three_it, 3);
}

TEST(QueueTest, Queue_EdgeCases)
{
    Queue<int> q;

    // Тест пустой очереди
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.getSize(), 0);
    EXPECT_EQ(q.begin(), q.end());

    // Тест одного элемента
    q.push(42);
    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.getSize(), 1);
    EXPECT_EQ(*q.begin(), 42);
    EXPECT_EQ(q.getFront(), 42);

    // Тест pop на одном элементе
    int val = q.pop();
    EXPECT_EQ(val, 42);
    EXPECT_TRUE(q.isEmpty());

    // Тест clear
    for (int i = 0; i < 5; ++i) q.push(i);
    EXPECT_EQ(q.getSize(), 5);
    q.clear();
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.getSize(), 0);

    // Тест перемещения семантики
    q.push(1);
    q.push(2);
    q.push(3);

    Queue<int> q2 = std::move(q);
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q2.getSize(), 3);

    int expected[] = {1, 2, 3};
    int idx = 0;
    for (auto v : q2) EXPECT_EQ(v, expected[idx++]);
}

TEST(QueueTest, Queue_GetFront)
{
    Queue<int> q;

    q.push(10);
    EXPECT_EQ(q.getFront(), 10);

    q.push(20);
    EXPECT_EQ(q.getFront(), 10);

    q.pop();
    EXPECT_EQ(q.getFront(), 20);

    const Queue<int>& const_q = q;
    EXPECT_EQ(const_q.getFront(), 20);
}

TEST(QueueTest, Queue_MovePush)
{
    Queue<std::string> q;

    std::string str1 = "Hello";
    std::string str2 = "World";

    q.push(std::move(str1));
    q.push(std::move(str2));

    EXPECT_TRUE(str1.empty());
    EXPECT_TRUE(str2.empty());

    EXPECT_EQ(q.getFront(), "Hello");
    q.pop();
    EXPECT_EQ(q.getFront(), "World");
}

TEST(QueueTest, Queue_Assignment)
{
    Queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    Queue<int> q2;
    q2.push(4);
    q2.push(5);

    q2 = q1;

    EXPECT_EQ(q2.getSize(), 3);

    int expected[] = {1, 2, 3};
    int idx = 0;
    for (auto v : q2) EXPECT_EQ(v, expected[idx++]);

    q2.pop();
    q2.push(99);

    idx = 0;
    for (auto v : q1) EXPECT_EQ(v, expected[idx++]);  // q1 не изменился
}

// Тест для проверки работы через базовый класс Collection
TEST(QueueCollectionTest, BaseCollectionInterface)
{
    Queue<int> q;
    Collection<int>& collection = q;

    collection.push(1);
    collection.push(2);
    collection.push(3);

    EXPECT_EQ(collection.getSize(), 3);
    EXPECT_FALSE(collection.isEmpty());
    EXPECT_EQ(collection.getFront(), 1);

    int val = collection.pop();
    EXPECT_EQ(val, 1);
    EXPECT_EQ(collection.getSize(), 2);

    int expected[] = {2, 3};
    int idx = 0;
    for (auto it = collection.begin(); it != collection.end(); ++it) {
        EXPECT_EQ(*it, expected[idx++]);
    }
}

TEST(QueueTest, Queue_StreamEmpty)
{
    Queue<int> q;
    std::stringstream sout;
    sout << q;
    EXPECT_EQ(sout.str(), "[  ]\n");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

