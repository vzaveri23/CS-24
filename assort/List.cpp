#include "List.h"
#include <stdexcept>
#include <iostream>
using namespace std;

List::List() {
    head = nullptr;
}

List::List(const List &other) {

}

List::List(List &&other) {
    head = other.head;
    other.head = nullptr;
}

List::~List() {
    Node *ptr = head;
    while (ptr) {
        Node *temp = ptr;
        ptr = ptr->next;
        delete temp;
    }

    head = nullptr;

}

size_t List::count() const {
    size_t count = 0;
    Node *ptr = head;
    while (ptr != nullptr) {
        count++;
        ptr = ptr->next;
    }

    return count;

}

void List::insert(const string& value) {
    Node *newNode;
    Node *ptr;
    Node *prev_ptr = nullptr;

    newNode = new Node;
    newNode->data = value;

    if (!head) {
        head = newNode;
        newNode->next = nullptr;
        return;
    } else {
        ptr = head;
        prev_ptr = nullptr;
        while (ptr != nullptr && ptr->data < value) {
            prev_ptr = ptr;
            ptr = ptr->next;
        }
    }

    if (prev_ptr == nullptr) {
        head = newNode;
        newNode->next = ptr;
    } else {
        prev_ptr->next = newNode;
        newNode->next = ptr;
    }
}

const string &List::lookup(size_t index) const {
    if (index >= count()) {
        throw out_of_range("invalid index");
    }

    Node *ptr;
    ptr = head;
    size_t i=0;
    while (i < index) {
        ptr = ptr->next;
        i++;
    }

    return ptr->data;

}

void List::print(bool reverse) const {
    if (!reverse) {
        Node *ptr;
        ptr = head;
        cout << "[";
        while (ptr) {
            if (ptr->next == nullptr) {
                cout << ptr->data;
                break;
            }
            cout << ptr->data << ", ";
            ptr = ptr->next;
        }
    } 
    
    cout << "]" << endl;
}

string List::remove(size_t index) {
    string val = lookup(index);
    Node *ptr;
    Node *prev_ptr;
    
    ptr = head;
    prev_ptr = nullptr;

    if (index==0) {
        Node *temp = ptr;
        head = ptr->next;
        delete temp;
        return val;
    }

    size_t i=0;
    while (ptr != nullptr && i < index) {
        prev_ptr = ptr;
        ptr = ptr->next;
        i++;
    }

    if (ptr) {
        prev_ptr->next = ptr->next;
        delete ptr;
    }

    return val;
}

size_t List::remove(const string &value) {
    size_t count=0;
    Node *ptr;
    Node *prev_ptr;

    ptr = head;
    prev_ptr = nullptr;

    if (ptr->data == value) {
        while (ptr->data == value) {
            Node *temp = ptr;
            ptr = ptr->next;
            count++;
            delete temp;
        }

        head = ptr;
        return count;
    }

    while (ptr) {
        if (ptr->data == value) {
            while (ptr->data == value) {
                Node *valPtr = ptr;
                ptr = ptr->next;
                delete valPtr;
                count++;
                prev_ptr->next=ptr;
            }

            continue;
        }

        prev_ptr = ptr;
        ptr = ptr->next;
    }

    return count;

}






