#ifndef COLLECTION_TPP
#define COLLECTION_TPP

#include "../include/Collection.h"

template<typename T>
Collection<T>::Iterator::Iterator() : iterator(nullptr) {}

template<typename T>
Collection<T>::Iterator::Iterator(IteratorBase* iterator) : iterator(iterator) {}

template<typename T>
Collection<T>::Iterator::Iterator(const Iterator& other) : iterator(other.iterator ? other.iterator->clone() : nullptr) {}

template<typename T>
Collection<T>::Iterator::Iterator(Iterator&& other) : iterator(other.iterator) {
    other.iterator = nullptr;
}

template<typename T>
Collection<T>::Iterator::Iterator(const ConstIterator& other)
        : iterator(other.iterator ? dynamic_cast<IteratorBase*>(other.iterator->clone()) : nullptr) {}

template<typename T>
Collection<T>::Iterator::~Iterator() {
    delete iterator;
}

template<typename T>
typename Collection<T>::Iterator& Collection<T>::Iterator::operator=(const Iterator& other) {
    if (this != &other) {
        delete iterator;
        iterator = other.iterator ? other.iterator->clone() : nullptr;
    }
    return *this;
}

template<typename T>
typename Collection<T>::Iterator& Collection<T>::Iterator::operator=(Iterator&& other) {
    if (this != &other) {
        delete iterator;
        iterator = other.iterator;
        other.iterator = nullptr;
    }
    return *this;
}

template<typename T>
typename Collection<T>::Iterator& Collection<T>::Iterator::operator=(const ConstIterator& other) {
    if (this != &other) {
        delete iterator;
        iterator = other.iterator ? dynamic_cast<IteratorBase*>(other.iterator->clone()) : nullptr;
    }
    return *this;
}

template<typename T>
typename Collection<T>::Iterator::reference Collection<T>::Iterator::operator*() {
    Iterator::checkOnNullIterator();
    return iterator->operator*();
}

template<typename T>
typename Collection<T>::Iterator::pointer Collection<T>::Iterator::operator->() {
    Iterator::checkOnNullIterator();
    return iterator->operator->();
}

template<typename T>
typename Collection<T>::Iterator& Collection<T>::Iterator::operator++() {
    if (iterator) iterator->operator++();
    return *this;
}

template<typename T>
typename Collection<T>::Iterator Collection<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    if (iterator) iterator->operator++();
    return temp;
}

template<typename T>
bool Collection<T>::Iterator::operator==(const Iterator& other) const {
    if (!iterator && !other.iterator) return true;
    if (!iterator || !other.iterator) return false;
    return iterator->operator==(*other.iterator);
}

template<typename T>
bool Collection<T>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

template<typename T>
bool Collection<T>::Iterator::operator==(const ConstIterator& other) const {
    if (!iterator && !other.iterator) return true;
    if (!iterator || !other.iterator) return false;
    return iterator->operator==(*other.iterator);
}

template<typename T>
bool Collection<T>::Iterator::operator!=(const ConstIterator& other) const {
    return !(*this == other);
}

template<typename T>
Collection<T>::ConstIterator::ConstIterator() : iterator(nullptr) {}

template<typename T>
Collection<T>::ConstIterator::ConstIterator(ConstIteratorBase* iterator) : iterator(iterator) {}

template<typename T>
Collection<T>::ConstIterator::ConstIterator(const ConstIterator& other)
        : iterator(other.iterator ? other.iterator->clone() : nullptr) {}

template<typename T>
Collection<T>::ConstIterator::ConstIterator(ConstIterator&& other) : iterator(other.iterator) {
    other.iterator = nullptr;
}

template<typename T>
Collection<T>::ConstIterator::ConstIterator(const Iterator& other)
        : iterator(other.iterator ? other.iterator->clone() : nullptr) {}

        // присваивание обычное. ПРобросить в base

template<typename T>
Collection<T>::ConstIterator::~ConstIterator() {
    delete iterator;
}

template<typename T>
typename Collection<T>::ConstIterator& Collection<T> ::ConstIterator::operator=(const ConstIterator& other) {
    if (this != &other) {
        delete iterator;
        iterator = other.iterator ? other.iterator->clone() : nullptr;
    }
    return *this;
}

template<typename T>
typename Collection<T>::ConstIterator& Collection<T> ::ConstIterator::operator=(ConstIterator&& other) {
    if (this != &other) {
        delete iterator;
        iterator = other.iterator;
        other.iterator = nullptr;
    }
    return *this;
}

template<typename T>
typename Collection<T>::ConstIterator& Collection<T> ::ConstIterator::operator=(const Iterator& other) {
    if (this != &other) {
        delete iterator;
        iterator = other.iterator ? dynamic_cast<ConstIteratorBase*>(other.iterator->clone()) : nullptr;
    }
    return *this;
}

template<typename T>
typename Collection<T>::ConstIterator::reference Collection<T> ::ConstIterator::operator*() const {
    ConstIterator::checkOnNullConstIterator();
    return iterator->operator*();
}

template<typename T>
typename Collection<T>::ConstIterator::pointer Collection<T> ::ConstIterator::operator->() const {
    ConstIterator::checkOnNullConstIterator();
    return iterator->operator->();
}

template<typename T>
typename Collection<T>::ConstIterator& Collection<T> ::ConstIterator::operator++() {
    if (iterator) iterator->operator++();
    return *this;
}

template<typename T>
typename Collection<T>::ConstIterator Collection<T> ::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    if (iterator) iterator->operator++();
    return temp;
}

template<typename T>
bool Collection<T>::ConstIterator::operator==(const ConstIterator& other) const {
    if (!iterator && !other.iterator) return true;
    if (!iterator || !other.iterator) return false;
    return iterator->operator==(*other.iterator);;
}

template<typename T>
bool Collection<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return !(*this == other);
}

template<typename T>
bool Collection<T>::ConstIterator::operator==(const Iterator& other) const {
    std::cout << "== отработало";
    if (!iterator && !other.iterator) return true;
    if (!iterator || !other.iterator) return false;
    return iterator == other.iterator;
}

template<typename T>
bool Collection<T>::ConstIterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
    os << "[";
    auto it = collection.begin();
    if (it != collection.end()) {
        os << *it;
        ++it;
    }
    for (; it != collection.end(); ++it) {
        os << " " << *it;
    }
    os << "]";
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Collection<T>& collection) {
    T value;
    while (is >> value) {
        collection.push(value);
    }

    if (is.eof()) {
        is.clear();
    }
    return is;
}

template<typename T>
void Collection<T>::Iterator::checkOnNullIterator() const {
    if (!iterator) {
        throw std::runtime_error("Разыменование null итератора");
    }
}

template<typename T>
void Collection<T>::ConstIterator::checkOnNullConstIterator() const {
    if (!iterator) {
        throw std::runtime_error("Разыменование null const итератора");
    }
}

#endif // COLLECTION_TPP