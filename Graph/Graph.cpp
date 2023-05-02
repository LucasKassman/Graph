#include "Graph.h"

Graph::Graph(const char* const & edgelist_csv_fn) {

ifstream my_file(edgelist_csv_fn);      // open the file
string line;                     // helper var to store current line
tuple<string,double,string> temp;
bool b1 =true;
bool b2 = true;
nodeNum = 0;
while(getline(my_file, line)) {  // read one line from the file
    
    b1 = true;
    b2 = true;
    istringstream ss(line);      // create istringstream of current line
    string first, second, third; // helper vars
    getline(ss, first, ',');     // store first column in "first"
    getline(ss, second, ',');    // store second column in "second"
    getline(ss, third, '\n');    // store third column column in "third"

    //edgemap.insert(first, tuple<string,double,string>(first,stod(third),second));
    //edgemap.insert(second, tuple<string,double,string>(second,stod(third),first));
   
    for (string i: nodelist){
        
        if (i == first) b1 = false;
        if (i == second) b2 = false; 
    }
    if (b1) {
        nodelist.push_back(first);
        nodeNum++;
       // edgemap[first] = new vector<tuple<string,double,string>>;
    }
    if (b2) {
        nodeNum++;
        nodelist.push_back(second);
       // edgemap[second] = new vector<tuple<string,double,string>>;
        }
    edgemap[first].push_back(tuple<string,double,string>(first,stod(third),second));
    edgemap[second].push_back(tuple<string,double,string>(second,stod(third),first));
 //   cout << nodelist.size() << endl;

}
my_file.close();      


    
}

Graph::~Graph(){
#if 1  
    //nodelist.erase(nodelist.cbegin(),nodelist.cend());
    unordered_map<string, vector<tuple<string,double,string>>>::iterator it = edgemap.begin();
    while (it != edgemap.end()){
        edgemap.erase(it);
        it = edgemap.begin();
    }
    vector<string>::iterator it2 =  nodelist.begin();
    vector<string>().swap(nodelist);
    /*int sz = nodelist.size();
    for (int i = 0; i< sz;i++){
        nodelist.pop_back();
    }

  /*  while (it2 != nodelist.end()){
        nodelist.erase(it2);
        it2 = nodelist.begin();
    }*/
   #endif
}

unsigned int Graph::num_nodes() {
    // TODO
 
return nodelist.size();

}

vector<string> Graph::nodes() {
    // TODO
    

    return nodelist;
}

unsigned int Graph::num_edges() {
    // TODO
    //MIGHT NEED TO HALVE THIS
    int size = 0;
    for (auto i:edgemap){
        size +=i.second.size();
    }


    return size/2;
}

unsigned int Graph::num_neighbors(string const & node_label) {
    vector<tuple<string,double,string>> temp = edgemap[node_label];
    return temp.size();
    

    // TODO
}

double Graph::edge_weight(string const & u_label, string const & v_label) {

    vector<tuple<string,double,string>> temp = edgemap[u_label];
    for (auto i:temp){
        if (get<2>(i) == v_label){
            return get<1>(i);
        }
    }
    return -1;
   


}

vector<string> Graph::neighbors(string const & node_label) {
    // TODO
    vector<tuple<string,double,string>> temp = edgemap[node_label];
    vector<string> retList;
    for (auto i:temp){
        retList.push_back(get<2>(i));
    }
    return retList;
    return vector<string>();

}

vector<string> Graph::shortest_path_unweighted(string const & start_label, string const & end_label) {
    // TODO
   // cout << " starting at: " << start_label << " going to " << end_label << endl;
   
    vector<string> returnVector;
    vector<string> visited;
    queue<pair<int, string>> exploreQueue;
    vector<pair<string, string>> predVec;
    unordered_map<string, int> lengthmap;
    for(string i:nodelist){
        predVec.push_back(make_pair(i,i));
        lengthmap[i]=INT_MAX;
        
    }
    int length;
    string curr, curr2;
    bool visitedd = false;
    bool tempVis = false;
    vector<tuple<string,double,string>> tump;
    pair<int, string> temp;
    exploreQueue.push(make_pair(0,start_label));
    while(exploreQueue.size()!=0){
        visitedd = false;
        tempVis = false;
        temp = exploreQueue.front();
        exploreQueue.pop();
        length = temp.first;
        //cout << "here" << endl;
        curr = temp.second;
       // cout << curr << endl;
        for(string i : visited){
            if (i==curr) visitedd = true;
        }
        if (!visitedd){
            visited.push_back(curr);
           // cout << "visiting: " << curr << endl;
            if (curr == end_label){
              //  cout << "found the end!" << endl;
               

                returnVector.push_back(curr);
                while (curr != start_label){
                    //cout << curr << endl;
                    for (auto &i: predVec){
                        // cout << i.second << endl;
                        // cout << curr << endl;
                        if (i.second == curr) {
                            curr = i.first;
                            //cout << i.first << endl;
                            returnVector.push_back(curr);
                           // cout << curr;
                            break;
                        }
                    }
                }
        
        reverse(returnVector.begin(), returnVector.end());
       // cout <<"shortest path is: " ;
        for (string i:returnVector){
           // cout << i << " -> ";
        }
       // cout << endl;
        return returnVector;
                
            }
            tump = edgemap[curr];
            for (auto i: tump){
                tempVis = false;
                curr2 = get<2>(i);
                for (string j: visited){
                    if (j==curr2) tempVis = true;
                }
                if(!tempVis){
                   // cout << " pushing " << curr2 << " onto the queue " << endl;
                    exploreQueue.push(make_pair(length+1,curr2));
                    for(auto &j: predVec){
                        if (curr2 == j.second){
                            
                           if (lengthmap[j.second]>length+1){
                               j.first = curr;
                                lengthmap[j.second] = length+1;
                           }
                          // cout << "setting " << curr2 << "'s  predecessor to " << curr << endl;
                            //cout << "he123re" << endl;    
                        }
                    }
                }
            }
        }
        
    }


//cout << "no path found " << endl;
return vector<string>();

}

vector<tuple<string,string,double>> Graph::shortest_path_weighted(string const & start_label, string const & end_label) {
    // TODO


  //  cout << endl;
   // cout << " starting at: " << start_label << " going to " << end_label << endl<<endl;
    
    double tempLength=0;
    vector<tuple<string,string,double>> returnVector;
    vector<string> visited;
    vector<pair<double, string>> exploreQueue;
    vector<pair<string, string>> predVec;
    tuple<string,string,double> tempTuple;
    unordered_map<string, double> lengthmap;
    vector<tuple<string,double,string>> tempVecTup;
    for(string i:nodelist){
        predVec.push_back(make_pair(i,i));
        lengthmap[i]=INT_MAX;
        
    }
    double length;
    double compare_min;
    int count = 0;
    int countAt = 0;
    string curr, curr2;
    bool visitedd = false;
    bool tempVis = false;
    vector<tuple<string,double,string>> tump;
    pair<double, string> temp;
    
    exploreQueue.push_back(make_pair(0,start_label));



    if (start_label==end_label){
        returnVector.push_back(make_tuple(start_label,start_label,-1));
        return returnVector;
    }
    while(exploreQueue.size()!=0){
        compare_min = INT_MAX;
        count=0;
        countAt = 0;
        for(auto &i: exploreQueue){
        if (i.first < compare_min) {
            compare_min = i.first;
            countAt=count;
        }
        count++;
        }
        visitedd = false;
        tempVis = false;
        temp = exploreQueue[countAt];
        exploreQueue.erase(exploreQueue.begin() + countAt);
        length = temp.first;
     //   cout << "setting length of " << temp.second << " to " << temp.first << endl;
        curr = temp.second;
       // cout << curr << endl;
        for(string i : visited){
            if (i==curr) visitedd = true;
        }
        if (!visitedd){
            visited.push_back(curr);
           // cout << "visiting: " << curr << endl;
            if (curr == end_label){
              //  cout << "found the end!" << endl;
               

               // returnVector.push_back(curr);
                while (curr != start_label){
                    //cout << curr << endl;
                    for (auto &i: predVec){
                        // cout << i.second << endl;
                        // cout << curr << endl;
                        if (i.second == curr) {
                            tempVecTup = edgemap[i.second];
                          //  cout << "checking: " << i.second <<  endl;
                            for (auto tupp: tempVecTup){
                                  //  cout << get<0>(tupp) << get<1>(tupp) << get<2>(tupp) << " with string: " << curr << endl;
                                if (get<2>(tupp)==i.first){
                                    
                                    tempTuple = make_tuple(get<2>(tupp),get<0>(tupp),get<1>(tupp));
                                }
                            }

                             


                            curr = i.first;
                            //cout << i.first << endl;
                            
                            returnVector.push_back(tempTuple);
                           // cout << curr;
                            break;
                        }
                    }
                }
        
        reverse(returnVector.begin(), returnVector.end());
        //cout <<"shortest path is: "  ;
        for (auto k: returnVector){
        //    cout << get<0>(k) << "->" << get<1>(k);
        }
      //  cout << endl;
        
  
        return returnVector;
                
            }
            tump = edgemap[curr];
            for (auto i: tump){
                tempVis = false;
                curr2 = get<2>(i);
                tempLength = get<1>(i)+length;
                for (string j: visited){
                    if (j==curr2) tempVis = true;
                }
                if(!tempVis){
                   // cout << " pushing " << curr2 << " onto the queue with length " << tempLength << endl;
                    exploreQueue.push_back(make_pair(tempLength,curr2));
                    for(auto &j: predVec){
                        if (curr2 == j.second){
                            
                           if (lengthmap[j.second]>length+tempLength){
                               j.first = curr;
                                lengthmap[j.second] = length+tempLength;
                           }
                          // cout << "setting " << curr2 << "'s  predecessor to " << curr << endl;
                            //cout << "he123re" << endl;    
                        }
                    }
                }
            }
        }
        
    }


//cout << "no path found " << endl;
return vector<tuple<string,string,double>>();


}

vector<vector<string>> Graph::connected_components(double const & threshold) {
    // TODO
    /*
    BFS(u,v):
    q = an empty queue
    add (0,u) to q // (0,u) -> (length from u, current vertex)
    while q is not empty:
        (length,curr) = q.dequeue()
        if curr is unvisited:
            mark curr as visited
            if curr == v: // if we have reached the vertex we are searching for
                return length
            for all outgoing edges (curr,w) from curr: // otherwise explore all neighbors
                if w has not yet been visited:
                    add (length+1,w) to q
    return "FAIL" // if I reach this point, then no path exists from u to v
    */

    vector<vector<string>> returnVec;
    vector<string> connectList;

    queue<pair<int, string>> Q;
    unordered_map<string, bool> visited;
    pair<int,string> temp;
    for(string i: nodelist){
        visited[i] = false;
    }
    for(string i: nodelist){

        if (!visited[i]){
            Q.push(make_pair(0,i));
            while(Q.size() != 0){
                temp = Q.front();
                Q.pop();
                if (!visited[temp.second]){
                    visited[temp.second]=true;
                    connectList.push_back(temp.second);                
                }
                for (auto tup: edgemap[temp.second]){
                    if (!visited[get<2>(tup)]){

                        if (get<1>(tup)<=threshold) Q.push(make_pair(temp.first+1,get<2>(tup)));
                    }
                }
            }
            returnVec.push_back(connectList);
            for(string s: connectList){
               //cout << s;
            }
          // cout << endl;
            connectList = vector<string>();
            
        }



    }

    return returnVec;

}

double Graph::smallest_connecting_threshold(string const & start_label, string const & end_label) {
    if (start_label == end_label) {
       // cout << "Node to itself " << start_label << endl;
        return 0;
    }
    // TODO
    DisjointSet disJ(nodelist);
    bool first = true;
    unordered_map<double,vector<pair<string,string>>> unionList;
    double min_weight=0;
    set<double> dubList;
   for (auto i:edgemap){

       for(auto edge: i.second){

           dubList.insert(get<1>(edge));
           unionList[get<1>(edge)].push_back(make_pair(get<0>(edge),get<2>(edge)));

       }

   }

   for (double x: dubList){
       for(auto i: unionList[x]){
           disJ.onion(i.first,i.second);
         //  cout << "unioning " << i.first << " with " << i.second << endl; 
       }
       if(disJ.find(start_label)==disJ.find(end_label)) {
          // cout << "smallest threshold between " << start_label << " and " << end_label << " is " << x << endl;
           return x;
       }
   }


  //  cout << "no path between "<< start_label << " and " << end_label << endl;
    return -1;
   

}
