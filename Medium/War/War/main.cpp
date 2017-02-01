#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int cardValue(string *p){
    if(p->at(0)=='A') return 14;
    if(p->at(0)=='K') return 13;
    if(p->at(0)=='Q') return 12;
    if(p->at(0)=='J') return 11;
    if(p->at(0)=='1') return 10;
    
    return stoi(p->substr(0,1));
}

int compareCard(string *p1, string *p2){
    //cerr << "p1 value = " << cardValue(p1) << " p2 value = " << cardValue(p2) << endl;
    if(cardValue(p1) < cardValue(p2)) return -1;
    if(cardValue(p1) == cardValue(p2)) return 0;
    if(cardValue(p1) > cardValue(p2)) return 1;
    return 0;
}

void debugDeque(deque<string> *d){
    for(string n:*d){
        cerr << n << endl;
    }
}
int main()
{
    deque<string> p1,p2;
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    cerr << n << endl;
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        p1.push_back(cardp1);
    }
    
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    cerr << m << endl;
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
        p2.push_back(cardp2);
    }
    
    int gameRounds = 0;
    bool draw = false;
    vector<string> p1WarCards, p2WarCards;
    
    while (!p1.empty() && !p2.empty()){
        if (compareCard(&p1.front(),&p2.front()) < 0){
            for (int i = 0; i < p1WarCards.size(); i++)
                p2.push_back(p1WarCards[i]);
            p1WarCards.clear();
            p2.push_back(p1.front());
            
            for (int i = 0; i < p2WarCards.size(); i++)
                p2.push_back(p2WarCards[i]);
            p2WarCards.clear();
            p2.push_back(p2.front());

            p1.pop_front(); p2.pop_front();
            gameRounds++;

        } else if (compareCard(&p1.front(),&p2.front()) > 0){
            for (int i = 0; i < p1WarCards.size(); i++)
                p1.push_back(p1WarCards[i]);
            p1WarCards.clear();
            p1.push_back(p1.front());
            
            for (int i = 0; i < p2WarCards.size(); i++)
                p1.push_back(p2WarCards[i]);
            p2WarCards.clear();
            p1.push_back(p2.front());
            
            p1.pop_front(); p2.pop_front();
            gameRounds++;
        } else if (compareCard(&p1.front(), &p2.front()) == 0) {
            // WAR!
            cerr << " WAR!" << endl;
            if (p1.size() < 4 || p2.size() < 4){
                draw = true;
                break;
            }
            
            for (int i = 0; i < 4; i++){
                p1WarCards.push_back(p1.front());
                p1.pop_front();
                
                p2WarCards.push_back(p2.front());
                p2.pop_front();
            }
        }
    }
    if (draw)
        cout << "PAT" << endl;
    else {
        if (p1.empty()) cout << "2 " << gameRounds << endl;
        if (p2.empty()) cout << "1 " << gameRounds << endl;
    }
}
