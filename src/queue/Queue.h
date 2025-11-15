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
    Node<T>* begin;
    Node<T>* end;
public:

    Queue() : begin(nullptr), end(nullptr) {}

    Queue(const Queue<T>& other) : begin(nullptr), end(nullptr) {
        *this = other;
    }

    Queue(Queue<T>&& other) : begin(other.begin), end(other.end) {
        other.begin = nullptr;
        other.end = nullptr;
    }

    ~Queue() {
        clear();
    }

    T& getFront() const override {
        return begin->getValue();
    }

    Node<T>* getBegin() const {
        return begin;
    }

    Queue<T>& operator=(const Queue<T>& queue);
    Queue<T>& operator=(Queue<T>&& queue);

    bool isEmpty() const override;

    T pop() override;

    void push(const T &value) override;

    size_t getSize() const override;

    void clear();

    Node<T>* getAnEnd() const {
        return end;
    }

    void setBegin(Node<T>* beginNode) {
        begin = beginNode;
    }

    void setEnd(Node<T>* endNode) {
        end = endNode;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Queue<U>& queue);
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Queue<U>& queue);

protected:
    void print(std::ostream &os) const override {
        os << *this;
    }
};

#include "Queue.tpp"

#endif //STACKANDQUEUE_QUEUE_H
