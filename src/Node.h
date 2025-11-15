#pragma once

#ifndef STACKANDQUEUE_NODE_H
#define STACKANDQUEUE_NODE_H


/**
 * Базовый класс, представляющий узел
 * Используется в {@link Stack} и {@link Queue}
 *
 * @author Linempy
 * @since 24.10.2025
 */
template<typename N> class Node {
private:
    N value;
    Node<N>* nextNode;
public:
    Node(N data) : value(data), nextNode(nullptr) {
    }

    Node(N data, Node<N>* next) : value(data), nextNode(next) {
    }

    N& getValue() {
        return value;
    }

    Node<N>* getNextNode() const {
        return nextNode;
    }

    void setNextNode(Node<N>* node) {
        nextNode = node;
    }
};


#endif //STACKANDQUEUE_NODE_H
