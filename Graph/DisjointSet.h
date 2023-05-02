#include <string>
#include <tuple>
#include <vector>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;


class DisjointSet {

unordered_map<string,tuple<int,string,string>> nodes;

public: 


    DisjointSet(vector<string> buildList);
    


    int onion(string u, string v);



    string find(string u);




};
