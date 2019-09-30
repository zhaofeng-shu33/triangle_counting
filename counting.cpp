#include "counting.h"

int triangle_count_given_edge(const ListGraph& G, const ListGraph::Edge& e){
    ListGraph::Node u = G.u(e);
    ListGraph::Node v = G.v(e);
    int t_count = 0;
    ArcLookUp<ListGraph> look_up(G);
    for(ListGraph::IncEdgeIt e1(G, u); e1 != INVALID; ++e1){
        ListGraph::Node u_target = G.v(e1);
        ListGraph::Arc a = look_up(u_target, v);
        t_count += (a != INVALID);
    }
    return t_count;
}

int triangle_count(const ListGraph& G){
    int triangle_sum = 0;
    for(ListGraph::EdgeIt e(G); e != INVALID; ++e){
        triangle_sum += triangle_count_given_edge(G, e);
    }
    return triangle_sum / 3;
}

