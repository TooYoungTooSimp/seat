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
        fputs("Optional result.txt is a file where this program will write result. \n    Otherwise the result will be write to stdout.\n", stderr);
        return 1;
    }
    FILE *nStream, *fStream, *rStream;
    nStream = fopen(argv[1], "r"), fStream = fopen(argv[2], "r");
    rStream = argc == 4 ? fopen(argv[3], "r") : stdout;
    array<char[9], 50> name;
    vector<int> res;
    vector<pair<int, int>> fixed;
    fixed.reserve(12), res.reserve(24);
    //read
    for (int id; ~fscanf(nStream, "%d", &id);) fscanf(nStream, "%s", name[id]);
    for (int x, y; ~fscanf(fStream, "%d%d", &x, &y);) fixed.push_back(make_pair(x, y));
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
    shuffle(fixed.begin(), fixed.end(), gen);
    for (vector<pair<int, int>>::iterator ite = fixed.begin(); ite != fixed.end(); ++ite)
        if (gen() & 1) swap(ite->first, ite->second);
    for (int i = 1; i <= 48; i++)
        if (!H[i]) res.push_back(i);
    shuffle(res.begin(), res.end(), gen);
    //special
    iter_swap(find(res.begin(), res.end(), 48), &res[(find(res.begin(), res.end(), 8) - res.begin()) ^ 1]);
    iter_swap(find_if(fixed.begin(), fixed.end(), [](pair<int, int> &p) { return min(p.first, p.second) == 20; }), fixed.begin() + 2 + (gen() & 1));
    //display
    for (int i = 0; i < 6; i++, fputs("|\n", rStream))
    {
        for (int j = 0; j < 4; j++)
            fprintf(rStream, "%s%-8s", &"| "[j & 1], name[res[i << 2 | j]]);
        for (int j = 0; j < 2; j++)
            fprintf(rStream, "| %-8s %-8s", name[fixed[i << 1 | j].first], name[fixed[i << 1 | j].second]);
    }
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
