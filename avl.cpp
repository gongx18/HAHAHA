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
    t.root = t.insert(t.root, 5); 
    t.insert(t.root, 6);
    t.insert(t.root, 7); 
    t.insert(t.root, 3); 
    t.insert(t.root, 3);  
    cout << "root is: " +to_string((t.root)->data) <<endl;
    cout << "root has height: " + to_string((t.root)->height)<<endl; 
    cout << "r-sub has height: " + to_string((t.root)->right->height)<<endl;  
    return 0; 
}
