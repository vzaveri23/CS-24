#include "GenePool.h"
using namespace std;
#include <iostream>

// GenePool Member Functions

GenePool::GenePool(istream &stream) {
    string line;
    while (getline(stream, line)) {
        if (line[0] == '#' || line.empty()) {
            continue;
        }

        istringstream iss(line);
        string t;
        size_t count=0;
        string name;
        Gender gender;
        Person *mother;
        Person *father;
        while (getline(iss, t, '\t')) {
            switch(count) {
                case 0:
                    name = t;
                    break;
                case 1:
                    if (t == "male") {
                        gender = Gender::MALE;
                    } else {
                        gender = Gender::FEMALE;
                    }
                    break;
                case 2:
                    if (t == "???") {
                        mother = nullptr;
                    } else {
                        mother = find(t);
                    }
                    break;
                case 3:
                    if (t == "???") {
                        father = nullptr;
                    } else {
                        father = find(t);
                    }
                    break;
            }

            count++;
        }

        Person *ptr = new Person(name, gender, mother, father);
        people[name] = ptr;
        if (mother) {
            mother->addChild(ptr);
        }

        if (father) {
            father->addChild(ptr);
        }
    }
}

GenePool::~GenePool() {
    for (auto [k, v] : people) {
        delete v;
    }
}

Person* GenePool::find(const string &name) const {
    return (people.count(name)==0) ? nullptr : people.at(name);
}
