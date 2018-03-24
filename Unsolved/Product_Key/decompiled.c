int main(int arg0, int arg1) {
    printf("Name: ");
    fflush(*__TMC_END__);
    fgets(&var_90, 0x21, *stdin@@GLIBC_2.2.5);
    *(int8_t *)(rbp + strcspn(&var_90, 0x4011ed) + 0xffffffffffffff70) = 0x0;

    printf("Email: ");
    fflush(*__TMC_END__);
    fgets(&var_60, 0x21, *stdin@@GLIBC_2.2.5);
    *(int8_t *)(rbp + strcspn(&var_60, 0x4011ed) + 0xffffffffffffffa0) = 0x0;

    printf("Product key: ");
    fflush(*__TMC_END__);
    fgets(&var_30, 0x21, *stdin@@GLIBC_2.2.5);
    *(int8_t *)(rbp + strcspn(&var_30, 0x4011ed) + 0xffffffffffffffd0) = 0x0;

    if (verify_key(&var_90, &var_60, &var_30) != 0x0) {
            puts("Windows has been activated");
            rax = 0x0;
    } else {
            puts("Invalid product key");
            rax = 0xffffffff;
    }
    // rcx = *0x28 ^ *0x28;
    // if (rcx != 0x0) {
    //         rax = __stack_chk_fail();
    // }
    return rax;
}


int verify_key(int arg0, int arg1, int arg2) {
    var_D8 = arg0;
    var_E0 = arg1;
    var_C8 = 0x0;
    for (var_90 = strtok(arg2, 0x4011e4); var_90 != 0x0; var_90 = strtok(0x0, 0x4011e4)) {
            rbx = var_C8;
            var_C8 = rbx + 0x1;
            *(int32_t *)(rbp + sign_extend_64(rbx) * 0x4 + 0xffffffffffffff90) = atoi(var_90);
    }
    if (var_C8 != 0x6) {
            rax = 0x0;
    }
    else {
            var_C4 = 0x0;
            for (var_C0 = 0x0; var_C0 <= 0x1; var_C0 = var_C0 + 0x1) {
                    var_88 = *(rbp + sign_extend_32(var_C0) * 0x8 + 0xffffffffffffff80);
                    var_A0 = strlen(var_88);
                    if (var_A0 <= 0x1f) {
                            var_9C = 0x20 - var_A0;
                            for (var_BC = 0x0; var_BC < var_9C; var_BC = var_BC + 0x1) {
                                    *(int8_t *)(sign_extend_64(var_BC + var_A0) + var_88) = *(int8_t *)(sign_extend_32(var_BC + var_C4) + 0x6020a0) & 0xff;
                            }
                            var_C4 = 0x20 - var_A0;
                            *(int8_t *)(var_88 + 0x20) = 0x0;
                    }
            }
            for (var_B8 = 0x0; var_B8 <= 0x1f; var_B8 = var_B8 + 0x1) {
                    *(int8_t *)(var_E0 + sign_extend_64(var_B8)) = *(int8_t *)(var_E0 + sign_extend_64(var_B8)) & 0xff ^ 0x5;
                    *(int8_t *)(var_D8 + sign_extend_64(var_B8)) = *(int8_t *)(var_D8 + sign_extend_64(var_B8)) & 0xff ^ 0xf;
            }
            for (var_B4 = 0x0; var_B4 <= 0x5; var_B4 = var_B4 + 0x1) {
                    rcx = sumChars(var_E0, 0x0, 0x20, var_B4 + 0x2) * sumChars(var_E0, var_B4 + 0x1, 0x20, var_B4 + 0x2);
                    *(int32_t *)(rbp + sign_extend_32(var_B4) * 0x4 + 0xffffffffffffff90) = ((SAR(HIDWORD(rcx * 0x68db8bad), 0xc)) - (SAR(rcx, 0x1f))) * 0x2710 + (*(int32_t *)(rbp + sign_extend_32(var_B4) * 0x4 + 0xffffffffffffff90) - rcx);
                    *(int32_t *)(rbp + sign_extend_32(var_B4) * 0x4 + 0xffffffffffffff90) = (sumChars(var_D8, 0x0, 0x20, 0x2) - sumChars(var_D8, 0x1, 0x20, 0x2)) * 0x4 + *(int32_t *)(rbp + sign_extend_32(var_B4) * 0x4 + 0xffffffffffffff90);
            }
            swapArr(&var_70, 0x3, 0x4);
            swapArr(&var_70, 0x2, 0x5);
            swapArr(&var_70, 0x1, 0x5);
            swapArr(&var_70, 0x2, 0x3);
            swapArr(&var_70, 0x0, 0x5);
            swapArr(&var_70, 0x4, 0x5);
            for (var_B0 = 0x0; var_B0 <= 0x5; var_B0 = var_B0 + 0x1) {
                    *(int32_t *)(rbp + sign_extend_32(var_B0) * 0x4 + 0xffffffffffffff90) = sumChars(var_D8, 0x0, 0x20, 0x1) + *(int32_t *)(rbp + sign_extend_32(var_B0) * 0x4 + 0xffffffffffffff90);
                    *(int32_t *)(rbp + sign_extend_32(var_B0) * 0x4 + 0xffffffffffffff90) = sumChars(var_E0, 0x0, 0x20, 0x1) + *(int32_t *)(rbp + sign_extend_32(var_B0) * 0x4 + 0xffffffffffffff90);
            }
            for (var_AC = 0x0; var_AC <= 0x5; var_AC = var_AC + 0x1) {
                    *(int32_t *)(rbp + sign_extend_32(var_AC) * 0x4 + 0xffffffffffffff90) = sumChars(var_E0, var_AC * 0x4, (var_AC << 0x2) + 0x1, 0x1) % sumChars(var_D8, (var_AC << 0x2) + 0x2, (var_AC << 0x2) + 0x3, 0x1) + *(int32_t *)(rbp + sign_extend_32(var_AC) * 0x4 + 0xffffffffffffff90);
            }
            sumChars(var_E0, 0x0, 0xa, 0x1);
            sumChars(var_E0, 0xa, 0x19, 0x1);
            sumChars(var_E0, 0x19, 0x20, 0x1);
            sumChars(var_D8, 0x0, 0xd, 0x1);
            sumChars(var_D8, 0xd, 0x14, 0x1);
            sumChars(var_D8, 0x14, 0x20, 0x1);
            for (var_A8 = 0x0; var_A8 <= 0x5; var_A8 = var_A8 + 0x1) {
                    rcx = *(int32_t *)(rbp + sign_extend_32(var_A8) * 0x4 + 0xffffffffffffffb0) * *(int32_t *)(rbp + sign_extend_32(var_A8) * 0x4 + 0xffffffffffffffd0);
                    *(int32_t *)(rbp + sign_extend_64(var_A8) * 0x4 + 0xffffffffffffffd0) = rcx - ((SAR(HIDWORD(rcx * 0x68db8bad), 0xc)) - (SAR(rcx, 0x1f))) * 0x2710;
            }
            var_C9 = 0x1;
            for (var_A4 = 0x0; var_A4 <= 0x5; var_A4 = var_A4 + 0x1) {
                    if (*(int32_t *)(rbp + sign_extend_32(var_A4) * 0x4 + 0xffffffffffffff90) != *(int32_t *)(rbp + sign_extend_32(var_A4) * 0x4 + 0xffffffffffffffd0)) {
                            var_C9 = 0x0;
                    }
            }
            rax = var_C9 & 0xff;
    }
    rbx = *0x28 ^ *0x28;
    if (rbx != 0x0) {
            rax = __stack_chk_fail();
    }
    return rax;
}

int swapArr(int arg0, int arg1, int arg2) {
    *(int32_t *)(arg0 + sign_extend_32(arg1) * 0x4) = *(int32_t *)(arg0 + sign_extend_64(arg2) * 0x4) ^ *(int32_t *)(arg0 + sign_extend_64(arg1) * 0x4);
    *(int32_t *)(arg0 + sign_extend_32(arg2) * 0x4) = *(int32_t *)(arg0 + sign_extend_64(arg1) * 0x4) ^ *(int32_t *)(arg0 + sign_extend_64(arg2) * 0x4);
    rax = arg0 + sign_extend_32(arg1) * 0x4;
    *(int32_t *)rax = *(int32_t *)(arg0 + sign_extend_64(arg2) * 0x4) ^ *(int32_t *)(arg0 + sign_extend_64(arg1) * 0x4);
    return rax;
}

int sumChars(int arg0, int arg1, int arg2, int arg3) {
    var_18 = arg0;
    var_20 = arg2;
    var_24 = arg3;
    var_8 = 0x0;
    for (var_4 = arg1; var_4 < var_20; var_4 = var_4 + var_24) {
            var_8 = var_8 + sign_extend_64(*(int8_t *)(var_18 + sign_extend_64(var_4)) & 0xff);
    }
    rax = var_8;
    return rax;
}