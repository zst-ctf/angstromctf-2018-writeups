
int verify_key(int name, int email, int product_key) {
    // Convert all product key to integer array
    /* get first token */
    int count = 0;
    token = strtok(product_key, '-');
    /* walk through other tokens */
    while (token != NULL) {
        *(int32_t *)(rbp + sign_extend_64(rbx) * 0x4 + 0xffffffffffffff90) = atoi(token);
        token = strtok(NULL, s);
        count++;
    }

    assert(count == 0x6);

    // Do for 2 times
    // pad name with 'w' onwards, until 32 chars ??
    // email is 26 chars: artemis.tosini@example.com
    // var_A0 = 6
    // pad email with '"' onwards
    var_C4 = 0x0;
    for (var_C0 = 0x0; var_C0 <= 0x1; var_C0 = var_C0 + 0x1) {
            var_88 = *(rbp + sign_extend_32(var_C0) * 0x8 + 0xffffffffffffff80);
            var_A0 = strlen(var_88);
            if (var_A0 <= 0x1f) { // len of 0 to 31
                    var_9C = 0x20 - var_A0; // 32 to 1
                    for (var_BC = 0x0; var_BC < var_9C; var_BC++) {
                        // pad @ 06020a0
                        // pad end of string with ?? until 32 in length
                        // pad = w<.k9.".$.sYgd!s..m[.feQ[CW'.j.m/.HD;H^.N.'.3F3J%^32(`n...(gC}W2
                        var_88[var_BC + var_A0] = pad[var_BC + var_C4]
                    }
                    var_C4 = 0x20 - var_A0;
                    *(int8_t *)(var_88 + 0x20) = 0x0;
            }
    }

    // single key XOR
    for (i = 0x0; i < 32; i++) {
            email[i] ^= 0x5;
            name[i] ^= 0xf;
    }

    for (var_B4 = 0x0; var_B4 <= 0x5; var_B4 = var_B4 + 0x1) {
            rcx = sumChars(email, 0x0, 0x20, var_B4 + 0x2) * sumChars(email, var_B4 + 0x1, 0x20, var_B4 + 0x2);
            *(int32_t *)(rbp + sign_extend_32(var_B4) * 0x4 + 0xffffffffffffff90) = ((SAR(HIDWORD(rcx * 0x68db8bad), 0xc)) - (SAR(rcx, 0x1f))) * 0x2710 + (*(int32_t *)(rbp + sign_extend_32(var_B4) * 0x4 + 0xffffffffffffff90) - rcx);
            *(int32_t *)(rbp + sign_extend_32(var_B4) * 0x4 + 0xffffffffffffff90) = (sumChars(name, 0x0, 0x20, 0x2) - sumChars(name, 0x1, 0x20, 0x2)) * 0x4 + *(int32_t *)(rbp + sign_extend_32(var_B4) * 0x4 + 0xffffffffffffff90);
    }

    // swap tokens from location a*4 to b*4
    swapArr(&var_70, 0x3, 0x4);
    swapArr(&var_70, 0x2, 0x5);
    swapArr(&var_70, 0x1, 0x5);
    swapArr(&var_70, 0x2, 0x3);
    swapArr(&var_70, 0x0, 0x5);
    swapArr(&var_70, 0x4, 0x5);
    for (var_B0 = 0x0; var_B0 <= 0x5; var_B0 = var_B0 + 0x1) {
        var_70[var_B0 * 4] += sumChars(name, 0x0, 0x20, 0x1);
        var_70[var_B0 * 4] += sumChars(email, 0x0, 0x20, 0x1);
    }
    for (var_AC = 0x0; var_AC <= 0x5; var_AC = var_AC + 0x1) {
        var_70[var_AC * 4] += 
            sumChars(email, var_AC * 0x4, (var_AC << 0x2) + 0x1, 0x1) %
            sumChars(name, (var_AC << 0x2) + 0x2, (var_AC << 0x2) + 0x3, 0x1);
    }

    // sum the ASCII codes together in range
    // these are stored in array
    sumChars(email, 0x0, 0xa, 0x1);
    sumChars(email, 0xa, 0x19, 0x1);
    sumChars(email, 0x19, 0x20, 0x1);
    sumChars(name, 0x0, 0xd, 0x1);
    sumChars(name, 0xd, 0x14, 0x1);
    sumChars(name, 0x14, 0x20, 0x1);

    // loop through array of the sums
    // do something?
    for (var_A8 = 0x0; var_A8 <= 0x5; var_A8 = var_A8 + 0x1) {
        rcx = *(int32_t *)(rbp + sign_extend_32(var_A8) * 0x4 + 0xffffffffffffffb0) * 
              *(int32_t *)(rbp + sign_extend_32(var_A8) * 0x4 + 0xffffffffffffffd0);
        *(int32_t *)(rbp + (var_A8) * 0x4 + 0xffffffffffffffd0) =
             rcx - ((SAR(HIDWORD(rcx * 0x68db8bad), 0xc)) - (SAR(rcx, 0x1f))) * 0x2710;
    }
    var_C9 = 0x1;

    // make sure original integer equals the calculated integer
    // return 0 if wrong
    for (var_A4 = 0x0; var_A4 <= 0x5; var_A4 = var_A4 + 0x1) {
        if (*(int32_t *)(rbp + sign_extend_32(var_A4) * 0x4 + 0xffffffffffffff90) != *(int32_t *)(rbp + sign_extend_32(var_A4) * 0x4 + 0xffffffffffffffd0)) {
                var_C9 = 0x0;
        }
    }
    rax = var_C9 & 0xff;

    return rax;
}

// XOR swap algorithm
int swapArr(int arg0, int arg1, int arg2) {
    arg0[arg1 * 4] ^= arg0[arg2 * 4];
    arg0[arg2 * 4] ^= arg0[arg1 * 4];
    return arg0[arg1 * 4] ^ arg0[arg2 * 4];
}

int sumChars(int arg0, int arg1, int arg2, int arg3) {
int sumChars(int input, int start, int end, int step) {
    x = 0x0;
    for (i = start; i < end; i += step) {
        x += input[i]
    }
    return x;
}