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
    class IteratorBase;
    class ConstIteratorBase;

    class Iterator;
    class ConstIterator;
    ~Collection() = default;

    virtual void push(const T& value) = 0;
    virtual void push(T&& value) = 0;
    virtual T pop() = 0;
    virtual T& getFront() = 0;
    virtual const T& getFront() const = 0;
    virtual size_t getSize() const = 0;
    virtual bool isEmpty() const = 0;

    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;
    virtual ConstIterator begin() const = 0;
    virtual ConstIterator end() const = 0;
    virtual ConstIterator cbegin() const = 0;
    virtual ConstIterator cend() const = 0;

    virtual Collection<T>& operator=(const Collection<T>& collection) = 0;

    class IteratorBase {
    public:
        virtual ~IteratorBase() = default;
        virtual T& operator*() = 0;
        virtual T* operator->() = 0;
        virtual IteratorBase& operator++() = 0;
        virtual bool operator==(const IteratorBase& other) const = 0;
        virtual bool operator!=(const IteratorBase& other) const = 0;
        virtual bool operator==(const ConstIteratorBase& other) const = 0;
        virtual bool operator!=(const ConstIteratorBase& other) const = 0;

    protected:
        virtual IteratorBase* clone() const = 0;
        friend class Iterator;
        friend class ConstIterator;
    };

    class ConstIteratorBase {
    public:
        virtual ~ConstIteratorBase() = default;
        virtual const T& operator*() const = 0;
        virtual const T* operator->() const = 0;
        virtual ConstIteratorBase& operator++() = 0;
        virtual bool operator!=(const ConstIteratorBase& other) const = 0;
        virtual bool operator==(const ConstIteratorBase& other) const = 0;
        virtual bool operator!=(const IteratorBase& other) const = 0;
        virtual bool operator==(const IteratorBase& other) const = 0;

    protected:
        virtual ConstIteratorBase* clone() const = 0;
        friend class Iterator;
        friend class ConstIterator;
    };

    class Iterator {
    private:
        IteratorBase* iterator;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator();
        Iterator(IteratorBase* iteratorBase);
        Iterator(const Iterator& other);
        Iterator(Iterator&& other);
        explicit Iterator(const ConstIterator& other);
        ~Iterator();

        Iterator& operator=(const Iterator& other);
        Iterator& operator=(Iterator&& other);
        Iterator& operator=(const ConstIterator& other);

        reference operator*();
        pointer operator->();

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        void checkOnNullIterator() const;
        friend class ConstIterator;
    };

    class ConstIterator {
    private:
        ConstIteratorBase* iterator;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator();
        explicit ConstIterator(ConstIteratorBase* base);
//        ConstIterator(IteratorBase* base);
        ConstIterator(const ConstIterator& other);
        ConstIterator(ConstIterator&& other);
        ConstIterator(const Iterator& other);
        ~ConstIterator();

        ConstIterator& operator=(const ConstIterator& other);
        ConstIterator& operator=(ConstIterator&& other);
        ConstIterator& operator=(const Iterator& other);

        reference operator*() const;
        pointer operator->() const;
        ConstIterator& operator++();
        ConstIterator operator++(int);

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    private:
        void checkOnNullConstIterator() const;
        friend class Iterator;
    };

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Collection<U>& collection);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, Collection<U>& collection);

};

#include "../src/Collection.tpp"

#endif //STACKANDQUEUE_COLLECTION_H
