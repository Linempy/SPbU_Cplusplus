#ifndef STACKANDQUEUE_COLLECTION_H
#define STACKANDQUEUE_COLLECTION_H

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
    ~Collection() = default;

    virtual void push(const T& value) = 0;
    virtual T pop() = 0;
    virtual T& getFront() const = 0;
    virtual size_t getSize() const = 0;
    virtual bool isEmpty() const = 0;

    virtual Collection<T>& operator=(const Collection<T>& collection) {
        return *this;
    };

protected:
    virtual void print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Collection& figure) {
        figure.print(os);
        return os;
    }
};

#endif //STACKANDQUEUE_COLLECTION_H
