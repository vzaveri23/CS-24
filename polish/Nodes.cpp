#include "Nodes.h"
#include <sstream>
#include <stdexcept>
#include <cmath>

// Implement your AST subclasses' member functions here.


// To format a double for output:
//   std::ostringstream stream;
//   stream << value;
//   return stream.str();

Numbers::Numbers(double data) {
    this->data = data;
}

string Numbers::prefix() const {
    std::ostringstream stream;
    stream << data;
    return stream.str();
}

string Numbers::postfix() const {
    std::ostringstream stream;
    stream << data;
    return stream.str();
}

double Numbers::value() const {
    return data;
}

Addition::Addition(AST *left, AST *right) {
    this->left = left;
    this->right = right;
}

Addition::~Addition() {
    delete left;
    delete right;
}

string Addition::prefix() const {
    return "+ " + left->prefix() + " " + right->prefix();
}

string Addition::postfix() const {
    return left->postfix() + " " + right->postfix() + " +";
}

double Addition::value() const {
    return left->value() + right->value();
}

Subtraction::Subtraction(AST *left, AST *right) {
    this->left = left;
    this->right = right;
}

Subtraction::~Subtraction() {
    delete left;
    delete right;
}

string Subtraction::prefix() const {
    return "- " + left->prefix() + " " + right->prefix();
}

string Subtraction::postfix() const {
    return left->postfix() + " " + right->postfix() + " -";
}

double Subtraction::value() const {
    return left->value() - right->value();
}

Multiplication::Multiplication(AST *left, AST *right) {
    this->left = left;
    this->right = right;
}

Multiplication::~Multiplication() {
    delete left;
    delete right;
}

string Multiplication::prefix() const {
    return "* " + left->prefix() + " " + right->prefix();
}

string Multiplication::postfix() const {
    return left->postfix() + " " + right->postfix() + " *";
}

double Multiplication::value() const {
    return left->value() * right->value();
}

Division::Division(AST *left, AST *right) {
    this->left = left;
    this->right = right;
}

Division::~Division() {
    delete left;
    delete right;
}

string Division::prefix() const {
   return "/ " + left->prefix() + " " + right->prefix();
}

string Division::postfix() const {
    return left->postfix() + " " + right->postfix() + " /";
}

double Division::value() const {
    if (right->value() == 0) {
        throw runtime_error("Division by zero.");
    }

    return left->value() / right->value();
}

Mod::Mod(AST *left, AST *right) {
    this->left = left;
    this->right = right;
}

Mod::~Mod() {
    delete left;
    delete right;
}

string Mod::prefix() const {
    return "% " + left->prefix() + " " + right->prefix();
}

string Mod::postfix() const {
    return left->postfix() + " " + right->postfix() + " %";
}

double Mod::value() const {
    if (right->value() == 0) {
        throw runtime_error("Division by zero.");
    }

    return fmod(left->value(), right->value());

}

Negate::Negate(AST *ptr) {
    this->ptr = ptr;
}

Negate::~Negate() {
    delete ptr;
}

string Negate::prefix() const {
    return "~ " + ptr->prefix();
}

string Negate::postfix() const {
    return ptr->postfix() + " ~";
}

double Negate::value() const {
    return -ptr->value();
}









