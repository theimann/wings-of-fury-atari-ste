"""Rpck decompressor (Broderbund Wings of Fury, Amiga).

Format: 'Rpck' + u32 BE unpacked size + PackBits-style stream with inverted sense:
  c >= 0x80 : copy (256 - c) literal bytes
  c <  0x80 : repeat next byte (c + 1) times
"""
import struct, sys

def is_rpck(data):
    return data[:4] == b'Rpck'

def unpack(data):
    assert is_rpck(data), 'not an Rpck file'
    size = struct.unpack('>I', data[4:8])[0]
    out = bytearray()
    i = 8
    while len(out) < size:
        c = data[i]; i += 1
        if c >= 0x80:
            n = 256 - c
            out += data[i:i + n]; i += n
        else:
            out += bytes([data[i]]) * (c + 1); i += 1
    if len(out) != size:
        raise ValueError(f'size mismatch: got {len(out)}, expected {size}')
    return bytes(out)

def load(path):
    data = open(path, 'rb').read()
    return unpack(data) if is_rpck(data) else data

if __name__ == '__main__':
    src, dst = sys.argv[1:3]
    open(dst, 'wb').write(load(src))
