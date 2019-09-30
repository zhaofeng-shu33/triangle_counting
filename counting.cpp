#include "counting.h"

int triangle_count_given_edge(const ListGraph& G, const ListGraph::Edge& e){
    ListGraph::Node u = G.u(e);
    ListGraph::Node v = G.v(e);
    int t_count = 0;
    for(ListGraph::IncEdgeIt e1(G, u); e1 != INVALID; ++e1){
        t_count += 0;
    }
    return t_count;
}

int triangle_count(const ListGraph& G){
    int triangle_sum = 0;
    for(ListGraph::EdgeIt e(G); e != INVALID; ++e){
        triangle_sum += triangle_count_given_edge(G, e);
    }
    return triangle_sum;
}

