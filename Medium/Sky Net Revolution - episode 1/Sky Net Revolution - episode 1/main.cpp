#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    
    cin >> N >> L >> E; cin.ignore();
    cerr << N << endl;
    cerr << L << endl;
    cerr << E << endl;
    int am[N][N];
    int e[E];
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            am[i][j] = 0;
        }
    }
    
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        am[N1][N2] = 1;
        am[N2][N1] = 1;
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        e[i] = EI;
    }
    
    // game loop
    while (1) {
        int SI;
        cin >> SI; cin.ignore();
        
        bool cut = false;
        int i = 0;
        
        for (int j = 0; j < E; j++){
            if (am[SI][e[j]] == 1) {
                cout << SI << " " << e[j] << endl;
                am[SI][e[j]] = 0;
                cut = true;
            }
        }
        if (!cut) {
            while (!cut && i < N) {
                if (am[SI][i] == 1) {
                    cout << SI << " " << i << endl;
                    am[SI][i] = 0;
                    cut = true;
                }
                i++;
            }
        }
    }
}
