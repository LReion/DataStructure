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
  BTNode *que[maxSize]; // 定义一个循环队列，用来记录将要访问的层次上的结点
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

// 假设二叉树采用二叉链表存储结构存储，设计一个算法，
// 求出该二叉树的宽度（具有节点数最多的那一层的节点数）
// 要求含有最多结点数的层上的结点数，可以分别求出每层的结点数
// 然后从中选出最多的
/* 下面定义的这个结构型为顺序非循环队列的队列元素，可以存储结点指针以及结点所在的层次号
 */
typedef struct {
  BTNode *p; // 结点指针
  int lno;   // 节点所在层次号
} St;
int maxNode(BTNode *p) {
  St que[maxSize];
  int front, rear; // 定义顺序非循环队列
  int Lno = 0, i, j, n, max = 0;
  front = rear = 0; // 队列置空
  BTNode *q;
  if (p != nullptr) {
    ++rear;
    que[rear].p = p;   // 树根入队
    que[rear].lno = 1; // 树根所在层次号设置为1
    while (front != rear) {
      ++front;
      q = que[front].p;
      Lno = que[front].lno; // Lno用来存取当前结点的层次号
      if (q->lchild != nullptr) {
        ++rear;
        que[rear].p = q->lchild;
        que[rear].lno = Lno + 1; // 根据当前结点的层次号，推知其孩子的层次号
      }
      if (q->rchild != nullptr) {
        ++rear;
        que[rear].p = q->rchild;
        que[rear].lno = Lno + 1;
      }
    }
    // 循环结束，Lno中保存了这颗二叉树的最大层数
    // 以下代码找出了含有结点最多的层数中的节点数
    max = 0;
    for (i = 1; i <= Lno; i++) {
      n = 0;
      for (j = 0; j < rear; j++) {
        if (que[j].lno == i) {
          ++n;
        }
        if (max < n)
          max = n;
      }
      return max;
    }
  } else
    return 0; // 空树直接返回0
  return 0;
}

// 二叉树遍历算法的改进
// 深度优先遍历算法都是用递归函数来实现的，这是很低效的，
// 原因在于系统帮你调用了一个栈，并做了诸如保护现场和恢复现场等复杂的操作，
// 才使得遍历可以用非常简洁的代码实现。

// 二叉树深度优先遍历算法的非递归实现
// 要写出其遍历的非递归算法，主要任务就是用自己
// 定义的栈来代替系统栈的功能
// 由此可以写出以下代码
void preorderNorecursion(BTNode *bt) {
  if (bt != nullptr) {
    BTNode *Stack[maxSize]; // 定义一个栈
    int top = -1;           // 栈顶指针
    BTNode *p;
    Stack[++top] = bt; // 根节点入栈
    while (top != -1) {
      p = Stack[top--]; // 栈顶元素出栈
      visit(p);         // 访问栈顶元素
      if (p->lchild != nullptr) {
        Stack[++top] = p->lchild; // 栈顶结点的左孩子存在，则左孩子入栈
      }
      if (p->rchild != nullptr) {
        Stack[++top] = p->rchild; // 栈顶结点的右孩子存在，则右孩子入栈
      }
    }
  }
}

// 中序遍历非递归算法
void inorderNorecursion(BTNode *bt) {
  if (bt != nullptr) {
    BTNode *Stack[maxSize];
    BTNode *p;
    int top = -1;
    p = bt;
    // 下面这个循环完成中序遍历
    // 当p不为空或者栈不为空时，循环继续，因为在左子树出栈过程中会出现栈为空的情况
    // 但此时p非空，根据这一点来维持循环的进行
    while (top != -1 || p != nullptr) {
      while (p != nullptr) // 左孩子存在，则左孩子入栈
      {
        Stack[++top] = p;
        p = p->lchild;
      }
      if (top != -1) { // 在栈不空的情况下出栈并输出出栈结点
        p = Stack[top--];
        visit(p);
        p = p->rchild; // 转向右子树
      }
    }
  }
}

// 后序遍历非递归算法
// 后序遍历的非递归算法比较复杂，需要用到两个栈
// 逆后序遍历序列是先序遍历过程中对左右子树遍历顺序交换得到的结果
// 因此需要两个栈，一个栈stack1用来做辅助做逆后序遍历，另一个栈stack2用来存储逆后序遍历的结果
// 然后将stack2中元素全部出栈，所得到的序列即为后序遍历序列
void postorderNorecursion(BTNode *bt) {
  if (bt != nullptr) {
    // 定义两个栈
    BTNode *stack1[maxSize];
    int top1 = -1;
    BTNode *stack2[maxSize];
    int top2 = -1;
    BTNode *p = nullptr;
    stack1[++top1] = bt; // 根节点入栈
    while (top1 != -1) {
      p = stack1[top1--];
      stack2[++top2] = p; // 栈1出栈，栈2入栈, 输出改为入栈stack2
      if (p->lchild != nullptr) {
        stack1[++top1] = p->lchild;
      }
      if (p->rchild != nullptr) {
        stack1[++top1] = p->rchild;
      }
    }
    while (top2 != -1) {
      /* 出栈序列即为后续遍历序列 */
      p = stack2[top2--];
      visit(p); // 访问p的函数
    }
  }
}

// 线索二叉树
// 二叉树非递归遍历算法避免了系统栈的调用，提高了一定的执行效率。
// 线索二叉树可以把用户栈也省掉，把二叉树的遍历过程线性化，进一步提高了效率。
// n个结点的二叉树有n+1个空链域，如果把这些空链域用来存放指向结点在某种遍历次序下的前驱和后继的指针，
// 就可以把二叉树看成一个链表结构，从而可以像遍历链表那样来遍历二叉树，进而提高效率。

// 1）如果ltag=0，则表示lchild为指针，指向结点的左孩子；如果ltag=1，则表示lchild为线索，指向结点的直接前驱
// 2）如果rtag=0，则表示rchild为指针，指向结点的右孩子；如果rtag=1，则表示rchild为线索，指向结点的直接后驱
// 对应的线索二叉树的结点定义如下：
typedef struct TBTNode {
  char data;      // 数据域
  int ltag, rtag; // 线索标记
  struct TBTNode *lchild;
  struct TBTNode *rchild;
} TBTNode;

// 线索二叉树可以分为前序线索二叉树、中序线索二叉树和后序线索二叉树。
// 对一棵树中所有结点的空指针按照某种遍历方法加线索的过程叫做线索化，
// 被线索化了的二叉树成为线索二叉树。

// 中序线索化分析
// 1）既然要对二叉树进行中序线索化，首先要有中序遍历的框架，这里采用二叉树中序递归遍历算法，在遍历过程中连接上合适的线索即可
// 2）线索化的规则是，左线索指针指向当前节点在中序遍历中的前驱节点，右线索指针指向后继结点。因此需要一个指针p指向当前正在访问的节点
// pre是指向p的前驱节点，p的左线索如果存在，则让其指向pre，pre的右线索如果存在，则让其指向p，因为p是pre的后继节点，这样就完成了
// 一对线索的的连接
void InThread(TBTNode *p, TBTNode *&pre) {
  if (p != nullptr) {
    InThread(p->lchild, pre);
    if (p->lchild == nullptr) {
      p->lchild = pre;
      p->ltag = 1;
    }
    if (pre != nullptr && pre->rchild == nullptr) {
      pre->rchild = p;
      pre->rtag = 1;
    }
    pre = p; // pre指向当前的p，作为p将要指向的下一个结点的前驱表示指针
    p = p->rchild; // p指向一个新结点，此时pre和p分别指向的节点形成了一个前驱后继对，为下一次线索的连接做准备
    InThread(p, pre); // 递归，右子树线索化
  }
}
// 通过中序遍历建立中序线索二叉树的主程序如下：
void createInThread(TBTNode *root) {
  TBTNode *pre = nullptr;
  if (root != nullptr) {
    InThread(root, pre);
    pre->rchild = nullptr; // 非空树线索化
    pre->rtag = 1;         // 处理中序最后一个节点
  }
}

// 遍历中序线索二叉树
// 在以p为跟的中序线索二叉树中，中序序列下的第一个节点的算法如下
TBTNode *First(TBTNode *p) {
  while (p->ltag == 0) // ltag不为0时，lchild是左孩子
    p = p->lchild;     // 左下结点（不一定是叶节点）
  return p;
}

// 求在中序线索二叉树中，结点p在中序下的后继节点的算法
TBTNode *Next(TBTNode *p) {
  if (p->rtag == 0) // 如果等于0，则rchild是右孩子
    return First(p->rchild);
  else
    return p->rchild; // 如果不等于0则是后继结点
}

char Visit(TBTNode *p) { return p->data; }
void Inorder(TBTNode *root) {
  for (TBTNode *p = First(root); p != nullptr;
       p = Next(p)) // 找到左孩子的第一个结点，然后依次找后继结点
    Visit(p);
}

// 前序线索化二叉树
void preThread(TBTNode *p, TBTNode *&pre) {
  if (p != nullptr) {
    if (p->lchild == nullptr) {
      p->lchild = pre;
      p->ltag = 1;
    }
    if (pre != nullptr && pre->rchild == nullptr) {
      pre->rchild = p;
      pre->rtag = 1;
    }
    pre = p;
    // 这里在递归入口处有限制条件，左右指针不是线索才继续递归
    if (p->ltag == 0)
      preThread(p->lchild, pre);
    if (p->rtag == 0)
      preThread(p->rchild, pre);
  }
}

// 在前序线索二叉树上执行前序遍历的算法如下：
void preorder(TBTNode *root) {
  if (root != nullptr) {
    TBTNode *p = root;
    while (p != nullptr) {
      while (p->ltag == 0) { // 当p不是线索时，则便访问边左移动
        Visit(p);
        p = p->lchild;
      }
      Visit(p);      // 此时p是线索，访问p
      p = p->rchild; // 此时p左孩子不在，若右指针非空，则不论是否为线索都指向其后继
    }
  }
}

// 后序线索二叉树
void postThread(TBTNode *p, TBTNode *&pre) {
  if (p != nullptr) {
    postThread(p->lchild, pre); // 递归，左子树线索化
    postThread(p->rchild, pre); // 递归，右子树线索化
  }
  if (p->lchild == nullptr) {
    p->lchild = pre;
    p->ltag = 1;
  }
  if (pre->rchild == nullptr) {
    pre->rchild = p;
    pre->rtag = 1;
  }
  pre = p; // 指向下一个节点
}

// 若结点x是二叉树的根，则其后继为空
// 若结点x是其双亲的右孩子，或是其双亲的左孩子且其双亲没有右子树，则其后继结点为其双亲
// 若结点x是其双亲的左孩子，且其双亲有右子树，则其后继为双亲右子树上按后序遍历列出的第一个节点

// 树和森林与二叉树的相互转换
// 1）用二叉链表存储二叉树，结点中一个指针被叫做lchild，指向左孩子，另一个指针域叫做rchild，指向右孩子
// 2）用二叉链表存储树，结点中一个指针指向一个孩子，另一个指针指向了自己的兄弟节点

// 真题仿造
// 已知二叉树的结点按先序遍历的序列存储在一维数组pre[L1, ..., R1]中，
// 按中序遍历的序列存储在一维数组in[L2, ..., R2]中，（其中L1、R1与L2、R2指示了
// 数组中元素（类型为char型）存储的下标范围），假设二叉树中结点数据值互不相同。
// 试写出pre[L1, ..., R1]和in[L2, ..., R2]构造二叉树的算法。
// 1）给出基本设计思想
// 2）根据设计思想，采用C或C++语言描述算法，并在关键之处给出注释

// 1）基本设计思想
// 先序遍历序列中第一个元素a为树的根节点数值。在中序遍历序列中找到a，由a将中序遍历序列分成两个子序列，
// 左边子序列中的元素构成左子树，右边子序列中的元素构成右子树。再对左、右两个子序列用同样的方法处理。
// 直到所处理的子序列只剩下一个元素时二叉树构造结束
// 2）算法描述
BTNode *CreateBT(char pre[], char in[], int L1, int R1, int L2, int R2) {
  /* 本函数返回所构造的二叉树的根节点指针 */
  BTNode *s;
  int i;
  if (L1 > R1)
    return nullptr; // 如果序列中没有元素，则树为空，返回nullptr
  s = (BTNode *)malloc(sizeof(BTNode));
  s->lchild = s->rchild = nullptr;
  for (i = L2; i <= R2; i++) // 查找当前子树根结点在in[]中的位置
    if (in[i] == pre[i])
      break;
  s->data = in[i]; // 将当前子树根结点的值赋给s的数据域
  /* 通过在in[]中找到的分界点i，确定在pre[]和in[]中当前子树的左子树的范围，并参照之前的方法（递归处理）建立左子树，
  将左子树根连接在s的左指针域上*/
  s->lchild = CreateBT(pre, in, L1 + 1, L1 + i - L2, L2, i - 1);
  /* 通过在in[]中找到的分界点i，确定在pre[]和in[]中当前子树的右子树的范围，并参照之前的方法（递归处理）建立右子树，*/
  s->rchild = CreateBT(pre, in, L1 + i - L2 + 1, R1, i + 1, R2);
  return s;
}