#ifndef TREE_H
#define TREE_H
class Tree{
public: 
Tree(); 
~Tree(); 

struct TreeNode{
    int data;
    int height; 
    struct TreeNode* left;
    struct TreeNode* right; 
    TreeNode(int x): data(x), left(0), right(0), height(0){}
};

struct range{
    int lb; 
    int ub; 
    range(int x, int y): lb(x), ub(y){}
};

int max(int a, int b);
TreeNode* leftRotate(TreeNode* node); 
TreeNode* rightRotate(TreeNode* node); 
int getHeight(TreeNode* node);
TreeNode* insert(TreeNode* root, int key); 
TreeNode* rotate(TreeNode* node, int dif, int val);
TreeNode* root; 
};
 
#endif 
