#include "counting.h"
#include "test_tools.h"

int main(){
    ListGraph G;
    ListGraph::Node n1 = G.addNode();
    ListGraph::Node n2 = G.addNode();
    ListGraph::Node n3 = G.addNode();
    G.addEdge(n1, n2);
    G.addEdge(n2, n3);
    G.addEdge(n1, n3);
    int tc = triangle_count(G);
    check(tc == 1, "");
    return 0;
}
