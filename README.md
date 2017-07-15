# seat [![Build Status](https://travis-ci.org/TooYoungTooSimp/seat.svg?branch=master)](https://travis-ci.org/TooYoungTooSimp/seat)

一个用来给22班随机排座位表的程序。因为他们班的同学认为@hr567的程序有问题，随机的不好，就让我来重写一个。

## 原有功能
现在seat.cpp已经实现seat_hr.cpp中的所有功能并且有着更好的随机性。
seat.cpp使用CryptGenRandom(Windows)或是/dev/random(unix-like)产生的高质量的随机数种子来初始化mt19937，达到了比srand(time(0))+rand()更好的随机性。

已实现的原有功能如下
- 把lcy放到第二排
- 把wzr放到lcy旁边

## Update 20170701
两件事情
- 表哥（wzr）回来了
- 22班座位安排方法进行了大的改动

于是实现新功能：按照给定的固定同桌表安排一些人，剩下的人随机分配。

## Update 20170715
固定同桌表的方式进行了更新，直接重写算了