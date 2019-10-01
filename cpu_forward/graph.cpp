#include "graph.h"

#include <algorithm>
#include <fstream>
namespace cpu_forward{
using namespace std;
int get_edge(std::ifstream& fin){
    fin.seekg(0, fin.end);
    int edge_size = fin.tellg();
    fin.seekg(0, fin.beg);    
    if (edge_size % 8 != 0){
        throw std::logic_error( std::string{} + "not multiply of 8 at " +  __FILE__ +  ":" + std::to_string(__LINE__));
    }
    return edge_size / 8;
}
unsigned int count_edges(const char* file_name){
    std::ifstream fin;
    fin.open(file_name, std::ifstream::binary | std::ifstream::in);
    unsigned int num_edges = get_edge(fin);
    fin.close();
    return num_edges;
}
Edges ReadEdgesFromFile(const char* filename) {
  Edges edges;
  int m = count_edges(filename);
  ifstream in(filename, ios::binary);
    char u_array[4], v_array[4];
    unsigned int *u, *v;
    for(int i = 0; i < m; i++){
        in.read(u_array, 4);
        in.read(v_array, 4);
        u = (unsigned int*)u_array;
        v = (unsigned int*)v_array;
        if(*u >= *v)
            continue;
        edges.push_back(std::make_pair(*u, *v));
    }

  return edges;
}

void WriteEdgesToFile(const Edges& edges, const char* filename) {
  ofstream out(filename, ios::binary);
  int m = edges.size();
  out.write((char*)&m, sizeof(int));
  out.write((char*)edges.data(), 2 * m * sizeof(int));
}

int NumVertices(const Edges& edges) {
  int num_vertices = 0;
  for (const pair<int, int>& edge : edges)
    num_vertices = max(num_vertices, 1 + max(edge.first, edge.second));
  return num_vertices;
}

void RemoveDuplicateEdges(Edges* edges) {
  sort(edges->begin(), edges->end());
  edges->erase(unique(edges->begin(), edges->end()), edges->end());
}

void RemoveSelfLoops(Edges* edges) {
  for (int i = 0; i < edges->size(); ++i) {
    if ((*edges)[i].first == (*edges)[i].second) {
      edges->at(i) = edges->back();
      edges->pop_back();
      --i;
    }
  }
}

void MakeUndirected(Edges* edges) {
  const size_t n = edges->size();
  for (int i = 0; i < n; ++i) {
    pair<int, int> edge = (*edges)[i];
    swap(edge.first, edge.second);
    edges->push_back(edge);
  }  
}

void PermuteEdges(Edges* edges) {
  random_shuffle(edges->begin(), edges->end());
}

void PermuteVertices(Edges* edges) {
  vector<int> p(NumVertices(*edges));
  for (int i = 0; i < p.size(); ++i)
    p[i] = i;
  random_shuffle(p.begin(), p.end());
  for (pair<int, int>& edge : *edges) {
    edge.first = p[edge.first];
    edge.second = p[edge.second];
  }
}

AdjList EdgesToAdjList(const Edges& edges) {
  // Sorting edges with std::sort to optimize memory access pattern when
  // creating graph gives less than 20% speedup.
  AdjList graph(NumVertices(edges));
  for (const pair<int, int>& edge : edges){
    graph[edge.first].push_back(edge.second);
    graph[edge.second].push_back(edge.first);
  }
  return graph;
}
}