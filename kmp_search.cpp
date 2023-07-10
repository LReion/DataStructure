#include "String.cpp"
void build_next(Str1 &substr, int next[]) {
  // 当模式串的第j个字符失配，从模式串的第next[j]个继续往后匹配
  // 将模式串逐个与自己匹配来记录next数组
  int i = 0, j = 0;
  next[0] = 0;
  while (i <= substr.length) {
    if (j == 0 ||
        substr.ch[i] ==
            substr.ch[j]) { // 将自己与自己匹配（如果匹配成功，则同时后移）
      ++i;
      ++j;
      next[i] = j; // 记录匹配到当前i位置匹配的成功的j位置
    } else
      j = next[j]; // 不匹配后，当前是j位置，根据next[j]来获取当前位置i匹配成功的j位置，
  }
}

int kmp_search(Str1 str, Str1 substr, int next[]) {
  int i = 0, j = 0;
  while (i <= str.length && j <= substr.length) {
    if (j == 0 ||
        str.ch[i] == substr.ch[j]) { // 计算字串与待匹配字符串的公共长度
      ++i;
      ++j; // 记录指针位置
    } else
      j = next[j]; // 获取不配后，j从第几位开始匹配
  }
  if (j >= substr.length)
    return i - substr.length;
  else
    return 0;
}

// KMP算法的改进，next数组的改进，使得next数组的值更加合理
// 模式串可能在1到5的位置上的字符完全相等，因此较为聪明的做法是在
// j等于5处发生不匹配时，直接跳过位置1到4的多余比较
