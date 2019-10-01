#include <gtest/gtest.h>
#include <iostream>
#include "counting.h"
#include "test_tools.h"
#include "io.h"
TEST(counting, alg){
    Graph G;
    std::vector<std::pair<int,int> > arcs;
    arcs.push_back(std::make_pair(0,1));
    arcs.push_back(std::make_pair(0,2));
    arcs.push_back(std::make_pair(1,2));
    G.build(3, arcs.begin(), arcs.end());    
    int tc = triangle_count(G, 3);
    EXPECT_EQ(tc, 1);
}

TEST(io, io_bin){
    Graph G;
    construct_graph_from_bin(G, "test_io.bin", 3);
    EXPECT_EQ(countArcs(G), 3);
    EXPECT_THROW(construct_graph_from_bin(G, "test_io_false.bin", 3), std::logic_error);
}

TEST(io, get_node_num){
    unsigned int node_num = count_nodes("test_io.bin");
    EXPECT_EQ(node_num, 3);
}

TEST(counting, collect_degree_info){
    Graph G;
    std::vector<std::pair<int,int> > arcs;
    arcs.push_back(std::make_pair(0,1));
    arcs.push_back(std::make_pair(1,2));
    G.build(3, arcs.begin(), arcs.end());    
    std::vector<int> degree_list;    
    int max_degree = collect_degree_info(G, degree_list, 3);
    EXPECT_EQ(max_degree, 2);
    EXPECT_EQ(degree_list.size(), 3);
}

TEST(counting, alg_node_first){
    Graph G;
    std::vector<std::pair<int,int> > arcs;
    arcs.push_back(std::make_pair(0,1));
    arcs.push_back(std::make_pair(0,2));
    arcs.push_back(std::make_pair(1,2));
    G.build(3, arcs.begin(), arcs.end());    
    std::vector<int> degree_list;
    int max_degree = collect_degree_info(G, degree_list, 3);
    int tc = triangle_count_vertex_iteration(G, degree_list, max_degree);
    EXPECT_EQ(tc, 1);
}

TEST(counting, alg_node_first_zero_triangle){
    Graph G;
    std::vector<std::pair<int,int> > arcs;
    arcs.push_back(std::make_pair(0,1));
    arcs.push_back(std::make_pair(1,2));
    G.build(3, arcs.begin(), arcs.end());    
   std::vector<int> degree_list;    
    int max_degree = collect_degree_info(G, degree_list, 3);
    int tc = triangle_count_vertex_iteration(G, degree_list, max_degree);
    EXPECT_EQ(tc, 0);
}