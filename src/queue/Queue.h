#ifndef STACKANDQUEUE_QUEUE_H
#define STACKANDQUEUE_QUEUE_H

#include "../Node.h"
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

    T& getFront() const override {
        return _begin->getValue();
    }

    Node<T>* getBegin() const {
        return _begin;
    }

    Queue<T>& operator=(const Queue<T>& queue);
    Queue<T>& operator=(Queue<T>&& queue);

    bool isEmpty() const override;

    T pop() override;

    void push(const T &value) override;

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

    QueueIterator begin() {
        return QueueIterator(_begin);
    }

    QueueIterator end() {
        return QueueIterator(nullptr);
    }

    QueueConstIterator cbegin() {
        return QueueIterator(_begin);
    }

    QueueConstIterator cend() {
        return QueueConstIterator(nullptr);
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Queue<U>& queue);
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Queue<U>& queue);

    class QueueIterator : public Collection<T>::Iterator {
    private:
        Node<T>* current;
    public:
        QueueIterator(Node<T>* node) : current(node) {};
        T& operator*() override;
        T* operator->();
        QueueIterator& operator++() override;
        bool operator!=(const Collection<T>::Iterator &other) override;
        bool operator==(const Collection<T>::Iterator &other) override;
    };

    class QueueConstIterator : public Collection<T>::ConstIterator {
    private:
        const Node<T>* current;
    public:
        QueueConstIterator(const Node<T>* node) : current(node) {};

        const T &operator*() const override;
        const T* operator->() const;
        const QueueConstIterator &operator++() const override;
        bool operator!=(const Collection<T>::ConstIterator &other) const override;
        bool operator==(const Collection<T>::ConstIterator &other) const override;
    };

protected:
    void print(std::ostream &os) const override {
        os << *this;
    }
};

#include "Queue.tpp"

#endif //STACKANDQUEUE_QUEUE_H
