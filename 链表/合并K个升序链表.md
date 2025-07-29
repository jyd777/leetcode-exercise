# 合并K个升序链表

## 题目描述

给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

 

**示例 1：**

```
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
```

**示例 2：**

```
输入：lists = []
输出：[]
```

**示例 3：**

```
输入：lists = [[]]
输出：[]
```

 

**提示：**

- `k == lists.length`

- `0 <= k <= 10^4`

- `0 <= lists[i].length <= 500`

- `-10^4 <= lists[i][j] <= 10^4`

- `lists[i]` 按 **升序** 排列

- `lists[i].length` 的总和不超过 `10^4`

  

## 解决方案

### 方法一：分治归并（推荐）

这是最优的解决方案，时间复杂度O(N log k)，其中N是所有链表的总节点数，k是链表个数。

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty())
            return NULL;
        // 分治归并
        return merge(lists, 0, lists.size()-1);
    }
private:
    ListNode* merge(vector<ListNode*>& lists, int left, int right){
        if(left == right)
            return lists[left];
        if(left > right)
            return NULL;
        int mid = (left+right)/2;
        ListNode *l = merge(lists, left, mid);
        ListNode *r = merge(lists, mid+1, right);
        return merge_two_list(l,r);
    }
    ListNode *merge_two_list(ListNode *l1, ListNode *l2){
        ListNode *prevhead = new ListNode(-1);
        ListNode *p = prevhead;
        while(l1 && l2){
            if(l1->val < l2->val){
                p->next = l1;
                l1 = l1->next;
            }
            else{
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        p->next = l1?l1:l2;
        return prevhead->next;
    }
};
```

### 方法二：优先队列（小顶堆）

使用优先队列来维护所有链表头节点的最小值。

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty())
            return NULL;
        // 优先队列（小顶堆）
        // 由于默认是大顶堆，所以要自定义比较函数
        auto cmp = [](ListNode* a, ListNode* b){
            return a->val > b->val;
        };
        /*
            ListNode*：队列中存储的元素类型是 ListNode 的指针。
            vector<ListNode*>：底层容器使用 vector 来存储这些指针。
            decltype(cmp)：指定比较器的类型（cmp 的编译时类型）
        */
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        // 初始化优先队列，将每一个list的头节点加入
        for (ListNode* list:lists)
            if(list)
                pq.push(list);
        // 每次取出队头
        ListNode *prevhead = new ListNode(-1);
        ListNode *cur = prevhead;
        while(!pq.empty()){
            ListNode* p = pq.top();
            pq.pop();
            cur->next = p;
            cur = cur->next;
            // 对于取出的这个结点，如果它所在的链表还有下一个结点，则补货
            if(p->next)
                pq.push(p->next);
        }
        return prevhead->next;
    }

};
```

### 方法三：顺序合并

逐个合并链表，简单但效率较低。

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        
        ListNode* result = lists[0];
        for (int i = 1; i < lists.size(); i++) {
            result = mergeTwoLists(result, lists[i]);
        }
        
        return result;
    }
    
private:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;
        
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        
        curr->next = l1 ? l1 : l2;
        return dummy->next;
    }
};
```

### 方法四：哈希表思路（优化版）

虽然可以用哈希表，但这种方法比较复杂且效率不高。

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 收集所有值
        vector<int> values;
        
        for (ListNode* list : lists) {
            ListNode* curr = list;
            while (curr) {
                values.push_back(curr->val);
                curr = curr->next;
            }
        }
        
        // 排序
        sort(values.begin(), values.end());
        
        // 创建新链表
        if (values.empty()) return nullptr;
        
        ListNode* head = new ListNode(values[0]);
        ListNode* curr = head;
        
        for (int i = 1; i < values.size(); i++) {
            curr->next = new ListNode(values[i]);
            curr = curr->next;
        }
        
        return head;
    }
};
```

## 复杂度分析

| 方法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 分治归并 | O(N log k) | O(log k) | 最优解，递归栈空间 |
| 优先队列 | O(N log k) | O(k) | 堆空间，适合k较小 |
| 顺序合并 | O(Nk) | O(1) | 简单但效率低 |
| 哈希表+排序 | O(N log N) | O(N) | 简单但空间复杂度高 |
