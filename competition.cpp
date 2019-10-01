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
    if(num_nodes == -1){
        std::cout <<" not supported file " << argv[2] << std::endl;
        exit(-1);
    }
    construct_graph_from_bin(G, argv[2], num_nodes);
    unsigned long tc = triangle_count(G);
    std::cout << "There are " << tc << " triangles in the input graph." << std::endl;
    return 0;
}