# format of bin data file

为二进制文件，为顺序存放的边表。每条边包含两个顶点（源顶点和目的顶点，各占4个字节），边的存储长度为8个字节，文件的存储格式为：
源顶点（4字节，无符号整型）目的顶点（4字节，无符号整型）源顶点（4字节，无符号整型）目的顶点（4字节，无符号整型）

| dataset               | |V|        | |E|         | |T|             |
|-----------------------|------------|-------------|-----------------|
| soc-LiveJournal1.bin  | 4,847,571  | 68,993,773  | 645,730,392     |
| s24.kron.edgelist.bin | 16,777,216 | 268,435,456 |                 |

The label of the node starts from 0 to |V| - 1.

程序运行方式
每个参赛组提交的程序将会以如下格式的命令运行、进行评测:
程序输入：-f 图数据文件（格式见表1和表2）
程序输出：
必须输出图数据文件中三角形个数的统计结果
输出格式： There are ?? triangles in the input graph.

## Our program
We use a naive method to count the triangles in the graph. The basic routine is a single thread counting function.

Use package manager to install `liblemon` and then use CMake to build the project.

## Reference

1. [Lecture Notes on Triangle Counting Algorithms](https://cs.stanford.edu/~rishig/courses/ref/l1.pdf)

## Baseline

| dataset | method                     | times(s) |
|---------|----------------------------|----------|
| journal | single threaded smartgraph | 2088     |
