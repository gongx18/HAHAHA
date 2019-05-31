else if(false){
            int value = boost::lexical_cast<int>(word); 
            int height = t.getHeight(t.root);
            int visits = 0;
            int rotNum = 0;
            int count = 0; 
            vector<int> v;  
            while(iss >> word){
                count += 1; 
                int k = t.lookup(t.root, value, visits, rotNum); 
                if(k != -99815)
                    v.push_back(k);
            }
            int i = 0;
            cout <<"Found " + to_string(v.size()) + " of " + to_string(count) + " nodes:" + "[";
            if(v.size() == 0){
                cout << "Found 0 of " +to_string(v.size()) + " nodes:[]"<<endl; 
            }
            for(i = 0; i < v.size() - 1; i++){
                cout << to_string()+", "; 
            }
                cout << to_string(i+1) + "]" <<endl; 
            cout << "Visited " + to_string(visits) + "("+ to_string(visits/count) + ") nodes and performed " + 
            to_string(rotNum) + "(" + to_string(rotNum/count)+") rotations."<<endl;       
