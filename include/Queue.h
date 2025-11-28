#ifndef STACKANDQUEUE_QUEUE_H
#define STACKANDQUEUE_QUEUE_H

#include "Node.h"
#include "iostream"

/**
 * Шаблонный класс представляющий собой структуру данных Очередь
 *
 * @author Linempy
 * @since 30.10.2025
 */
template<typename T>
class Queue : public Collection<T> {
private:
    Node<T>* _begin;
    Node<T>* _end;
public:
    class QueueIterator;
    class QueueConstIterator;

    using Iterator = typename Collection<T>::Iterator;
    using ConstIterator = typename Collection<T>::ConstIterator;

    Queue() : _begin(nullptr), _end(nullptr) {}

    Queue(const Queue<T>& other) : _begin(nullptr), _end(nullptr) {
        *this = other;
    }

    Queue(Queue<T>&& other) : _begin(other._begin), _end(other._end) {
        other._begin = nullptr;
        other._end = nullptr;
    }

    ~Queue() {
        clear();
    }

    T& getFront() override {
        return _begin->getValue();
    }

    const T& getFront() const override {
        return _begin->getValue();
    }

    Node<T>* getBegin() const {
        return _begin;
    }

    Queue<T>& operator=(const Queue<T>& queue);
    Queue<T>& operator=(Queue<T>&& queue);

    Queue<T>& operator=(const Collection<T> &collection) override;

    bool isEmpty() const override;
    T pop() override;
    void push(const T& value) override;
    void push(T&& value) override;
    size_t getSize() const override;

    void clear();

    Node<T>* getAnEnd() const {
        return _end;
    }

    void setBegin(Node<T>* beginNode) {
        _begin = beginNode;
    }

    void setEnd(Node<T>* endNode) {
        _end = endNode;
    }

    Iterator begin() override;
    Iterator end() override;
    ConstIterator begin() const override;
    ConstIterator end() const override;
    ConstIterator cbegin() const override;
    ConstIterator cend() const override;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Queue<U>& queue);
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Queue<U>& queue);

    class QueueIterator : public Collection<T>::IteratorBase {
    private:
        Node<T>* current;
    public:
        using IteratorBase = Collection<T>::IteratorBase;
        using ConstIteratorBase = Collection<T>::ConstIteratorBase;

        QueueIterator(Node<T>* node) : current(node) {};
        T& operator*() override;
        T* operator->() override;
        QueueIterator& operator++() override;
        bool operator==(const IteratorBase &other) const override;
        bool operator!=(const IteratorBase &other) const override;
        bool operator==(const ConstIteratorBase &other) const override;
        bool operator!=(const ConstIteratorBase &other) const override;

    protected:
        IteratorBase *clone() const override;
        friend class QueueConstIterator;
    };

    class QueueConstIterator : public Collection<T>::ConstIteratorBase {
    private:
        const Node<T>* current;
    public:
        using IteratorBase = Collection<T>::IteratorBase;
        using ConstIteratorBase = Collection<T>::ConstIteratorBase;

        QueueConstIterator(const Node<T>* node) : current(node) {};

        const void* getPtr() const;

        const T &operator*() const override;
        const T* operator->() const override;
        QueueConstIterator &operator++() override;
        bool operator!=(const ConstIteratorBase &other) const override;
        bool operator==(const ConstIteratorBase &other) const override;
        bool operator!=(const IteratorBase &other) const override;
        bool operator==(const IteratorBase &other) const override;

    protected:
        ConstIteratorBase *clone() const override;
        friend class QueueIterator;
    };
};

#include "../src/queue/Queue.tpp"

#endif //STACKANDQUEUE_QUEUE_H
