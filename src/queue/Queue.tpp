#ifndef STACKANDQUEUE_QUEUE_TPP
#define STACKANDQUEUE_QUEUE_TPP

#include "Queue.h"

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue) {
    if (this == &queue) {
        return *this;
    }

    clear();

    if (queue.isEmpty()) {
        return *this;
    }

    begin = new Node(queue.begin->getValue());
    Node<T>* current = begin;
    Node<T>* currentQueue = queue.begin->getNextNode();

    while (currentQueue != nullptr) {
        current->setNextNode(new Node(currentQueue->getValue()));
        current = current->getNextNode();
        currentQueue = currentQueue->getNextNode();
    }

    end = current;
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& queue) {
    if (this == &queue) {
        return *this;
    }

    clear();

    if (queue.isEmpty()) {
        return *this;
    }

    begin = queue.begin;
    end = queue.end;

    queue.begin = nullptr;
    queue.end = nullptr;

    return *this;
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return begin == nullptr;
}

template<typename T>
T Queue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Очередь пуста. Невозможно удалить элемент");
    }

    T value = begin->getValue();
    Node<T>* temp = begin;
    begin = begin->getNextNode();

    if (begin == nullptr) {
        end = nullptr;
    }

    delete temp;
    return value;
}

template<typename T>
void Queue<T>::push(const T &value) {
    Node<T>* newNode = new Node(value);
    if (isEmpty()) {
        begin = newNode;
        end = newNode;
    } else {
        end->setNextNode(newNode);
        end = newNode;
    }
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
    Node<T>* currentNode = queue.begin;
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
std::istream& operator>>(std::istream& is, Queue<T>& queue) {
    queue.clear();
    T value;
    while (is >> value) {
        queue.push(value);
    }

    if (is.eof()) {
        is.clear();
    }

    return is;
}

template<typename T>
void Queue<T>::clear() {
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
size_t Queue<T>::getSize() const{
    Node<T>* currentNode = begin;
    size_t count = 0;
    while (currentNode != nullptr) {
        currentNode = currentNode->getNextNode();
        count++;
    }

    return count;
}

#endif //STACKANDQUEUE_QUEUE_TPP
