#include "io.h"
#include <string>
#include <map>
#include <fstream>
#if VERBOSE
#include <iostream>
#endif  
namespace lemon{
unsigned long get_edge(std::ifstream& fin){
    fin.seekg(0, fin.end);
    unsigned long edge_size = fin.tellg();
    fin.seekg(0, fin.beg);    
    if (edge_size % 8 != 0){
        throw std::logic_error( std::string{} + "not multiply of 8 at " +  __FILE__ +  ":" + std::to_string(__LINE__));
    }
    return edge_size / 8;
}
unsigned long count_edges(const char* file_name){
    std::ifstream fin;
    fin.open(file_name, std::ifstream::binary | std::ifstream::in);
    unsigned long num_edges = get_edge(fin);
    fin.close();
    return num_edges;
}
std::pair<int, int> read_binfile_to_arclist(const char* file_name, std::vector<std::pair<int, int>>& arcs){
    std::ifstream fin;
    fin.open(file_name, std::ifstream::binary | std::ifstream::in);
    unsigned long file_size = get_edge(fin);
#if VERBOSE
    std::cout << "Start file reading..." << std::endl;
    int base_counter = file_size / 10 + 1;
#endif
    char u_array[4], v_array[4];
    unsigned int *u, *v;
    std::map<int, int> kv_map; 
    std::map<std::pair<int,int>, bool> arc_exist_map;
    int node_id = 1;
    for(unsigned long i = 0; i < file_size; i++){
#if VERBOSE
    if(i % base_counter == 1)
        std::cout << 10 * i / base_counter << "% processed for input file"  << std::endl;    
#endif        
        fin.read(u_array, 4);
        fin.read(v_array, 4);
        u = (unsigned int*)u_array;
        v = (unsigned int*)v_array;
        int& u_id = kv_map[*u];
        if(u_id == 0){
            u_id = node_id;
            node_id ++;
        }
        int& v_id = kv_map[*v];
        if(v_id == 0){
            v_id = node_id;
            node_id ++;
        }
        if(u_id < v_id){
            bool& arc_exist = arc_exist_map[std::make_pair(u_id, v_id)];
            if(arc_exist)
                continue;
            arc_exist = true;
        }
        else if(u_id > v_id){
            bool& arc_exist = arc_exist_map[std::make_pair(v_id, u_id)];
            if(arc_exist)
                continue;
            arc_exist = true;            
        }       
    }
    int actual_edge_num = arc_exist_map.size();
#if VERBOSE
    std::cout << "File reading finished" << std::endl;
    std::cout << "Actual node size " << node_id - 1<< std::endl;
    std::cout << "Actual edges " << actual_edge_num << std::endl;
#endif    
    fin.close();
    arcs.reserve(actual_edge_num);
    for(std::map<std::pair<int,int>, bool>::iterator it = arc_exist_map.begin(); it != arc_exist_map.end(); ++it){
        arcs.push_back(std::make_pair(it->first.first -1, it->first.second - 1));
    }
    return std::make_pair(node_id - 1, actual_edge_num);
}

void construct_graph_from_arclist(Graph& G, const std::vector<std::pair<int,int> >& arcs, int node_size){
    G.build(node_size, arcs.begin(), arcs.end());
#if VERBOSE
    std::cout << "Graph construction finished" << std::endl;
#endif
}

unsigned int count_nodes(const char* file_name){
    std::ifstream fin;
    fin.open(file_name, std::ifstream::binary | std::ifstream::in);
    int edge_size = get_edge(fin);
    char u_array[4];
    unsigned int *u;
    unsigned int max_id = 0;
    for(int i = 0; i < 2 * edge_size; i++){
        fin.read(u_array, 4);
        u = (unsigned int*)u_array;
        if(max_id < *u)
            max_id = *u;
    }
    fin.close();
    return max_id + 1;
}
}