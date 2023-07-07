#include <iostream>
#include <stdlib.h>
#define maxSize 20
using namespace std;
typedef struct {
  char str
      [maxSize +
       1]; // maxSize为已经定义的常量，表示串的最大长度；str数组长度定义为maxSize+1，是为了存放串结束标志'\0'
  int length;
} Str;

// 变长分配存储表示（又叫动态分配存储表示）方法的特点是，在程序执行过程中根据需要动态分配。其结构体定义如下：
typedef struct {
  char *ch;   // 指向动态分配存储区首字符的字符指针
  int length; // 串长度
} Str1;

// 串的基本操作
// 串赋值操作函数
int strassign(Str1 &str, char *ch) {
  if (str.ch)
    free(str.ch); // 释放原串空间
  int len = 0;
  char *c = ch;
  while (*c) { // 求ch串的长度
    ++len;
    ++c;
  }
  if (len == 0) { // 如果ch为空串，而直接返回空串
    str.ch = nullptr;
    str.length = 0;
    return 1;
  } else { // 如果不是空串，则为串分配空间，复制串
    str.ch = (char *)malloc(sizeof(char) * (len + 1));
    // 取len+1是为了多分配一个空间存放'\0'字符
    if (str.ch == nullptr) // 如果空间不够
      return 0;
    else {    // 空间够
      c = ch; // 通过c指针复制串
      for (int i = 0; i <= len; i++, c++)
        str.ch[i] = *c; // 将c中字符拷贝到ch数组中
      /* 循环条件中之所以使用"<="，是为了将ch最后的'\0'复制到新串中作为结束标记"*/
      str.length = len;
      return 1;
    }
  }
}

// 取串长度操作
int strlength(Str1 str) { return str.length; }

// 串比较
// 设两串S1和S2中的待比较字符分别为a和b，如果a的ASCII码
// 小于b的ASCII码，则称S1小于S2；如果a的ASCII码大于b的ASCII码，则称S1大于S2；
// 如果相等则继续比较两串中的下一对字符。经过上述比较后，在没有比较出S1和S2大小的情况下，
// 先结束的串为较小串，两串同时结束则返回两串相等标记
int strcompare(Str1 s1, Str1 s2) {
  for (int i = 0; i < s1.length && i < s2.length; ++i)
    if (s1.ch[i] != s2.ch[i])
      return s1.ch[i] - s2.ch[i];
  return s1.length - s2.length;
}