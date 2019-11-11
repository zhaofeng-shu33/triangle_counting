// Copyright 2019 zhaofeng-shu33
#include "lemontc/io.h"

#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#if VERBOSE
#include <iostream>
#if TIMECOUNTING
#include <chrono>  // NOLINT(build/c++11)
#endif
#endif

#if __GNUG__
#include <bits/stdc++.h>
#else
#define INT_MAX 2147483647
#endif

namespace lemon {
int64_t get_edge(std::ifstream& fin) {
    fin.seekg(0, fin.end);
    int64_t edge_size = fin.tellg();
    fin.seekg(0, fin.beg);
    if (edge_size % 8 != 0) {
        throw std::logic_error(std::string {} + "not multiply of 8 at " +
                               __FILE__ +  ":" + std::to_string(__LINE__));
    }
    return edge_size / 8;
}

std::pair<int, int> read_binfile_to_arclist(const char* file_name,
                    std::vector<std::pair<int, int>>* arcs_pointer) {
    std::ifstream fin;
    fin.open(file_name, std::ifstream::binary | std::ifstream::in);
    int64_t file_size = get_edge(fin);
    std::vector<std::pair<int, int>>& arcs = *arcs_pointer;
#if VERBOSE
    std::cout << "num of edges before cleanup: " << file_size << std::endl;
#endif
    arcs.resize(file_size);
    fin.read(reinterpret_cast<char*>(arcs.data()),
        2 * file_size * sizeof(int));
    int node_num = 0;
    for (std::vector<std::pair<int, int>>::iterator it = arcs.begin();
        it != arcs.end(); ++it) {
        if (it->first > node_num) {
            node_num = it->first;
        } else if (it->second > node_num) {
            node_num = it->second;
        }
        if (it->first == it->second) {
            it->first = INT_MAX;
            it->second = INT_MAX;
        } else if (it->first > it->second) {
            std::swap(it->first, it->second);
        }
    }
    // sort arcs
    std::sort(arcs.begin(), arcs.end());
    // remove the duplicate
    std::pair<int, int> last_value = arcs[0];
    for (int64_t i = 1; i < arcs.size() - 1; i++) {
        while (arcs[i].first == last_value.first &&
               arcs[i].second == last_value.second) {
            arcs[i].first = INT_MAX;
            arcs[i].second = INT_MAX;
            i++;
        }
        last_value = arcs[i];
    }
    // sort arcs again
    std::sort(arcs.begin(), arcs.end());
    // find the number of duplicate edges
    int edges = 0;
    while (edges < arcs.size()) {
        if (arcs[edges].first == INT_MAX) {
            break;
        }
        edges++;
    }
    arcs.resize(edges);
    return std::make_pair(node_num + 1, edges);
}

void construct_graph_from_arclist(Graph* G,
        const std::vector<std::pair<int, int> >& arcs, int node_size) {
    G->build(node_size, arcs.begin(), arcs.end());
#if VERBOSE
    std::cout << "Graph construction finished" << std::endl;
#endif
}

}  // namespace lemon
