#ifndef STACKANDQUEUE_STACK_TPP
#define STACKANDQUEUE_STACK_TPP

#include "Stack.h"

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack) {
    if (this == &stack) {
        return *this;
    }

    clear();

    if (stack.isEmpty()) {
        return *this;
    }

    top = new Node<T>(stack.top->getValue());
    Node<T>* current = top;
    Node<T>* currentNodeStack = stack.top->getNextNode();

    while (currentNodeStack != nullptr) {
        current->setNextNode(new Node(currentNodeStack->getValue()));
        current = current->getNextNode();
        currentNodeStack = currentNodeStack->getNextNode();
    }

    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& stack) {
    if (this == &stack) {
        return *this;
    }

    clear();

    if (stack.isEmpty()) {
        return *this;
    }

    top = stack.top;
    stack.top = nullptr;

    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Collection<T>& collection) {
    const auto* other = dynamic_cast<const Stack<T>*>(&collection);
    if (!other) {
        throw std::invalid_argument("Нельзя привести данный тип к Stack");
    }
    *this = *other;
    return *this;
}

template<typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Стек пуст. Невозможно удалить элемент");
    }

    T value = this->top->getValue();
    Node<T>* temp = this->top;
    this->top = this->top->getNextNode();
    delete temp;
    return value;
}

template<typename T>
void Stack<T>::push(const T& value) {
    top = new Node(value, top);
}

template<typename T>
void Stack<T>::push(T&& value) {
    top = new Node(std::move(value), top);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    Node<T>* currentNode = stack.top;
    os << "[ ";
    while (currentNode != nullptr) {
        os  << currentNode->getValue();
        currentNode = currentNode->getNextNode();
        if (currentNode != nullptr) {
            os << ", ";
        }
    }
    os  << " ]\n";

    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Stack<T>& stack) {
    stack.clear();
    T value;
    while (is >> value) {
        stack.push(value);
    }

    if (is.eof()) {
        is.clear();
    }

    return is;
}

template<typename T>
size_t Stack<T>::getSize() const{
    Node<T>* currentNode = top;
    size_t count = 0;
    while (currentNode != nullptr) {
        count++;
        currentNode = currentNode->getNextNode();
    }
    return count;
}

template<typename T>
void Stack<T>::clear() {
    while(!isEmpty()) {
        pop();
    }
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

template<typename T>
void Stack<T>::print(std::ostream &os) const {
    os << *this;
}

#endif //STACKANDQUEUE_STACK_TPP
