#!/usr/bin/env python3
import struct

def lcg(m, a, c, x):
    return (a*x + c) % m

m = pow(2, 32)

a = 3204287424
c = 1460809397
x = 2445943554

d = open('../flag.png.enc', 'rb').read()
d = [d[i:i+4] for i in range(0, len(d), 4)]

e = b''
for i in range(len(d)):
    e += struct.pack('>I', x ^ struct.unpack('>I', d[i])[0])
    x = lcg(m, a, c, x)

e = e.rstrip(b'x00') # remove pads

with open('flag.png', 'wb') as f:
    f.write(e)
    f.close()
