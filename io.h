#include "config.h"
namespace lemon{
    void construct_graph_from_bin(Graph& G, const char* file_name, int node_size);
    unsigned int count_nodes(const char* file_name);
    unsigned int count_edges(const char* file_name);
}