#include "Stack.h"

// Implement your Stack member functions here.

Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    Node *ptr = nullptr, *nextNode = nullptr;
    ptr = top;
    while (ptr) {
        nextNode = ptr->next;
        delete ptr;
        ptr = nextNode;
    }
}

void Stack::push(AST *ptr) {
    Node *newNode = nullptr;
    newNode = new Node;
    newNode->data = ptr;

    if (isEmpty()) {
        top = newNode;
        newNode->next = nullptr;
    } else {
        newNode->next = top;
        top = newNode;
    }
}

AST* Stack::pop() {
    AST *deleted = top->data;
    Node *nodePtr = nullptr;
    if (isEmpty()) {
        return nullptr;
    }

    nodePtr = top;
    top = top->next;
    delete nodePtr;
    nodePtr = nullptr;

    return deleted;
}


bool Stack::isEmpty() const {
    return (!top) ? true : false;
}

Node* Stack::topNode() const {
    return top;
}

size_t Stack::size() const {
    size_t count = 0;
    Node *ptr = top;
    while (ptr != nullptr) {
        ptr = ptr->next;
        count++;
    }

    return count;
}


