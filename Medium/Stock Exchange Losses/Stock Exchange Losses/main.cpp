#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n;
    cin >> n; cin.ignore();
    int prices[n];
    int priceDiffs[n-1];
    int maxLosses[n-1];
    
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v; cin.ignore();
        prices[i] = v;
        if (i > 0){
            priceDiffs[i-1] = prices[i] - prices[i-1];
            
            if (i == 1)
                maxLosses[i-1] = priceDiffs[i-1];
            else
                maxLosses[i-1] = fmin(priceDiffs[i-1], maxLosses[i-2] + priceDiffs[i-1]);
        }
    }
    int maxLoss = 0;
    for (int i = 0; i < n-1; i++){
        maxLoss = fmin(maxLoss, maxLosses[i]);
    }
    
    cout << maxLoss << endl;
}
