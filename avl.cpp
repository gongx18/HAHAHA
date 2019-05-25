#include "Tree.h"
#include <string>
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
int main(){
    Tree t; 
    t.root = t.insert(t.root, 3);
    t.root = t.insert(t.root, 4); 
    cout << (t.root)->data <<endl; 
    t.root = t.insert(t.root, 5); 
    cout << (t.root)->data <<endl;
    cout << (t.root)->left->data<<endl;   
    return 0; 
}
