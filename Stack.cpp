#include <stdlib.h>
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

// 顺序队列定义
typedef struct {
  int data[maxSize];
  int front; // 队首指针
  int rear;  // 队尾指针
} SqQueue;   // 顺序队类型定义

// 链队节点定义
typedef struct QNode {
  int data;           // 数据域
  struct QNode *next; // 指针域
} QNode;              // 队结点类型定义

// 链队类型定义
typedef struct {
  QNode *front; // 队头指针
  QNode *rear;  // 队尾指针
} LiQueue;      // 链队类型定义

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
  if (lst->next = nullptr)
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