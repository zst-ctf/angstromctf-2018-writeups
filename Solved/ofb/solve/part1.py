#!/usr/bin/env python3
import struct

with open('flag.png.enc', 'rb') as f:
    enc = f.read()

# get the first 2 dwords
dword_1 = struct.unpack('>I', enc[0:4])[0]
dword_2 = struct.unpack('>I', enc[4:8])[0]
dword_3 = struct.unpack('>I', enc[8:12])[0]
dword_4 = struct.unpack('>I', enc[12:16])[0]

# compare with PNG header to get x and lcg values
x = dword_1 ^ 0x89504e47
lcg_x = dword_2 ^ 0x0d0a1a0a

print('x: ',    dword_1 ^ 0x89504e47)
print('lcg1: ', dword_2 ^ 0x0d0a1a0a)
print('lcg2: ', dword_3 ^ 0x0000000d)
print('lcg3: ', dword_4 ^ 0x49484452)


# now bruteforce coefficient of a
for a in range(0, 2**32):
	print('\r', a, end='')
	#val = (4196912501 + a * 905046208) % 4294967296
	val = (4196912501 + a * 905046208) & 0xFFFFFFFF
	if val == 1320590709:
		print(val)
		print(val)
		quit()
