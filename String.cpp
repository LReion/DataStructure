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

// 串连接操作
int concat(Str1 &str, Str1 str1, Str1 str2) {
  if (str.ch) {
    free(str.ch);
    str.ch = nullptr;
  }
  str.ch = (char *)malloc(sizeof(char) * (str1.length + str2.length + 2));
  if (str.ch == nullptr)
    return 0;
  int i = 0;
  while (i < str1.length) {
    str.ch[i] = str1.ch[i];
    ++i;
  }
  int j = 0;
  while (j <= str2.length) {
    str.ch[i + j] = str.ch[j];
    ++j;
  }
  str.length = str1.length + str2.length;
  return 1;
}

// 求子串的操作
// 从给定串中某一位置开始到某一位置结束的串操作称为求字串操作
// （规定开始位置总在结束位置前面），如下面的代码实现了求str串中
// 从pos位置开始，长度为len的字串，字串由substr返回给用户
int substrin(Str1 &substr, Str1 str, int pos, int len) {
  // 检查开始位置，长度是否合法，如果不合法则返回0
  if (pos < 0 || pos > str.length || len < 0 || len > str.length - pos)
    return 0;
  if (substr.ch) {       // 如果字串不为空串
    free(substr.ch);     // 释放字串
    substr.ch = nullptr; // 设置好空指针
  }
  if (len == 0) {        // 如果长度是0
    substr.ch = nullptr; // 则直接返回空串
    substr.length = 0;   // 空串长度为0
    return 1;
  } else { // len不为0
    substr.ch = (char *)malloc(
        sizeof(char) * (len + 1)); // 为字串分配空间，len+1，是为了存放'\0'
    int i = pos;                   // 开始位置
    int j = 0;                     // 偏移位置
    while (i < pos + len) { // 从开始位置开始，复制len个字符到字串中
      substr.ch[j] = str.ch[i];
      ++i;
      ++j;
    }
    substr.ch[j] = '\0'; // 设置字串结束标志
    substr.length = len; // 设置字串长度
    return 1;
  }
}

// 串清空操作
int cleanstring(Str1 &str) {
  if (str.ch) { // 如果串不为空串
    free(str.ch);
    str.length = 0;
  }
  // 如果是空串
  str.length = 0;
  return 1;
}

// 串的模式匹配算法
// 简单模式匹配算法，是一种最简单的模式匹配算法。
// 其中待定位的字串成为模式串。算法的基本思想：
// 从主串的第一个位置起和模式串的第一个字符开始比价，
// 如果相等，则继续比较下一个字符，否则从主串的第二个字符开始重新和模式串的第一个字符比较，
// 以此类推，直到比较完模式串中的所有字符。若匹配成功，则返回模式串在主串中的位置：如匹配不成，则要返回一个可区别于所有位置的值，如“-1“
int index(Str1 str, Str1 substr) {
  int i = 0, j = 0, k = i; // 串从数组下标0位置开始存储
  while (i < str.length && j < substr.length) {
    if (str.ch[i] == substr.ch[i]) {
      ++i;
      ++j;
    } else {
      j = 0;
      i = ++k; // 匹配失败，i从主串的下一个位置开始，j从模式串的第一个位置开始,k记录匹配失败时主串的下一个位置
    }
  }
  // 如果j找到的长度大于等于字串的长度，则找到了匹配的子串
  // 因为可能出来的情况是j小于字串的长度，没有匹配完整个子串
  if (j >= substr.length)
    return k;
  else
    return -1;
}
