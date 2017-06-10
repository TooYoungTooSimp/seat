#include <algorithm>
#include <cstdio>
#include <random>
using namespace std;
#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "advapi32.lib")
mt19937 __get_random_engine()
{
    unsigned __seed;
    HCRYPTPROV hProvider;
    CryptAcquireContext(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
    CryptGenRandom(hProvider, sizeof(__seed), (BYTE *)&__seed);
    CryptReleaseContext(hProvider, 0);
    return mt19937(__seed);
}
#else
mt19937 __get_random_engine()
{
    unsigned __seed;
    FILE *fd = fopen("/dev/random", "r");
    fread(&__seed, sizeof(__seed), 1, fd);
    fclose(fd);
    return mt19937(__seed);
}
#endif
int num[49];
#define lcy 20
#define wzr 22
#define lyc 48
int main()
{
    freopen("out.txt", "w", stdout);
    mt19937 gen = __get_random_engine();
    for (int i = 0; i < 49; i++) num[i] = i + 1;
    shuffle(num, num + 49, gen);
    swap(num[(gen() & 7) | 8], *find(num, num + 49, lcy));
    swap(*find(num, num + 49, wzr), num[(find(num, num + 49, lcy) - num) ^ 1]);
    iter_swap(find(num, num + 49, wzr), find(num, num + 49, lyc));
    iter_swap(find(num, num + 49, wzr), num + 48);
    for (int i = 0; i < 6; i++, putchar('\n'))
        for (int j = 0; j < 8; j++, putchar(' '))
            printf("%2d", num[i << 3 | j]);
    return 0;
}
