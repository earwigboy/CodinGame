#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

vector<string> split(const char *str, char c = ';'){
    vector<string> result;
    do {
        const char *begin = str;
        while(*str != c && *str)
            str++;
        result.push_back(string(begin, str));
    } while (0 != *str++);
    
    return result;
}

double distance(double latA, double latB, double lonA, double lonB){
    return sqrt(pow(latA-latB,2)+pow(lonA-lonB,2));;
}

int main(){
    regex r(",");
    struct Defib{
        string id;
        string name;
        string address;
        string tel;
        double longitude;
        double latitude;
    };
    
    string LON; cin >> LON; cin.ignore();
    string LAT; cin >> LAT; cin.ignore();
    int N; cin >> N; cin.ignore();
    string location;
    double minDist = 0;
    
    for (int i = 0; i < N; i++) {
        string DEFIB;
        getline(cin, DEFIB); //cerr << DEFIB << endl;
        
        vector<string> attr = split(DEFIB.c_str());
        
        Defib d;
        d.id = attr[0];
        d.name = attr[1];
        d.address = attr[2];
        d.tel = attr[3];
        d.longitude = stod(regex_replace(attr[4],r,"."));
        d.latitude = stod(regex_replace(attr[5],r,"."));
        
        double dd = distance(d.latitude,
                             stod(regex_replace(LAT,r,".")),
                             d.longitude,
                             stod(regex_replace(LON,r,".")));
        if(dd < minDist || i == 0){
            minDist = dd;
            location = d.name;
        }
    }
    cout << location << endl;
}
