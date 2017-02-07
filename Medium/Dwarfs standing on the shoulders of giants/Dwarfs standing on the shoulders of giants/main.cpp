#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

map<int, vector<int>> adjList;

int maxHeight(int index){
    if (adjList[index].empty()){
        return 0;
    }
    int maxDepth = 0;
    
    for (auto & i : adjList[index]){
        maxDepth = fmax(maxDepth,maxHeight(i));
    }
    
    return maxDepth + 1;
}

int main(int argc, const char * argv[]) {
    //ifstream infile("input");
    int n; // the number of relationships of influence
    cin >> n; cin.ignore();
    
    int root = 0;
    for (int i = 0; i < n; i++) {
        int x; // a relationship of influence between two people (x influences y)
        int y;
        
        // infile >> x >> y;
        cin >> x >> y; cin.ignore();
        if (i == 0)
            root = x;
        
        if (adjList.count(x) == 0){
            vector<int> nodes(0);
            nodes.push_back(y);
            adjList[x] = nodes;
        } else {
            adjList[x].push_back(y);
        }
        
        if (adjList.count(y) == 0) {
            vector<int> nodes(0);
            adjList[y] = nodes;
        }
    }

    int maxDepth = 0;
    for (auto & ad : adjList){
        maxDepth = fmax(maxDepth, maxHeight(ad.first));
    }
    cout << maxDepth + 1 << endl;
    
}




