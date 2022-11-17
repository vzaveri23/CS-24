#include "StarMap.h"
#include "Helpers.h"
#include <sstream>
#include <cmath>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

void findHelp(KDTree::Node *, Heap, Star);
float distance(Star, Star);

StarMap* StarMap::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream);
}

StarMap::StarMap(istream &stream) {
  kt = new KDTree(stream);
}

StarMap::~StarMap() {
  delete kt;
}

vector<Star> StarMap::find(size_t n, float x, float y, float z) {
  Star ship;
  ship.x = x;
  ship.y = y;
  ship.z = z;
  Heap heap(n);
  vector<Star> result;
  findHelp(kt->root, heap, ship);
  for (size_t i=0; i<n; i++) {
    result.push_back(heap.pop().data);
  }

  reverse(result.begin(), result.end());
  return result;

}

void StarMap::findHelp(KDTree::Node *currentNode, Heap &heap, Star &ship) {
  if (currentNode == nullptr) {
    return;
  }

  if (!(heap.count() == heap.capacity())) {
    heap.push(currentNode->data, distance(currentNode->data, ship));
  }

  if (heap.count() == heap.capacity() && distance(currentNode->data, ship) < heap.top().score) {
    heap.pushpop(currentNode->data, distance(currentNode->data, ship));
  } 

  if (currentNode->axis == 0) {
    if (ship.x < currentNode->data.x) {
      findHelp(currentNode->left, heap, ship);
    } else {
      findHelp(currentNode->right, heap, ship);
    }
  } else if (currentNode->axis == 1) {
    if (ship.y < currentNode->data.y) {
      findHelp(currentNode->left, heap, ship);
    } else {
      findHelp(currentNode->right, heap, ship);
    }
  } else if (currentNode->axis == 2) {
     if (ship.z < currentNode->data.z) {
      findHelp(currentNode->left, heap, ship);
    } else {
      findHelp(currentNode->right, heap, ship);
    }
  }

  if (currentNode->axis == 0) {
    if ((ship.x - currentNode->data.x)*(ship.x - currentNode->data.x) < heap.top().score) {
      if (ship.x < currentNode->data.x) {
        findHelp(currentNode->right, heap, ship);
      } else {
        findHelp(currentNode->left, heap, ship);
      }
    }
  } else if (currentNode->axis == 1) {
    if ((ship.y - currentNode->data.y)*(ship.y - currentNode->data.y) < heap.top().score) {
      if (ship.y < currentNode->data.y) {
        findHelp(currentNode->right, heap, ship);
      } else {
        findHelp(currentNode->left, heap, ship);
      }
    }
  } else if (currentNode->axis == 2) {
    if ((ship.z - currentNode->data.z)*(ship.z - currentNode->data.z) < heap.top().score) {
      if (ship.z < currentNode->data.z) {
        findHelp(currentNode->right, heap, ship);
      } else {
        findHelp(currentNode->left, heap, ship);
      }
    }
  }


}

float distance(Star s1, Star s2) {
  return (s1.x-s2.x)*(s1.x-s2.x) + (s1.y-s2.y)*(s1.y-s2.y) + (s1.z-s2.z)*(s1.z-s2.z);
}






