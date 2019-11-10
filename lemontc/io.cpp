// Copyright 2019 zhaofeng-shu33
#include "lemontc/io.h"

#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#if VERBOSE
#include <iostream>
#if TIMECOUNTING
#include <chrono>  // NOLINT(build/c++11)
#endif
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
                    std::vector<std::pair<int, int>>* arcs) {
    std::ifstream fin;
    fin.open(file_name, std::ifstream::binary | std::ifstream::in);
    int64_t file_size = get_edge(fin);
#if VERBOSE
#if TIMECOUNTING
    std::chrono::system_clock::time_point start_time =
        std::chrono::system_clock::now();
#endif
    std::cout << "Start file reading..." << std::endl;
    int base_counter = file_size / 10 + 1;
#endif
    char u_array[4], v_array[4];
    int *u, *v;
    std::map<int, int> kv_map;
    std::map<std::pair<int, int>, bool> arc_exist_map;
    int node_id = 1;
    for (int64_t i = 0; i < file_size; i++) {
#if VERBOSE
    if (i % base_counter == 1)
        std::cout << 10 * i / base_counter <<
                     "% processed for input file"  << std::endl;
#endif
        fin.read(u_array, 4);
        fin.read(v_array, 4);
        u = reinterpret_cast<int*>(u_array);
        v = reinterpret_cast<int*>(v_array);
        int& u_id = kv_map[*u];
        if (u_id == 0) {
            u_id = node_id;
            node_id++;
        }
        int& v_id = kv_map[*v];
        if (v_id == 0) {
            v_id = node_id;
            node_id++;
        }
        if (u_id < v_id) {
            bool& arc_exist = arc_exist_map[std::make_pair(u_id, v_id)];
            if (arc_exist)
                continue;
            arc_exist = true;
        } else if (u_id > v_id) {
            bool& arc_exist = arc_exist_map[std::make_pair(v_id, u_id)];
            if (arc_exist)
                continue;
            arc_exist = true;
        }
    }
    int actual_edge_num = arc_exist_map.size();
#if VERBOSE
#if TIMECOUNTING
    std::chrono::system_clock::time_point end_time =
        std::chrono::system_clock::now();
    std::chrono::system_clock::duration dtn =
        end_time - start_time;
    using std::chrono::duration_cast;
    typedef std::chrono::milliseconds milliseconds;
    float time_used = duration_cast<milliseconds>(dtn).count()/1000.0;
    std::cout << "File reading finished, Time used: " <<
                 time_used << "s" << std::endl;
#else
    std::cout << "File reading finished" << std::endl;
#endif
    std::cout << "Actual node size " << node_id - 1<< std::endl;
    std::cout << "Actual edges " << actual_edge_num << std::endl;
#endif
    fin.close();
    arcs->reserve(actual_edge_num);
    std::map<std::pair<int, int>, bool>::iterator it;
    for (it = arc_exist_map.begin();
         it != arc_exist_map.end(); ++it) {
        arcs->push_back(std::make_pair(it->first.first -1,
                        it->first.second - 1));
    }
    return std::make_pair(node_id - 1, actual_edge_num);
}

void construct_graph_from_arclist(Graph* G,
        const std::vector<std::pair<int, int> >& arcs, int node_size) {
    G->build(node_size, arcs.begin(), arcs.end());
#if VERBOSE
    std::cout << "Graph construction finished" << std::endl;
#endif
}

}  // namespace lemon
