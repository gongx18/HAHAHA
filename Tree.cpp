#include "Tree.h"
#include <math.h>
#include <iostream>
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

Tree::TreeNode* Tree::insert(TreeNode* root, int key) {
    //normal BST insertion: 
    if(root == 0)
        return new TreeNode(key); 
    else{
//        visits += 1;  
        if(root->data == key){
//            visits -= 1; 
            return root; 
        }
        if(root->data < key){
            root->right = insert(root->right, key); 
        }else{
            root->left = insert(root->left, key); 
        }
            //if violates balance property, perform rotation
        if(abs(getHeight(root->right) - getHeight(root->left)) > 1){
            root = rotate(root, getHeight(root->right) - getHeight(root->left), key); 
//            rotation += 1; 
        }   
        root->height = 1 + max(getHeight(root->right), getHeight(root->left)); //increment height
        return root; 
    }
}


Tree::TreeNode* Tree::rotate(TreeNode* node, int dif, int val){//node here is the 
    bool b = false; 
    //if true, then it is inserted to the right of root
    if(dif == 2){
         b = true; //right height - left height; 
    }
    if(b == true){
        //>
        if(val < node->right->data){
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        }else{
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

//stores the value of all leaves nodes in this vector
void findLeaves(TreeNode* root, vector<TreeNode*> v){
    if(root == NULL) return; 
    if(root->left == NULL && root->right = NULL){
        v.push_back(root); 
    }
    findLeaves(root->left);
    findLeaves(root->right); 
}

//adds on to the vector that is filled with range object for a single leaf node; 

//note that the key here is the data of a single leaf node; 
Tree::range deleteLeaf(TreeNode* root, int key, TreeNode* parent, string rotType, vector<range> v){
    if(key < root->data){
        deleteLeaf(root->left);
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1; 
    }
    else if(key > root->data){
        deleteLeaf(root->right);
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;  
            
    }    
    else{
        root->height += 1; 
        return; 
    }
    if(abs(getHeight(root->right) - getHeight(root->left)) > 1){
        if(checkViolation(root) == rotType){
           v.push_back(range(root->findPre(), root->findSuc())); 
        }
    }
    
}

//12: rl  
string checkViolationType(TreeNode* root){ 
        if(val < node->right->data){
            return "right-left"; 
        }else{
            return "left"; 
        }

    }else{//inserted to the left of node; 
        //<
        if(val < node->left->data){
            return "left-right";
        }else{
            return "right";
        }
    }
}

//return the number that representes 
int fakeInsert(TreeNode* root, vector<TreeNode*>v){
    for(i = 0; i < v.size(); i++){
        range r(root->findPre(), root->findSuc()); 
        
    }
}






//those findPre and findSuc are special, since they are only finding the predecessor or sucessor of leaf node. 
int findPre(TreeNode* root, int val, int pre){ 
    while(root != NULL){
        if(val > root->data){
            pre = root->data; 
            findPre(root->right); 
        }else{
            findPre(root->left); 
        }
    }
    return pre; 
}

int findSuc(TreeNode* root, int val, int suc){
    while(root != NULL){
        if(val < root->data){
            suc = root->data; 
            findSuc(root->left)
        }else{
            findSuc(root->right); 
        }
    }
    return suc; 
}

