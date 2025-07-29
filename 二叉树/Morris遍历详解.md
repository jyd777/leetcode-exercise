# Morris遍历详解

## 什么是Morris遍历？

Morris遍历是一种不使用栈也不使用递归的二叉树遍历方法，它的空间复杂度为O(1)。这种方法是由J. H. Morris在1979年提出的，因此被称为Morris遍历。

## 核心思想

Morris遍历的核心思想是**利用树中大量空闲的指针**，将二叉树转换为线索二叉树，从而避免使用栈或递归。

### 关键概念：前驱节点

对于中序遍历，每个节点的前驱节点是其左子树的最右节点。

例如，对于节点A：
```
    A
   / \
  B   C
 / \
D   E
   \
    F
```

节点A的前驱节点是F（A的左子树B的最右节点）。

## 算法步骤详解

### 中序遍历的Morris算法

```cpp
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;
    
    while (curr != nullptr) {
        if (curr->left == nullptr) {
            // 情况1：没有左子树
            result.push_back(curr->val);
            curr = curr->right;
        } else {
            // 情况2：有左子树
            // 找到当前节点的前驱节点
            TreeNode* predecessor = curr->left;
            while (predecessor->right != nullptr && predecessor->right != curr) {
                predecessor = predecessor->right;
            }
            
            if (predecessor->right == nullptr) {
                // 情况2a：第一次访问，建立线索
                predecessor->right = curr;
                curr = curr->left;
            } else {
                // 情况2b：第二次访问，恢复结构并访问当前节点
                predecessor->right = nullptr;
                result.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    
    return result;
}
```

## 详细执行过程

让我们用一个具体的例子来说明：

```
     1
   /   \
  2     3
 / \
4   5
```

### 执行步骤：

**初始状态：** curr = 1

**第1步：** curr = 1, 有左子树
- 找到前驱节点：predecessor = 5
- predecessor->right = nullptr，所以建立线索：5->right = 1
- curr = curr->left = 2

**第2步：** curr = 2, 有左子树
- 找到前驱节点：predecessor = 4
- predecessor->right = nullptr，所以建立线索：4->right = 2
- curr = curr->left = 4

**第3步：** curr = 4, 没有左子树
- 访问节点4：result = [4]
- curr = curr->right = 2（通过线索）

**第4步：** curr = 2, 有左子树
- 找到前驱节点：predecessor = 4
- predecessor->right = 2（已建立线索），所以恢复结构：4->right = nullptr
- 访问节点2：result = [4, 2]
- curr = curr->right = 5

**第5步：** curr = 5, 没有左子树
- 访问节点5：result = [4, 2, 5]
- curr = curr->right = 1（通过线索）

**第6步：** curr = 1, 有左子树
- 找到前驱节点：predecessor = 5
- predecessor->right = 1（已建立线索），所以恢复结构：5->right = nullptr
- 访问节点1：result = [4, 2, 5, 1]
- curr = curr->right = 3

**第7步：** curr = 3, 没有左子树
- 访问节点3：result = [4, 2, 5, 1, 3]
- curr = curr->right = nullptr

**结束：** curr = nullptr，遍历完成

## 为什么这样设计？

### 1. 线索的作用

当我们第一次访问一个节点时，我们建立从它的前驱节点指向它的线索。==这样，当我们遍历完左子树后，可以通过这个线索回到当前节点。==

### 2. 区分第一次和第二次访问

- **第一次访问**：predecessor->right == nullptr
  - 建立线索：predecessor->right = curr
  - 继续遍历左子树：curr = curr->left

- **第二次访问**：predecessor->right == curr
  - 恢复结构：predecessor->right = nullptr
  - 访问当前节点并转向右子树：curr = curr->right

### 3. 空间复杂度O(1)

我们只使用了几个指针变量（curr, predecessor），没有使用额外的数据结构，所以空间复杂度是O(1)。

## 时间复杂度分析

虽然看起来每个节点可能被访问多次，但实际上：

- 每个节点最多被访问2次（一次建立线索，一次恢复结构）
- 寻找前驱节点的过程，每个边最多被遍历2次
- 总的时间复杂度仍然是O(n)

## 优缺点

### 优点：
1. **空间复杂度O(1)**：不使用栈或递归
2. **原地操作**：不修改树的结构（临时修改会恢复）

### 缺点：
1. **实现复杂**：容易出错
2. **难以理解**：逻辑相对复杂
3. **不适合生产环境**：代码可读性差

## 其他遍历的Morris算法

### 前序遍历
```cpp
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;
    
    while (curr != nullptr) {
        if (curr->left == nullptr) {
            result.push_back(curr->val);
            curr = curr->right;
        } else {
            TreeNode* predecessor = curr->left;
            while (predecessor->right != nullptr && predecessor->right != curr) {
                predecessor = predecessor->right;
            }
            
            if (predecessor->right == nullptr) {
                result.push_back(curr->val);  // 第一次访问就输出
                predecessor->right = curr;
                curr = curr->left;
            } else {
                predecessor->right = nullptr;
                curr = curr->right;
            }
        }
    }
    
    return result;
}
```

### 后序遍历
后序遍历的Morris算法更复杂，需要反转部分链表，这里不详细展开。

## 总结

Morris遍历是一种巧妙的算法，它通过临时修改树的结构来实现O(1)空间复杂度的遍历。虽然实现复杂，但理解其思想对于深入理解二叉树遍历和算法设计很有帮助。

在实际应用中，除非空间极度受限，否则建议使用递归或迭代方法，因为它们更简单、更可靠。 