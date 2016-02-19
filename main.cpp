#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
void show_elem(const T& e) {
  cout << e << " ";
}

template<typename T>
void show_vec(const vector<T>& v) {
  for_each(begin(v), end(v), show_elem<T>);
  cout << endl;
}

void for_each_example() {
  vector<int> v{1, 2, 3, 4, 5};
  show_vec(v);
}

void all_of_example() {
  vector<int> r{1, 2, 3, 4, 5};
  show_vec(r);
  assert(all_of(begin(r), end(r), [](int i) { return i < 4; }) == false);
}

typedef pair<int, int> ipair;

bool adjacent_ipairs(const ipair& after, const ipair& before) {
  return after.first == before.second;
}

void mismatch_example() {
  vector<ipair> v{ipair(1, 2), ipair(2, 3), ipair(3, 4), ipair(4, 5)};
  pair<vector<ipair>::iterator, vector<ipair>::iterator> p;
  p = mismatch(begin(v), end(v), begin(v) + 1);
  vector<ipair>::iterator f = p.first;
  ipair d = *f;
  cout << "(" << d.first << ", " << d.second << ")" << endl;
  p = mismatch(begin(v) + 1, end(v), begin(v), adjacent_ipairs);
  f = p.first;
  d = *f;
  assert(f == end(v));
  f = p.second;
  d = *f;
  cout << "(" << d.first << ", " << d.second << ")" << endl;
}

void show_ipair(const ipair& ip) {
  cout << "(" << ip.first << ", " << ip.second << ")" << " ";
}

void mismatch_example_2() {
  vector<ipair> v{ipair(1, 2), ipair(2, 3), ipair(5, 5), ipair(5, 6)};
  pair<vector<ipair>::iterator, vector<ipair>::iterator> p;
  p = mismatch(begin(v) + 1, end(v), begin(v), adjacent_ipairs);
  vector<ipair> consecutive(begin(v), p.first);
  for_each(consecutive.begin(), consecutive.end(), show_ipair);
  cout << endl;
}

int main() {
  for_each_example();
  all_of_example();
  mismatch_example();
  mismatch_example_2();
  return 0;
}
