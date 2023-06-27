#include <stdlib.h>

// 双链表节点定义
typedef struct DLNode {
  int data;             // data中存放结点数据域（默认是int型）
  struct DLNode *prior; // 指向前驱节点的指针
  struct DLNode *next;  // 指向后驱节点的指针
} DLNode;               // 定义双链表节点类型

// 采用尾插法建立双链表
void createDlistR(DLNode *&L, int a[], int n) {
  DLNode *s, *r;
  int i;
  L = (DLNode *)malloc(sizeof(DLNode));
  L->prior = nullptr;
  L->next = nullptr r =
      L; // 和单链表一样，r始终指向终端节点，开始头节点也是尾节点
  for (i = 0; i < n; i++) {
    s = (DLNode *)malloc(sizeof(DLNode));
    s->data = a[i];
    // 将s插入L的尾部，并且将r指向s，此时s的前驱节点是r。此时s是终端结点，r=s将r指向现在的终端结点s
    r->next = s;
    s->prior = r;
    r = s;
  }
  r->next = nullptr;
}

// 查找结点的算法
// 在双链表中查找第一个值为x的结点，从第一个节点开始，边扫描边比较
// 若找到这样的节点，则返回结点指针，否则返回null
DLNode *findNode(DLNode *C, int x) {
  DLNode *p = C->next;
  while (p != nullptr) {
    if (p->data == x)
      break;
    p = p->next;
  }
  return p; // 如果找到，则p中内容是节点地址（循环因break结束）
  // 如果没找到，则p中内容是null（循环因p==null结束）
  // 将题干中要求的两种返回值的情况统一起来
}

// 插入节点的算法
// 假设在双链表中p所指的结点之后插入一个s，其操作语句如下：

/* s->next = p->next;
s->prior = p;
p->next = s;
s->next->prior = s; */

// 删除节点的算法
// 设要删除双链表中p节点的后继结点，其操作语句如下：

/* q = p->next;
p->next = q->next;
q->next->prior = p;
free(q); */

// 循环单链表和循环双链表是由对应的单链表和双链表改造而来，只需在终端结点和头节点间建立联系即可。
// 循环单链表终端结点的next指针指向表头结点；循环双链表的终端节点的next指针指向表托结点，头结点的prior
// 指向表尾结点。需要注意的是，如果p指针沿着循环链表行走，则判断p走到表尾节点的条件是p->next=head, 
// 循环链表的各种操作均与非循环链表类似
