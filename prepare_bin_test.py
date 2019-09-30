import struct
if __name__ == '__main__':
    f = open('build/test_io.bin', 'wb')
    f.write(struct.pack('6I',0,1,1,2,0,2))
    f.close()
    f = open('build/test_io_false.bin', 'wb')
    f.write(struct.pack('5I',0,1,1,2,0))
    f.close()