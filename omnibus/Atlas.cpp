#include "Atlas.h"
#include "Helpers.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <climits>
using namespace std;

Atlas* Atlas::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}

Atlas::Atlas(istream &stream) {
  string line, t, station, numS, lineName;
  int num, prevNum;
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

  // for (auto [k, v] : graph) {
  //   cout << k << ": ";
  //   for (Edge *e:v->neighbors) {
  //     cout << e->src->name << " ";
  //   }

  //   cout << endl;
  // }
}


Atlas::~Atlas() {
  for (auto [k, v] : graph) {
    delete v;
  }
}

Trip Atlas::route(const string &src, const string &dst) {
  map<Station*, Edge*> visited;
  map<Station*, int> distances;
  priority_queue<Pair> heap;
  // map<Station*, bool> ifVisited;
  // vector<Station*> path;
  // bool isBreak = false;

  for (auto [k, v] : graph) {
    distances[v] = INT_MAX;
    visited[v] = nullptr;
  }

  Station *start = graph.at(src);
  distances[start] = 0;

  Pair p;
  p.distance = 0;
  p.id = start;
  p.prev = nullptr;

  heap.push(p);

  // while (heap.size() > 0) {
  //   Station *top = heap.top().id;
  //   heap.pop();
  //   for (Edge *e : top->neighbors) {
  //     if (e->src->name == dst) {
  //       Station *end = graph.at(dst);
  //       visited.insert({end, e});
  //       isBreak = true;
  //       break;
  //     }

  //     if (visited.find(e->src) == visited.end()) {
  //       visited.insert({top, e});

  //       if (e->distance + distances.at(top) < distances.at(e->src)) {
  //         distances[e->src] = e->distance + distances.at(top);
  //         Pair p;
  //         p.distance = e->distance + distances.at(top);
  //         p.prev = top;
  //         p.id = e->src;
  //         heap.push(p);
  //       }

  //     }
  //   }

  //   if (isBreak) {
  //      break;
  //   }

  // }

  while (heap.size()>0) {
    Station *top = heap.top().id;
    heap.pop();
    // int parentDistance = distances.at(top);
    if (top->name == dst) {
      break;
    }
    if (top || distances.at(top) != INT_MAX) {
      for (Edge *e : top->neighbors) {
        if(distances.at(top) + e->distance < distances.at(e->src))
        {
          distances[e->src] = distances.at(top) + e->distance;
          visited[top] = e;
          Pair p;
          p.distance = distances.at(top) + e->distance;
          p.id = e->src;
          p.prev = top;
          heap.push(p);
        }
      }
    }
  
    // for (Edge *e : top->neighbors) {
    //   if (visited.find(e->dst) == visited.end()) {
    //     visited.insert({e->dst, e});
    //     if (parentDistance + e->distance < distances.at(e->src)) {
    //       distances[e->src] = parentDistance + e->distance;
    //       Pair p;
    //       p.distance = parentDistance + e->distance;
    //       p.id = e->dst;
    //       p.prev = top;
    //       heap.push(p);
    //     }
    //   }
    // }

    // if (isBreak) {
    //   break;
    // }
  }

  for (auto [k, v] : visited) {
    cout << k->name << ": " << v->src->name << endl;
  }


  Trip trip;
  // trip.start = src;
  // auto itr = visited.at(graph.at(dst));

  // while (itr->src->name != src) {
  //   Trip::Leg leg;
  //   leg.line = itr->line;
  //   leg.stop = itr->src->name;
  //   trip.legs.push_back(leg);
  //   itr = visited.at(graph.at(itr->src->name));
  // }


  // if (trip.legs.size() == 0) {
  //   throw runtime_error("No route.");
  // }

  // reverse(trip.legs.begin(), trip.legs.end());
  return trip;
}

