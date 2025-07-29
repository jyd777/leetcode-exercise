# LRU缓存

## 题目描述

请你设计并实现一个满足 [LRU (最近最少使用) 缓存](https://baike.baidu.com/item/LRU) 约束的数据结构。

实现 `LRUCache` 类：

- `LRUCache(int capacity)` 以 **正整数** 作为容量 `capacity` 初始化 LRU 缓存
- `int get(int key)` 如果关键字 `key` 存在于缓存中，则返回关键字的值，否则返回 `-1` 。
- `void put(int key, int value)` 如果关键字 `key` 已经存在，则变更其数据值 `value` ；如果不存在，则向缓存中插入该组 `key-value` 。如果插入操作导致关键字数量超过 `capacity` ，则应该 **逐出** 最久未使用的关键字。

函数 `get` 和 `put` 必须以 `O(1)` 的平均时间复杂度运行。

 

**示例：**

```
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4
```

 

**提示：**

- `1 <= capacity <= 3000`
- `0 <= key <= 10000`
- `0 <= value <= 105`
- 最多调用 `2 * 105` 次 `get` 和 `put`



## 解决方案

### 核心思路

LRU缓存需要满足以下要求：
1. **快速查找**：O(1)时间找到key对应的value
2. **快速插入/删除**：O(1)时间插入新元素或删除最久未使用的元素
3. **维护访问顺序**：需要知道哪个元素最久未使用

**数据结构选择：**
- **哈希表**：实现O(1)的查找
- **双向链表**：实现O(1)的插入/删除，维护访问顺序

### 实现方案

```cpp
class LRUCache {
private:
    // 双向链表
    struct Node{
        int key;
        int val;
        Node *prev;
        Node *next;
        Node(int k, int v): key(k),val(v), prev(NULL), next(NULL){}
    };
    int capacity;
    unordered_map<int, Node*> cache;
    // 链表头是最近使用，所以每次逐出时是把尾部结点移除
    Node *head;
    Node *tail;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        head = new Node(0,0);
        tail = new Node(0,0);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        // 用哈希表去查找
        // 没找到
        if(cache.find(key) == cache.end())
            return -1;
        // 找到了
        // 把这个结点移到链表头部（最近使用）
        move2head(cache[key]);
        return cache[key]->val;
    }
    
    void put(int key, int value) {
        // 首先判断是否已经存在
        if(cache.find(key) != cache.end()){
            // 更新value
            cache[key]->val = value;
            // 移动到头部
            move2head(cache[key]);
        }
        else{
            // 先创建新节点
            Node *newNode = new Node(key, value);
            cache[key] = newNode;
            add2head(newNode);
            // 判断是否超出容量
            if(cache.size() > capacity){
                // 把尾部结点删除
                Node *oldNode = tail->prev;
                cache.erase(oldNode->key);
                oldNode->prev->next = tail;
                tail->prev = oldNode->prev;
                delete oldNode;
            }
        }
    }

private:
    void move2head(Node* node){
        // 把该结点从当前位置删除
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
        // 把该结点移动到头部
        add2head(node);
    }
    void add2head(Node*node){
        node->prev = head;
        node->next = head->next;
        node->next->prev = node;
        head->next = node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

### 算法分析

**时间复杂度：**
- `get(key)`：O(1)
- `put(key, value)`：O(1)

**空间复杂度：** O(capacity)

**关键操作：**
1. **查找**：哈希表O(1)查找
2. **插入**：双向链表头部插入O(1)
3. **删除**：双向链表尾部删除O(1)
4. **移动**：删除+插入，O(1)

### 双向链表的作用

1. **维护访问顺序**：最近使用的在头部，最久未使用的在尾部
2. **快速移动**：O(1)时间将节点从任意位置移到头部
3. **快速删除**：O(1)时间删除尾部节点

### 哈希表的作用

1. **快速查找**：O(1)时间找到key对应的节点
2. **判断存在性**：O(1)时间判断key是否在缓存中

## 测试用例

```cpp
int main() {
    LRUCache cache(2);
    
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;      // 返回 1
    cache.put(3, 3);                   // 该操作会使得关键字 2 作废
    cout << cache.get(2) << endl;      // 返回 -1 (未找到)
    cache.put(4, 4);                   // 该操作会使得关键字 1 作废
    cout << cache.get(1) << endl;      // 返回 -1 (未找到)
    cout << cache.get(3) << endl;      // 返回 3
    cout << cache.get(4) << endl;      // 返回 4
    
    return 0;
}
```

## 总结

LRU缓存是一个经典的数据结构设计问题，核心是结合哈希表和双向链表的优势：

- **哈希表**：提供O(1)的查找能力
- **双向链表**：提供O(1)的插入/删除能力，维护访问顺序

这种设计模式在很多场景中都有应用，比如：
- 数据库查询缓存
- 浏览器页面缓存
- 操作系统页面置换算法 