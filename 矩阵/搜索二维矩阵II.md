# 搜索二维矩阵II

编写一个高效的算法来搜索 `*m* x *n*` 矩阵 `matrix` 中的一个目标值 `target` 。该矩阵具有以下特性：

- 每行的元素从左到右升序排列。
- 每列的元素从上到下升序排列。

 

**示例 1：**

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/11/25/searchgrid2.jpg)

```
输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
输出：true
```

**示例 2：**

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/11/25/searchgrid.jpg)

```
输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
输出：false
```

 

**提示：**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= n, m <= 300`
- `-109 <= matrix[i][j] <= 109`
- 每行的所有元素从左到右升序排列
- 每列的所有元素从上到下升序排列
- `-109 <= target <= 109`



**核心思想**

从右上角开始搜索的关键在于**利用矩阵的单调性**：
- 每行从左到右递增
- 每列从上到下递增

**算法步骤**

**1. 起始位置**

从矩阵的右上角 `matrix[0][n-1]` 开始搜索

**2. 搜索策略**

在当前位置 `matrix[row][col]` 时：

- **如果 `matrix[row][col] == target`**：找到目标，返回 `true`
- **如果 `matrix[row][col] > target`**：目标值更小，向左移动（`col--`）
  - matrix\[row][col] > target 时：
    - 当前列的从row开始的元素都 > target（因为列递增）
    - **需要注意的是对于matrix\[<row][col]的元素并不在我们的搜索范围内（从当前位置到达不了这些元素位置，换而言之，这些元素已经在前几轮移动行的时候被排除了）**
    - 所以可以排除整个当前列，向左移动

- **如果 `matrix[row][col] < target`**：目标值更大，向下移动（`row++`）
  - matrix\[row][col] < target 时：
    - 当前行的从col开始的元素都 < target（因为行递增）
    - 所以可以排除整个当前行，向下移动


**3. 终止条件**

当 `row >= m` 或 `col < 0` 时停止搜索，返回 `false`

## 代码实现

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        if (n == 0) return false;
        
        // 从右上角开始搜索
        int row = 0, col = n - 1;
        
        while (row < m && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] > target) {
                // 当前元素太大，向左移动
                col--;
            } else {
                // 当前元素太小，向下移动
                row++;
            }
        }
        
        return false;
    }
};
```

**算法分析**

**时间复杂度**

- **最坏情况**：O(m + n)
- 每次移动都会排除一行或一列
- 最多移动 m + n 次

**空间复杂度**

- O(1)，只使用常数额外空间

