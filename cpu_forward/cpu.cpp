#include "cpu.h"
#include "timer.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>
#include <utility>
#if VERBOSE
#include <iostream>
#endif     

namespace cpu_forward{
template <class InputIterator1, class InputIterator2>
int IntersectionSize(
    InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2) {
  int result = 0;
  while (first1 != last1 && first2 != last2) {
    if (*first1 < *first2)
      ++first1;
    else if (*first1 > *first2)
      ++first2;
    else {
      ++result;
      ++first1;
      ++first2;
    }
  }
  return result;
}
  // namespace

uint64_t CpuForward(const AdjList& graph) {
  const int n = graph.size();
  std::vector<std::vector<int>> A(n);
  
  std::vector<std::pair<int, int>> deg(n);
  for (int i = 0; i < n; ++i)
    deg[i] = std::make_pair(graph[i].size(), i);
  std::sort(deg.begin(), deg.end(), std::greater<std::pair<int, int>>());
  // perm maps the graph node id to its position iwhtin the deg list
  std::vector<int> perm(n);
  for (int i = 0; i < n; ++i)
    perm[deg[i].second] = i;

  uint64_t c = 0;
  for (int i = 0; i < n; ++i) {
    const int s = deg[i].second;
    for (const int t : graph[s]) {
      // node t has less degree than node s
      if (perm[t] <= i) continue;
      c += IntersectionSize(A[s].begin(), A[s].end(), A[t].begin(), A[t].end());
      A[t].push_back(i);
    }
#if VERBOSE
    if(i % 500000 == 1)
        std::cout << i << " nodes processed" << std::endl;
#endif     
  }

  return c;
}

uint64_t CpuCompactForward(const AdjList& graph) {
  const int n = graph.size();

  std::vector<std::pair<int, int>> deg;
  deg.reserve(n);
  for (int i = 0; i < n; ++i)
    deg.push_back(std::make_pair(graph[i].size(), i));
  std::sort(deg.begin(), deg.end(), std::greater<std::pair<int, int>>());
  std::vector<int> perm(n);
  for (int i = 0; i < n; ++i)
    perm[deg[i].second] = i;
 
  AdjList sorted_graph(n);
  for (int i = 0; i < n; ++i) {
    const std::vector<int>& src = graph[i];
    const int s = perm[i];
    std::vector<int>& dst = sorted_graph[s];
    dst.reserve(src.size());  // this wastes some memory but saves a lot of time
    for (int t : src) {
      t = perm[t];
      if (t < s)
        dst.push_back(t);
    }
    sort(dst.begin(), dst.end());
  }

  uint64_t c = 0;
  for (int s = 0; s < n; ++s) {
    for (const int t : sorted_graph[s]) {
      c += IntersectionSize(
          sorted_graph[s].begin(), sorted_graph[s].end(),
          sorted_graph[t].begin(), sorted_graph[t].end());
    }
  }

  return c;
}

uint64_t CpuCompactForwardForEdgeArray(const Edges& edges) {
  std::unique_ptr<Timer> timer(Timer::NewTimer());
    
  const int n = NumVertices(edges);
  timer->Done("Calculate number of vertices");
  
  Edges sorted_edges;
  {
    std::vector<int> deg(n);
    for (const std::pair<int, int>& edge : edges)
      deg[edge.first]++;
    timer->Done("Calculate degrees");
    std::vector<std::pair<int, int>> temp(n);
    for (int i = 0; i < n; ++i)
      temp[i] = std::make_pair(n - deg[i], i);
    std::sort(temp.begin(), temp.end());
    std::vector<int> rename(n);
    for (int i = 0; i < n; ++i)
      rename[temp[i].second] = i;
    timer->Done("Calculate renaming permutation");
    sorted_edges.reserve(edges.size() / 2);
    for (const std::pair<int, int>& edge : edges) {
      int s = edge.first, t = edge.second;
      s = rename[s];
      t = rename[t];
      if (s > t)
        sorted_edges.push_back(std::make_pair(s, t));
    }
    timer->Done("Copy and rename edges");
    sort(sorted_edges.begin(), sorted_edges.end());
    timer->Done("Sort edges");
  }

  std::vector<int> heads(sorted_edges.size());
  for (int i = 0; i < sorted_edges.size(); ++i)
    heads[i] = sorted_edges[i].second;

  std::vector<std::vector<int>::iterator> nodes;
  nodes.reserve(n + 1);
  for (int k = 0; k <= sorted_edges.front().first; ++k)
    nodes.push_back(heads.begin());
  for (int i = 1; i < sorted_edges.size(); ++i)
    if (sorted_edges[i-1].first != sorted_edges[i].first) {
      int k = sorted_edges[i].first - sorted_edges[i-1].first;
      while (k--)
        nodes.push_back(heads.begin() + i);
    }
  while (nodes.size() < n + 1)
    nodes.push_back(heads.end());

  timer->Done("Copy edges and calculate nodes");
  uint64_t c = 0;
  for (const std::pair<int, int>& edge : sorted_edges) {
    const int s = edge.first, t = edge.second;
    c += IntersectionSize(nodes[s], nodes[s+1], nodes[t], nodes[t+1]);
  }
  return c;
}
}