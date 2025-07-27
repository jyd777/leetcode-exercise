# 环形链表II

给定一个链表的头节点  `head` ，返回链表开始入环的第一个节点。 *如果链表无环，则返回 `null`。*

如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 `pos` 来表示链表尾连接到链表中的位置（**索引从 0 开始**）。如果 `pos` 是 `-1`，则在该链表中没有环。**注意：`pos` 不作为参数进行传递**，仅仅是为了标识链表的实际情况。

**不允许修改** 链表。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png)

```
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。
```

**示例 2：**

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test2.png)

```
输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。
```

**示例 3：**

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test3.png)

```
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。
```

 

**提示：**

- 链表中节点的数目范围在范围 `[0, 104]` 内
- `-105 <= Node.val <= 105`
- `pos` 的值为 `-1` 或者链表中的一个有效索引

 

**进阶：**你是否可以使用 `O(1)` 空间解决此题？



## 核心思想

### 方法一：快慢指针法（最优解）

**核心思路**：
1. 使用快慢指针检测是否有环
2. 如果有环，找到相遇点后，让一个指针从头开始，另一个从相遇点开始，以相同速度前进
3. 两个指针再次相遇的点就是环的入口

**数学原理**：
- 设链表头到环入口的距离为 `a`
- 环入口到相遇点的距离为 `b`
- 相遇点到环入口的距离为 `c`
- 环的长度为 `L = b + c`

**快慢指针相遇时**：
- 慢指针走了：`a + b`
- 快指针走了：`a + b + n*L`（n为快指针在环中走的圈数）
- 由于快指针速度是慢指针的2倍：`2(a + b) = a + b + n*L`
- 化简得：`a + b = n*L`
- 进一步：`a = n*L - b = (n-1)*L + c`

**关键发现**：
- 从相遇点走 `c` 步到达环入口
- 从链表头走 `a` 步也到达环入口
- 由于 `a = (n-1)*L + c`，所以从相遇点走 `c` 步和从链表头走 `a` 步（此时n=1）会到达同一个点，而这个点也是环入口点

## 代码实现

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return nullptr;
        
        // 第一步：使用快慢指针检测是否有环
        ListNode *slow = head, *fast = head;
        bool hasCycle = false;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }
        
        // 如果没有环，返回null
        if (!hasCycle) return nullptr;
        
        // 第二步：找到环的入口
        // 让一个指针从头开始，另一个从相遇点开始，以相同速度前进
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow;  // 返回环的入口节点
    }
};
```

## 算法分析

**时间复杂度**：O(n)
- 第一次遍历：检测是否有环
- 第二次遍历：找到环入口
- 总共最多遍历2次链表

**空间复杂度**：O(1)
- 只使用了两个指针变量

## 算法步骤详解

### 步骤1：检测环
```
链表：1 -> 2 -> 3 -> 4 -> 5 -> 3 (环)
pos = 2 (环入口是节点3)

快慢指针移动过程：
初始：slow=1, fast=1
第1步：slow=2, fast=3
第2步：slow=3, fast=5
第3步：slow=4, fast=3
第4步：slow=5, fast=5 (相遇)
```

### 步骤2：找到环入口
```
相遇点：节点5
从链表头开始：slow=1
从相遇点开始：fast=5

移动过程：
第1步：slow=2, fast=3
第2步：slow=3, fast=4
第3步：slow=4, fast=5
第4步：slow=5, fast=3
第5步：slow=3, fast=3 (再次相遇，这就是环入口)
```

## 其他解法

### 方法二：使用哈希表
```cpp
ListNode *detectCycle(ListNode *head) {
    unordered_set<ListNode*> visited;
    ListNode *p = head;
    
    while (p) {
        if (visited.count(p)) {
            return p;  // 找到环入口
        }
        visited.insert(p);
        p = p->next;
    }
    
    return nullptr;  // 无环
}
```

**缺点**：空间复杂度为O(n)，不满足进阶要求

