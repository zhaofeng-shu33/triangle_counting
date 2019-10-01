import struct
import os
import networkx as nx

BUILD_DIR = os.environ.get('BUILD_DIR', 'build')
def networkx_to_bin(G, filename):
    f = open(os.path.join(BUILD_DIR, filename), 'wb')
    for i,j in G.edges:
        f.write(struct.pack('2I', i, j))
    f.close()
if __name__ == '__main__':
    f = open(os.path.join(BUILD_DIR, 'test_io.bin'), 'wb')
    f.write(struct.pack('6I',0,1,1,2,0,2))
    f.close()
    f = open(os.path.join(BUILD_DIR, 'test_io_false.bin'), 'wb')
    f.write(struct.pack('5I',0,1,1,2,0))
    f.close()
    networkx_to_bin(nx.complete_graph(8), "complete_8.bin")
    networkx_to_bin(nx.complete_graph(4), "complete_4.bin")
