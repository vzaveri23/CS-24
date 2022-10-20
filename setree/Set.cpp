#include "Set.h"
#include <stdexcept>
#include <iostream>
using namespace std;

size_t place(Node *&, Node *&);
size_t countNodes(Node *);
size_t deleteNode(string, Node *&);
void deletion(Node *&);
void printer(Node *);
void deleteNode(Node *);

Set::Set() {
    mRoot = nullptr;
}

Set::Set(const Set& other) {

}

Set::Set(Set&& other) {
    mRoot = other.mRoot;
    other.mRoot = nullptr;
}

Set::~Set() {
    delete mRoot;
}

size_t Set::clear() {
    size_t val = count();
    if (mRoot == nullptr) {
        return 0;
    }

    deleteNode(mRoot);
    return val;
}

void deleteNode(Node *ptr) {
    if (ptr == nullptr) {
        return;
    }

    deleteNode(ptr->left);
    deleteNode(ptr->right);

    delete ptr;
}

bool Set::contains(const string& value) const {
    Node *ptr = mRoot;
    while (ptr) {
        if (ptr->data == value) {
            return true;
        } else if (value < ptr->data) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }

    return false;

}

size_t Set::count() const {
    if (mRoot == nullptr) {
        return 0;
    }

    return countNodes(mRoot);

}

size_t Set::insert(const string &value) {
    if (contains(value)) {
        return 0;
    }

    Node *newNode = new Node;
    newNode->data = value;
    newNode->left = newNode->right = nullptr;

    return place(mRoot, newNode);
}

const string &Set::lookup(size_t n) const {
    Node *ptr = mRoot;
    if (n < count()) {

    }

    return ptr->data;

}

void Set::print() const {
    printer(mRoot);
    cout << endl;
}

void printer(Node *ptr) {
    if (ptr == nullptr) {
        cout << "-";
    } else if (ptr->left == nullptr && ptr->right == nullptr) {
        cout << ptr->data;
    } else {
        cout << "(";
        printer(ptr->left);
        cout << " ";
        cout << ptr->data;
        cout << " ";
        printer(ptr->right);
        cout << ")";
    }
}

size_t Set::remove(const string &value) {
    if (!contains(value)) {
        return 0;
    }

   return deleteNode(value, mRoot);

}

size_t place(Node *&ptr, Node *&newNode) {
    if (ptr == nullptr) {
        ptr = newNode;
    } else if (newNode->data < ptr->data) {
        place(ptr->left, newNode);
    } else {
        place(ptr->right, newNode);
    }

    return 1;
}

size_t countNodes(Node *ptr) {
    if (ptr == nullptr) {
        return 0;
    }
    
    return 1 + countNodes(ptr->left) + countNodes(ptr->right);
}

size_t deleteNode(string val, Node *&ptr) {
    if (val < ptr->data) {
        deleteNode(val, ptr->left);
    } else if (val > ptr->data) {
        deleteNode(val, ptr->right);
    } else {
        deletion(ptr);
    }

    return 1;
}

void deletion(Node *&ptr) {
    Node *temp = nullptr;
    if (ptr == nullptr) {
        return;
    } else if (ptr->right == nullptr && ptr->left == nullptr) {
        delete ptr;
        ptr = nullptr;
    } else if (ptr->right == nullptr) {
        temp = ptr;
        ptr = ptr->left;
        delete temp;
    } else if (ptr->left == nullptr) {
        temp = ptr;
        ptr = ptr->right;
        delete temp;
    } else {
        Node *prev_ptr = nullptr;
        temp = ptr->left;
        while (temp->right) {
            prev_ptr = temp;
            temp = temp->right;
        }

        if (prev_ptr == nullptr) {
            ptr->data = temp->data;
            ptr->left = temp->left;
            delete temp;
            return;
        }

        ptr->data = temp->data;
        deletion(prev_ptr->right);
    }

}

