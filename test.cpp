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
    t.root = t.insert(t.root, 3, visits, rotNum); 
    t.root = t.insert(t.root, 4, visits, rotNum);  
    t.root = t.insert(t.root, 5, visits, rotNum);
    t.root = t.insert(t.root, 6, visits, rotNum); 
    t.root = t.insert(t.root, 7, visits, rotNum); 

    cout<<"rotNum is: " + to_string(rotNum)<<endl; 
//    cout << "root is: " +to_string((t.root)->data) <<endl;
    cout << "root has height: " + to_string((t.root)->height)<<endl; 
//    cout << "l-sub has height: " + to_string((t.root)->left->height)<<endl; 
    vector<Tree::TreeNode*> v;  
    t.findLeaves(t.root, &v); 
    cout << "number of leaves is :" +to_string(v.size()) <<endl; 
    vector<Tree::range> ans;
    cout<<ans.size()<<endl;  
    for(int i = 0; i < v.size(); i++){
        t.deleteLeaf(t.root, v[i]->data, "left-left", &ans);
        t.resetH(t.root, v[i]->data); //reset height after fake insert is done; 
    }
    cout << "ans.size() is: " + to_string(ans.size())<<endl; 
    cout <<"val is: "+to_string(v[2]->data)<<endl;
    cout <<ans[0].lb<<endl;
    cout <<ans[0].ub<<endl;  
    return 0; 
}
