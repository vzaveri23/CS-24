#include "Helpers.h"
#include <algorithm>

// Space to implement helper class member functions.
bool sortX(Star, Star);
bool sortY(Star, Star);
bool sortZ(Star, Star);

KDTree::KDTree(istream &stream) {
    string line, t;
    float x, y, z;
    Star s;
    vector<Star> stars;
    int i=0;
    while (stream >> x >> y >> z) {
        s.id = ++i;
        s.x = x;
        s.y = y;
        s.z = z;
        stars.push_back(s);
    }

    root = makeTree(stars, 0, stars.size(), 0);
}

bool sortX(Star s1, Star s2) {
    return s1.x < s2.x;
}

bool sortY(Star s1, Star s2) {
    return s1.y < s2.y;
}

bool sortZ(Star s1, Star s2) {
    return s1.z < s2.z;
}

KDTree::Node* KDTree::makeTree(vector<Star> &stars, size_t start, size_t end, size_t axis) {
    if (end-start<1) {
        return nullptr;
    }

    if (axis==0) {
        sort(&stars[start], &stars[end], sortX);
    } else if (axis==1) {
        sort(&stars[start], &stars[end], sortY);
    } else {
        sort(&stars[start], &stars[end], sortZ);
    }

    Star median = stars[(start+end)/2];
    Node *ptr = new Node;
    ptr->data = median;
    ptr->left = makeTree(stars, start, (start+end)/2, (axis+1)%3);
    ptr->right = makeTree(stars, (start+end)/2 + 1, end, (axis+1)%3);
    ptr->axis = axis;

    return ptr;
}

void swap(Heap::Entry [], size_t, size_t);

Heap::Heap(size_t capacity) {
    mData = new Entry[capacity];
    mCount = 0;
    mCapacity = capacity;
}

Heap::Heap(const Heap &other) {
    mCapacity = other.mCapacity;
    mData = new Entry[mCapacity];
    mCount = 0;
    for (size_t i=0; i<other.count(); i++) {
        mData[i] = other.mData[i];
        mCount++;
    }
}

Heap::Heap(Heap &&other) {
    mData = other.mData;
    other.mData = NULL;
    mCapacity = other.mCapacity;
    mCount = other.mCount;
}

Heap::~Heap() {
    delete [] mData;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

const Heap::Entry &Heap::lookup(size_t index) const {
    if (index >= count()) {
        throw out_of_range("invalid index");
    }

    return mData[index];
}

Heap::Entry Heap::pop() {
    if (count() == 0) {
        throw underflow_error("invalid: empty");
    }

    Entry e = mData[0];
    mData[0] = mData[count()-1];
    mCount--;
    size_t i=0;
    size_t left, right;

    while (true) {
         left = i*2+1;
         right = i*2+2;

        if (left >= count()) {
            break;
        }

        if (right < count() && mData[right].score > mData[left].score) {
            if (mData[right].score > mData[i].score) {
                swap(mData, right, i);
                i = right;
                continue;
            }
        } else if (mData[left].score > mData[i].score) {
            swap(mData, left, i);
            i = left;
            continue;
        }

        break;
    }

    return e;
}

Heap::Entry Heap::pushpop(const Star&value, float score) {
    if (count() == 0) {
        throw underflow_error("invalid: empty");
    }

    Entry e = mData[0];
    Entry en;
    en.data = value;
    en.score = score;
    mData[0] = en;
    size_t i=0;
    size_t left, right;

     while (true) {
         left = i*2+1;
         right = i*2+2;

        if (left >= count()) {
            break;
        }

        if (right < count() && mData[right].score > mData[left].score) {
            if (mData[right].score > mData[i].score) {
                swap(mData, right, i);
                i = right;
                continue;
            }
        } else if (mData[left].score > mData[i].score) {
            swap(mData, left, i);
            i = left;
            continue;
        }

        break;
    }

    return e;

}

void Heap::push(const Star &value, float score) {
    if (count() == capacity()) {
        throw overflow_error("invalid: not enough space");
    }

    Entry e;
    e.data = value;
    e.score = score;
    mData[count()] = e;
    mCount++;
    size_t i=count()-1;
    while (i > 0 && mData[(i-1)/2].score < mData[i].score) {
        swap(mData, (i-1)/2, i);
        i = (i-1)/2;
    }
}

const Heap::Entry &Heap::top() const {
    if (count() == 0) {
        throw underflow_error("invalid: empty");
    }

    return mData[0];
}

void swap(Heap::Entry arr[], size_t a, size_t b) {
    Heap::Entry temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

