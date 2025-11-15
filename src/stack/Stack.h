#ifndef STACKANDQUEUE_STACK_H
#define STACKANDQUEUE_STACK_H

#include "../Node.h"
#include "utility"
#include "../Collection.h"
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

    T pop();

    void push(const T& value);
    void push(T&& value);

    T& getFront() const override {
        if (isEmpty()) {
            throw std::runtime_error("Стек пуст");
        }
        return top->getValue();
    }

    void print(std::ostream& os) const override;

    size_t getSize() const override;

    bool isEmpty() const override;
};

#include "Stack.tpp"

#endif //STACKANDQUEUE_STACK_H
