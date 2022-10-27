#ifndef STACK_H
#define STACK_H

#include "AST.h"

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

struct Node {
    AST *data;
    Node *next;
};

class Stack {
    
    Node *top;

    private:
        size_t operators;
        size_t operands;
    
    public:
        Stack();
        ~Stack();
        void push(AST *);
        AST* pop();
        bool isEmpty() const;
        Node* topNode() const;  
        size_t size() const;
};

#endif
