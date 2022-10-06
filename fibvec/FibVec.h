//FibVec.h
#ifndef FIBVEC_H_
#define FIBVEC_H_
#include <cstddef>
using namespace std;

class FibVec {
    private:
       int *arr;
       size_t numVals;
       size_t prev_cap;
       size_t current_cap;
    public:
        FibVec();
        ~FibVec();
        size_t capacity() const;
        size_t count() const;
        void insert(int, size_t);
        int lookup(size_t) const;
        int pop();
        void push(int);
        int remove(size_t);
        FibVec slice(size_t, size_t) const;
        void resize(size_t);

};

#endif /* FIBVEC_H */