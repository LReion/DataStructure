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