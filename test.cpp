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
    int visits = 0;
    int rotNum = 0;  
    t.root = t.insert(t.root, 12, visits, rotNum); 
    t.root = t.insert(t.root, 7, visits, rotNum); 
    t.root = t.insert(t.root, 108, visits, rotNum); 
//    t.print(t.root, 0, NULL); 

//    t.root = t.insert(t.root, 6, visits, rotNum); 
//    t.root = t.insert(t.root, 7, visits, rotNum); 
//    t.root = t.insert(t.root, 8, visits, rotNum);  
    t.print(t.root, 0, NULL); 
//for(int i = 1; i < 9; i++){
//    t.root = t.insert(t.root, i, visits, rotNum);  
//}

    cout<<"rotNum is: " + to_string(rotNum)<<endl; 
//    cout << "root is: " +to_string((t.root)->data) <<endl;
    cout << "root has height: " + to_string((t.root)->height)<<endl; 
//    cout << "l-sub has height: " + to_string((t.root)->left->height)<<endl; 
    vector<Tree::TreeNode*> v;  
    t.findLeaves(t.root, &v); 
    cout << "number of leaves is :" +to_string(v.size()) <<endl; 
    vector<Tree::range> ans; 
    for(int i = 0; i <ans.size(); i++){
        cout <<"+" + to_string(v[i]->data)<<endl; 
    } 
    for(int i = 0; i < v.size(); i++){
        bool b = true; 
        t.deleteLeaf(t.root, v[i]->data, "left-left", &ans, b);
        cout <<"let me see" <<endl; 
        t.resetH(t.root, v[i]->data); //reset height after fake insert is done; 
    }
    cout << "ans.size() is: " + to_string(ans.size())<<endl;   
//    t.print(t.root, 0, NULL);//not sure 
    cout << "pre of 108 is: " + to_string(t.findPre(t.root, 108, NULL))<<endl; 
    return 0; 
}
