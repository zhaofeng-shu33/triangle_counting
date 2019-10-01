#include <gtest/gtest.h>
#include <iostream>
#include "counting.h"
#include "test_tools.h"
#include "io.h"
TEST(counting, alg){
    Graph G;
    Graph::Node n1 = G.addNode();
    Graph::Node n2 = G.addNode();
    Graph::Node n3 = G.addNode();
    G.addEdge(n1, n2);
    G.addEdge(n2, n3);
    G.addEdge(n1, n3);
    int tc = triangle_count(G, 3);
    EXPECT_EQ(tc, 1);
}

TEST(io, io_bin){
    Graph G;
    construct_graph_from_bin(G, "test_io.bin", 3);
    EXPECT_EQ(countEdges(G), 3);
    EXPECT_THROW(construct_graph_from_bin(G, "test_io_false.bin", 3), std::logic_error);
}

TEST(io, get_node_num){
    unsigned int node_num = count_nodes("test_io.bin");
    EXPECT_EQ(node_num, 3);
}

TEST(counting, collect_degree_info){
    Graph G;
    Graph::Node n1 = G.addNode();
    Graph::Node n2 = G.addNode();
    Graph::Node n3 = G.addNode();
    G.addEdge(n1, n2);
    G.addEdge(n2, n3);
    std::vector<int> degree_list;    
    int max_degree = collect_degree_info(G, degree_list, 3);
    EXPECT_EQ(max_degree, 2);
    EXPECT_EQ(degree_list.size(), 3);
}

TEST(counting, alg_node_first){
    Graph G;
    Graph::Node n1 = G.addNode();
    Graph::Node n2 = G.addNode();
    Graph::Node n3 = G.addNode();
    G.addEdge(n1, n2);
    G.addEdge(n2, n3);
    G.addEdge(n1, n3);
    std::vector<int> degree_list;
    int max_degree = collect_degree_info(G, degree_list, 3);
    int tc = triangle_count_vertex_iteration(G, degree_list, max_degree);
    EXPECT_EQ(tc, 1);
}