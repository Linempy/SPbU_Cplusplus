#include <iostream>
#include <sstream>
#include "src/stack/Stack.h"
#include "src/queue/Queue.h"

int main() {

    Stack<int> myFirstStack = Stack<int>();
    Stack<int> mySecondStack = Stack<int>(new Node(5, new Node(2)));

    std::cout << mySecondStack;

    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    std::cout << stack;

    stack.pop();
    std::cout << stack;
    stack.pop();
    std::cout << stack;
    try {
        stack.pop();
    } catch (std::runtime_error e) {
        std::cout << "Кажется произошла ошибка удаления элемента из стека\n";
    }

    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);

    Stack<int> stack2 = stack1;
    std::cout << stack2.getSize() << '\n' << stack1.getSize();

    Stack<int> stack3;
    stack3.push(5);
    stack3.push(6);

    Stack<int> stack4;
    stack4 = stack3;
    std::cout << stack4;

    Stack<int> stack5 = Stack<int>{new Node(4, new Node(5))};
    std::cout << stack5;

    Stack<int> stackIs;
    std::istringstream iss("10 20 30");
    iss >> stack;
    std::cout << stack;


    Queue<int> myFirstQueue = Queue<int>{};
    std::cout << myFirstQueue;

    Queue<int> mySecondQueue;
    mySecondQueue.push(1);
    mySecondQueue.push(2);
    mySecondQueue.push(3);
    std::cout << mySecondQueue;

    Queue<int> queue3;
    queue3.push(10);
    queue3.push(20);
    queue3.push(30);
    std::cout << queue3;

    Queue<int> queue4;
    queue4.push(1);
    queue4.push(2);

    Queue<int> queue5 = queue4;
    std::cout << queue5;
    std::cout << queue4;

    Queue<int> queue6;
    queue6 = queue4;
    std::cout << queue6;
    std::cout << queue4;

    Queue<int> queue7;
    queue7.push(7);
    queue7.push(8);

    Queue<int> queue8 = std::move(queue7);
    std::cout << queue7;
    std::cout << queue8;

    queue8.clear();
    std::cout << queue8;

    Queue<int> queueError;

    try {
        queueError.pop();
    } catch (const std::runtime_error& e) {
        std::cout << "Ошибочка";
    }

    stack1.print(std::cout);

    return 0;
}

