#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
//#include <fstream>

using namespace std;


int main()
{
    //ifstream infile("input");
    map<int,vector<int>> adjList;
    map<int,vector<int>>::iterator adjListIterator;
    int n; // the number of adjacency relations
    cin >> n; cin.ignore();
    //infile >> n;
    cerr << n << endl;
    for (int i = 0; i < n; i++) {
        
        int xi; // the ID of a person which is adjacent to yi
        int yi; // the ID of a person which is adjacent to xi
        cin >> xi >> yi; cin.ignore();
        //infile >> xi >> yi;
        
        //
        if (adjList.count(xi) == 0){
            vector<int> nodes(0);
            nodes.push_back(yi);
            adjList[xi] = nodes;
        } else {
            adjList[xi].push_back(yi);
        }
        
        if (adjList.count(yi) == 0){
            vector<int> nodes(0);
            nodes.push_back(xi);
            adjList[yi] = nodes;
        } else {
            adjList[yi].push_back(xi);
        }
        cerr << xi << " " << yi << endl;
    }
    
    for (adjListIterator = adjList.begin(); adjListIterator != adjList.end(); adjListIterator++){
        cerr << adjListIterator->first << " | ";
        for (vector<int>::iterator it = adjListIterator->second.begin(); it != adjListIterator->second.end(); it++ ){
            cerr << *it << ", ";
        }
        cerr << endl;
    }
    
    int relays = 0;
    //cerr << "size = " << adjList.size() << endl;
    while (adjList.size() > 1){
        vector<int> removeKeys;
        vector<int> singleKeys;
        for (adjListIterator= adjList.begin(); adjListIterator != adjList.end(); adjListIterator++){
            if (adjListIterator->second.size() == 1){
                singleKeys.push_back(adjListIterator->first);
            }
        }
        //for (adjListIterator= adjList.begin(); adjListIterator != adjList.end(); adjListIterator++){
        for (vector<int>::iterator vit = singleKeys.begin(); vit != singleKeys.end(); vit++){
            //int key = adjListIterator->first;
            //vector<int> value = adjListIterator->second;
            int key = *vit;
            vector<int> value = adjList[key];
            if (value.size() == 1) {
                // remove the reference from the node referenced in the key
                vector<int>::iterator it = find(adjList[value[0]].begin(), adjList[value[0]].end(), key);
                if (it != adjList[value[0]].end()){
                    adjList[value[0]].erase(it);
                }
                //adjListIterator->second.clear();
                adjList[key].clear();
                removeKeys.push_back(key);
                //removeKeys.push_back(adjListIterator->first);
            }
        }
        for(int i=0; i < removeKeys.size(); i++)
            adjList.erase(removeKeys[i]);
        //cerr << "size = " << adjList.size() << endl;
        
        relays++;
        /*
        for (adjListIterator = adjList.begin(); adjListIterator != adjList.end(); adjListIterator++){
            cerr << adjListIterator->first << " | ";
            for (vector<int>::iterator it = adjListIterator->second.begin(); it != adjListIterator->second.end(); it++ ){
                cerr << *it << ", ";
            }
            cerr << endl;
        }
         */
    }
    /*
    for (adjListIterator = adjList.begin(); adjListIterator != adjList.end(); adjListIterator++){
        cerr << adjListIterator->first << " | ";
        for (vector<int>::iterator it = adjListIterator->second.begin(); it != adjListIterator->second.end(); it++ ){
            cerr << *it << ", ";
        }
        cerr << endl;
    }
     */
    cout << relays << endl;
    
}
