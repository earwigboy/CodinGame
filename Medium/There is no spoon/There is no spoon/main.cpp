#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/
int main()
{
    char sp = {' '};
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    int grid[width][height];
    
    for (int i = 0; i < height; i++) {
        string line; // width characters, each either 0 or .
        cerr << line << endl;
        getline(cin, line);
        for (int j = 0; j < width; j++){
            if (line.at(j) == '0')
                grid[j][i] = 0; // node
            else
                grid[j][i] = 1; // empty cell
        }
    }

    int x,y,rx, ry, bx, by;
    x = y = rx = ry = bx = by = -1;
    for (int i = 0; i < height; i++) {
        y = i;
        for (int j = 0; j < width; j++) {
            if (grid[j][i] == 0){
                x = j;
                rx = j + 1; ry = i;
                // find nearest neighbour to the right
                bool nfound = false;
                while (rx < width && !nfound) {
                    if (grid[rx][ry] == 0) {
                        nfound = true;
                    } else {
                        rx++;
                    }
                }
                if (!nfound) {
                    rx = -1; ry = -1;
                }
                
                bx = j; by = i + 1;
                // find nearest neighbour below
                nfound = false;
                while (by < height && !nfound) {
                    if (grid[bx][by] == 0) {
                        nfound = true;
                    } else {
                        by++;
                    }
                }
                if (!nfound) {
                    bx = -1; by = -1;
                }
                cout << x << sp << y << sp << rx << sp << ry << sp << bx << sp << by << sp << endl;
            }
            
        }
        
    }
    
    
    // Three coordinates: a node, its right neighbor, its bottom neighbor
    //cout << "0 0 1 0 0 1" << endl;
}
