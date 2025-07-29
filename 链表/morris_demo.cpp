#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class MorrisDemo {
public:
    // 带详细输出的Morris中序遍历
    vector<int> inorderTraversalWithDetails(TreeNode* root) {
        vector<int> result;
        TreeNode* curr = root;
        int step = 1;
        
        cout << "=== Morris中序遍历详细过程 ===" << endl;
        
        while (curr != nullptr) {
            cout << "\n步骤 " << step++ << ": curr = " << curr->val << endl;
            
            if (curr->left == nullptr) {
                // 情况1：没有左子树
                cout << "  情况1：没有左子树" << endl;
                cout << "  访问节点 " << curr->val << endl;
                result.push_back(curr->val);
                cout << "  转向右子树" << endl;
                curr = curr->right;
            } else {
                // 情况2：有左子树
                cout << "  情况2：有左子树" << endl;
                
                // 找到当前节点的前驱节点
                TreeNode* predecessor = curr->left;
                cout << "  寻找前驱节点，从 " << curr->left->val << " 开始";
                
                while (predecessor->right != nullptr && predecessor->right != curr) {
                    cout << " -> " << predecessor->right->val;
                    predecessor = predecessor->right;
                }
                cout << endl;
                cout << "  找到前驱节点：" << predecessor->val << endl;
                
                if (predecessor->right == nullptr) {
                    // 情况2a：第一次访问，建立线索
                    cout << "  情况2a：第一次访问，建立线索" << endl;
                    cout << "  " << predecessor->val << "->right = " << curr->val << endl;
                    predecessor->right = curr;
                    cout << "  转向左子树" << endl;
                    curr = curr->left;
                } else {
                    // 情况2b：第二次访问，恢复结构并访问当前节点
                    cout << "  情况2b：第二次访问，恢复结构并访问当前节点" << endl;
                    cout << "  " << predecessor->val << "->right = nullptr" << endl;
                    predecessor->right = nullptr;
                    cout << "  访问节点 " << curr->val << endl;
                    result.push_back(curr->val);
                    cout << "  转向右子树" << endl;
                    curr = curr->right;
                }
            }
            
            cout << "  当前结果: [";
            for (int i = 0; i < result.size(); i++) {
                cout << result[i];
                if (i < result.size() - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
        
        cout << "\n遍历完成！最终结果: [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
        
        return result;
    }
    
    // 标准Morris中序遍历
    vector<int> inorderTraversal(TreeNode* root) {
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
                    predecessor->right = curr;
                    curr = curr->left;
                } else {
                    predecessor->right = nullptr;
                    result.push_back(curr->val);
                    curr = curr->right;
                }
            }
        }
        
        return result;
    }
    
    // 打印树的结构
    void printTree(TreeNode* root, string prefix = "", bool isLeft = true) {
        if (root == nullptr) return;
        
        cout << prefix;
        cout << (isLeft ? "└── " : "┌── ");
        cout << root->val << endl;
        
        printTree(root->left, prefix + (isLeft ? "    " : "│   "), true);
        printTree(root->right, prefix + (isLeft ? "    " : "│   "), false);
    }
};

// 辅助函数：创建测试树
TreeNode* createTestTree() {
    // 创建树：
    //     1
    //   /   \
    //  2     3
    // / \
    //4   5
    
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    return root;
}

// 辅助函数：释放树的内存
void freeTree(TreeNode* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    cout << "=== Morris遍历演示 ===" << endl;
    
    // 创建测试树
    TreeNode* root = createTestTree();
    
    cout << "树的结构：" << endl;
    MorrisDemo demo;
    demo.printTree(root);
    
    cout << "\n中序遍历的期望结果：[4, 2, 5, 1, 3]" << endl;
    
    // 执行带详细输出的Morris遍历
    vector<int> result = demo.inorderTraversalWithDetails(root);
    
    // 验证结果
    vector<int> expected = {4, 2, 5, 1, 3};
    bool correct = (result == expected);
    
    cout << "\n=== 验证结果 ===" << endl;
    cout << "期望结果: [4, 2, 5, 1, 3]" << endl;
    cout << "实际结果: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    cout << "结果" << (correct ? "正确" : "错误") << "！" << endl;
    
    // 释放内存
    freeTree(root);
    
    return 0;
} 