#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
struct Node {
    int item;
    struct Node *firstchild;
    struct Node *nextsibling;
};

void printTree(Node *n, ostream & out) {
    if (n != nullptr) {
        printTree(n->nextsibling, out);
        out << n->item << endl;
        printTree(n->firstchild, out);
    }
}

Node * find(Node *root, int item) {
    if (root != nullptr) {
        if (root->item == item)
            return root;
        else {
            Node *sn = find(root->nextsibling, item);
            if (sn == nullptr) {
                sn = find(root->firstchild, item);
            }
            return sn;
        }
    } else {
        return nullptr;
    }
}


int maxHeight(Node *n){
    if (n == nullptr) return 0;
    int left = maxHeight(n->firstchild);
    int right = maxHeight(n->nextsibling);
    
    return (left > right) ? left + 1 : right + 1;
}

void addSibling(Node *n, int a){
    if (n->nextsibling == nullptr)
        n->nextsibling = new Node{a, nullptr,nullptr};
    else
        addSibling(n->nextsibling, a);
}

void addItem(Node *parent, int a, int b) {
    Node *n = find(parent,a);
    
    if (n->firstchild == nullptr)
        n->firstchild = new Node{b,nullptr,nullptr};
    else
        addSibling(n->firstchild,b);
    
    return;
}

int main()
{
    int n; // the number of adjacency relations
    cin >> n; cin.ignore();
    cerr << n << endl;
    Node *root = new Node{-1,nullptr,nullptr};
    for (int i = 0; i < n; i++) {
        
        int xi; // the ID of a person which is adjacent to yi
        int yi; // the ID of a person which is adjacent to xi
        cin >> xi >> yi; cin.ignore();
        
        if (i == 0) {
            root->item = xi;
        }
        addItem(root, xi, yi);
        
        cerr << xi << " " << yi << endl;
    }
    
    // The minimal amount of steps required to completely propagate the advertisement
    //cout << "answer" << endl;
    printTree(root, cerr);
    cerr << "Height = " << maxHeight(root) << endl;
    /*
    Node *root = new Node{12,nullptr,nullptr};
    //printTree(root);
    addItem(root, 12, 25);
    addItem(root, 12, 24);
    addItem(root, 25, 26);
    addItem(root, 25, 270);
    //addSibling(root, 25);
    printTree(root, cerr);
     */
    
}
