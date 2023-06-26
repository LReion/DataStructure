#define maxSize 100 // 这里定义一个整型常量maxSize，值为100

// 线性表的结构体定义
typedef struct {
  int data[maxSize]; // 存放顺序表元素的数组（默认是int型，也可以是其他类型）
  int length;        // 存放顺序表的长度
} Sqlist;            // 顺序表类型的定义

// 单链表节点定义
typedef struct LNode {
  int data;           // data中存放节点数据域（默认是int型）
  struct LNode *next; // 指向后继节点的指针
} LNode;              // 定义单链表节点类型

// 双链表节点定义
typedef struct DLNode {
  int data;             // data中存放结点数据域（默认是int型）
  struct DLNode *prior; // 指向前驱节点的指针
  struct DLNode *next;  // 指向后驱节点的指针
} DLNode;               // 定义双链表节点类型

// 此函数返回第一个比x大的元素的位置
int findElem(Sqlist L, int x) {
  int i;
  for (i = 0; i < L.length; i++) {
    if (x < L.data[i]) { // 对顺序表中的元素从小到大进行逐个判断
      return i; // 看x是否小于顺序表中的元素，若小于，则返回该元素的位置
    }
  }
  return i; // 如果顺序表中不存在比x大的元素，则应该将x插入表尾元素之后
  // 返回i来标记这种情况，因为i<L.length这一句不成立而退出for循环后
  // i正好指示了表尾元素之后的位置，同样也是正确的插入位置
}

// 将元素插入顺序表
void insertElem(Sqlist &L, int x) { // 因为L本身要发生改变，所以要用引用类型
  int p, i;
  p = findElem(L, x); // 调用函数findElem()来找到插入位置p
  for (i = L.length - 1; i >= p; i--)
    L.data[i + 1] = L.data[i]; // 从右往左，逐个将元素右移一个位置
  L.data[p] = x;               // 将x放在插入位置p上
  ++L.length;                  // 表内元素多了一个，因此表长自增1
}

// 按元素值的查找算法
int findElem_v2(Sqlist L, int e) {
  int i;
  for (i = 0; i < L.length; i++)
    if (L.data[i] == e)
      return i; // 找到了，返回该元素的位置
  return -1;    // 没找到，返回-1，作为失败标记
}

// 插入元素的算法完整版
// 在顺序表L的p位置上插入新的元素e。如果p的输入不正确，则返回0，代表插入失败
// 如果p的输入正确，则将顺序表第p个元素以及后面的元素都向后移动一个位置，然后将新元素e插入到顺序表的第p个位置上
int insertElem_v2(Sqlist &L, int p, int e) { // L本身要发生改变，所以用引用类型
  int i;
  if (p < 0 || p > L.length || L.length == maxSize) // 判断p的范围是否有效
    return 0; // 返回0，表示插入失败
  for (i = L.length - 1; i >= p; i--)
    L.data[i + 1] = L.data[i]; // 从右往左，逐个将元素右移一个位置
  L.data[p] = e;               // 将新元素e放在插入位置p上
  ++L.length;                  // 表内元素多了一个，因此表长自增1
  return 1;                    // 返回1，表示插入成功
}

// 删除顺序表L中下表为p的元素，并用e返回其值。如果p的输入不正确，则返回0，代表删除失败
int deleteElem(Sqlist &L, int p, int &e) { // 需要改变的变量用引用型
  int i;
  if (p < 0 || p > L.length - 1) // 判断p的范围是否有效
    return 0;                    // 返回0，表示删除失败
  e = L.data[p];                 // 将被删除的元素赋值给e
  for (i = p; i < L.length - 1;
       i++) // 从p位置开始，将其后面的元素逐个前移一个位置
    L.data[i] = L.data[i + 1];
  --L.length; // 表长减1
  return 1;   // 删除成功，返回1
}

// 初始化顺序表的算法
void initList(Sqlist &L) { // 要改变，所以用引用型
  L.length = 0;
}
// 返回指定未知元素的算法
// 用e返回L中p位置上的元素
int getElem(Sqlist L, int p, int &e) { // 要改变，所以用引用型
  if (p < 0 || p > L.length - 1) // p值越界错误，返回0
    return 0;
  e = L.data[p];
  return 1;
}