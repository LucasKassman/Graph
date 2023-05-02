#include "DisjointSet.h"






DisjointSet::DisjointSet(vector<string> nodelist){
	for(string i: nodelist){
		nodes[i]=make_tuple(1,"",i);
	}

}



int DisjointSet::onion(string x,string y){

	if(find(x)==find(y)) return 0;
	string u = find(x);
	string v = find(y);

	if (get<0>(nodes[v])>get<0>(nodes[u])){
	//	cout << "changing " << u  << "'s next to: " << v << endl;
		get<1>(nodes[u]) = v;
		get<0>(nodes[v])++;
	}
	else{
		get<1>(nodes[v])=u;
	//	cout << "changing " << v  << "'s next to: " << u << endl;
		get<0>(nodes[u])++;
	}
	
}


string DisjointSet::find(string u){
	vector<string> childList;

	tuple<int,string,string> tempTup= nodes[u];

	while (get<1>(tempTup)!=""){
	//	cout << "current key " << get<1>(tempTup) << endl;
		childList.push_back(get<2>(tempTup));
		tempTup=nodes[get<1>(tempTup)];
	}
	for(string s: childList){
		get<1>(nodes[s])=get<2>(tempTup);
	}
	return get<2>(tempTup);
	
}
