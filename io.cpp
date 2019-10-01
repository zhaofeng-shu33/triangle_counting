#include "io.h"
#include <string>
#include <fstream>
#if VERBOSE
#include <iostream>
#endif  
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
void construct_graph_from_bin(Graph& G, const char* file_name, int node_size){
    std::ifstream fin;
    fin.open(file_name, std::ifstream::binary | std::ifstream::in);
    int edge_size = get_edge(fin);
    std::vector<std::pair<int,int> > arcs;
    arcs.resize(edge_size);
#if VERBOSE
    std::cout << "Number of Nodes: " << node_size << std::endl;
    std::cout << "Number of Edges: " << edge_size << std::endl;
#endif
    char u_array[4], v_array[4];
    unsigned int *u, *v;
    for(int i = 0; i < edge_size; i++){
        fin.read(u_array, 4);
        fin.read(v_array, 4);
        u = (unsigned int*)u_array;
        v = (unsigned int*)v_array;
        arcs[i] = std::make_pair(*u, *v);
#if VERBOSE
    if(i % 1000000 == 1)
        std::cout << i << " edges added" << std::endl;
#endif        
    }
    fin.close();
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