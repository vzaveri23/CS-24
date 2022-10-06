#include "FibVec.h"
#include <stdexcept>

//Constructor
FibVec::FibVec() throw() {
    numVals = 0;
    arr = new int[1];
    current_cap = 1;
    prev_cap = 1;
}

//Destructor
FibVec::~FibVec() throw() {
    delete [] arr;
}

size_t FibVec::capacity() const {
    return current_cap;
}

size_t FibVec::count() const {
    return numVals;
}

void FibVec::insert(int val, size_t index) throw() {
    if (index > count()) {
        throw std::out_of_range("invalid index");
        return;
    }

    if (count() == capacity()) {
        resize(current_cap + prev_cap);
        size_t new_capacity = current_cap + prev_cap;
        prev_cap = current_cap; 
        current_cap = new_capacity;
    }

    for (int i=count()-1; i>=index; i--) {
        arr[i+1] = arr[i];
    }

    arr[index] = val;
    numVals++;
 }

int FibVec::lookup(size_t index) const throw() {
    if (index < count()) {
        return arr[index];
    } 

    throw std::out_of_range("invalid index");
}

int FibVec::pop() throw() {
    if (count() == 0) {
        throw std::underflow_error("invalid");
    }
    
    remove(count()-1);
}

void FibVec::push(int val) {
    insert(count(), val);
}

int FibVec::remove(size_t index) throw() { 
    if (index >= count()) {
        throw std::out_of_range("invalid index");
        return -1;
    }

    int remove_val = arr[index];

    //condition may be i<count()-1
    for (int i=index; i<count(); i++) {
        arr[i] = arr[i+1];
    }

    numVals--;

    if (count() < (current_cap-prev_cap)) {
        resize(prev_cap);
    }

    return remove_val;
}

FibVec FibVec::slice(size_t index, size_t c) const {

}

void FibVec::resize(size_t size) {
    int *new_arr = new int[size];
    for (int i=0; i<count(); i++) {
        new_arr[i] = arr[i];
    }

    delete [] arr;
    arr = new_arr;
}






