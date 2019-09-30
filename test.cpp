#include "counting.h"
#include "test_tools.h"
#include "io.h"
void test_alg(){
    ListGraph G;
    ListGraph::Node n1 = G.addNode();
    ListGraph::Node n2 = G.addNode();
    ListGraph::Node n3 = G.addNode();
    G.addEdge(n1, n2);
    G.addEdge(n2, n3);
    G.addEdge(n1, n3);
    int tc = triangle_count(G);
    check(tc == 1, "");
}
void test_io(){
    ListGraph G;
    construct_graph_from_bin(G, "test_io.bin", 3);
    check(countEdges(G) == 3, "test_io fails");
    try{
        construct_graph_from_bin(G, "test_io_false.bin", 3);
    }
    catch(std::logic_error e){
        std::cout << "catched error with messge:" << std::endl << e.what() << std::endl;
    }
}

int main(){
    test_alg();
    test_io();
    return 0;
}
