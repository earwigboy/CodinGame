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
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    getline(cin, temps);
    
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    int closest = 0;
    int start = 0;
    int pos = 0;
    int k = 0;
    bool done = false;
    string temp;
    while (k < n) {
        if (n == 1) {
            if (temps.size() > 0)
                closest = stoi(temps);
        } else {
            pos = temps.find(" ", start);
            if (pos != string::npos){
                temp = temps.substr(start,pos-start);
                start = pos + 1;
                
                if (k == 0)
                    closest = stoi(temp);
            } else {
                
                if (start < temps.size()){
                    temp = temps.substr(start,temps.size());
                }
                done = true;
            }
            if (!temp.empty()){
                if (abs(stoi(temp)) < abs(closest)){
                    closest = stoi(temp);
                } else if (abs(stoi(temp)) == abs(closest) && stoi(temp) > 0) {
                    closest = stoi(temp);
                }
            }
        }
        k++;
    }
    cout << closest << endl;
