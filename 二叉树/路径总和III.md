# 路径总和 III

给定一个二叉树的根节点 `root` ，和一个整数 `targetSum` ，求该二叉树里节点值之和等于 `targetSum` 的 **路径** 的数目。

**路径** 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/04/09/pathsum3-1-tree.jpg)

```
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。
```

**示例 2：**

```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3
```

## 解题思路

### 核心思想
1. **前缀和技巧：** 使用前缀和来快速计算任意路径的和
2. **回溯思想：** 在遍历过程中维护当前路径的前缀和
3. **哈希表记录：** 用哈希表记录每个前缀和出现的次数

### 算法步骤
1. 使用DFS遍历二叉树
2. 维护当前路径的前缀和
3. 对于每个节点，检查是否存在前缀和差等于targetSum
4. 更新哈希表，递归处理子节点，回溯时恢复状态

## 代码实现

### 方法一：前缀和 + DFS（推荐）

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
private:
    unordered_map<long long, int> pre_sum_cnt;// 前缀和出现次数
public:
    int ret;
    int pathSum(TreeNode* root, int targetSum) {
        pre_sum_cnt[0] = 1;
        dfs(root, 0, targetSum);
        return ret;
    }
private:
    void dfs(TreeNode* root, long long cur_sum, int target){
        if(!root)
            return;
        // 计算当前路径前缀和
        cur_sum += root->val;
        // 检查是否有前缀和等于target
        if(pre_sum_cnt.find(cur_sum - target)!= pre_sum_cnt.end())
            ret+= pre_sum_cnt[cur_sum - target];
        // 更新哈希表（注意要找完再更新，因为否则当target = 0时就会计算个数出错）
        pre_sum_cnt[cur_sum]++;
        // 左子树
        dfs(root->left, cur_sum, target);
        // 右子树
        dfs(root->right, cur_sum, target);
        // 回溯，恢复哈希表
        pre_sum_cnt[cur_sum]--;
    }
};
```

### 方法二：双重DFS（暴力解法）

```cpp
class Solution {
private:
    // 从当前节点开始，计算所有以该节点为起点的路径和
    void pathSumFromRoot(TreeNode* root, long long current_sum) {
        if (!root) return;
        
        current_sum += root->val;
        
        if (current_sum == target) {
            result++;
        }
        
        pathSumFromRoot(root->left, current_sum);
        pathSumFromRoot(root->right, current_sum);
    }
    
    // 对每个节点都尝试作为路径起点
    void dfs(TreeNode* root) {
        if (!root) return;
        
        pathSumFromRoot(root, 0);
        
        dfs(root->left);
        dfs(root->right);
    }
    
public:
    int result = 0;
    int target;
    
    int pathSum(TreeNode* root, int targetSum) {
        target = targetSum;
        dfs(root);
        return result;
    }
};
```

### 方法三：优化版（你的思路改进）

```cpp
class Solution {
private:
    // 记录从根到当前节点的路径和
    vector<long long> path_sums;
    int target;
    
    void dfs(TreeNode* root, long long current_sum) {
        if (!root) return;
        
        current_sum += root->val;
        path_sums.push_back(current_sum);
        
        // 检查所有可能的路径和
        for (int i = 0; i < path_sums.size() - 1; i++) {
            if (current_sum - path_sums[i] == target) {
                result++;
            }
        }
        
        // 检查从根到当前节点的路径
        if (current_sum == target) {
            result++;
        }
        
        dfs(root->left, current_sum);
        dfs(root->right, current_sum);
        
        // 回溯
        path_sums.pop_back();
    }
    
public:
    int result = 0;
    
    int pathSum(TreeNode* root, int targetSum) {
        target = targetSum;
        dfs(root, 0);
        return result;
    }
};
```

## 复杂度分析

### 方法一：前缀和 + DFS
- **时间复杂度：** O(n)，其中 n 是树中节点的个数
- **空间复杂度：** O(n)，哈希表空间 + 递归栈深度

### 方法二：双重DFS
- **时间复杂度：** O(n²)，最坏情况下每个节点都要作为起点
- **空间复杂度：** O(n)，递归栈深度

### 方法三：优化版
- **时间复杂度：** O(n²)，需要检查所有路径组合
- **空间复杂度：** O(n)，路径数组 + 递归栈深度

