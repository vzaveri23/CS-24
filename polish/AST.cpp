#include "AST.h"
#include "Nodes.h"
#include "Stack.h"

#include <sstream>
#include <cctype>
#include <stdexcept>
#include <iostream>

using namespace std;

Numbers* numberParser(string);

 size_t operators=0, operands=0;

AST* AST::parse(const std::string& expression) {
    Stack stack;
    istringstream iss(expression);

    string t;
    string line;
    while (iss >> t) {
        if (t == "+") {
            if (stack.size() > 1) {
                AST *first = stack.pop();
                AST *second = stack.pop();
                Addition *ptr = new Addition(second, first);
                stack.push(ptr);
                operators++;
            } else {
                throw runtime_error("Not enough operands.");
            }
        } else if (t == "-") {
            if (stack.size() > 1) {
                AST *first = stack.pop();
                AST *second = stack.pop();
                Subtraction *ptr = new Subtraction(second, first);
                stack.push(ptr);
                operators++;
            } else {
                throw runtime_error("Not enough operands.");
            }
        } else if (t == "*") {
            if (stack.size() > 1) {
                AST *first = stack.pop();
                AST *second = stack.pop();
                Multiplication *ptr = new Multiplication(second, first);
                stack.push(ptr);
                operators++;
            } else {
                throw runtime_error("Not enough operands.");
            }
        } else if (t == "/") {
            if (stack.size() > 1) {
                AST *first = stack.pop();
                AST *second = stack.pop();
                Division *ptr = new Division(second, first);
                stack.push(ptr);
                operators++;
            } else {
                throw runtime_error("Not enough operands.");
            }
        }  else if (t == "%") {
            if (stack.size() > 1) {
                AST *first = stack.pop();
                AST *second = stack.pop();
                Mod *ptr = new Mod(second, first);
                stack.push(ptr);
                operators++;
            } else {
                throw runtime_error("Not enough operands.");
            }
        } else if (t == "~") {
            if (stack.size() >= 1) {
                AST *val = stack.pop();
                Negate *ptr = new Negate(val);
                stack.push(ptr);
                operators++;
            } else {
                throw runtime_error("Not enough operands.");
            }
        } else {
            Numbers *ptr = numberParser(t);
            if (ptr == nullptr) {
                throw runtime_error("Invalid token: " + t);
            } else {
                stack.push(ptr);
                operands++;
            }
        }
            
    }

    if (stack.isEmpty()) {
        throw runtime_error("No input.");
    } else if (stack.size() > 1) {
        throw runtime_error("Too many operands.");
    }

    return stack.pop();
}

Numbers* numberParser(string token) {
    size_t idx;
    double t;
    try {
       t = stod(token, &idx);
    } catch (...) {
        throw runtime_error("Invalid token: " + token);
    }
    if (token.size() != idx) {
        return nullptr;
    }

    return new Numbers(t);
}
