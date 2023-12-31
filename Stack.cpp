#include <iostream>
#include <malloc.h>
#include <stdlib.h>

using namespace std;
#define maxSize 20
// 顺序栈定义
typedef struct {
  int data[maxSize]; // 存放栈中元素，maxSize是已定义的常量
  int top;           // 栈顶指针
} SqStack;           // 顺序栈类型定义

// 链栈节点定义
typedef struct LNode {
  int data;           // 数据域
  struct LNode *next; // 指针域
} LNode;              // 链栈结点
/*   链栈就是采用链表来存储栈。这里用带头结点的单链表来作为存储体 */

// 初始化栈
void initStack(SqStack &st) {
  st.top = -1; // 这里规定将栈顶指针设置为-1时，栈为空
}

// 判断栈是否为空
/* 栈st为空时返回1，否则返回0，其对应代码如下 */
int isEmpty(SqStack st) {
  if (st.top == -1)
    return 1;
  else
    return 0;
}

// 进栈代码
int push(SqStack &st, int x) {
  if (st.top == maxSize - 1) // 栈满不能进栈
    return 0;
  st.data[++st.top] = x; // ++st.top先移动栈道顶指针，再进栈数据x
  return 1;
}

// 出栈代码
int pop(SqStack &st, int &x) {
  if (st.top == -1) // 如果栈为空，则不能出栈
    return 0;
  x = st.data[st.top--]; // 先出栈，再移动栈顶指针
  return 1;
}

// 链栈的基本操作
// 初始化链栈
void initStack(LNode *&lst) {
  lst = (LNode *)malloc(sizeof(LNode)); // 分配一个头结点
  lst->next = nullptr;                  // 头结点的指针域置空
}

// 判断栈空代码
/* 当栈空时返回1，否则返回0，代码如下 */
int isEmpty(LNode *lst) { // 判断是否为空
  if (lst->next == nullptr)
    return 1;
  else
    return 0;
}

// 进栈代码
void push(LNode *lst, int x) {
  LNode *p;
  p = (LNode *)malloc(sizeof(LNode)); // 为进栈元素申请结点空间
  p->next = nullptr; // 申请新节点时，将其指针域设置为nullptr可以避免一些错误

  /*   以下三句就是链表的头插法 */
  p->data = x;
  p->next = lst->next;
  lst->next = p;
}

// 出栈代码
/* 在栈不空的情况下可以执行，返回1，否则返回0，代码如下： */
int pop(LNode *lst, int &x) {
  LNode *p;
  if (lst->next == nullptr)
    return 0;
  // 单链表的删除操作
  p = lst->next;
  x = p->data;
  lst->next = p->next;
  free(p);
  return 1;
}

// 顺序栈的应用
/* C语言中算术运算符的括号只有小括号。编写算法，判断一个表达式中的括号是否正确配对，表达式已经存入字符数组exp[]中，
表达式中字符个数为n */
int match(char exp[], int n) {
  char stack[maxSize]; // 两句话完成栈的定义和初始化
  int top = -1;        // 考试中用这种写法可以节省时间
  int i;
  for (i = 0; i < n; i++) {
    if (exp[i] == '(')
      stack[++top] = '(';
    if (exp[i] == ')') {
      if (top == -1) // 如果当前遇到的括号是")”，而且栈已空，则不匹配，返回0
        return 0;
      else
        --top; // 如果栈不空，则出栈
      // 划掉两个括号的操作，当前的不入栈，而且栈顶元素出栈
    }
  }
  if (top == -1) // 栈空（所有括号都被处理掉了），则匹配，返回1
    return 1;
  else // 否则括号不匹配
    return 0;
}

/* 编写一个函数，求后缀表达式的数值，其中后缀表达式存于一个字符数组exp中，
exp中最后一个字符为'\0'作为结束符，并且假设后缀式中的数字都只有一位。 */
int op(int a, char Op, int b) { // 本函数是运算函数，用来完成算式 “a Op b”的运算
  if (Op == '+')
    return a + b;
  if (Op == '-')
    return a - b;
  if (Op == '*')
    return a * b;
  if (Op == '/') {
    if (b == 0) {
      cout << "ERROR" << endl; // 这里需要判断，如果除数为0，则输出错误标记
      return 0;
    } else
      return a / b;
  }
  return 0;
}
// 当遇到数字时，将其转换为整型后进栈，当遇到运算符时，从栈顶取出两个操作数，进行运算后，将结果进栈，直到表达式结束。
int com(char exp[]) { // 后缀表达式计算函数
  int i, a, b, c;     // a, b为操作数，c来保存结果
  int stack[maxSize]; // 栈的初始化和定义
  int top = -1;
  char Op; // Op用来取操作符
  for (i = 0; exp[i] != '\0';
       i++) { // 如果遇到操作数，则入栈等待处理，体现了栈的记忆功能
    if (exp[i] >= '0' && exp[i] <= '9')
      stack[++top] = exp[i] - '0'; // 字符型和整型的转换
    else { // 如果遇到运算符，则说明前面待处理的数字的处理条件已经具备，开始运算
      Op = exp[i]; // 取运算符
      b = stack[top--];
      // 取第二个操作数（因为第二个操作数后入栈，所以先出栈的是第二个操作数）
      a = stack[top--]; // 取第一个操作数
      c = op(a, Op, b); // 将两个操作数结合运算符Op进行运算，结果保存在c中
      stack[++top] = c; // 运算结果入栈
    }
  }
  return stack[top];
}

// 链栈的应用
/* 用不带头结点的单链表存储链栈，设计初始化栈、判断栈是否为空、进栈和出栈等相应的算法
 */
// 不带头结点的单链表lst为空的条件是lst=nullptr，进栈和出栈操作都是在表头进行的
void initStac1(LNode *&lst) { // 初始化栈
  lst = nullptr;
}
int isEmpty1(LNode *lst) { // 判断栈是否为空
  if (lst == nullptr)
    return 1;
  else
    return 0;
}
void push1(LNode *&lst, int x) { // 进栈
  LNode *p;
  p = (LNode *)malloc(sizeof(LNode));
  p->next = nullptr;
  p->data = x;
  /* 下面是插入操作 */
  p->next = lst; // 将链栈链接在新结点之后
  lst = p;       // 将新结点作为链栈的第一个结点
}

int pop1(LNode *&lst, int &x) { // 元素出栈
  LNode *p;
  if (lst == nullptr)
    return 0;
  /*     删除结点操作 */
  p = lst;
  x = p->data;
  lst = lst->next;
  free(p);
  return 1;
}

/* 1. 为了充分利用空间，顺序栈s0、s1共享一个存储区elem[0, ... , maxSize-1]。
试设计共享栈s0、s1以及有关入栈和出栈的算法，假设栈中元素为int型。要求
（1）给出基本设计思想
（2）根据设计思想，采用C或C++语言描述算法（对于共享栈要写出其结构定义），关键之处给出注释
*/

// 共享栈的结构定义
typedef struct {
  int elem[maxSize]; // 栈空间，maxSize是已经定义的常量
  int top[2];        // top[0]为s0栈顶，top[1]为s1栈顶
} ShStack;

// 入栈操作
int push(ShStack &st, int stNo, int x) {
  if (st.top[0] + 1 < st.top[1]) { // 栈未满，则元素可以入栈
    if (stNo == 0) {               // 元素入s0栈
      st.elem[++st.top[0]] = x;
      return 1;             // 入栈成功，返回1
    } else if (stNo == 1) { // 元素入s1栈
      st.elem[++st.top[1]] = x;
      return 1; // 入栈成功返回1
    } else
      return -1; // 栈编号错误，返回-1
  } else
    return 0; // 栈满，返回0
}

// 出栈操作
int pop(ShStack &st, int stNo, int &x) { // stNo是栈的编号，指示元素x接受哪个
  if (stNo == 0) {                       // s0元素出栈
    if (st.top[0] != -1) {               // s0不空，则可以出栈
      x = st.elem[st.top[0]--];
      return 1; // 出栈成功返回1
    } else
      return 0;                 // 栈空，返回0
  } else if (stNo == 1) {       // s1元素出栈
    if (st.top[1] != maxSize) { // 栈不满
      x = st.elem[st.top[1]++];
      return 1; // 出栈成功，返回1
    } else
      return 0; // 栈空，返回0
  } else
    return -1; // 编号错误，返回-1
}

/* 2）s0的栈顶为top0，s0入栈操作为：top0先自增1；然后存入元素；
出栈操作为：先取出栈顶元素，top0再自减1。s1的栈顶为top1，s1
入栈操作为：top1先自减1，然后存入元素；出栈操作为：先取出栈顶元素，
top1再自增1
（1）基本思想
栈的特点是先进后出，队列的特点是先进先出。所以，当用两个栈s1和s2模拟一个队列时，
s1作为输入栈，逐个元素压栈，以此模拟队列元素的入栈操作；当需要出队时，将栈s1退栈
并逐个压入栈s2中，s1中最先入栈的元素在s2中处于栈顶。s2退栈，相当于队列的出队操作，
实现了先进先出。只有栈s2为空且s1也为空，才算是队列空。
（2）算法描述 */

// 实现队列的入队操作
int enQueue(SqStack &s1, SqStack &s2, int x) {
  /* s1是容量为maxSize的栈。本算法将x入栈，若入栈成功则返回1，否则返回0*/
  int y;
  if (s1.top == maxSize - 1) { // 如果栈s1满，则看s2是否为空
    if (!isEmpty(s2))          // 如果栈s2不为空，这是s1不能再入栈
      return 0;
    else if (isEmpty(s2)) { // 如果s2为空
      while (!isEmpty(s1)) { // 而且如果s1不空，则将s1中元素逐个出栈并入栈s2
        pop(s1, y);
        push(s2, y);
      }
      push(s1, x); // 入栈x
      return 1;
    }
  } else { // 如果s1为没有满，则直接入栈即可
    push(s1, x);
    return 1;
  }
  return 0;
}

// 实现队列的出队操作
int deQueue(SqStack &s1, SqStack &s2, int &x) {
  /* s2栈顶元素出栈，实现出队操作，x接受出队元素，若成功则返回1，否则返回0 */
  int y;
  if (!isEmpty(s2)) { // 如果s2不空，则直接将栈顶元素出栈
    pop(s2, x);
    return 1;
  } else {
    if (isEmpty(s1))
      return 0;
    else {
      while (!isEmpty(s1)) {
        pop(s2, y);
        push(s2, y);
      }
      pop(s2, x);
      return 1;
    }
  }
}

// 在算法中，扫描程序中的每一个字符，当扫描到每个左花括号、左方括号、左圆括号时，
// 令其进栈；当扫描到右花括号、右方括号、右圆括号时，则检查栈顶是否为相应的左括号，
// 若是则做退栈处理，若不是则表明出现了语法错误，返回0。当扫描到程序文件结尾时，
// 若栈为空，则表明没有发现括号匹配错误，返回1；否则表明栈中还有未匹配的括号，
// 返回0。另外，对于一对单引号或双引号内的字符不进行括号匹配检查。

int bracketCheck(char f[]) {
  SqStack S;
  char ch;
  char *p = f;
  while (*p != '\0') {
    if (*p == 39) {
      ++p;
      while (*p != 39)
        ++p;
      ++p;
    } else if (*p == 34) {
      ++p;
      while (*p != 34)
        ++p;
      ++p;
    } else {
      switch (*p) {
      case '{':
      case '[':
      case '(':
        push(S, *p);
        // 出现左括号，进栈
        break;
      case ']':
        getTop(S, ch);
        if (ch == '[')
          pop(S, ch);
        else
          return 0;
        break;
      case ']':
        getTop(S, ch);
        if (ch == '[') {
          pop(S, ch);
        } else
          return 0;
        break;
      case ')':
        getTop(S, ch);
        if (ch == '(')
          pop(S, ch);
        else
          return 0;
      }
      ++p;
    }
  }
  if (isEmpty(S))
    return 1;
  else
    return 0;
}