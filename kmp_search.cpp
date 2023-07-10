#include "String.cpp"
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

int kmp_search(Str1 str, Str1 substr, int next[]) {
  int i = 1, j = 1;
  while (i <= str.length && j <= substr.length) {
    if (j == 0 ||
        str.ch[i] == substr.ch[j]) { // 计算字串与待匹配字符串的公共长度
      ++i;
      ++j; // 记录指针位置
    } else
      j = next[j]; // 获取不匹配后，j从第几位开始匹配
  }
  if (j > substr.length)
    return i - substr.length;
  else
    return 0;
}

// KMP算法的改进，next数组的改进，使得next数组的值更加合理
// 模式串可能在1到5的位置上的字符完全相等，因此较为聪明的做法是在
// j等于5处发生不匹配时，直接跳过位置1到4的多余比较
void build_nextval(Str1 substr, int nextval[]) {
  int i = 1, j = 0; // 串从数组下标1位置开始存储，因此i初值为1
  nextval[1] = 0;
  while (i < substr.length) {
    if (j == 0 || substr.ch[i] == substr.ch[j]) { // 如果相等或者j=0
      ++i;
      ++j;
      if (substr.ch[i] !=
          substr.ch
              [j]) // 如果，当前字符与j位置的字符不相等，则直接记录相等时候j的位置
        nextval[i] = j;
      else // 如果当前字符与位置i的字符相等了，则可以j，直到没有相等，来记录不重复的next数组
        j = nextval[j];
    }
  }
}