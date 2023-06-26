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