#include "Atlas.h"
#include "Helpers.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

Atlas* Atlas::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}

Atlas::Atlas(istream &stream) {
  string line, t, station, numS, lineName;
  int num = 0;
  int prevNum = 0;
  Station *prevStation;
  bool isTrain = false;
  while (getline(stream, line)) {
    if (line[0] == '#' || line.empty()) {
      continue;
    }

    istringstream iss(line);
    iss >> t;
    if (t == "BUS:" || t == "TRAIN:") {
      if (t == "TRAIN:") {
        isTrain = true;
      } else {
        isTrain = false;
      }

      iss >> ws;
      getline(iss, lineName);
      prevStation = nullptr;
      continue;
    }

    if (t == "-") {
      iss >> numS;
      num = stoi(numS);
      iss >> ws;
      getline(iss, station);
    }

    if (graph.count(station) == 0) {
      Station *s = new Station;
      s->name = station;
      graph[station] = s;
      if (prevStation == nullptr) {
        prevStation = s;
        prevNum = num;
      } else {
        Edge *e = new Edge;
        Edge *e2 = new Edge;

        e->src = prevStation;
        e->dst = s;
        e->line = lineName;
        e->isTrain = isTrain;

        e2->src = s;
        e2->dst = prevStation;
        e2->line = lineName;
        e2->isTrain = isTrain;

        if (isTrain) {
          e->distance = abs(num-prevNum);
          e2->distance = abs(num-prevNum);
        } else {
          e->distance = 0;
          e2->distance = 0;
        }

        s->neighbors.push_back(e);
        prevStation->neighbors.push_back(e2);
        prevStation = s;
        prevNum = num;
      }
    } else {
      Station *s = graph.at(station);
      if (prevStation == nullptr) {
        prevStation = s;
        prevNum = num;
      } else {
        Edge *e = new Edge;
        Edge *e2 = new Edge;

        e->src = prevStation;
        e->dst = s;
        e->line = lineName;
        e->isTrain = isTrain;

        e2->src = s;
        e2->dst = prevStation;
        e2->line = lineName;
        e2->isTrain = isTrain;

        if (isTrain) {
          e->distance = abs(num-prevNum);
          e2->distance = abs(num-prevNum);
        } else {
          e->distance = 0;
          e2->distance = 0;
          }

        s->neighbors.push_back(e);
        prevStation->neighbors.push_back(e2);
        prevStation = s;
        prevNum = num;
      }
    }
  }
}


Atlas::~Atlas() {
  for (auto [k, v] : graph) {
    for (Edge *e : v->neighbors) {
      delete e;
    }
    delete v;
  }
}

Trip Atlas::route(const string &src, const string &dst) {
  map<Station*, Edge*> visited;
  map<Station*, int> distances;
  priority_queue<Pair> heap;

  run_dijkstra(src, dst, visited, distances, heap);

  Trip trip;
  trip.start = src;
  Station *current = graph.at(dst);
  string prevLine = "";
  while (current->name != src) {
    if (visited.find(current) == visited.end()) {
      throw runtime_error("No route.");
    }
    Station *prev = visited.at(current)->dst;
    Trip::Leg leg;
    leg.line = visited.at(current)->line;
    leg.stop = visited.at(current)->src->name;
    if (leg.line != prevLine) {
      trip.legs.push_back(leg);
    }
  
    current = prev;
    prevLine = leg.line;
  }

  if (trip.legs.size() == 0) {
    throw runtime_error("No route.");
  }

  reverse(trip.legs.begin(), trip.legs.end());
  return trip;
}

void Atlas::run_dijkstra(const string &src, const string &dst, map<Station*, Edge*> &visited, map<Station*, int> &distances
, priority_queue<Pair> &heap) {
  for (auto [k, v] : graph) {
    distances[v] = INT_MAX;
  }

  Station *start = graph.at(src);
  distances[start] = 0;

  Pair p;
  p.distance = 0;
  p.edge = nullptr;

  heap.push(p);
  
  while (!heap.empty()) {
    Station *top;
    Edge *edge;
    if (heap.top().edge == nullptr) {
      top = graph.at(src);
      edge = nullptr;
    } else {
      top = heap.top().edge->src;
      edge = heap.top().edge;
    }

    heap.pop();
  
    if (visited.find(top) != visited.end()) {
      continue;
    } else {
        visited.insert({top, edge});
    }

    if (top->name == dst) {
      break;
    }

    for (Edge *e : top->neighbors) {
      if (e->distance + distances.at(top) < distances.at(e->src)) {
        distances[e->src] = e->distance + distances.at(top);
        Pair p;
        p.distance = e->distance + distances.at(top);
        p.edge = e;

        heap.push(p);
      }

    }
  }
}

