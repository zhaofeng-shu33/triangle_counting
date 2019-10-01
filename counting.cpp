#include "counting.h"
#if VERBOSE
#include <iostream>
#endif        
int triangle_count_given_edge(const Graph& G, const Graph::Edge& e, const ArcLookUp<Graph>& look_up){
    Graph::Node u = G.u(e);
    Graph::Node v = G.v(e);
    int t_count = 0;
    
    for(Graph::IncEdgeIt e1(G, u); e1 != INVALID; ++e1){
        Graph::Node u_target = G.v(e1);
        Graph::Arc a = look_up(u_target, v);
        t_count += (a != INVALID);
    }
    return t_count;
}

unsigned long triangle_count(const Graph& G){
    ArcLookUp<Graph> look_up(G);
    unsigned long triangle_sum = 0;
#if VERBOSE
    int iteration_cnt = 0;
#endif        
    for(Graph::EdgeIt e(G); e != INVALID; ++e){
        triangle_sum += triangle_count_given_edge(G, e, look_up);
#if VERBOSE
    if(iteration_cnt % 500000 == 1)
        std::cout << iteration_cnt << " edges processed" << std::endl;
    iteration_cnt ++;
#endif
    }    
    return triangle_sum / 3;
}

