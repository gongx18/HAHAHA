#include "Tree.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <climits>
using namespace std; 

struct TreeNode{
    int data; 
    struct TreeNode* left;
    struct TreeNode* right;
    int height;  
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
    if(root == 0){
        return new TreeNode(key); 
    }else{
        visits += 1; 
        if(root->data == key){
            return root; 
        }
        if(root->data < key){
            root->right = insert(root->right, key, visits, rotNum); 
        }else{
            root->left = insert(root->left, key, visits, rotNum); 
        }
        //perform rotation if unbalanced
        if(abs(getHeight(root->right) - getHeight(root->left)) > 1){
            root = rotate(root, getHeight(root->right) - getHeight(root->left), key, rotNum); 
//            rotNum += 1; 
        }   
        //re-adjust height
        root->height = 1 + max(getHeight(root->right), getHeight(root->left)); 
        return root; 
    }
}

int Tree::lookup(TreeNode* root, int& key, int& visits){
    if(root == NULL)
        return -99815;
    else if(root->data == key){
        visits ++; 
        return key; 
    }
    //not null, not equal, continue search
    if(root->data > key){
        visits ++;
        return lookup(root->left, key, visits); 
    }else{
        visits ++; 
        return lookup(root->right, key, visits); 
    }
//    throw "no return type exception"; 
}

Tree::TreeNode* Tree::rotate(TreeNode* node, int dif, int val, int& rotNum){
    if(dif >=  2){
        //> : right-left
        if(val < node->right->data){ 
            rotNum += 2; 
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        }else{//left-left
            rotNum += 1;
            return leftRotate(node); 
        }

    }else{//inserted to the left of node; 
        //<
        if(val > node->left->data){
            rotNum += 2;
            node->left = leftRotate(node->left); 
            return rightRotate(node); 
        }else{
            rotNum += 1;
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
void Tree::deleteLeaf(TreeNode* root, TreeNode* trueRoot, int key, string rotType, vector<range>& v, bool& b){
    if(key < root->data){
        deleteLeaf(root->left, trueRoot,  key, rotType, v, b);
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1; 
    }
    else if(key > root->data){
        deleteLeaf(root->right, trueRoot, key, rotType, v, b);
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;  
    }    
    else{
        root->height += 1; 
        return; 
    }
//    cout << "node is :" + to_string(root->data) + ", right height is :" + to_string(getHeight(root->right)) + " left height is : " + to_string(getHeight(root->left)) << endl; 
    //check balanced property (backward)
    if(abs(getHeight(root->right) - getHeight(root->left)) > 1 && b == true && getHeight(root) != 2){ 
        int lb = findPre(trueRoot, key, INT_MIN);
        int ub = findSuc(trueRoot, key, INT_MAX); 
        if(lb != INT_MIN)
            lb += 1;
        if(ub != INT_MAX)
            ub -= 1;  
        if(checkViolationType(root, key) == rotType){  
            v.push_back(range(lb, key - 1)); 
            v.push_back(range(key + 1, ub));  
        }
        b = false;//stop recursing after the first unbalance. 
    }else if(abs(getHeight(root->right) - getHeight(root->left)) > 1 && checkViolationType(root, key) == "edge"){ //no need to check whether b is true;  
        int lb = findPre(trueRoot, key, INT_MIN);
        int ub = findSuc(trueRoot, key, INT_MAX); 
        if(lb != INT_MIN)
            lb += 1;
        if(ub != INT_MAX)
            ub -= 1;    
        if(root ->left != NULL){
            if(rotType == "left-right"){
                v.push_back(range(root->left->data + 1, ub));
            }else if(rotType == "left-left"){
                v.push_back(range(lb, root->left->data - 1)); 
            } 
        }else{//root->right != NULL
            if(rotType == "right-left"){
                v.push_back(range(lb, root->right->data - 1)); 
            }else if(rotType == "right-right"){ 
                v.push_back(range(root->right->data + 1, ub)); 
            }
        }
        b = false; 
    }
}

//return type of violation(string);   
string Tree::checkViolationType(TreeNode* root, int val){ 
    if(val > root->data){ 
        if(val == root->right->data)
            return "edge"; 
        else if(val < root->right->data)
            return "right-left"; 
        else
            return "right-right"; 
            //return "right-right"; 
        
    }else{//inserted to the left of node; 
        //<
        if(val == root->left->data)
            return "edge"; 
        else if(val > root->left->data)
            return "left-right";
        else
            return "left-left";
    }
}

//inorder print: 
void Tree::print(TreeNode* root, int count, TreeNode* parent){
    string s;
    for(int i = 0; i < count; i++){ 
        s += "  "; 
    }
    if(root != 0){
        count += 1;
        if(root->height > 0)
            cout <<s+ "Node(" + to_string(root->data) + ", h=" + to_string(root->height) +"):" <<endl; 
        else
            cout <<s+ "Leaf(" + to_string(root->data) + ")" << endl; 
        print(root->left, count, root);
        print(root->right, count, root); 
    }else{
        if(getHeight(parent) != 0)
            cout << s + "Null" << endl; 
    }
}

//reset height after one fake insert
void Tree::resetH(TreeNode* root, int val){ 
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

int Tree::findPre(TreeNode* root,int val, int pre){
    if(root->data == val){
        return pre; 
    }else if(val > root->data){
        pre = root->data;
        return findPre(root->right, val, pre); 
    }else{
        return findPre(root->left, val, pre); 
    }
//    throw "no return type Exception";
//    return -2147483647;
} 

int Tree::findSuc(TreeNode* root,  int val, int suc){  
    if(root->data == val){
        return suc; 
    }else if(val < root->data){
        suc = root->data; 
        return findSuc(root->left, val, suc);
    }else{
        return findSuc(root->right, val, suc); 
    }
//    throw "no return type Exception"; 
//    return 2147483647;
}


