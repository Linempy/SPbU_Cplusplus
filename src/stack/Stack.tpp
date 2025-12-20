#ifndef STACKANDQUEUE_STACK_TPP
#define STACKANDQUEUE_STACK_TPP

#include "../../include/Stack.h"
#include "../../include/Queue.h"

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
    clear();

    for (auto it = collection.begin(); it != collection.end(); ++it) {
        push(*it);
    }

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
typename Stack<T>::Iterator Stack<T>::begin() {
    return Iterator(new StackIterator(top));
}

template<typename T>
typename Stack<T>::Iterator Stack<T>::end() {
    return Iterator(new StackIterator(nullptr));
}

template<typename T>
typename Stack<T>::ConstIterator Stack<T>::begin() const {
    return ConstIterator(new StackConstIterator(top));
}

template<typename T>
typename Stack<T>::ConstIterator Stack<T>::end() const {
    return ConstIterator(new StackConstIterator(nullptr));
}

template<typename T>
typename Stack<T>::ConstIterator Stack<T>::cbegin() const {
    return ConstIterator(new StackConstIterator(top));
}

template<typename T>
typename Stack<T>::ConstIterator Stack<T>::cend() const {
    return ConstIterator(new StackConstIterator(nullptr));
}

template<typename T>
T &Stack<T>::StackIterator::operator*() {
    return current->getValue();
}

template<typename T>
T* Stack<T>::StackIterator::operator->() {
    return &current->getValue();
}

template<typename T>
Stack<T>::StackIterator &Stack<T>::StackIterator::operator++() {
    if (current) {
        current = current->getNextNode();
    }
    return *this;
}

template<typename T>
bool Stack<T>::StackIterator::operator!=(const Collection<T>::IteratorBase& other) const {
    return !(*this == other);
}

template<typename T>
bool Stack<T>::StackIterator::operator==(const Collection<T>::IteratorBase& other) const {
    if (typeid(other) != typeid(StackIterator)) return false;
    const StackIterator* derived = static_cast<const StackIterator*>(&other);
    return current == derived->current;
}

template<typename T>
bool Stack<T>::StackIterator::operator==(const typename Collection<T>::ConstIteratorBase& other) const {
    if (typeid(other) != typeid(StackConstIterator)) return false;
    const StackConstIterator* derived = static_cast<const StackConstIterator*>(&other);
    return current == derived->current;
}

template<typename T>
bool Stack<T>::StackIterator::operator!=(const typename Collection<T>::ConstIteratorBase& other) const {
    return !(*this == other);

}

template<typename T>
typename Collection<T>::IteratorBase* Stack<T>::StackIterator::clone() const {
    return new StackIterator(current);
}

template<typename T>
Collection<T>::ConstIteratorBase* Stack<T>::StackConstIterator::clone() const {
    return new StackConstIterator(current);
}

template<typename T>
const T &Stack<T>::StackConstIterator::operator*() const {
    return current->getValue();
}

template<typename T>
const T* Stack<T>::StackConstIterator::operator->() const {
    return &current->getValue();
}

template<typename T>
typename Stack<T>::StackConstIterator &Stack<T>::StackConstIterator::operator++() {
    if (current) {
        current = current->getNextNode();
    }
    return *this;
}

template<typename T>
bool Stack<T>::StackConstIterator::operator!=(const Collection<T>::ConstIteratorBase& other) const {
    return !(*this == other);
}

template<typename T>
bool Stack<T>::StackConstIterator::operator==(const Collection<T>::ConstIteratorBase& other) const {
    if (typeid(other) != typeid(StackConstIterator)) return false;
    const StackConstIterator* derived = static_cast<const StackConstIterator*>(&other);
    return current == derived->current;
}

template<typename T>
bool Stack<T>::StackConstIterator::operator==(const typename Collection<T>::IteratorBase& other) const {
    if (typeid(other) != typeid(StackIterator)) return false;
    const StackIterator* derived = static_cast<const StackIterator*>(&other);
    return current == derived->current;
}

template<typename T>
bool Stack<T>::StackConstIterator::operator!=(const typename Collection<T>::IteratorBase& other) const {
    return !(*this == other);

}

#endif //STACKANDQUEUE_STACK_TPP
