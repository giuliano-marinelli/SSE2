#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>	// Need this for SSE2 compiler intrinsics

int main(int argc, char* argv[]) {
    //ejer1();
    //ejer2();
    ejer3();
    return 1;
}

void ejer1() {
    float *mem;
    __m128 v1, v2, v3;
    int i;
    int cant = 10000000;

    if (posix_memalign((void*) &mem, 16, cant * 4) != 0) {
        perror("posix_memalign dio error");
        exit(1);
    }

    for (i = 0; i < cant; i++) {
        mem[i] = 1;
    }

    v3 = _mm_set1_ps(0);
    for (i = 0; i < cant / 4; i = i + 2) {
        v1 = _mm_load_ps((__m128*) (mem + i * 4));
        v2 = _mm_load_ps((__m128*) (mem + (i + 1) * 4));
        v2 = _mm_add_ps(v1, v2);
        v3 = _mm_add_ps(v2, v3);
    }
    _mm_store_ps((__m128*) mem, v3);

    printf("%.2f", mem[0] + mem[1] + mem[2] + mem[3]);
}

void ejer2() {
    double *mem;
    __m128d v1, v2, v3;
    int i;
    int cant = 10000000;

    if (posix_memalign((void*) &mem, 16, cant * 8) != 0) {
        perror("posix_memalign dio error");
        exit(1);
    }

    for (i = 0; i < cant; i++) {
        mem[i] = 1;
    }

    v3 = _mm_set1_pd(0);
    for (i = 0; i < cant / 2; i = i + 2) {
        v1 = _mm_load_pd((__m128d*) (mem + i * 2));
        v2 = _mm_load_pd((__m128d*) (mem + (i + 1) * 2));
        v2 = _mm_add_pd(v1, v2);
        v3 = _mm_add_pd(v2, v3);
    }
    _mm_store_pd((__m128d*) mem, v3);

    printf("%.2f", mem[0] + mem[1]);
}

void ejer3() {
    unsigned char *mem;
    __m128i v1, v2, v3;
    int i;
    int cant = 4064;
    int res = 0;

    if (posix_memalign((void*) &mem, 16, cant) != 0) {
        perror("posix_memalign dio error");
        exit(1);
    }

    for (i = 0; i < cant; i++) {
        mem[i] = 1;
    }

    v3 = _mm_set1_epi8(0);
    for (i = 0; i < cant / 16; i = i + 2) {
        v1 = _mm_load_si128((__m128i*) (mem + i * 16));
        v2 = _mm_load_si128((__m128i*) (mem + (i + 1) * 16));
        v2 = _mm_add_epi8(v1, v2);
        v3 = _mm_add_epi8(v2, v3);
    }

    _mm_store_si128((__m128i*) mem, v3);
    
    for (i = 0; i < 16; i++) {
        res += mem[i];
    }
    
    printf("%u", mem[0]);
    for (i = 1; i < 16; i++) {
        printf("+%u", mem[i]);
    }
    
    printf(" = %u", res);
}

void ejer1alt() {
    int *mem;
    __m128i v1, v2;
    int i;

    if (posix_memalign((void*) &mem, 32, 32) != 0) {
        perror("posix_memalign dio error");
        exit(1);
    }

    v1 = _mm_set1_epi32(1);
    v2 = _mm_set1_epi32(1);
    for (i = 1; i < 10000000 / 4; i++) {
        v2 = _mm_add_epi32(v1, v2);
    }
    _mm_store_si128((__m128*) mem, v2);

    printf("%i", mem[0] + mem[1] + mem[2] + mem[3]);
}

void ejer2alt() {
    double *mem;
    __m128d v1, v2;
    int i;

    if (posix_memalign((void*) &mem, 32, 32) != 0) {
        perror("posix_memalign dio error");
        exit(1);
    }

    v1 = _mm_set1_pd(1);
    v2 = _mm_set1_pd(1);
    for (i = 1; i < 100000000; i++) {
        v2 = _mm_add_pd(v1, v2);
    }
    _mm_store_pd((__m128*) mem, v2);

    printf("\n%.2f", *mem);
}

void ejemplo() {
    char *a;
    __m128i v1, v2;
    int i;

    //printf("%i",posix_memalign((void*) &a, 16, 32));
    if (posix_memalign((void*) &a, 16, 32) != 0) {
        perror("posix_memalign dio error");
        exit(1);
    }

    a[0] = 4;
    a[1] = 4;
    a[2] = 2;
    a[3] = 1;
    a[4] = 1;
    a[5] = 4;
    a[6] = 9;
    a[7] = 9;
    a[8] = 7;
    a[9] = 4;
    a[10] = 2;
    a[11] = 2;
    a[12] = 2;
    a[13] = 5;
    a[14] = 5;
    a[15] = 6;

    v1 = _mm_load_si128((__m128i*) a);
    v2 = _mm_set1_epi8(2);
    v2 = _mm_cmpeq_epi8(v1, v2);
    _mm_store_si128((__m128i*) (a + 16), v2);

    for (i = 0; i < 16; i++)
        printf("%3d", a[i]);
    printf("\n");

    for (i = 16; i < 32; i++)
        printf("%3hhx", a[i]);
    printf("\n");

    return 0;
}