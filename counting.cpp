#include "counting.h"
#if VERBOSE
#include <iostream>
#endif
#if TIMECOUNTING
#include <iostream>
#include <chrono>
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
#if TIMECOUNTING
    std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
#endif    
    for(Graph::EdgeIt e(G); e != INVALID; ++e){
        triangle_sum += triangle_count_given_edge(G, e, look_up);
#if VERBOSE
    if(iteration_cnt % 500000 == 1)
        std::cout << iteration_cnt << " edges processed" << std::endl;
    iteration_cnt ++;
#endif
    }
#if TIMECOUNTING
    std::chrono::system_clock::time_point end_time = std::chrono::system_clock::now();
    std::chrono::system_clock::duration dtn = end_time - start_time;
    float time_used = std::chrono::duration_cast<std::chrono::milliseconds>(dtn).count()/1000.0;
    std::cout << "Time used: " << time_used << "s" << std::endl;
#endif        
    return triangle_sum / 3;
}

