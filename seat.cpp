#include <algorithm>
#include <array>
#include <cstdio>
#include <random>
#include <vector>
using namespace std;
mt19937 __get_random_engine();
int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
    {
        fputs("Error: Invalid argument.\n", stderr);
        fputs("Usage: seat name.txt fixed.txt [result.txt]\n", stderr);
        fputs("name.txt is a file that gives a map of id and name.\n", stderr);
        fputs("fixed.txt is a file that gives several pairs of fixed deskmates by their ids.\n", stderr);
        fputs("Optional result.txt is a file where this program will write result. \n    Otherwise the result will be write to stdout.", stderr);
        return 1;
    }
    FILE *nStream, *fStream, *rStream;
    nStream = fopen(argv[1], "r"), fStream = fopen(argv[2], "r");
    rStream = argc == 4 ? fopen(argv[3], "r") : stdout;
    array<int, 48> res;
    array<char[9], 49> name;
    vector<pair<int, int>> fixed;
    //read
    const int lcy = 20, yyl = 48, hr = 8;
    for (int id; ~fscanf(nStream, "%d", &id);) fscanf(nStream, "%s", name[id]);
    for (int x, y; ~fscanf(fStream, "%d%d", &x, &y);) fixed.push_back(make_pair(x, y));
    fixed.push_back(make_pair(yyl, hr));
    //check
    array<bool, 49> H;
    fill(H.begin(), H.end(), false);
    for (vector<pair<int, int>>::iterator ite = fixed.begin(); ite != fixed.end(); ++ite)
        if (H[ite->first] || H[ite->second])
        {
            fprintf(stderr, "Error: %s error, id repeated.\n", argv[2]);
            return 2;
        }
        else
            H[ite->first] = H[ite->second] = true;
    //generate
    mt19937 gen = __get_random_engine();
    for (int i = 0; i < 48; i++) res[i] = i + 1;
    shuffle(res.begin(), res.end(), gen);
    iter_swap(find(res.begin(), res.end(), lcy), &res[(gen() & 7) | 8]); //Special: lcy is on row 2
    for (vector<pair<int, int>>::iterator ite = fixed.begin(); ite != fixed.end(); ++ite)
        iter_swap(find(res.begin(), res.end(), ite->first), &res[(find(res.begin(), res.end(), ite->second) - res.begin()) ^ 1]);
    //display
    for (int i = 0; i < 6; i++, fputs("|\n", rStream))
        for (int j = 0; j < 8; j++)
            fprintf(rStream, "%s%-8s", &"| "[j & 1], name[res[i << 3 | j]]);
    fclose(nStream), fclose(fStream), fclose(rStream);
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
#include <ctime>
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
