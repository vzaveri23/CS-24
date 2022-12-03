#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <vector>
using namespace std;

// If you want to add any helper classes,
// here's some space to do it in.
struct Station;

struct Edge {
    int distance;
    string line;
    Station *src;
    Station *dst;
    bool isTrain;
};


struct Station {
    string name;
    vector<Edge*> neighbors;
};


struct Pair {
    int distance;
    Station *id;
    Station *prev;

    bool operator < (const Pair& other) const {
        return this->distance > other.distance;
    }
};

#endif
