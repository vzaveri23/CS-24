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
            AST *first = stack.pop();
            AST *second = stack.pop();
            Addition *ptr = new Addition(second, first);
            stack.push(ptr);
            operators++;
        } else if (t == "-") {
            AST *first = stack.pop();
            AST *second = stack.pop();
            Subtraction *ptr = new Subtraction(second, first);
            stack.push(ptr);
            operators++;
        } else if (t == "*") {
            AST *first = stack.pop();
            AST *second = stack.pop();
            Multiplication *ptr = new Multiplication(second, first);
            stack.push(ptr);
            operators++;
        } else if (t == "/") {
            AST *first = stack.pop();
            AST *second = stack.pop();
            Division *ptr = new Division(second, first);
            stack.push(ptr);
            operators++;
        }  else if (t == "%") {
            AST *first = stack.pop();
            AST *second = stack.pop();
            Mod *ptr = new Mod(second, first);
            stack.push(ptr);
            operators++;
        } else if (t == "~") {
            AST *val = stack.pop();
            Negate *ptr = new Negate(val);
            stack.push(ptr);
            operators++;
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
    } else if (operands <= operators) {
        throw runtime_error("Not enough operands.");
    }

    return stack.topNode()->data;
}

Numbers* numberParser(string token) {
    size_t idx;
    double t = stod(token, &idx);
    if (token.size() != idx) {
        return nullptr;
    }

    return new Numbers(stod(token));
}
