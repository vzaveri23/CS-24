#ifndef HELPERS_H
#define HELPERS_H

#include "Star.h"
#include <sstream>
#include <istream>
#include <vector>
using namespace std;

// If you want to add any helper classes,
// here's some space to do it in.

class KDTree {
    public:
        struct Node {
            Star data;
            Node *left, *right;
            size_t axis;
        };

    Node *root;
    KDTree(istream &stream);
    Node* makeTree(vector<Star> &, size_t, size_t, size_t);
};

class Heap {
public:
   struct Entry {
    Star data;
    float score;
};

private:
    Entry* mData;
    size_t mCapacity;
    size_t mCount;

public:
    Heap(size_t capacity);
    Heap(const Heap& other);
    Heap(Heap&& other);
    ~Heap();

    size_t       capacity() const;
    size_t       count() const;
    const Entry& lookup(size_t index) const;
    Entry        pop();
    Entry        pushpop(const Star&value, float score);
    void         push(const Star &value, float score);
    const Entry& top() const;
};

#endif
