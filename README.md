# Triangle Counting
[![Build Status](https://api.travis-ci.com/zhaofeng-shu33/triangle_counting.svg?branch=master)](https://travis-ci.com/zhaofeng-shu33/triangle_counting/)
[![Windows](https://ci.appveyor.com/api/projects/status/github/zhaofeng-shu33/triangle_counting?branch=master&svg=true)](https://ci.appveyor.com/project/zhaofeng-shu33/triangle-counting)
[![codecov](https://codecov.io/gh/zhaofeng-shu33/triangle_counting/branch/master/graph/badge.svg)](https://codecov.io/gh/zhaofeng-shu33/triangle_counting)
[![Documentation Status](https://readthedocs.org/projects/triangle-counting/badge/?version=latest)](https://triangle-counting.readthedocs.io/en/latest/?badge=latest)

## How to build

Use package manager to install `liblemon` and then use `CMake` to generate the build recipe.

## How to install
```shell
make install # default to /usr/local
```
## How to use
```shell
lemon-tc -f input.bin
```
The bin file has the following format. It uses 8 bytes to store an edge: source node id(4 bytes), sink node id(4 bytes) ... 

## Reference

1. [Lecture Notes on Triangle Counting Algorithms](https://cs.stanford.edu/~rishig/courses/ref/l1.pdf)

## Method used in detail
Internally, we use directed graph data structure to save space. The node id is from 0 to |V|-1. The arc id is from 0 to |E|-1. The arc direction is from i to j if i < j and (i, j) belongs to the edge set.
Once the directed graph is constructed, we provide two methods: edge iteration first and node iteration first method.

### Edge Iteration first

We enumerate every edge of the graph first. For each edge e of the graph, we count how many triangles there are including this edge. For this inner task, we are given the graph and edge (u,v). We enumerate every incident node w of u and figure out whether there is an edge (w,v) or not. Notice that the existence test of (w,v) has time complexity log d where d is the degree of node w.

### Node Iteration first

We enumerate every node of the graph first. For each node n of the graph, we count how many triangles there are including this node. For this inner task, we are given the graph and node n. We enumerate all its incident node pairs u and v which have larger degrees than n. If the degrees are same, we choose nodes with higher node id. Also, the existence test of (w,v) has time complexity log d where d is the degree of node w. This method is faster than the previous one for two reasons. One reason is that every triangle is counted only once. The other reason is that the sorting of degree makes each enumeration of (u,v) pairs not too much. That is, we save time of the total number of existence test.
There are also two drawbacks of this method. Firstly, it needs extra time to compute the degree of each node. This time is not included when comparing node-first with edge-first method. Secondly, it needs extra space to save the degree of each node and those nodes which have larger degree than node n.

## Baseline

See [another repository](https://github.com/zhaofeng-shu33/triangle_counting_benchmark) for detail.

