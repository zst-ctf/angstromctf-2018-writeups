# Accumulator
binary - 50 points

## Challenge 
I found this [program](accumulator64) ([source](accumulator.c)) that lets me add positive numbers to a variable, but it won't give me a flag unless that variable is negative! Can you help me out? Navigate to `/problems/accumulator/` on the shell server to try your exploit out!

## Hint
How many bytes can an int store? How are positive and negative numbers represented in C?

## Solution
Simple exploit of overflowing integers

	team014544@shell:/problems/accumulator$ ./accumulator64

	The accumulator currently has a value of 0.
	Please enter a positive integer to add: 2147483648
	You can't enter negatives!

	The accumulator currently has a value of 0.
	Please enter a positive integer to add: 2147483647
	The accumulator currently has a value of 2147483647.

	Please enter a positive integer to add: 1
	The accumulator has a value of -2147483648. You win!
	actf{signed_ints_aint_safe}


## Flag

	actf{signed_ints_aint_safe}
