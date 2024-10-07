#include <iostream>

using namespace std;

// 定义二叉树节点结构
struct TreeNode {
    int val; // 节点值
    TreeNode* left; // 左子树指针
    TreeNode* right; // 右子树指针

    // 构造函数
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 最近公共祖先函数
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // 基准条件：如果当前节点为空，或是 p 或 q，则返回当前节点
    if (!root || root == p || root == q) {
        return root;
    }

    // 递归查找左子树和右子树
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    // 如果左子树和右子树都非空，当前节点是最近公共祖先
    if (left && right) {
        return root;
    }
    
    // 返回非空的子树
    return left ? left : right;
}

int main() 
{
    return 0;
}

