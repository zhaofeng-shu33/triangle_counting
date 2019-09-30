#include "io.h"
#include <string>
#include <fstream>
void construct_graph_from_bin(ListGraph& G, const char* file_name, int node_size){
    std::ifstream fin;
    fin.open(file_name, std::ifstream::binary | std::ifstream::in);
    fin.seekg(0, fin.end);
    int edge_size = fin.tellg();
    fin.seekg(0, fin.beg);    
    if (edge_size % 8 != 0){
        throw std::logic_error( std::string{} + "not multiply of 8 at " +  __FILE__ +  ":" + std::to_string(__LINE__));
    }
    edge_size /= 8;
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
}