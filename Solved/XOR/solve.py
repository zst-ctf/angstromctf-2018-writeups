#!/usr/bin/env python3

f = open('ciphertext.txt').read().strip()
ctext = bytes.fromhex(f)

for key in range(0, 0xFF):
    ch = list(map(lambda c: chr(c ^ key), list(ctext)))
    text = ''.join(ch)
    if text.startswith('actf{'):
        print(text)
        quit()
