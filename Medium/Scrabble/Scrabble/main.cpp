#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>


using namespace std;


int main()
{
    map<char,int> weights;
    weights['e'] = 1;
    weights['a'] = 1;
    weights['i'] = 1;
    weights['o'] = 1;
    weights['n'] = 1;
    weights['r'] = 1;
    weights['t'] = 1;
    weights['l'] = 1;
    weights['s'] = 1;
    weights['u'] = 1;
    weights['d'] = 2;
    weights['g'] = 2;
    weights['b'] = 3;
    weights['c'] = 3;
    weights['m'] = 3;
    weights['p'] = 3;
    weights['f'] = 4;
    weights['h'] = 4;
    weights['v'] = 4;
    weights['w'] = 4;
    weights['y'] = 4;
    weights['k'] = 5;
    weights['j'] = 8;
    weights['x'] = 8;
    weights['q'] = 10;
    weights['z'] = 10;
    
    int N;
    cin >> N; cin.ignore();
    vector<string> dictionary(N);
    for (int i = 0; i < N; i++) {
        string W;
        getline(cin, W);
        dictionary[i] = W;
    }
    string LETTERS;
    getline(cin, LETTERS);
    char l[LETTERS.length()];
    for (int i = 0; i < LETTERS.length(); i++){
        l[i] = LETTERS[i];
    }
    
    sort(l,l + LETTERS.length());
    
    std::vector<char> v(14);
    std::vector<char>::iterator it;
    
    int maxScore = 0;
    string winningWord;
    for(auto & d:dictionary){
        int score = 0;
        for (auto & m:d){
            score += weights[m];
        }
        if (score > maxScore){
            char dItem[d.length()];
            for(int i = 0; i < d.length(); i++)
                dItem[i] = d[i];
            
            sort(dItem, dItem + d.length());
            
            it=set_intersection (l,l + LETTERS.length(), dItem, dItem + d.length(), v.begin());
            
            v.resize(it-v.begin());
            
            if (v.size() == d.length()){
                maxScore = score;
                winningWord = d;
            }
        }
    }
    
    cout << winningWord << endl;
}
