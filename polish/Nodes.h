#ifndef NODES_H
#define NODES_H

#include "AST.h"
#include <string>
using namespace std;

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.


class Numbers: public AST {
    private:
        double data;
    public:
        Numbers(double);
        string prefix() const;
        string postfix() const;
        double value() const;
};

class Addition: public AST {
    public:
        Addition(AST*, AST*);
        ~Addition();
        AST *left;
        AST *right;
        string prefix() const;
        string postfix() const;
        double value() const;
};

class Subtraction: public AST {
    public:
        Subtraction(AST*, AST*);
        ~Subtraction();
        AST *left;
        AST *right;
        string prefix() const;
        string postfix() const;
        double value() const;
};

class Multiplication: public AST {
    public:
        Multiplication(AST*, AST*);
        ~Multiplication();
        AST *left;
        AST *right;
        string prefix() const;
        string postfix() const;
        double value() const;
};

class Division: public AST {
    public:
        Division(AST*, AST*);
        ~Division();
        AST *left;
        AST *right;
        string prefix() const;
        string postfix() const;
        double value() const;
};

class Mod: public AST {
    public:
        Mod(AST*, AST*);
        ~Mod();
        AST *left;
        AST *right;
        string prefix() const;
        string postfix() const;
        double value() const;
};

class Negate: public AST {
    public:
        Negate(AST*);
        ~Negate();
        AST *ptr;
        string prefix() const;
        string postfix() const;
        double value() const;
};

#endif
