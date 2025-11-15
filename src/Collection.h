#ifndef STACKANDQUEUE_COLLECTION_H
#define STACKANDQUEUE_COLLECTION_H

#include <memory>
#include "Node.h"
#include "iostream"

/**
 * Абстрактный класс для коллекций.
 * Имеет основные методы для работы с коллекциями
 *
 * @author Linempy
 * @since 08.11.2025
 */
template<typename T>
class Collection {
public:
    class Iterator;
    ~Collection() = default;

    virtual void push(const T& value) = 0;
    virtual T pop() = 0;
    virtual T& getFront() const = 0;
    virtual size_t getSize() const = 0;
    virtual bool isEmpty() const = 0;

    virtual Collection<T>& operator=(const Collection<T>& collection) {
        return *this;
    };

    class Iterator {
    public:
        virtual ~Iterator() = default;
        virtual T& operator*() = 0;
        virtual Iterator& operator++() = 0;
        virtual bool operator!=(const Iterator& other) = 0;
        virtual bool operator==(const Iterator& other) = 0;
    };

    class ConstIterator {
    public:
        virtual ~ConstIterator() = default;
        virtual const T& operator*() const = 0;
        virtual const ConstIterator& operator++() const = 0;
        virtual bool operator!=(const ConstIterator& other) const = 0;
        virtual bool operator==(const ConstIterator& other) const = 0;
    };


protected:
    virtual void print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Collection& figure) {
        figure.print(os);
        return os;
    }
};

#endif //STACKANDQUEUE_COLLECTION_H
