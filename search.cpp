#include <stdlib.h>
#define maxSize 100

int Search(int A[], int n, int k) {
  int i;
  for (i = 1; i <= n; i++) {
    if (A[i] == k)
      return i; // 查找成功返回i
  }
  return 0; // 查找失败返回0
}
// 二分查找
// 假设线性表是递增有序的
int Bsearch(int R[], int low, int high, int k) {
  int mid;
  while (low <= high) {     // 当子表长度大于等于1时进行循环
    mid = (low + high) / 2; // 取当前表的中间位置
    if (R[mid] == k)        // 找到后返回元素的位置
      return mid;
    else if (R[mid] > k) // 说明需要在R[low, ..., mid]中继续查找
      high = mid - 1;
    else // 说明需要在R[mid, ..., high]中继续查找
      low = mid + 1;
  }
  return 0;
}

// 分块查找
typedef struct {
  int key;       // 假设表内元素为int型
  int low, high; // 记录某块中第一个和最后一个元素的位置
} indexElem;
indexElem index[maxSize]; // 定义索引表，maxSize是已定义的常量
// 分块查找算法可以分两步进行，首先确定待查找的元素属于哪一块，然后再块内精准查找该元素。
// 由于索引表是递增有序地，因此第一步采用二分查找。块内元素的个数一般较少，因此第二步采用顺序查找即可。
// 分块查找实际上是进行两次查找，整个算法的平均查找长度是两次查找长度的平均查找长度之和，即二分查找平均查找长度
// +顺序查找平均查找长度

// 树形查找
// 二叉排序树
typedef struct BTNode {
  int key; // 这里将data改成key，代表关键字
  struct BTNode *lchild;
  struct BTNode *rchild;
} BTNode;

BTNode *BSTSearch(BTNode *bt, int key) {
  if (bt == nullptr)
    return nullptr; // 查找不成功，则返回nullptr
  else {
    if (bt->key ==
        key) // 等于根节点中的关键字，查找成功，返回关键字所在的结点指针
      return bt;
    else if (bt->key > key) // 小于根节点中的关键字，则到左子树去查找
      return BSTSearch(bt->lchild, key);
    else // 大于根节点中的关键字，则到右子树去查找
      return BSTSearch(bt->rchild, key);
  }
}

int BSTInsert(BTNode *&bt, int key) { // 因为指针bt要改变，因此使用引用型指针
  if (bt == nullptr) {
    bt = (BTNode *)malloc(sizeof(BTNode));
    bt->lchild = bt->rchild = nullptr;
    bt->key = key;
    return 1;
  } else {
    if (key == bt->key) // 关键字已存在于树中，插入失败，返回0
      return 0;
    else if (key < bt->key) // 插入到左子树
      return BSTInsert(bt->lchild, key);
    else // 插入到右子树
      return BSTInsert(bt->rchild, key);
  }
}

// 二叉排序树的构造算法
// 假设关键字已经存入数据key[]中
void CreateBST(BTNode *&bt, int key[], int n) {
  int i;
  bt = nullptr;
  for (i = 0; i < n; i++) {
    BSTInsert(bt, key[i]);
  }
}