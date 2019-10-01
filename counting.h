#include "config.h"
unsigned long triangle_count(const Graph& G, int total_edge);
int collect_degree_info(const Graph& G, std::vector<int>& degree_list, int node_size);
unsigned long triangle_count_vertex_iteration(const Graph& G, const std::vector<int>& degree_list, int max_degree);