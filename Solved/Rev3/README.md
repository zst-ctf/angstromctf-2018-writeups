# Rev3
re - 110 points

## Challenge 
Let's try `Rev 3`! For this executable, you will need to figure out what input makes the program return `"Correct"`. You don't need the shell server for this one, but the binary can be found at `/problems/rev3/` on the shell server.

## Hint
Use a dissasembler or decompiler, then try and figure out how the program is checking your input.

## Solution

Decompile in Hopper...

It seems that the input goes through some `encode()` function before being compared

    encode(*(*(ebp + 0xffffffe4) + 0x4), *(ebp + 0xfffffff0));
    ...

    if (strcmp(*(ebp + 0xfffffff0), "egzloxi|ixw]dkSe]dzSzccShejSi^3q") == 0x0) {
        puts("Congrats, that's right! Enter your input as the flag!");
    }

The `encode()` function in decompiled code

    int encode(int arg0, int arg1) {
        var_C = strlen(arg0);
        var_10 = 0x0;
        do {
            eax = var_10;
            if (eax >= var_C) {
                break;
            }
            *(int8_t *)(arg1 + var_10) = (*(int8_t *)(arg0 + var_10) & 0xff ^ 0x9) - 0x3;
            var_10 = var_10 + 0x1;
        } while (true);
        return eax;
    }

Simplify it

    void encode(char * input_str, char * output_str) {
        len = strlen(input_str);
        for (int i = 0; i < len; i++) {
            output_str[i] = (input_str[i] ^ 0x9) - 0x3;
        }
    }

Hence, we can make a decode function in Python...

    $ python3

    def decode(enc_text):
        dec = lambda c: chr( (ord(c) + 3) ^ 0x9 )
        return ''.join( map(dec, list(enc_text)) )
        
    >>> decode("egzloxi|ixw]dkSe]dzSzccShejSi^3q")
    'actf{reversing_aint_too_bad_eh?}'

## Flag

    actf{reversing_aint_too_bad_eh?}
