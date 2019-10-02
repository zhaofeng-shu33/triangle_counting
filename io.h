#include "config.h"
namespace lemon{
    std::pair<int, int> construct_graph_from_bin(Graph& G, const char* file_name);
    unsigned int count_nodes(const char* file_name);
    unsigned long count_edges(const char* file_name);
}