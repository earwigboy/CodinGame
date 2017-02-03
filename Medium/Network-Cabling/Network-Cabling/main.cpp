#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


int main()
{
    int N;
    cin >> N; cin.ignore();
    vector<long long int> yValues;
    vector<long long int> xValues;
    
    for (int i = 0; i < N; i++) {
        int X;
        int Y;
        
        cin >> X >> Y; cin.ignore();
        yValues.push_back(Y);
        xValues.push_back(X);
    }
    nth_element(yValues.begin(), yValues.begin() + yValues.size()/2, yValues.end());
    long long int median = yValues[yValues.size()/2];
    long long int minX = *min_element(xValues.begin(), xValues.end());
    long long int maxX = *max_element(xValues.begin(), xValues.end());
    
    long long int cableLength = maxX - minX;
    
    for (int i = 0; i < N; i++) {
        cableLength += abs(median - yValues[i]);
    }
    cout << cableLength << endl;
}
