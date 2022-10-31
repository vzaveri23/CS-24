#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set set;

  
  // cout << set.insert("s") << endl;
  // cout << set.insert("d") << endl;
  // cout << set.insert("z") << endl;
  // cout << set.insert("q") << endl;
  // cout << set.insert("n") << endl;
  // cout << set.insert("w") << endl;
  // cout << set.insert("g") << endl;
  // cout << set.insert("b") << endl;
  // cout << set.insert("c") << endl;
  // cout << set.insert("a") << endl;
  
  cout << set.insert("d") << endl;
  cout << set.insert("b") << endl;
  cout << set.insert("e") << endl;
  cout << set.insert("a") << endl;
  cout << set.insert("c") << endl;
  cout << set.insert("f") << endl;

  set.clear();
  cout << "count: " << set.count() << endl;
  set.print();
  

  
  // cout << "count: " << set.count() << endl;



  // std::cout << "This program doesn't do anything interesting yet...\n";

  return 0;
}
