#define FILE_STREAM
#ifdef FILE_STREAM
#include <fstream>
#endif

#include <iostream>
#include <iomanip>
#include <array>
#include <algorithm>
#include <random>

namespace {
#ifdef _GLIBCXX_USE_RANDOM_TR1
std::random_device e;
#else
#include <ctime>
std::default_random_engine e(time(0));
#endif
}

struct SeatTable
{
    using num = unsigned int;
    static constexpr int m = 6, n = 8;
    static constexpr num N = m * n;

    using table = std::array<int, N>;
    using seat = table::iterator;

    SeatTable()
    {
        for (num i = 0; i != N; ++i)
            a[i] = i;
        //随机打乱座位次序。
        std::random_shuffle(a.begin(), a.end(), [](num i) { return e() % i; });
    }

    table a;

    seat find(num x); //返回学号为x的同学的座位
    seat deskmate(num x); //返回学号为x的同学的同桌的座位
    seat rand(table::size_type f, table::size_type l); //返回从[l, r)中的任意一个座位
};

SeatTable::seat SeatTable::find(num x)
{
    return std::find(a.begin(), a.end(), x);
}

SeatTable::seat SeatTable::deskmate(num x)
{
    auto p = find(x);
    return ((p - a.begin()) & 1)^1 ? p + 1 : p - 1;
}

SeatTable::seat SeatTable::rand(table::size_type f, table::size_type l)
{
    static std::uniform_int_distribution<table::size_type> uud(f, l);
    return a.begin() + uud(e);
}

std::ostream &operator<<(std::ostream &ou, const SeatTable &st)
{
    using std::endl;
    using std::setw;
    ou << "门————————————————————————————————————————————————窗" << endl;
    for (int i = 0; i != st.m; ++i)
    {
        for (int j = 0; j != st.n; ++j)
            ou << setw(4 << (j & 1)) << st.a[i * st.n + j];
        ou << endl;
    }
    return ou;
}

int main()
{
    SeatTable st;

    //把20号放到第二排然以一个位置，在把22号放在20号同桌的位置。
    std::swap(*st.find(20), *st.rand(st.m, 2 * st.m));
    std::swap(*st.find(22), *st.deskmate(20));

    //把空位放到7号旁边
    std::swap(*st.find(0), *st.deskmate(7));

    std::cout << st << std::endl;

#ifdef FILE_STREAM
    std::ofstream fout("seat.txt");
    fout << st << std::endl;
    std::cout << std::endl;
    std::cout << "————————————————————————————————————————" << std::endl;
    std::cout << "The output is already in file \"seat.txt\"" << std::endl;
    std::cout << "————————————————————————————————————————" << std::endl;
#endif

    return 0;
}

