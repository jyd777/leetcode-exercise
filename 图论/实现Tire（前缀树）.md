# 实现Tire（前缀树）

**[Trie](https://baike.baidu.com/item/字典树/9825209?fr=aladdin)**（发音类似 "try"）或者说 **前缀树** 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

请你实现 Trie 类：

- `Trie()` 初始化前缀树对象。
- `void insert(String word)` 向前缀树中插入字符串 `word` 。
- `boolean search(String word)` 如果字符串 `word` 在前缀树中，返回 `true`（即，在检索之前已经插入）；否则，返回 `false` 。
- `boolean startsWith(String prefix)` 如果之前已经插入的字符串 `word` 的前缀之一为 `prefix` ，返回 `true` ；否则，返回 `false` 。

 

**示例：**

```
输入
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]

解释
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True
```

 

**提示：**

- `1 <= word.length, prefix.length <= 2000`
- `word` 和 `prefix` 仅由小写英文字母组成
- `insert`、`search` 和 `startsWith` 调用次数 **总计** 不超过 $3 * 10^4$ 次

## 解题思路

### 核心思想：图结构 + 节点标记
你的想法很正确！Trie可以看作是一个特殊的图结构：
- 每个节点代表一个字符
- 边代表字符之间的连接关系
- 需要标记哪些节点是单词的结束位置

### 数据结构设计
1. **节点结构**：每个节点包含26个子节点（对应26个小写字母）
2. **结束标记**：`isEnd` 标记当前节点是否是某个单词的结束
3. **图的思想**：`children[char]` 存储从当前字符出发能到达的下一个字符

## 代码实现

### 方法一：数组实现

```cpp
class Trie {
private:
    struct TrieNode {
        vector<TrieNode*> children;
        bool isEnd;
        
        TrieNode() : children(26, nullptr), isEnd(false) {}
    };
    
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEnd = true; // 标记单词结束
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false; // 路径不存在
            }
            node = node->children[index];
        }
        return node->isEnd; // 必须是单词结束位置
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false; // 路径不存在
            }
            node = node->children[index];
        }
        return true; // 前缀存在即可
    }
};
```

### 方法二：哈希表实现

```cpp
class Trie {
private:
    struct TrieNode{
        // 每个节点存储其后续字符
        unordered_map<char, TrieNode*> next_char;
        bool is_end;
        TrieNode():is_end(false){}
    };
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* cur = root;
        // 遍历单词每个字符，构建图结构
        for(char c:word){
            // 如果当前字符不在图中，则创建新节点
            if(cur->next_char.find(c) == cur->next_char.end())
                cur->next_char[c] = new TrieNode();
            // 更新到下一个结点
            cur = cur->next_char[c];
        }
        // 单词结束
        cur->is_end = true;
    }
    
    bool search(string word) {
        TrieNode* cur = root;
        // 在图结构中找路径
        for(char c: word){
            if(cur->next_char.find(c) == cur->next_char.end())
                return false;
            cur = cur->next_char[c];
        }
        // 是否到该路径的末端？
        return cur->is_end;
    }
    
    bool startsWith(string prefix) {
        TrieNode *cur = root;
        // 在图结构中找前缀路径
        for(char c:prefix){
            if(cur->next_char.find(c) == cur->next_char.end())
                return false;
            cur = cur->next_char[c];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```

## 复杂度分析

### 时间复杂度
- **插入**：O(L)，其中L是单词长度
- **搜索**：O(L)，其中L是单词长度
- **前缀搜索**：O(L)，其中L是前缀长度

### 空间复杂度
- **数组实现**：O(26^L)，最坏情况下每个节点都有26个子节点
- **哈希表实现**：O(L)，只存储实际存在的字符

## 关键概念解释

### 1. 图的思想
- **节点**：每个字符位置
- **边**：字符之间的连接关系
- **路径**：从根到某个节点的路径代表一个字符串

### 2. 结束标记的重要性
- `isEnd` 标记区分完整单词和前缀
- 例如："app" 是 "apple" 的前缀，但不是完整单词

### 3. 三种操作的差异
- **insert**：构建路径，在终点标记结束
- **search**：查找完整路径，必须到达结束标记
- **startsWith**：查找前缀路径，不需要结束标记
