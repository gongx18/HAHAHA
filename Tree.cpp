#include "Tree.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <climits>
using namespace std; 
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

Tree::Tree(){
    root = 0; 
}

Tree::~Tree(){
    delete root; 
}

int Tree::max(int a, int b)  
{  
    return (a > b)? a : b;  
} 

Tree::TreeNode* Tree::leftRotate(TreeNode* node){
    TreeNode* mid = node->right; 
    TreeNode* tran = mid->left;
    node->right = tran; 
    mid->left = node;

    mid->height = max(getHeight(mid->left), getHeight(mid->right)) + 1; 
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1; 

    return mid;
}

Tree::TreeNode* Tree::rightRotate(TreeNode* node){
    TreeNode* mid = node->left; 
    TreeNode* tran = mid->right; 
    node->left = tran; 
    mid->right = node;

    mid->height = max(getHeight(mid->left), getHeight(mid->right)) + 1; 
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1; 

    return mid;
}

int Tree::getHeight(TreeNode* node){
    if(node == 0) 
        return -1; 
    else 
        return node->height; 
}

Tree::TreeNode* Tree::insert(TreeNode* root, int key, int& visits, int& rotNum) { 
    //BST insertion
    if(root == 0)
        return new TreeNode(key); 
    else{
        visits += 1;  
        if(root->data == key){
            visits -= 1; 
            return root; 
        }
        if(root->data < key){
            root->right = insert(root->right, key, visits, rotNum); 
        }else{
            root->left = insert(root->left, key, visits, rotNum); 
        }
        //perform rotation if unbalanced
        if(abs(getHeight(root->right) - getHeight(root->left)) > 1){
            root = rotate(root, getHeight(root->right) - getHeight(root->left), key); 
            rotNum += 1; 
        }   
        //re-adjust height
        root->height = 1 + max(getHeight(root->right), getHeight(root->left)); 
        return root; 
    }
}


Tree::TreeNode* Tree::rotate(TreeNode* node, int dif, int val){
    if(dif == 2){
        //> : right-left
        if(val < node->right->data){
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        }else{//left-left
            return leftRotate(node); 
        }

    }else{//inserted to the left of node; 
        //<
        if(val < node->left->data){
            node->left = leftRotate(node->left); 
            return rightRotate(node); 
        }else{
            return rightRotate(node); 
        }
    }
}

//fill v with pointers to leaf nodes
void Tree::findLeaves(TreeNode* root, vector<TreeNode*>* v){
    if(root == NULL) return; 
    else if(getHeight(root) == 0){
        v->push_back(root); 
    }
    findLeaves(root->left, v);
    findLeaves(root->right, v); 
}

//basically fake insertion
void Tree::deleteLeaf(TreeNode* root, int key, string rotType, vector<range>* v, bool& b){
    if(key < root->data){
        deleteLeaf(root->left, key, rotType, v, b);
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1; 
    }
    else if(key > root->data){
        deleteLeaf(root->right, key, rotType, v, b);
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;  
    }    
    else{
        root->height += 1; 
        return; 
    }
    
    //check balanced property (backward)
    if(abs(getHeight(root->right) - getHeight(root->left)) > 1 && b == true){ 
        cout <<"violation type is: " +checkViolationType(root, key)<<endl; 
        if(checkViolationType(root, key) == rotType){
            v->push_back(range(findPre(root, key, INT_MIN), findSuc(root, key, INT_MAX))); 
            b = false;//stop recursing after the first unbalance. 
        }
    }
}

//return type of violation(string);   
string Tree::checkViolationType(TreeNode* root, int val){ 
    if(val > root->data){ 
        if(val < root->right->data)
            return "right-left"; 
        else
            return "left-left"; 
        
    }else{//inserted to the left of node; 
        //<
        if(val < root->left->data)
            return "left-right";
        else
            return "right-right";
    }
}

//reset height after one fake insert
void Tree::resetH(TreeNode* root, int val){
    cout <<"current node is " + to_string(root->data)<<endl; 
    if(root->data == val){
        root->height = 0;
        return; 
    }else if(val > root->data){
        resetH(root->right, val); 
    }else{
        resetH(root->left, val);
    }
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    return; 
}


int Tree::findPre(TreeNode* root, int val, int pre){
    if(root->data == val){ 
        return pre; 
    }else if(val > root->data){
        pre = root->data; 
        findPre(root->right, val, pre); 
    }else{
        findPre(root->left, val, pre); 
    }
} 


int Tree::findSuc(TreeNode* root, int val, int suc){  
    if(root->data == val){
        return suc; 
    }else if(val < root->data){
        suc = root->data; 
        findSuc(root->left, val, suc);
    }else{
        findSuc(root->right, val, suc); 
    }
}


