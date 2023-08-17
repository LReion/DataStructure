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