#include "Tree.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <climits>
#include <stdint.h>
#include <limits.h>
using namespace std;

void f1(string violationType, vector<Tree::TreeNode*> &v, vector<Tree::range> &ans, Tree t){
    for(size_t i = 0; i < v.size(); i++){
        int val = v[i]->data;
        bool b = true; 
        t.deleteLeaf(t.root, t.root, val, violationType, ans, b);
        t.resetH(t.root, v[i]->data);  
    }

        size_t j = 0;
        int b = true; 
        if(ans.size() ==  0){
            cout << "No inserts would cause a " + violationType + " rotation." <<endl<<endl; 
        }else if(b){
            while(j < ans.size()){
                if(ans[j].ub - ans[j].lb >= 0)
                    b = false;
                j++; 
            }
            if(b)
                cout << "No inserts would cause a " + violationType + " rotation." <<endl<<endl; 
        }
        if(!b){
            cout<<"The following inserts would cause a " + violationType + " rotation:"<<endl;  
            for(j = 0; j < ans.size() - 1; j++){
                if(ans[j].ub - ans[j].lb > 0){
                    cout<< to_string(ans[j].lb)+ " to " + to_string(ans[j].ub) + ", "; 
                }else if(ans[j].ub - ans[j].lb == 0){
                    cout<< to_string(ans[j].lb) + ","; 
                }
            }
            if(ans[j].ub - ans[j].lb > 0){
                cout<< to_string(ans[j].lb)+ " to " + to_string(ans[j].ub) <<endl<<endl; ; 
            }else if(ans[j].ub - ans[j].lb == 0){
                cout<< to_string(ans[j].lb) << endl<<endl; 
            } 
        }
}

int main(int args, char* argv[]){
    Tree t; 
    ifstream inFile;
    if(args != 2){
        cerr <<"wrong input format"<<endl; 
        exit(1); 
    }
    inFile.open(argv[1]); //how to upload file??????
    if(inFile.fail( )){
        cerr <<"unable to open file";
        exit(1);
    }
    while(!inFile.eof()){
        string line; 
        getline(inFile, line);
        istringstream iss(line);
        string word;
        iss >> word; 
        if(word == "#" || word == ""){ 
            continue; 
        }else if(word == "insert"){
            int visits = 0;
            int rotNum = 0; 
            int count = 0;
            int add = 0;  
            int temp = 0;
            while(iss >> word){  
                int value = stoi(word); 
                if(t.lookup(t.root, value, temp) == -99815) //temp is just some random value you pass in for the sake of passing in; 
                    add ++; 
                t.root = t.insert(t.root, value, visits, rotNum); 
//                if(t.getHeight(t.root) != height)
//                    add++; 
                count ++; 
            }
            cout <<"Added " << add << " of " << count << " nodes." <<endl; 
            cout << "Visited " << visits << " (" << visits*1.0/count << ") nodes and performed " << rotNum << " (" << rotNum* 1.0/count << ") rotations."<<endl<<endl;
                    
        }else if(word == "lookup"){
            int visits = 0;
            int count = 0;   
            vector<int> v; 
            while(iss >> word){
                count += 1; 
                int value = stoi(word);  
                int temp =  t.lookup(t.root, value, visits);
                if(temp  != -99815){
                    v.push_back(temp); 
                }
            }
            string s = "Found " + to_string(v.size()) + " of " + to_string(count)+ " nodes: ["; 
            for(size_t i = 0; i < v.size(); i++){
                s+= to_string(v[i]);
                if(i != v.size() - 1)
                    s+= ", ";
            }
            cout << s+"]" <<endl; 
            cout << "Visited "  << visits <<" (" << visits*1.0/count <<  ") nodes and performed 0 (0) rotations."<<endl<<endl;   
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
            cout << endl; 
        }
    } 
};
