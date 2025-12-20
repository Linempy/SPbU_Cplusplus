#ifndef STACKANDQUEUE_STACK_H
#define STACKANDQUEUE_STACK_H

#include "Node.h"
#include "utility"
#include "Collection.h"
#include <iostream>
#include <stdexcept>

/**
 * Шаблонный класс для структуры данных Stack
 *
 * @author Linempy
 * @since 24.10.2025
 */
template<typename T>
class Stack : public Collection<T> {
private:
    Node<T>* top;

public:

    class StackIterator;
    class StackConstIterator;

    using Iterator = typename Collection<T>::Iterator;
    using ConstIterator = typename Collection<T>::ConstIterator;

    Stack() : top(nullptr) {
    }
    Stack(Node<T>* node) : top(node) {
    }
    Stack(Stack<T>&& stack) : top(stack.top) {
        stack.top = nullptr;
    }
    Stack(const Stack<T>& stack) : top(nullptr){
        *this = stack;
    }
    ~Stack() {
        clear();
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& stack);
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Stack<U>& stack);

    Stack<T>& operator=(const Stack<T>& stack);
    Stack<T>& operator=(const Collection<T>& stack) override;
    Stack<T>& operator=(Stack<T>&& stack);

    void clear();

    T pop() override;
    void push(const T& value) override;
    void push(T&& value) override;

    T& getFront() override {
        if (isEmpty()) {
            throw std::runtime_error("Стек пуст");
        }
        return top->getValue();
    }
    const T& getFront() const override {
        if (isEmpty()) {
            throw std::runtime_error("Стек пуст");
        }
        return top->getValue();
    }

    size_t getSize() const override;
    bool isEmpty() const override;

    Iterator begin() override;
    Iterator end() override;
    ConstIterator begin() const override;
    ConstIterator end() const override;
    ConstIterator cbegin() const override;
    ConstIterator cend() const override;

    class StackIterator : public Collection<T>::IteratorBase {
    private:
        Node<T>* current;
    public:
        using IteratorBase = Collection<T>::IteratorBase;
        using ConstIteratorBase = Collection<T>::ConstIteratorBase;

        StackIterator(Node<T>* node) : current(node) {};

        T& operator*() override;
        T* operator->() override;
        StackIterator& operator++() override;

        bool operator==(const IteratorBase &other) const override;
        bool operator!=(const IteratorBase &other) const override;
        bool operator==(const ConstIteratorBase &other) const override;
        bool operator!=(const ConstIteratorBase &other) const override;

    protected:
        IteratorBase *clone() const override;
        friend class StackConstIterator;
    };

    class StackConstIterator : public Collection<T>::ConstIteratorBase {
    private:
        const Node<T>* current;
    public:
        using IteratorBase = Collection<T>::IteratorBase;
        using ConstIteratorBase = Collection<T>::ConstIteratorBase;

        StackConstIterator(const Node<T>* node) : current(node) {};

        const T& operator*() const override;
        const T* operator->() const override;
        StackConstIterator& operator++() override;
        bool operator!=(const ConstIteratorBase &other) const override;
        bool operator==(const ConstIteratorBase &other) const override;
        bool operator!=(const IteratorBase &other) const override;
        bool operator==(const IteratorBase &other) const override;

    protected:
        ConstIteratorBase* clone() const override;
        friend class StackIterator;
    };
};

#include "../src/stack/Stack.tpp"

#endif //STACKANDQUEUE_STACK_H
