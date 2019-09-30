#include "io.h"
#include <string>
#include <fstream>
int get_edge(std::ifstream& fin){
    fin.seekg(0, fin.end);
    int edge_size = fin.tellg();
    fin.seekg(0, fin.beg);    
    if (edge_size % 8 != 0){
        throw std::logic_error( std::string{} + "not multiply of 8 at " +  __FILE__ +  ":" + std::to_string(__LINE__));
    }
    return edge_size / 8;
}
void construct_graph_from_bin(ListGraph& G, const char* file_name, int node_size){
    std::ifstream fin;
    fin.open(file_name, std::ifstream::binary | std::ifstream::in);
    int edge_size = get_edge(fin);
    G.reserveNode(node_size);
    for(int i = 0; i < node_size; i++){
        G.addNode();
    }
    char u_array[4], v_array[4];
    unsigned int *u, *v;
    for(int i = 0; i < edge_size; i++){
        fin.read(u_array, 4);
        fin.read(v_array, 4);
        u = (unsigned int*)u_array;
        v = (unsigned int*)v_array;
        G.addEdge(G.nodeFromId(*u), G.nodeFromId(*v));
    }
    fin.close();
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