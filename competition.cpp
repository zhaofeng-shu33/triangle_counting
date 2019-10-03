#include <iostream>
#include <cstring>
#include "io.h"
#include "counting.h"
#include "cpu_forward/graph.h"
#include "cpu_forward/cpu.h"
using namespace lemon;

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
#if VERBOSE && OPENMP
    std::cout << "OPENMP enabled." << std::endl;
#endif
    int num_nodes, num_edges;
    const char* method_hint = std::getenv("METHOD");
    cpu_forward::AdjList adjlist;
    {
#if VERBOSE && OPENMP
        // check openmp threads number
        int actual_num_threads = 0;
        #pragma omp parallel shared(actual_num_threads)
        {
            #pragma omp critical
            actual_num_threads = actual_num_threads + 1;
        }
        std::cout << "Num of threads used: " << actual_num_threads << std::endl;
#endif        
        // data loader block
        std::vector<std::pair<int, int>> arcs;
        std::tie(num_nodes, num_edges) = read_binfile_to_arclist(argv[2], arcs);
        if(method_hint == NULL || strcmp(method_hint, "cpu_forward") != 0){
        construct_graph_from_arclist(G, arcs, num_nodes);
        }
        else{
            cpu_forward::Edges& edges = arcs;
            adjlist = cpu_forward::EdgesToAdjList(edges);
        }
        // destroy arcs to save memory
    }
    unsigned long tc = 0;
    if(method_hint == NULL){
        tc = triangle_count(G, num_edges);
    }
    else if(strcmp(method_hint, "node_first") == 0){
#if VERBOSE
        std::cout << "using node_first method" << std::endl;
#endif
        std::vector<int> degree_list;
        int max_degree = collect_degree_info(G, degree_list, num_nodes);
        tc = triangle_count_vertex_iteration(G, degree_list, max_degree);
    }
    else if(strcmp(method_hint, "cpu_forward") == 0){
#if VERBOSE
        std::cout << "using cpu_forward method" << std::endl;
#endif           
        tc = cpu_forward::CpuForward(adjlist);
    }
    else{ // for other unknown method
        tc = triangle_count(G, num_edges);
    }
    std::cout << "There are " << tc << " triangles in the input graph." << std::endl;
    return 0;
}