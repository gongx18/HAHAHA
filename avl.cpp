#include "Tree.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <cstdint>
#include <climits>
#include <stdint.h>
#include <limits.h>
using namespace std;

void f1(string violationType, vector<Tree::TreeNode*> &v, vector<Tree::range> &ans, Tree t){
    for(int i = 0; i < v.size(); i++){
        int val = v[i]->data;
        bool b = true; 
        t.deleteLeaf(t.root, t.root, val, violationType, ans, b);
//        cout<< "root has height:" + to_string(t.root->height) <<endl; 

        t.resetH(t.root, v[i]->data); 
//        cout <<"root has height:" + to_string(t.root->height)<<endl; 
    }

        int j = 0;
        if(ans.size() ==  0){
            cout << "No inserts would cause a " + violationType + " rotation:" <<endl; 
        }else if(ans[j].ub - ans[j].lb < 0){
            cout << "No inserts would cause a " + violationType + " rotation:" <<endl; 
        }else{
            cout<<"The following inserts would cause a " + violationType + " rotation:"<<endl;  
            for(j = 0; j < ans.size() - 1; j++){
                if(ans[j].ub - ans[j].lb > 0){
                    cout<< to_string(ans[j].lb)+ " to " + to_string(ans[j].ub) + ", "; 
                }else if(ans[j].ub - ans[j].lb == 0){
                    cout<< to_string(ans[j].lb) + ","; 
                }
            }
            if(ans[j].ub - ans[j].lb > 0){
                cout<< to_string(ans[j].lb)+ " to " + to_string(ans[j].ub) <<endl; ; 
            }else if(ans[j].ub - ans[j].lb == 0){
                cout<< to_string(ans[j].lb) << endl; 
            } 
        }
}

int main(){
    Tree t; 
    ifstream inFile;
    inFile.open("prog2.txt"); //how to upload file??????
    if(inFile.fail( )){
        cerr <<"unable to open file";
        exit(1);
    }
//reached here 
    while(!inFile.eof()){//the line is not empty;  
        string line; 
        getline(inFile, line); //important
        istringstream iss(line);
        string word;
        iss >> word; 
        if(word == "#" || word == ""){ //???
            continue; 
        }else if(word == "insert" || word == "lookup"){
            int visits = 0;
            int rotNum = 0; 
            int count = 0;
            int add = 1;  
            while(iss >> word){//?????
                cout << "word is :" + word<<endl; 
                int value = boost::lexical_cast<int>(word); 
                int height = t.getHeight(t.root);
                t.root = t.insert(t.root, value, visits, rotNum); 
                if(t.getHeight(t.root) != height)
                    add++;  
                count ++; 
            }
            cout <<"Added " + to_string(add) + " of" + to_string(count) + " nodes." <<endl; 
            cout << "Visited " + to_string(visits) + "("+ to_string(visits/count) + ") nodes and performed " + 
            to_string(rotNum) + "(" + to_string(rotNum/count)+") rotations."<<endl;       
        }else if(word == "print"){
            iss >> word; 
            if(word == "tree"){
                t.print(t.root, 0, t.root);      
            }else{
                vector<Tree::TreeNode*> v; 
                vector<Tree::range> ans; 
                t.findLeaves(t.root, &v); 
                iss >> word; 
                if(word == "left-left"){
                    f1("left-left", v, ans, t); 
                }else if(word == "left-right"){
                    f1("left-right", v, ans, t); 
                }else if(word == "right-left"){
                    f1("right-left", v, ans, t); 
                }else if(word == "right-right"){
                    f1("right-right", v, ans, t); 
                }
            }
        }
    } 
};
