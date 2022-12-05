#ifndef ATLAS_H
#define ATLAS_H

#include <istream>
#include <string>
#include "Trip.h"
#include "Helpers.h"
#include <set>
#include <queue>
#include <map>
using namespace std;


class Atlas {
public:
  // Required Class Function
  static Atlas* create(std::istream& stream);

private:
  // Member Variables
  map<string, Station *> graph;
public:
  // Constructor & Destructor
  Atlas(std::istream& stream);
  ~Atlas();

  // Required Member Function
  Trip route(const std::string& src, const std::string& dst);
  void run_dijkstra(const string &, const string &, map<Station*, Edge*> &, map<Station*, int> &, priority_queue<Pair> &);
};

#endif
