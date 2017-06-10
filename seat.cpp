#include <algorithm>
#include <cstdio>
#include <random>
using namespace std;
#ifdef _MSC_VER
#include <Windows.h>
unsigned __rand()
{
    unsigned ret;
    HCRYPTPROV hProvider;
    CryptAcquireContextW(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
    CryptGenRandom(hProvider, 4, (BYTE *)&ret);
    CryptReleaseContext(hProvider, 0);
    return ret;
}
#else
unsigned __rand()
{
    FILE *fd = fopen("/dev/random", "r");
    unsigned ret;
    fread(&ret, sizeof(ret), 1, fd);
    fclose(fd);
    return ret;
}
#endif
int num[49];
#define lcy 20
#define wzr 22
#define lyc 48
int main()
{
    freopen("out.txt", "w", stdout);
    mt19937 gen(__rand());
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
