import struct
import os
if __name__ == '__main__':
    BUILD_DIR = os.environ.get('BUILD_DIR', 'build')
    f = open(os.path.join(BUILD_DIR, 'test_io.bin'), 'wb')
    f.write(struct.pack('6I',0,1,1,2,0,2))
    f.close()
    f = open(os.path.join(BUILD_DIR, 'test_io_false.bin'), 'wb')
    f.write(struct.pack('5I',0,1,1,2,0))
    f.close()
