#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // Number of elements which make up the association table.
    cin >> N; cin.ignore();
    int Q; // Number Q of file names to be analyzed.
    cin >> Q; cin.ignore();
    
    unordered_map<string, string> u;
    vector<string> f;
    
    for (int i = 0; i < N; i++) {
        string EXT; // file extension
        string MT; // MIME type.
        cin >> EXT >> MT; cin.ignore();
        transform(EXT.begin(), EXT.end(), EXT.begin(), ::tolower);
        u[EXT] = MT;
        cerr << "ext: " << EXT << " mt: " << MT << endl;
    }
    for (int i = 0; i < Q; i++) {
        string FNAME; // One file name per line.
        getline(cin, FNAME);
        transform(FNAME.begin(), FNAME.end(), FNAME.begin(), ::tolower);
        f.push_back(FNAME);
        cerr << "fn: " << FNAME << endl;
    }
    
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    
    // For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
    for(vector<string>::iterator it = f.begin(); it != f.end(); ++it) {
        unsigned long period = it->rfind(".");
        if (period != string::npos){
            string extension = it->substr(period + 1,it->length());
            cerr << "f ext: " << extension << endl;
            unordered_map<std::string,string>::const_iterator got = u.find (extension);
            
            if ( got == u.end() )
                std::cout << "UNKNOWN" << endl;
            else
                std::cout << got->second << endl;
        } else {
            std::cout << "UNKNOWN" << endl;
        }
        
    }
    //cout << "UNKNOWN" << endl;
}
