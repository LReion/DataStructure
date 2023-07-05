#include <iostream>
using namespace std;
// 设计一个递归算法，求n个不同字符的所有全排列
// 递归算法的设计思想是：将n个字符分成两部分，第一个字符和其余的字符。首先求出除第一个字符外其余字符的全排列，然后将第一个字符与其余字符的全排列进行组合。
// 递归算法的实现思想是：将n个字符的全排列问题转化为n-1个字符的全排列问题，然后递归求解。
// 递归算法的实现步骤是：首先将第一个字符与其余字符进行交换，然后递归地求出除第一个字符外其余字符的全排列，最后将第一个字符与其余字符进行交换。
// 递归算法的终止条件是：当只有一个字符时，其全排列就是其本身。
// 递归算法的时间复杂度是：O(n!)，空间复杂度是：O(n)。
void swap(char &a, char &b) { // 交换函数
  char temp;
  temp = a;
  a = b;
  b = temp;
}

void Perm(char list[], int start, int end) { // 递归函数
  int i;
  if (start == end) { // 递归出口，当只有一个字符时，其全排列就是其本身
    for (i = 0; i <= end; i++)
      cout << list[i];
    cout << endl;
  } else {
    for (i = start; i <= end; i++) { // 递归体，将第一个字符与其余字符进行交换
      swap(list[start], list[i]);
      Perm(list, start + 1, end); // 递归求出除第一个字符外其余字符的全排列
      swap(list[start], list[i]);
    }
  }
}
int main() {
  char a[] = {'a', 'b', 'c'};
  Perm(a, 0, 2);
  return 0;
}
