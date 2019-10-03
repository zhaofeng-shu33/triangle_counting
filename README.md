[![Build Status](https://api.travis-ci.com/zhaofeng-shu33/triangle_counting.svg?branch=master)](https://travis-ci.com/zhaofeng-shu33/triangle_counting/)

# format of bin data file

为二进制文件，为顺序存放的边表。每条边包含两个顶点（源顶点和目的顶点，各占4个字节），边的存储长度为8个字节，文件的存储格式为：
源顶点（4字节，无符号整型）目的顶点（4字节，无符号整型）源顶点（4字节，无符号整型）目的顶点（4字节，无符号整型）

| dataset               | N(V)       | N(E)        | N(T)            |
|-----------------------|------------|-------------|-----------------|
| soc-LiveJournal1.bin  | 4,847,571  | 68,993,773  | 285,730,264     |
| s24.kron.edgelist.bin | 16,777,216 | 268,435,456 | 10,286,638,314  |

The homepage of LiveJournal dataset is hosted at [stanford](https://snap.stanford.edu/data/soc-LiveJournal1.html), both datasets are temporarily accessible at [LiveJournal1](http://datafountain.int-yt.com/BDCI2019/FeiMa/soc-LiveJournal1.bin) and [s24-kron](http://datafountain.int-yt.com/BDCI2019/FeiMa/s24.kron.edgelist.bin). These temporary data download links may be invalid. Notice that the record may have self looped edges and some edge occurs twice in the form (u, v) and (v, u) but some occurs only once. These details need some preprocessing task. Also the label of the node may not be continuous from 0 to |V| -1. Some mapping conversion is necessary.


程序运行方式
每个参赛组提交的程序将会以如下格式的命令运行、进行评测:
程序输入：-f 图数据文件（格式见表1和表2）
程序输出：
必须输出图数据文件中三角形个数的统计结果
输出格式： There are ?? triangles in the input graph.

## Our program
We use a naive method to count the triangles in the graph. The basic routine is a single thread counting function.

Use package manager to install `liblemon` and then use CMake to build the project in development.

For competition build, we provide a Makefile which produces `build/main` as the final executable with OpenMP enabled.

## Reference

1. [Lecture Notes on Triangle Counting Algorithms](https://cs.stanford.edu/~rishig/courses/ref/l1.pdf)

## Baseline

These results are obtained on a Ubuntu server with 32 Intel(R) Xeon(R) CPU E5-2620 v4 @ 2.10GHz.
| dataset | method                      | times(s) |
|---------|-----------------------------|----------|
| journal | single threaded node_first  | 63       |
| journal | single threaded edge_first  | 610      |
| journal | 32 threads node_first       | 15       |
| journal | 32 threads edge_first       | 102      |

## Our method
Internally, we use directed graph data structure to save space. The node id is from 0 to |V|-1. The arc id is from 0 to |E|-1. The arc direction is from i to j if i < j and (i, j) belongs to the edge set.
Once the directed graph is constructed, we provide two methods: edge iteration first and node iteration first method.

### Edge Iteration first

We enumerate very edge of the graph first. For each edge e of the graph, we count how many triangles there are including this edge. For this inner task, we are given the graph and edge (u,v). We enumerate every incident node w of u and figure out whether there is an edge (w,v) or not. Notice that the existence test of (w,v) has time complexity log d where d is the degree of node w.

### Node Iteration first

We enumerate every node of the graph first. For each node n of the graph, we count how many triangles there are including this node. For this inner task, we are given the graph and node n. We enumerate all its incident node pairs u and v which have larger degrees than n. If the degrees are same, we choose nodes with higher node id. Also, the existence test of (w,v) has time complexity log d where d is the degree of node w. This method is faster than the previous one for two reasons. One reason is that every triangle is counted only once. The other reason is that the sorting of degree makes each enumeration of (u,v) pairs not too much. That is, we save time of the total number of existence test.
There are also two drawbacks of this method. Firstly, it needs extra time to compute the degree of each node. This time is not included when comparing node-first with edge-first method. Secondly, it needs extra space to save the degree of each node and those nodes which have larger degree than node n.