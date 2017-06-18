#include <algorithm>
#include <cstdio>
#include <random>
using namespace std;
mt19937 __get_random_engine();
int num[49];
char name[50][9];
#define numRange num, num + 49
const int lcy = 20, wzr = 26, lyc = 49, yyl = 48, hr = 8;
int main(int argc, char **argv)
{
    FILE *iS, *oS;
    if (argc == 1) iS = stdin, oS = stdout;
    if (argc == 2) iS = fopen(argv[1], "r"), oS = stdout;
    if (argc == 3) iS = fopen(argv[1], "r"), oS = fopen(argv[2], "w");
    for (int id; ~fscanf(iS, "%d", &id);)
        fscanf(iS, "%s", name[id]);
    mt19937 gen = __get_random_engine();
    for (int i = 0; i < 49; i++) num[i] = i + 1;
    shuffle(numRange, gen);
    iter_swap(find(numRange, lcy), &num[(gen() & 7) | 8]);
    iter_swap(find(numRange, wzr), &num[(find(numRange, lcy) - num) ^ 1]);
    iter_swap(find(numRange, yyl), &num[(find(numRange, hr) - num) ^ 1]);
    iter_swap(find(numRange, wzr), find(numRange, lyc));
    iter_swap(find(numRange, wzr), num + 48);
    for (int i = 0; i < 6; i++, fputc('\n', oS))
        for (int j = 0; j < 8; j++, fputc(' ', oS))
            fprintf(oS, "%-8s%c", name[num[i << 3 | j]], " |"[j & 1]);
    return 0;
}
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
    if (FILE *fd = fopen("/dev/random", "r"))
        fread(&__seed, sizeof(__seed), 1, fd), fclose(fd);
    else
        __seed = time(0);
    return mt19937(__seed);
}
#endif
