#include <iostream>
#define maxSize 20
using namespace std;
typedef struct BTNode {
  char
      data; // 这里默认节点data域为char型，如果题目中需要其他类型，则只需要修改此处
  struct BTNode *lchild;
  struct BTNode *rchild;
} BTNode;

char visit(BTNode *p) { return p->data; }

// 先序遍历
// 1）访问根节点
// 2）先序遍历左子树
// 3）先序遍历右子树
void preorder(BTNode *p) {
  if (p != nullptr) {
    visit(
        p); // 假设访问函数visit已经定义，其中包含了对结点p的各种访问操作，如可以打印出p对应的数值
    preorder(p->lchild); // 先序遍历左子树
    preorder(p->rchild); // 先序遍历右子树
  }
}

// 中序遍历
// 1）中序遍历左子树
// 2）访问根节点
// 3）中序遍历右子树
void inorder(BTNode *p) {
  if (p != nullptr) {
    inorder(p->lchild);
    visit(p);
    inorder(p->rchild);
  }
}

// 后序遍历
// 1）后序遍历左子树
// 2）后序遍历右子树
// 3）访问根节点
void postorder(BTNode *p) {
  if (p != nullptr) {
    postorder(p->lchild);
    postorder(p->rchild);
    visit(p);
  }
}

// 表达式（a-（b+c））*（d/e）存储在一棵以二叉链表为存储结构的二叉树中
// 二叉树的结点的data域为字符型
// 请写出算法，计算该表达式的值
int comp(BTNode *p) {
  int A, B;
  if (p != nullptr) {
    if (p->lchild != nullptr && p->rchild != nullptr) {
      // 如果左右子树都不为空，则说明该节点为运算符
      A = comp(p->lchild);
      B = comp(p->rchild);
      switch (p->data) {
      case '+':
        return A + B;
      case '-':
        return A - B;
      case '*':
        return A * B;
      case '/':
        return A / B;
      }
    } else {
      // 如果当前节点的左右子树都为空，则为数值，直接返回
      return p->data - '0';
    }
  } else // 如果是空树，则表达式的值为0
    return 0;
  return 0;
}

// 写一个算法求一棵树的深度，二叉树以二叉链表为存储方式
int getDepth(BTNode *p) {
  int LD, RD;
  if (p == nullptr) {
    return 0; // 如果数是空树，则返回0（定义空树的深度为0）
  } else {
    LD = getDepth(p->lchild);       // 求左子树的深度
    RD = getDepth(p->rchild);       // 求右子树深度
    return (LD > RD ? LD : RD) + 1; // 返回左、右子树的深度的较大值加1
    // 即求整棵树深度
  }
}

// 在一个以二叉链表为存储结构的二叉树中，查找data域值等于key的结点是否存在
// 假设二叉树已经存在且p指向其根节点
void search(BTNode *p, BTNode *&q, int key) { // q定义为引用型指针，因为q要改变
  if (p != nullptr) { // 如果树为空树，则什么都不做，q保持null值
    if (p->data == key) { // 如果p所指节点的data域值为key，则q指向该节点
      q = p;
    } else { // 否则到左右子树中去查找
      search(p->lchild, q, key);
      search(p->rchild, q, key);
    }
  }
}

// 改进策略，如果在左子树中找到了满足要求的结点后，则无需继续查找右子树，直接退出本层递归
// 这就是剪枝
void searchv2(BTNode *p, BTNode *&q, int key) {
  if (p != nullptr) {
    if (p->data == key) {
      q = p;
    } else {
      searchv2(p->lchild, q, key);
      if (q == nullptr) { // 如果在左子树中没有找到，则继续在右子树中查找
        searchv2(p->rchild, q, key);
      }
    }
  }
}

// 假设二叉树采用二叉链表存储结构存储，编写一个程序，输出先序遍历序列中第k个结点的值
int n;
void trave(BTNode *p, int k) {
  if (p != nullptr) {
    ++n; // 当第一次来到第一个结点时计数，表示这是第n个结点
    if (k ==
        n) { // 当第一次来到一个结点时进行判断，看这个结点是不是先序序列的第k个结点
      cout << p->data << endl; // 如果是直接输出
      return;
    }
    trave(p->lchild, k);
    trave(p->rchild, k);
  }
}

// 若将题目中的先序改成中序或者后序
void intrave(BTNode *p, int k) {
  if (p != nullptr) {
    trave(p->lchild, k);
    ++n;
    if (k == n) {
      cout << p->data << endl;
      return;
    }
    trave(p->rchild, k);
  }
}
void posttrave(BTNode *p, int k) {
  if (p != nullptr) {
    trave(p->lchild, k);
    trave(p->rchild, k);
    ++n;
    if (k == n) {
      cout << p->data << endl;
      return;
    }
  }
}

// 层次遍历
// 要进行层次遍历，需要建立一个循环队列。先将二叉树头节点
// 入队列，然后出队列，访问该节点，如果它有左子树，则将左子树的根节点入队；
// 如果它有右子树，则将右子树的根节点入队。然后出队列，对出队的结点访问
void level(BTNode *p) {
  int front, rear;
  BTNode *que[maxSize];
  front = rear = 0;
  BTNode *q;
  if (p != nullptr) {
    rear = (rear + 1) % maxSize;
    que[rear] = p; // 根节点入队
    while (front != rear) {
      front = (front + 1) % maxSize;
      q = que[front]; // 队头结点出队
      visit(q);       // 访问队头结点
      if (q->lchild != nullptr) { // 如果左子树不为空，则左子树的根节点入队
        rear = (rear + 1) % maxSize;
        que[rear] = q->lchild;
      }
      if (q->rchild !=
          nullptr) { // 如果右子树的根节点不为空，则右子树的根节点入队
        rear = (rear + 1) % maxSize;
        que[rear] = q->rchild;
      }
    }
  }
}