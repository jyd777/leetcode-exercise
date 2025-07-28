#  K个一组翻转链表

给你链表的头节点 `head` ，每 `k` 个节点一组进行翻转，请你返回修改后的链表。

`k` 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 `k` 的整数倍，那么请将最后剩余的节点保持原有顺序。

你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex1.jpg)

```
输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex2.jpg)

```
输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]
```

 

**提示：**

- 链表中的节点数目为 `n`
- `1 <= k <= n <= 5000`
- `0 <= Node.val <= 1000`

 

**进阶：**你可以设计一个只用 `O(1)` 额外内存空间的算法解决此问题吗？



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
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 仍旧只需要四个额外指针
        // p2、p3指向要翻转的一头一尾
        // p1->next = p2, p3->next =p4
        // 先翻转p2和p3中间的链表，再处理头尾
        // p2和p3则采用先走K步的方式来圈出范围
        if(!head||!head->next)
            return head;
        ListNode *prevhead = new ListNode(-1);
        prevhead->next = head;
        ListNode *p1=prevhead, *p2=head, *p3=head, *p4;
        while(p2){
            // 找到p3位置
            p3 = p2;
            for(int i=0;i<k-1 && p3;i++)
                p3 = p3->next;
            if(!p3)
                break;
            p4 = p3->next;
            // 首先翻转p2和p3中间的链表
            reverseList(p2,k);
            // 处理头尾
            p1->next = p3;
            p2->next = p4;
            // 更新p1和p2
            p1 = p2;
            p2 = p4;
        }
        return prevhead->next; 
    }
private:
    void reverseList(ListNode* head, int k){
        if (!head||!head->next)
            return;
        ListNode *prev=NULL,*cur=head;
        while(k--){
            ListNode *tmp = cur;
            cur = cur->next;
            tmp->next = prev;
            prev = tmp;
        }
    }
};
```

