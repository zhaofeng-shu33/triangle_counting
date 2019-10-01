import os
import struct
import argparse
BUILD_DIR = os.environ.get('BUILD_DIR', 'build')
def get_max_id(filename):
    f = open(os.path.join(BUILD_DIR, filename), 'rb')
    b = f.read(4)
    a = 0
    cnt = 0
    while b != b'':
        b1 = struct.unpack('I',b)[0]
        if a < b1:
            a = b1
        cnt += 1
        if cnt % 1000000 == 0:
            print(cnt)
        b = f.read(4)
    print(a)

def get_min_id(filename):
    f = open(os.path.join(BUILD_DIR, filename), 'rb')
    b = f.read(4)
    a = 1000000
    cnt = 0
    while b != b'':
        b1 = struct.unpack('I',b)[0]
        if a > b1:
            a = b1
        cnt += 1
        if cnt % 1000000 == 0:
            print(cnt)
        b = f.read(4)    

def inspect_data(filename):
    # get the position of edge starting pos
    f = open(os.path.join(BUILD_DIR, filename), 'rb')
    b = f.read(8)
    while b != b'':
        a1, b1 = struct.unpack('2I', b)
        print(a1, b1)
        b = f.read(8)
    f.close()

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--task', default='inspect', choices=['inspect', 'get_max_id', 'get_min_id'])
    parser.add_argument('--filename', default='test_io.bin')
    args = parser.parse_args()
    if args.task == 'inspect':
        inspect_data(args.filename)
    elif args.task == 'get_max_id':
        get_max_id(args.filename)
    else:
        get_min_id(args.filename)