#include <iostream>
#include "../include/Stack.h"

int main() {
    Stack<int> stack1 = Stack<int>(new Node<int>(4, new Node<int>(5)));

    for (auto node : stack1) {
        std::cout << node;
    }

    for (auto node : stack1) {
        std::cout << node;
    }



    return 0;
}