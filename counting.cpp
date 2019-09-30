#include "counting.h"
#if VERBOSE
#include <iostream>
#endif        
int triangle_count_given_edge(const ListGraph& G, const ListGraph::Edge& e, const ArcLookUp<ListGraph>& look_up){
    ListGraph::Node u = G.u(e);
    ListGraph::Node v = G.v(e);
    int t_count = 0;
    
    for(ListGraph::IncEdgeIt e1(G, u); e1 != INVALID; ++e1){
        ListGraph::Node u_target = G.v(e1);
        ListGraph::Arc a = look_up(u_target, v);
        t_count += (a != INVALID);
    }
    return t_count;
}

int triangle_count(const ListGraph& G){
    ArcLookUp<ListGraph> look_up(G);
    int triangle_sum = 0;
#if VERBOSE
    int iteration_cnt = 0;
#endif        
    for(ListGraph::EdgeIt e(G); e != INVALID; ++e){
        triangle_sum += triangle_count_given_edge(G, e, look_up);
#if VERBOSE
    if(iteration_cnt % 100000 == 1)
        std::cout << iteration_cnt << " edges processed" << std::endl;
    iteration_cnt ++;
#endif
    }    
    return triangle_sum / 3;
}

