import hashlib
import struct
def p64(i):
    return struct.unpack("<I", struct.pack(">I", i))[0]


prefix = b'secret'
data = b'data'
byte_len = len(prefix + data)

# padding length is congruent to 56 bytes
pad_len = 56 - byte_len % 64
padding = b'\x80' + b'\x00' * (pad_len - 1) 
assert len(prefix + data + padding) % 64 == 56 

# little endian length field
length_field = (byte_len * 8).to_bytes(8, byteorder='little') 

# 8 bytes = 64 bit / bytes(p64(byte_len * 8))
# appended text
postfix = b'append'

payload1 = prefix + data +postfix
payload2 = prefix + data + padding + length_field + postfix

###################

print(payload1)
print(payload2)
print("****")
print(hashlib.md5(payload1).hexdigest())
print(hashlib.md5(payload2).hexdigest())
'''
Guess byte_len

PAYLOAD
data
\x80 + \x00 * (byte_len-1)
p64(byte_len*8)
append


TEST
A*byte_len+payload
'''