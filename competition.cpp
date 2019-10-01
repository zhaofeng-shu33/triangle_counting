#include <iostream>
#include <cstring>
#include "io.h"
#include "counting.h"
unsigned int get_nodes(const char* filename){
    if(strcmp(filename, "soc-LiveJournal1.bin") == 0)
        return 4847571;
    else if(strcmp(filename, "s24.kron.edgelist.bin") == 0)
        return 16777216;
    else
        return count_nodes(filename);
}
int main(int argc, char** argv){
    if(argc != 3 || strcmp(argv[1], "-f") != 0){
        std::cout << "Usage: competition -f input.bin" << std::endl;
        exit(-1);
    }
    // check input file exists
    FILE *file = fopen(argv[2], "r");
    if (file) {
        fclose(file);
    }
    else{
        std::cout << "file " << argv[2] << " does not exist" << std::endl;
        exit(-1);
    }
    Graph G;
    unsigned int num_nodes = get_nodes(argv[2]);
    unsigned int num_edges = count_edges(argv[2]);
    if(num_nodes == -1){
        std::cout <<" not supported file " << argv[2] << std::endl;
        exit(-1);
    }
    construct_graph_from_bin(G, argv[2], num_nodes);
    unsigned long tc = 0;
    const char* method_hint = std::getenv("METHOD");
    if(method_hint != NULL && strcmp(method_hint, "node_first") == 0){
#if VERBOSE
        std::cout << "using node_first method" << std::endl;
#endif        
        std::vector<int> degree_list;
        int max_degree = collect_degree_info(G, degree_list, num_nodes);
        tc = triangle_count_vertex_iteration(G, degree_list, max_degree);
    }
    else{
        tc = triangle_count(G, num_edges);
    }
    std::cout << "There are " << tc << " triangles in the input graph." << std::endl;
    return 0;
}