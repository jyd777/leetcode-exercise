# 删除链表的倒数第N个结点

给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)

```
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
```

**示例 2：**

```
输入：head = [1], n = 1
输出：[]
```

**示例 3：**

```
输入：head = [1,2], n = 1
输出：[1]
```

 

**提示：**

- 链表中结点的数目为 `sz`
- `1 <= sz <= 30`
- `0 <= Node.val <= 100`
- `1 <= n <= sz`

 

**进阶：**你能尝试使用一趟扫描实现吗？



```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 设置两个指针，第一个指针先走n个结点，第二个指针再出发
        // 当第一个指针走到末尾时，第二个指针所指位置就是要删去的结点
        if (!head || !head->next)
            return NULL;
        ListNode *p1 =head, *p2 =head, *prev = NULL;
        for (int i=0;i<n;i++)
            p1 =p1->next;
        while(p1 && p2){
            p1 = p1->next;
            prev = p2;
            p2 = p2->next;
        }
        // 特殊情况：n=sz
        if (p2 == head)
            return p2->next;
        // 其余情况
        prev->next = p2->next;
        return head;  
    }
};
```

