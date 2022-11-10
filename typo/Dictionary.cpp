#include "Dictionary.h"
#include <cmath>
#include <iostream>
using namespace std;

double distance(Point, Point);
double score(double);
bool isLower(string);

Dictionary::Dictionary(istream &stream) {
    string line;
    while (getline(stream, line)) {
        if (isLower(line)) {
            mWords.push_back(line);
        }
    }
}

Heap Dictionary::correct(const vector<Point> &points, size_t maxcount, float cutoff) const {
    Heap h(maxcount);
    for (string s : mWords) {
        if (s.size() == points.size()) {
            double sc = 0;
            for (size_t i=0; i<s.size(); i++) {
                Point p1 = QWERTY[int(s[i])-97];
                sc += score(distance(p1, points[i]));
            }

            if (h.count() == maxcount) {
                if (sc/s.size() > h.top().score) {
                    h.pushpop(s, sc/s.size());
                }
            } else if (sc/s.size() >= cutoff) {
                h.push(s, sc/s.size());
            }
        } 
    }

    return h;
}

bool isLower(string s) {
    for (size_t i=0; i<s.size(); i++) {
        if (!islower(s[i])) {
            return false;
        }
    }

    return true;
}
double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x-p1.x, 2) + pow(p2.y-p1.y,  2));
}

double score(double distance) {
    return 1.0/(10.0*pow(distance, 2) + 1);
}