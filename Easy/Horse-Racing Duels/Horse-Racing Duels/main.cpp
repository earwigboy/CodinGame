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
    int N;
    cin >> N; cin.ignore();
    vector<int> strengths(N);
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        strengths[i] = Pi;
    }
    
    sort (strengths.begin(), strengths.end());
    int minDiff;
    for (vector<int>::iterator it=strengths.begin(); it!=strengths.end(); ++it){
        int d = abs(*it - *(it+1));
        if (d < minDiff)
            minDiff = d;
    }
    
    
    cout << minDiff << endl;
}
