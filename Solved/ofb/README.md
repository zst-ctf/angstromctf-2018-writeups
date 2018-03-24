# ofb
crypto - 120 points

## Challenge 
defund made a simple OFB cipher, if you can even call it that. Here's the [source](encrypt.py) and the [encrypted flag](flag.png.enc).

## Hint
Good luck!

## Solution

#### Analysis of program

1. Read `flag.png` as bytes (append 0x00 padding to make multiple of 4)
2. Split up bytes into groups of DWORDS (4 bytes in big-endian order)
3. For each group
	- XOR 4 bytes with initial value of `x`
	- calculate `lcg` as new `x`
	- XOR the next 4 bytes

Simplifying `lcg`, we get this

	(a*x + c) % 4294967296


#### Solve for `x`

This means that the key for the first DWORD is `x` and the key for the second DWORD is `lcg(x)`

We can instantly get `x` and `lcg(x)` using XOR of the PNG Header

Refer to: http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html

	12.12. PNG file signature
	The first eight bytes of a PNG file always contain the following values:

	   (decimal)              137  80  78  71  13  10  26  10
	   (hexadecimal)           89  50  4e  47  0d  0a  1a  0a
	   (ASCII C notation)    \211   P   N   G  \r  \n \032 \n

To make it clearer, if we `xxd` any PNG file we see this

	89504e47 0d0a1a0a 0000000d    .PNG........IHDR


The 1st and 2nd DWORDs are the PNG header, the 3rd DWORD is the chunk length, and the 4th DWORD is always IHDR text.

I'm not that familiar with chunk length, but I assume it will likely be `0000000d` since all my PNGs I tried have that value.

So let's XOR these 4 DWORDs to get the keys... 


Running my `part1.py`, I get this

	x:  2445943554
	lcg1:  2225636917
	lcg2:  1320590709
	lcg3:  4196912501

We have x!

#### Solve for `a`

From the output we can sub into the equations...

Hence,

	x = 2445943554
	2225636917 = (a * 2445943554 + c) % 4294967296
	1320590709 = (a * 2225636917 + c) % 4294967296
	4196912501 = (a * 1320590709 + c) % 4294967296

Rearranging the equations

	2225636917 = (a * 2445943554 + c) % 4294967296
	1320590709 = (a * 2225636917 + c) % 4294967296

	The difference is: a * 220306637

	(1320590709 + difference) % 4294967296 = 2225636917

We can now bruteforce `a`...

It was too slow to bruteforce in Python, so I wrote it in C (`part2.c`).

I left it for less than 2 hours and got back...

	$ ./part2 
	3204287424

	Solved
	a = 3204287424

	...

We have `a`!

#### Solve for `c`

Reverse calculate

	# Using: 4196912501 = (a * 1320590709 + c) % 4294967296
	>>> a = 3204287424
	>>> c = 0
	>>> (a * 1320590709 + c) % 4294967296
	2736103104
	>>> 4196912501 - 2736103104
	1460809397

	# Confirm by plugging back the values
	>>> a = 3204287424
	>>> c = 1460809397
	>>> (a * 2225636917 + c) % 4294967296
	1320590709
	>>> (a * 2445943554 + c) % 4294967296
	2225636917

#### Decrypt!

We have the values. Now it is complete.

	a = 3204287424
	c = 1460809397
	x = 2445943554

The encryption is a simple XOR, so decryption is the same process

And we get back the picture with the flag!

## Flag

	actf{pad_rng}


(Note: I have a feeling bruteforcing is not the intended method though, haha. There's probably an easier method)
