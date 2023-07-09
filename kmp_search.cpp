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
      next[i] =
          j; // 并且记录匹配的长度，以便于后面不匹配后，对应i匹配的j从第几位开始
    } else
      j = next[j]; // 不匹配后，从第next[j]位开始匹配
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