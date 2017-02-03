#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

string conwayString(string a){
    if (a.length() == 1)
        return "1"+a;
    
    string result;
    string head = a.substr(0,1);
    string tail = a.substr(1, a.length()-1);
    
    size_t count = tail.find_first_not_of(head);
    
    if (count != string::npos){
        string remainder = tail.substr(count, tail.length()-count);
        return to_string(count+1) + head += conwayString(remainder);
    } else {
        return to_string(tail.length()+1) + head;
    }
    //return result;
}
int main()
{
    int R;
    cin >> R; cin.ignore();
    int L;
    cin >> L; cin.ignore();
    
    string c = to_string(R);
    for (int i = 0; i < L; i++)
        c = conwayString(c);
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    cout << c << endl;
}
