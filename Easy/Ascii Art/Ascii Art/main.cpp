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
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);
    transform(T.begin(), T.end(), T.begin(), ::toupper);
    
    char ascii[L*27][H];
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ?";
    
    for (int i = 0; i < H; i++) {
        string ROW;
        getline(cin, ROW);
        //cout << ROW << endl;
        for (int j = 0; j < L*27; j++){
            ascii[j][i] = ROW.at(j);
        }
    }
    
    
    
    for (int i = 0; i < H; i++) {
        for (int k = 0; k < T.size(); k++){
            int position = alphabet.find(T.at(k));
            if(position == string::npos) {
                position = alphabet.find("?");
                //cerr << "not found. new position = " << position << endl;
            }
            for (int j = position*L; j < position*L + L; j++) {
                cout << ascii[j][i] ;
            }
        }
        cout << endl;
    }
    
    
    //cout << c << endl;
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    //cout << "answer" << endl;
}
