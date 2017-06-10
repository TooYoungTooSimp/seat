# seat ![WTFPL](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-2.png)
一个用来给22班随机排座位表的程序。因为他们班的同学认为@hr567的程序有问题，随机的不好，就让我来重写一个。

现在seat.cpp已经实现seat_hr.cpp中的所有功能并且有着更好的随机性。
seat.cpp使用CryptGenRandom(Windows)或是/dev/random(unix-like)产生的高质量的随机数种子来初始化mt19937，达到了比srand(time(0))+rand()更好的随机性。

已实现的原有功能如下
- 把lcy放到第二排
- 把wzr放到lcy旁边

由于我来到22班蹭课并且wzr跑回家去，经过一致同意，我就抢占了wzr的位置。于是增加了两个新功能：
- 把我和wzr交换
- 把wzr放到我现在坐的特殊位置上去。
