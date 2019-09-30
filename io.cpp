#include "io.h"
#include <fstream>
void construct_graph_from_bin(ListGraph& G, const char* file_name, int node_size){
    G.reserveNode(node_size);
    for(int i = 0; i < node_size; i++){
        G.addNode();
    }
    std::ifstream fin(file_name, std::ifstream::binary | std::ifstream::in);
    unsigned int u, v;
    while(fin.good()){
        fin >> u >> v;
        G.addEdge(G.nodeFromId(u), G.nodeFromId(v));
    }
}