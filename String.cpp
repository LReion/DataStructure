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

// 将串str中所有值为ch1的字符转换成ch2的字符，如果str为空串，或者串中不含ch1的字符，则什么都不做
void convect(Str1 &str, char &ch1, char &ch2) {
  if (str.ch) {
    for (int i = 0; i < str.length; i++)
      if (str.ch[i] == ch1)
        str.ch[i] = ch2;
  } else {
    str.ch = nullptr;
    str.length = 0;
  }
}

// 实现串str的逆转函数，如果str为空串
void reverse(Str1 &str) {
  if (str.ch) {
    char temp;
    for (int i = 0, j = str.length - 1; i < j; i++, j--) {
      temp = str.ch[i];
      str.ch[i] = str.ch[j];
      str.ch[j] = temp;
    }
  } else {
    str.ch = nullptr;
    str.length = 0;
  }
}

// 删除str中值为ch的所有字符，如果str为空串，或者串中不含ch的字符，则什么都不做
void del(Str1 &str, char &ch) {
  if (str.ch) { // 不为空串
    for (int i = 0; i < str.length; i++)
      if (str.ch[i] == ch) {
        for (int j = i; i < str.length; j++)
          str.ch[j] = str.ch[j + 1]; // 用后续字符来覆盖前面的字符
        str.length--;
        str.ch[str.length] = '\0'; // 添加结束字符
      }
  } else {
    str.ch = nullptr;
    str.length = 0;
  }
}
// del改进版本
void del2(Str1 &str, char ch) {
  if (str.length != 0) {
    int ch_num = 0;
    int i, j;
    while (str.ch[i] != '\0') {
      if (str.ch[i] == ch) {
        ++ch_num;
        for (
            j = i + 1; str.ch[j] != '\0';
            j++) // 将每个待删字符到后一个待删字符之间的字符向前移动i个位置，i是目前扫描到的待删除字符的个数，这样就能覆盖掉待删字符
          str.ch[j - ch_num] = str.ch[j];
        i = j;
        --str.length;
      } else
        ++i;
    }
    str.ch[str.length] = '\0';
  }
}

// 从串str的pos位置开始，求出与substr串匹配的字串位置，如果str为空串，或者串中不含
// 与substr匹配的字串，则返回-1做标记
void build_next(Str1 &substr, int next[]) {
  // 当模式串的第j个字符失配，从模式串的第next[j]个继续往后匹配
  // 将模式串逐个与自己匹配来记录next数组
  int i = 1, j = 1; // 串从数组下标1位置开始存储，因此初值为1
  next[0] = 0;
  while (i < substr.length) {
    if (j ==
            0 || // 如果找到第一个仍没有匹配，则会出现j=0的情况，然后i跳到下一个字符与j来寻找配对字符
        substr.ch[i] == substr.ch[j]) { // (计算最大公共前后缀)
      ++i;
      ++j;
      next[i] = j; // 记录匹配到当前i位置匹配的成功的j位置
    } else
      j = next[j]; // 没有匹配，往前找，看能否匹配
  }
}
int getPos(Str1 &str, Str1 &substr, int pos) {
  int next[substr.length];
  build_next(substr, next);
  int i = pos, j = i;
  while (i <= str.length && j <= substr.length) {
    if (j == 0 || str.ch[i] == substr.ch[i]) {
      ++i;
      ++j;
    } else {
      j = next[j];
    }
  }
  if (j > substr.length) {
    return i - substr.length;
  } else {
    return -1;
  }
}

// 采用定长顺序存储表示串，编写一个函数，删除串中从下标为i的字符开始的j个字符
// 如果下标为i的字符没有足够的j,则有几个删几个
void deletePos(Str1 &str, int i, int j) {
  if (i < 0 || i >= str.length || j < 0) // 判断位置是否合法
    return; // 如果位置不合法，返回1标识删除错误
  else {    // 从i开始，删除j
    for (int k = i + j; k < str.length; ++k)
      str.ch[k - j] = str.ch[k];
    str.length -= (str.length - i < j ? str.length - i : j);
    // 调整串长，需要考虑两种情况
    str.ch[str.length] = '\0';
  }
}

// 采用顺序存储方式存储串，编写一个函数，将串str1中的下标i到下标j之间的字符
// （包括i和j两个位置上的字符）用str2串替换
int replace(Str1 &str1, int i, int j, Str1 &str2) {
  if (i < 0 || j < 0 || i > str1.length || j > str1.length || i > j)
    return 0;
  else {
    if (i + j > str1.length) {
      for (int k = i; k < str1.length; k++)
        str1.ch[k] = str2.ch[k - i];
      return 1;
    } else {
      for (int k = i; k < str1.length - j; k++)
        str1.ch[k] = str2.ch[k - i];
      return 1;
    }
  }
}

// 编写一个函数，计算一个字串在一个主串中出现的次数，如果该字串不出出现，则返回0
// 本题不考虑主串重叠的情况，如：主串为aaaa，子串为aaa，考虑字串重叠结果为2
// 不考虑子串重叠结果为1
int computeOverlap(Str1 &str1, Str1 &str2) {
  if (str1.length < str2.length)
    return -1;
  else {
    int i = 0, j = 1, k = i;
    int count = 0;
    while (i < str1.length &&
           j < str2.length) { // i和j的位置都要小于各自对应的长度
      if (str1.ch[i] == str2.ch[j]) { // 如果相等，继续往后比
        ++i;
        ++j;
      } else {   // 出现不匹配
        j = 1;   // 模式串从头开始比
        i = ++k; // 主串从下一个开始
      }

      if (j >
          str2.length) { // 如果对比的途中，j的长度大于等于模式串的长度，则代表匹配成功
        ++count;         // 记录匹配成功的次数
        j = 1;           // 继续对主串进行匹配
        i = ++k;
      }
    }
    return count;
  }
}

// 构造出串的链表节点数据结构（每个结点内存储一个字符），编写一个函数，找出串str1中第一个不在str2中出现的字符
typedef struct SNode {
  char ch;
  struct SNode *next;
} SNode;
char findFirst(SNode *str1, SNode *str2) {
  for (SNode *p = str1; p != nullptr; p = p->next) {
    bool flag = false;
    for (SNode *q = str2; q != nullptr; q = q->next)
      if (p->ch == q->ch) {
        flag = false;
        break;
      }
    if (flag == false)
      return p->ch;
  }
  return '\0';
}