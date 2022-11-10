#include "Heap.h"
#include <stdexcept>
using namespace std;

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

        if (right < count() && mData[right].score < mData[left].score) {
            if (mData[right].score < mData[i].score) {
                swap(mData, right, i);
                i = right;
                continue;
            }
        } else if (mData[left].score < mData[i].score) {
            swap(mData, left, i);
            i = left;
            continue;
        }

        break;
    }

    return e;
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (count() == 0) {
        throw underflow_error("invalid: empty");
    }

    Entry e = mData[0];
    Entry en;
    en.value = value;
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

        if (right < count() && mData[right].score < mData[left].score) {
            if (mData[right].score < mData[i].score) {
                swap(mData, right, i);
                i = right;
                continue;
            }
        } else if (mData[left].score < mData[i].score) {
            swap(mData, left, i);
            i = left;
            continue;
        }

        break;
    }

    return e;

}

void Heap::push(const std::string& value, float score) {
    if (count() == capacity()) {
        throw overflow_error("invalid: not enough space");
    }

    Entry e;
    e.value = value;
    e.score = score;
    mData[count()] = e;
    mCount++;
    size_t i=count()-1;
    while (mData[(i-1)/2].score > mData[i].score) {
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





