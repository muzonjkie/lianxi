#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>


using namespace std;

struct TreeNode 
{
    TreeNode(int x = 0) 
        :val(x)
        ,left(nullptr)
        ,right(nullptr)
    {}
    TreeNode(int x, TreeNode *left, TreeNode *right) 
        :val(x)
        ,left(left)
        ,right(right)
    {}

    int val;
    TreeNode* left;
    TreeNode* right;
};


TreeNode* buildTree(vector<int> &preorder, vector<int> &inorder); 
void cal(TreeNode* root);

vector<int> split(string parm, string delim)
{
    vector<int> res;
    while(parm.find(delim) != string::npos)
    {
        int found = parm.find(delim);
        int temp;
        temp = stoi(parm.substr(0, found));
        res.push_back(temp);
        parm = parm.substr(found + 1);
    }
    res.push_back( stoi(parm) );
    return res;
}

int main()
{
    string str1, str2;
    getline(cin, str1, '\n');
    getline(cin, str2, '\n');
    vector<int> inorder = split(str1, " ");
    vector<int> preorder = split(str2, " ");
    TreeNode* root = buildTree(preorder, inorder);
    cal(root);
    return 0;
}

int cal_sum(TreeNode* node)
{
    if(nullptr == node)
    {
        return 0;
    }
    return node->val + cal_sum(node->left) + cal_sum(node->right);
}

void cal(TreeNode* root)
{
    //这里不必考虑root为空指针的问题，因为我不会让它为空
    queue<TreeNode*> que_;
    que_.push(root);
    //用原树构造新树
    while(que_.size())
    {
        TreeNode* now = que_.front();
        que_.pop();
        now->val = 0;
        if(now->left)
        {
            que_.push(now->left);
            now->val += cal_sum(now->left);
        }
        if(now->right)
        {
            que_.push(now->right);
            now->val += cal_sum(now->right);
        }
    }

    stack<TreeNode*> stack_;
    vector<int> result;
    TreeNode* T = root;
    while(T || stack_.size())
    {
        if(T)
        {
            stack_.push(T);
            T = T->left;
        }
        else
        {
            T = stack_.top();
            stack_.pop();
            result.push_back(T->val);
            T = T->right;
        }
    }

    string out_str = "";
    for(size_t i = 0; i < result.size(); ++i)
    {
        out_str += to_string(result[i]) + " ";
    }
    if(out_str.size())
    {
        out_str = out_str.substr(0, out_str.size() - 1);
    }
    cout << out_str << "\n";
}

TreeNode* buildTree(vector<int> &preorder, vector<int> &inorder) 
{
    if (preorder.empty())
    {
        // 空节点
        return nullptr;
    }
    //找到先序的根节点在中序的位置后得到左子树的大小
    int left_size = ranges::find( inorder, preorder[0] ) - inorder.begin(); 
    //左子树加上其长度
    vector<int> pre1(preorder.begin() + 1, preorder.begin() + 1 + left_size);
    //右子树
    vector<int> pre2(preorder.begin() + 1 + left_size, preorder.end());
    //左子树
    vector<int> in1(inorder.begin(), inorder.begin() + left_size);
    //右子树
    vector<int> in2(inorder.begin() + 1 + left_size, inorder.end());
    //递归建左右子树
    TreeNode* left = buildTree(pre1, in1);
    TreeNode* right = buildTree(pre2, in2);
    return new TreeNode(preorder[0], left, right);
}

