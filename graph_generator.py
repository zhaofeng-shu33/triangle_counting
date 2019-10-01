import struct
import os
import argparse
import networkx as nx

BUILD_DIR = os.environ.get('BUILD_DIR', 'build')
def networkx_to_bin(G, filename):
    f = open(os.path.join(BUILD_DIR, filename), 'wb')
    for i,j in G.edges:
        f.write(struct.pack('2I', i, j))
    f.close()
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--task', default='test_required', choices=['test_required', 'complete_graph', 'random_graph'])
    parser.add_argument('--num_nodes', default=4, type=int)
    args = parser.parse_args()
    if args.task == 'test_required':
        f = open(os.path.join(BUILD_DIR, 'test_io.bin'), 'wb')
        f.write(struct.pack('6I',0,1,1,2,0,2))
        f.close()
        f = open(os.path.join(BUILD_DIR, 'test_io_false.bin'), 'wb')
        f.write(struct.pack('5I',0,1,1,2,0))
        f.close()
    elif args.task == 'complete_graph':
        num_nodes = args.num_nodes
        networkx_to_bin(nx.complete_graph(num_nodes), "complete_%d.bin" % num_nodes)
    elif args.task == 'random_graph':
        num_nodes = args.num_nodes
        networkx_to_bin(nx.binomial_graph(num_nodes, 0.5), "random_%d.bin" % num_nodes)

