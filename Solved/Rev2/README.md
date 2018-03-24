# Rev2
re - 80 points

## Challenge 
It's time for [Rev2](rev2_32)! This one is pretty similar to the first: once you get the inputs right to the program, you will get the flag. You don't need the shell server for this one, but the binary can be found at `/problems/rev2/` if you would like to run it there.

## Hint
Find a dissasembler or decompiler and try to figure out what the program is doing with your numerical input.

## Solution

#### Decompile

Hopper Decompiler

	int main(int arg0) {
	    puts("Welcome to Rev2! You'll probably want to use a dissassembler or gdb.");
	    printf("Level 1: What number am I thinking of: ");
	    __isoc99_scanf(0x8048730, ebp + 0xffffffe4);

	    esp = ((((esp & 0xfffffff0) - 0x50) + 0x10 - 0x10) + 0x10 - 0x10) + 0x10;
	    if (*(ebp + 0xffffffe4) != 0x11d7) {
	            printf("Sorry, your guess of %d was incorrect. Try again!\n", *(ebp + 0xffffffe4));
	            eax = 0x0;
	    } else {

            printf("Level 2: Which two two-digit numbers will solve this level. Enter the two numbers separated by a single space (num1 should be the lesser of the two): ");
            __isoc99_scanf("%d %d", ebp + 0xffffffe8, ebp + 0xffffffec);


            esp = ((esp - 0x10) + 0x10 - 0x10) + 0x10;
            if ((((
            	*(ebp + 0xffffffe8) <= 0x63) &&
            	(*(ebp + 0xffffffe8) > 0x9)) &&
            	(*(ebp + 0xffffffec) <= 0x63)) &&
            	(*(ebp + 0xffffffec) > 0x9)) {
	                    if (*(ebp + 0xffffffe8) > *(ebp + 0xffffffec)) {
                            puts("Numbers do not meet specifications. Try again!");
                            eax = 0x0;
	                    } else {
                            *(ebp + 0xfffffff0) = *(ebp + 0xffffffec) * *(ebp + 0xffffffe8);
                            if (*(ebp + 0xfffffff0) != 0xd67) {
                                    printf("Sorry, your guess of %d and %d was incorrect. Try again!\n", *(ebp + 0xffffffe8), *(ebp + 0xffffffec));
                                    eax = 0x0;
                            }
                            else {
                                    printf("Congrats, you passed Rev2! The flag is: actf{%d_%d_%d}\n", *(ebp + 0xffffffe4), *(ebp + 0xffffffe8), *(ebp + 0xffffffec));
                                    eax = 0x0;
                            }
	                    }
            } else {
                puts("Numbers do not meet specifications. Try again!");
                eax = 0x0;
            }
	    }
	}

#### Analysis

Level 1:

- enter `0x11d7` or `4567`


Level 2:

- enter any 2 numbers between `0x9` and `0x63` (between `9` and `99`)
- the smaller number first
- where the 2 numbers multiplied together should equal `0xd67` or `3431`

Hence, [we can enter `47` and `73`](http://www.mathwarehouse.com/arithmetic/numbers/prime-number/prime-factorization.php?number=3431).

#### Solve 
	$ ./rev2_32 
	Welcome to Rev2! You'll probably want to use a dissassembler or gdb.
	Level 1: What number am I thinking of: 4567
	Level 2: Which two two-digit numbers will solve this level. Enter the two numbers separated by a single space (num1 should be the lesser of the two): 47 73
	Congrats, you passed Rev2! The flag is: actf{4567_47_73}

## Flag

	actf{4567_47_73}