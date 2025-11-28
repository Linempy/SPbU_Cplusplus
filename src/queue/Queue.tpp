#ifndef STACKANDQUEUE_QUEUE_TPP
#define STACKANDQUEUE_QUEUE_TPP

#include "../../include/Queue.h"

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue) {
    if (this == &queue) {
        return *this;
    }

    clear();

    if (queue.isEmpty()) {
        return *this;
    }

    _begin = new Node(queue._begin->getValue());
    Node<T>* current = _begin;
    Node<T>* currentQueue = queue._begin->getNextNode();

    while (currentQueue != nullptr) {
        current->setNextNode(new Node(currentQueue->getValue()));
        current = current->getNextNode();
        currentQueue = currentQueue->getNextNode();
    }

    _end = current;
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

    _begin = queue._begin;
    _end = queue._end;

    queue._begin = nullptr;
    queue._end = nullptr;

    return *this;
}


template<typename T>
Queue<T>& Queue<T>::operator=(const Collection<T>& collection) {
    clear();

    for (auto it = collection.begin(); it != collection.end(); ++it) {
        push(*it);
    }

    return *this;
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return _begin == nullptr;
}

template<typename T>
T Queue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Очередь пуста. Невозможно удалить элемент");
    }

    T value = _begin->getValue();
    Node<T>* temp = _begin;
    _begin = _begin->getNextNode();

    if (_begin == nullptr) {
        _end = nullptr;
    }

    delete temp;
    return value;
}

template<typename T>
void Queue<T>::push(const T &value) {
    Node<T>* newNode = new Node(value);
    if (isEmpty()) {
        _begin = newNode;
        _end = newNode;
    } else {
        _end->setNextNode(newNode);
        _end = newNode;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
    Node<T>* currentNode = queue._begin;
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
    Node<T>* currentNode = _begin;
    size_t count = 0;
    while (currentNode != nullptr) {
        currentNode = currentNode->getNextNode();
        count++;
    }

    return count;
}


template<typename T>
void Queue<T>::push(T&& value) {
    Node<T>* newNode = new Node<T>(std::move(value));
    if (isEmpty()) {
        _begin = newNode;
        _end = newNode;
    } else {
        _end->setNextNode(newNode);
        _end = newNode;
    }
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::begin() {
    return Iterator(new QueueIterator(_begin));
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::end() {
    return Iterator(new QueueIterator(nullptr));
}

template<typename T>
typename Queue<T>::ConstIterator Queue<T>::begin() const {
    return ConstIterator(new QueueConstIterator(_begin));
}

template<typename T>
typename Queue<T>::ConstIterator Queue<T>::end() const {
    return ConstIterator(new QueueConstIterator(nullptr));
}

template<typename T>
typename Queue<T>::ConstIterator Queue<T>::cbegin() const {
    return ConstIterator(new QueueConstIterator(_begin));
}

template<typename T>
typename Queue<T>::ConstIterator Queue<T>::cend() const {
    return ConstIterator(new QueueConstIterator(nullptr));
}

template<typename T>
T& Queue<T>::QueueIterator::operator*() {
    return current->getValue();
}

template<typename T>
T* Queue<T>::QueueIterator::operator->() {
    return &current->getValue();
}

template<typename T>
Queue<T>::QueueIterator &Queue<T>::QueueIterator::operator++() {
    if (current) {
        current = current->getNextNode();
    }
    return *this;
}

template<typename T>
bool Queue<T>::QueueIterator::operator!=(const Collection<T>::IteratorBase &other) const {
    return !(*this == other);
}

template<typename T>
bool Queue<T>::QueueIterator::operator==(const Collection<T>::IteratorBase &other) const {
    auto* otherIter = dynamic_cast<const QueueIterator*>(&other);
    return otherIter && current == otherIter->current;
}

template<typename T>
bool Queue<T>::QueueIterator::operator!=(const Collection<T>::ConstIteratorBase &other) const {
    return !(*this == other);
}

template<typename T>
bool Queue<T>::QueueIterator::operator==(const Collection<T>::ConstIteratorBase &other) const {
    auto* otherIter = dynamic_cast<const QueueConstIterator*>(&other);
    return otherIter && current == otherIter->current;
}

template<typename T>
typename Collection<T>::IteratorBase* Queue<T>::QueueIterator::clone() const {
    return new QueueIterator(current);
}

template<typename T>
const T &Queue<T>::QueueConstIterator::operator*() const {
    if (!current) {
        throw std::runtime_error("Разыменование null const итератора");
    }
    return current->getValue();
}

template<typename T>
const T* Queue<T>::QueueConstIterator::operator->() const {
    return &current->getValue();
}

template<typename T>
Queue<T>::QueueConstIterator &Queue<T>::QueueConstIterator::operator++() {
    if (current) {
        current = current->getNextNode();
    }
    return *this;
}

template<typename T>
bool Queue<T>::QueueConstIterator::operator!=(const Collection<T>::ConstIteratorBase& other) const {
    return !(*this == other);
}

template<typename T>
bool Queue<T>::QueueConstIterator::operator==(const Collection<T>::ConstIteratorBase& other) const {
    auto* otherIter = dynamic_cast<const QueueConstIterator*>(&other);
    return otherIter && current == otherIter->current;
}

template<typename T>
bool Queue<T>::QueueConstIterator::operator!=(const Collection<T>::IteratorBase& other) const {
    return !(*this == other);

}

template<typename T>
bool Queue<T>::QueueConstIterator::operator==(const Collection<T>::IteratorBase& other) const {
    auto* otherIter = dynamic_cast<const QueueIterator*>(&other);
    return otherIter && current == otherIter->current;
}

template<typename T>
typename Collection<T>::ConstIteratorBase* Queue<T>::QueueConstIterator::clone() const {
    return new QueueConstIterator(current);
}



#endif //STACKANDQUEUE_QUEUE_TPP
