# 二叉搜索树中第K小的元素

给定一个二叉搜索树的根节点 `root` ，和一个整数 `k` ，请你设计一个算法查找其中第 `k` 小的元素（从 1 开始计数）。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/01/28/kthtree1.jpg)

```
输入：root = [3,1,4,null,2], k = 1
输出：1
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2021/01/28/kthtree2.jpg)

```
输入：root = [5,3,6,2,4,null,null,1], k = 3
输出：3
```

 

 

**提示：**

- 树中的节点数为 `n` 。
- `1 <= k <= n <= 104`
- `0 <= Node.val <= 104`

 

**进阶：**如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 `k` 小的值，你将如何优化算法？



**解答：**

依旧利用BST的中序遍历得到的是升序序列的特点

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> val;
        inorderTrav(root, val);
        return val[k-1];
    }
private:
    void inorderTrav(TreeNode* root,vector<int>& ret){
        if(!root)
            return;
        // 左子树
        if(root->left)
            inorderTrav(root->left, ret);
        // 当前结点
        ret.push_back(root->val);
        // 右子树
        if(root->right)
            inorderTrav(root->right, ret);

    }
};
```



**进阶问题解决方案**

**思路和算法（leetcode官方题解）：**

在方法一中，我们之所以需要中序遍历前 k 个元素，是因为我们不知道子树的结点数量，不得不通过遍历子树的方式来获知。

因此，我们可以记录下以每个结点为根结点的子树的结点数，并在查找第 k 小的值时，使用如下方法搜索：

1. 令 `node` 等于根结点，开始搜索。
2. 对当前结点 `node` 进行如下操作：
   - 如果 `node` 的左子树的结点数 `left` 小于 `k−1`，则第 k 小的元素一定在 `node` 的右子树中，令 `node` 等于其的右子结点，`k` 等于 `k−left−1`，并继续搜索；
   - 如果 `node` 的左子树的结点数 `left` 等于 `k−1`，则第 k 小的元素即为 `node`，结束搜索并返回 `node` 即可；
   - 如果 `node` 的左子树的结点数 `left` 大于 `k−1`，则第 k 小的元素一定在 `node` 的左子树中，令 `node` 等于其左子结点，并继续搜索。

在实现中，我们既可以将以每个结点为根结点的子树的结点数存储在结点中，也可以将其记录在哈希表中。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        // 计算每个结点的子树大小
        unordered_map<TreeNode*, int> node_count;
        cal_subtree_size(root, node_count);
        // 查找第k小的元素
        return find_kth_smallest(root,k, node_count);
    }
private:
    int cal_subtree_size(TreeNode* node, unordered_map<TreeNode*, int>& node_count){
        if(!node)
            return 0;
        // 递归计算左子树和右子树的大小
        int left_size = cal_subtree_size(node->left,node_count);
        int right_size = cal_subtree_size(node->right, node_count);
        node_count[node] = left_size+right_size+1;
        return node_count[node];
    }

    int find_kth_smallest(TreeNode* node, int k, unordered_map<TreeNode*, int>& node_count){
        if(!node)
            return -1;
        // 左子树结点个数
        int left_count = node->left? node_count[node->left]: 0;
        
        if(k <= left_count)
            // 在左子树中继续找
            return find_kth_smallest(node->left, k ,node_count);
        else if (k == left_count+1)
            // 就是当前结点
            return node->val;
        else
            // 在右子树中继续找
            return find_kth_smallest(node->right, k-left_count-1, node_count);
    }
};
```



