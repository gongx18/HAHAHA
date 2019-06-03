#ifndef TREE_H
#define TREE_H
#include <string>
#include <vector>
#include <string>
#include <iostream>

using namespace std; 

class Tree{
public: 
Tree(); 
~Tree(); 

struct TreeNode{
    int data; 
    struct TreeNode* left;
    struct TreeNode* right; 
    int height; 
    TreeNode(int x): data(x), left(0), right(0), height(0){}
    ~TreeNode(){
//        cout <<"Node destructor called" <<endl; 
        delete left;
        delete right; 
    }
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
TreeNode* insert(TreeNode* root, int key, int& visits, int& rotNum); 
TreeNode* rotate(TreeNode* node, int dif, int val, int& rotNum);
void findLeaves(TreeNode* root, vector<TreeNode*>* v);
void deleteLeaf(TreeNode* root, TreeNode* trueRoot, int key, string rotType, vector<range>& v, bool& b);
void print(TreeNode* root, int count, TreeNode* parent); 
//int lookup(TreeNode* root, int key, int& visits, int& rotNum){
int lookup(TreeNode* root, int& key,int& visits); 
string checkViolationType(TreeNode* root, int val); 
int findPre(TreeNode* root, int val, int pre);
int findSuc(TreeNode* root, int val, int suc);
void resetH(TreeNode* root, int val);


TreeNode* root; 
};
 
#endif 
