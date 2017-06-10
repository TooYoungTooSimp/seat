#include <bits/stdc++.h>
using namespace std;
int num[49];
int main()
{
    freopen("out.txt", "w", stdout);
    puts("门————————————————————————————————————————————————窗");
    srand(time(0));
    for (int i = 0; i < 49; i++) num[i] = i + 1;
    random_shuffle(num, num + 49);
    int pos = 0;
    while (num[pos] != 20) pos++;
    pos = 0;
    int pos2 = ((rand() + 42) & 7) + 8;
    swap(num[pos], num[pos2]);
    for (int i = 0; i < 6; i++, putchar('\n'))
        for (int j = 0; j < 8; j++, putchar(' '))
            printf("%2d", num[i << 3 | j]);
    return 0;
}
