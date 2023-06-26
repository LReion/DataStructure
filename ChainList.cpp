#include <stdlib.h>
// 单链表节点定义
typedef struct LNode {
  int data;           // data中存放节点数据域（默认是int型）
  struct LNode *next; // 指向后继节点的指针
} LNode;              // 定义单链表节点类型

// A和B是两个单链表（带头节点），其中元素递增有序。
// 设计一个算法，将A和B归并成一个按元素值非递减有序的链表C，
// C由A和B中的节点组成.
void merge(LNode *A, LNode *B, LNode *&C) {
  LNode *p = A->next; // p来跟踪A的最小值结点
  LNode *q = B->next; // q来跟踪B的最小值节点
  LNode *r;
  C = A;             // 用A的头节点来做C的头节点
  C->next = nullptr; // 从A链表中取下头节点作为C的头节点，此时C只有一个头节点
  free(B);           // 此时B的头结点已无用，则释放掉
  r = C;             // r指向C，因为此时头节点也是终端节点
  while (p != nullptr && q != nullptr) { // 当p与q都不空时
                                         /*   以下的if
                                           else语句中，r始终指向当前链表的的终端界定，作为接纳新节点的一个媒介，
                                           通过它，新节点被链接入C并且重新指向新的终端节点，以便于接收下一个新节点，
                                           这里体现了建立链表的尾插法思想 */
    if (p->data <= q->data) {
      r->next = p;
      p = p->next;
      r = r->next;
    } else {
      r->next = q;
      q = q->next;
      r = r->next;
    }
  }
  r->next = nullptr; // 将结束后r的next设置为空指针
  // 一下两个if语句将还有剩余节点的链表链接在C的尾部
  if (p != nullptr)
    r->next = p;
  if (q != nullptr)
    r->next = q;
}

// 使用尾插法创建单链表
// 假设有m个元素已经存储在数组a中，用尾插法来建立链表C
void createListR(LNode *&C, int a[], int n) {
  LNode *s, *r;
  C = (LNode *)malloc(sizeof(LNode)); // 创建头节点
  C->next = nullptr;                  // 初始为空链表
  r = C; // r始终指向终端节点，开始时指向头节点
  for (int i = 0; i < n; i++) {
    s = (LNode *)malloc(sizeof(LNode)); // 创建新节点
    s->data = a[i];                     // 赋值
    r->next = s;                        // 将新节点s链接到终端节点后
    r = s;                              // r指向新的终端节点
  }
  r->next = nullptr; // 将终端节点的next设置为空指针
}

// 头插法
void createlistF(LNode *&C, int a[], int n) {
  LNode *s;
  int i;
  C = (LNode *)malloc(sizeof(LNode));
  C->next = nullptr;
  for (i = 0; i < n; i++) {
    s = (LNode *)malloc(sizeof(LNode));
    s->data = a[i];
    s->next = C->next; // s所指新节点的指针域next指向C中开始结点
    C->next =
        s; // 头结点的指针域next指向s，这样就把s所指新节点链接到C的开始结点之前
  }
}

// 归并成递减的单链表的算法代码如下：
void merge_v2(LNode *A, LNode *B, LNode *&C) {
  LNode *p = A->next;
  LNode *q = B->next;
  LNode *s;
  C = A;
  C->next = nullptr;
  free(B);
  while (p != nullptr && q != nullptr) {
    if (p->data <= q->data) {
      s = p;
      p = p->next;
      s->next = C->next;
      C->next = s;
    } else {
      s = q;
      q = q->next;
      s->next = C->next;
      C->next = s;
    }
  }
  /* 以下两个循环是和求递增归并序列不同的地方，必须将剩余元素逐个插入C的头部才能得到最终的dijianxulie*/
  while (p != nullptr) {
    s = p;
    s->next = C->next;
    C->next = s;
    p = p->next;
  }
  while (q != nullptr) {
    s = q;
    s->next = C->next;
    C->next = s;
    q = q->next;
  }
}
// 查找链表C（带头结点）中是否存在一个值为x的节点，若存在，则删除该节点并返回1，否则返回0
int findAndDelte(LNode *&C, int x) {
  LNode *p, *q;
  p = C;
  while (p->next != nullptr) {
    if (p->next->data == x)
      break;
    p = p->next;
  }
  // 查找部分结束
  if (p->next == nullptr)
    return 0; // 没有找到
  else {
    q = p->next; // 用q来记录x的节点位置
    p->next = q->next;
    free(q);
    // 删除部分结束
    return 1;
  }
}