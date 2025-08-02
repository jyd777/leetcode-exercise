# N皇后

按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

**n 皇后问题** 研究的是如何将 `n` 个皇后放置在 `n×n` 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 `n` ，返回所有不同的 **n 皇后问题** 的解决方案。

每一种解法包含一个不同的 **n 皇后问题** 的棋子放置方案，该方案中 `'Q'` 和 `'.'` 分别代表了皇后和空位。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/11/13/queens.jpg)

```
输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。
```

**示例 2：**

```
输入：n = 1
输出：[["Q"]]
```

 

**提示：**

- `1 <= n <= 9`

## 解决方案

```cpp
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        ret = vector<string>(n, string(n, '.'));
        col = vector<bool>(n, false);
        diag1 = vector<bool> (2 * n - 1, false);
        diag2 = vector<bool> (2 * n - 1, false);
        backtrack(0, n);
        return rets;
    }
private:
    vector<vector<string>> rets;
    vector<string> ret;
    vector<bool> col; // 列是否被占用
    vector<bool> diag1; // 主对角线是否被占用
    vector<bool> diag2;  // 副对角线是否被占用
    void backtrack(int row, int n){
        if (row == n){
            rets.push_back(ret);
            return;
        }
        // 对于该行，尝试每一列
        for(int c=0;c<n;c++){
            // 主对角线上的皇后满足 row + col = 常数
            // 副对角线上的皇后满足 row - col = 常数
            if(!col[c] && !diag1[row+c] && !diag2[row-c+n-1]){
                // 放置皇后
                ret[row][c] = 'Q';
                // 更新占用信息
                col[c] = true;
                diag1[row+c] = true;
                diag2[row-c+n-1] = true;
                // 递归
                backtrack(row+1, n);
                // 还原
                ret[row][c] = '.';
                col[c] = false;
                diag1[row+c] = false;
                diag2[row-c+n-1] = false;
            }
        }
    }
};
```

## 算法思路

1. **状态表示**：
   - `board`：当前棋盘状态，用二维字符串表示
   - `col`：记录每列是否被皇后占用
   - `diag1`：记录主对角线是否被占用（row + col）
   - `diag2`：记录副对角线是否被占用（row - col + n - 1）（对于这里需要+n-1是为了防止row-c为负值）

2. **回溯过程**：
   - 逐行放置皇后，每行只能放一个皇后
   - 对于每一行，尝试在每一列放置皇后
   - 检查列、主对角线、副对角线是否被占用
   - 如果安全，放置皇后并递归处理下一行
   - 回溯时移除皇后

3. **冲突检测**：
   - **列冲突**：同一列不能有多个皇后
   - **主对角线冲突**：主对角线上的皇后满足 row + col = 常数
   - **副对角线冲突**：副对角线上的皇后满足 row - col = 常数

4. **终止条件**：当 row == n 时，说明已经成功放置了n个皇后

## 时间复杂度

- 时间复杂度：O(n!)，其中n是棋盘大小
- 空间复杂度：O(n)，递归调用栈的深度

## 优化技巧

1. **对称性剪枝**：利用棋盘的对称性可以减少一半的搜索空间
2. **位运算优化**：可以使用位运算来加速冲突检测
3. **启发式搜索**：优先选择约束最多的位置进行搜索