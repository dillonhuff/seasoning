#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
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
  vector<ipair> v{{1, 2}, {2, 3}, {3, 4}, {4, 5}};
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
  vector<ipair> v{{1, 2}, {2, 3}, {5, 5}, {5, 6}};
  pair<vector<ipair>::iterator, vector<ipair>::iterator> p;
  p = mismatch(begin(v) + 1, end(v), begin(v), adjacent_ipairs);
  vector<ipair> consecutive(begin(v), p.first);
  for_each(consecutive.begin(), consecutive.end(), show_ipair);
  cout << endl;
}

void iota_example() {
  vector<int> v{0, 0, 0, 0, 0};
  iota(v.begin(), v.end(), 0);
  show_vec(v);
}

vector<int>& sum_next(vector<int>& sums,
		      int next) {
  int res = sums.back() + next;
  sums.push_back(res);
  return sums;
}

void accumulate_example() {
  vector<int> v(10);
  iota(v.begin(), v.end(), 1);
  vector<int> successive_sums{0};
  vector<int> k = accumulate(v.begin(),
			     v.end(),
			     successive_sums,
			     sum_next);
  show_vec(k);
  cout << "last sum = " << k.back() << endl;
}

void partial_sum_example() {
  vector<double> v(10);
  iota(v.begin(), v.end(), 1);
  show_vec(v);
  vector<double> sums(v.size());
  partial_sum(v.begin(), v.end(), sums.begin());
  show_vec(sums);
}

int cmp_ints(int l, int r) {
  return l == r ? 1 : 0;
}

void inner_product_example() {
  vector<int> l{0, 12, 4, 134, 9, 4, 7};
  vector<int> r{1, 12, 3, 134, 8, 3, 7, 9};
  int res = inner_product(l.begin(), l.end(), r.begin(), 0);
  cout << "res = " << res << endl;
  int num_matching = inner_product(l.begin(), l.end(),
				   r.begin(),
				   0,
				   std::plus<int>(),
				   cmp_ints);
  cout << "Num matching = " << num_matching << endl;
}

int num_transition(int r, int l) {
  return r == l ? 0 : -1*r;
}

bool sort_gt(int l, int r) {
  return l > r;
}

void stable_sort_and_adjacent_difference_example() {
  vector<int> l{1, 3, 1, 5, 6, 2, 6, 6, 1, 3, 1};
  stable_sort(l.begin(), l.end(), sort_gt);
  cout << "Sorted" << endl;
  show_vec(l);
  vector<int> transitions(l.size() - 1);
  adjacent_difference(l.begin(), l.end(), transitions.begin() - 1, num_transition);
  show_vec(transitions);
}

void rotate_example() {
  vector<int> l{1, 2, 3, 4, 5};
  rotate(l.begin(), l.begin() + 1, l.begin() + 3);
  show_vec(l);
}

void permutation_and_reverse_example() {
  cout << "Forward Permutations" << endl;
  vector<int> v{1, 2, 3};
  do {
    show_vec(v);
  } while (next_permutation(v.begin(), v.end()));

  cout << "Reverse permutations" << endl;

  reverse(v.begin(), v.end());

  do {
    show_vec(v);
  } while (prev_permutation(v.begin(), v.end()));
}

void adjacent_find_example() {
  vector<int> v{1, 2, 3, 4, 5, 5, 5, 6, 7, 8};
  vector<int>::iterator p = adjacent_find(v.begin(), v.end());
  vector<int> after_adjacent_find(p, v.end());
  cout << "After adjacent find" << endl;
  show_vec(after_adjacent_find);
}

struct gt {
  int i;
  gt(int ip) : i(ip) {}
  bool operator()(int p) { return p > i; }
};
  
void find_if_example() {
  vector<int> v{1, 2, 1, 7, 8, 2, 7};
  vector<int> drop_7(find(v.begin(), v.end(), 7), v.end());
  cout << "Dropping all before 7" << endl;
  show_vec(drop_7);
  vector<int> drop_lt_5(find_if(v.begin(), v.end(), gt(5)), v.end());
  cout << "Dropping while less than 5" << endl;
  show_vec(drop_lt_5);
}

void heap_example() {
  cout << "Heap" << endl;
  vector<int> h{1, 5, 2, 4, -1, 6};
  make_heap(h.begin(), h.end());
  show_vec(h);
  h.push_back(7);
  show_vec(h);
  push_heap(h.begin(), h.end());
  show_vec(h);
  pop_heap(h.begin(), h.end());
  int x = h.back();
  h.pop_back();
  cout << "heap pop result = " << x << endl;
  show_vec(h);
}

void unique_example() {
  vector<int> v{1, 1, 2, 3, 4, 4, 4, 4};
  cout << "v before unique" << endl;
  show_vec(v);
  v.erase(unique(v.begin(), v.end()), v.end());
  cout << "v after unique" << endl;
  show_vec(v);

  vector<int> k{1, 2, 3, 4, 5, 4, 3, 2, 1};
  cout << "k before unique" << endl;
  show_vec(k);
  k.erase(unique(k.begin(), k.end(), [](int l, int r) { return l < r; }), k.end());
  cout << "k after unique" << endl;
  show_vec(k);
}

int main() {
  for_each_example();
  all_of_example();
  mismatch_example();
  mismatch_example_2();
  iota_example();
  accumulate_example();
  partial_sum_example();
  inner_product_example();
  stable_sort_and_adjacent_difference_example();
  rotate_example();
  permutation_and_reverse_example();
  adjacent_find_example();
  find_if_example();
  heap_example();
  unique_example();
  return 0;
}
