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
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    cerr << "W = " << W << " H = " << H << endl;
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();
    
    
    // game loop
    int x0,x1,y0,y1,maxX,maxY,minX,minY;
    x0 = X0;
    y0 = Y0;
    x1 = y1 = 0;
    minX = minY = 0;
    maxX = W;
    maxY = H;
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();
        
        
        if (bombDir.compare("U") == 0){
            x1 = x0;
            y1 = minY;
            y0 = y0 - 1;
            maxY = y0;
        }
        
        if (bombDir.compare("D") == 0){
            x1 = x0;
            y1 = maxY;
            y0 = y0 + 1;
            minY = y0;
        }
        
        if (bombDir.compare("R") == 0){
            x1 = maxX;
            y1 = y0;
            x0 = x0 + 1;
            minX = x0;
        }
        
        if (bombDir.compare("L") == 0){
            x1 = minX;
            y1 = y0;
            x0 = x0 - 1;
            maxX = x0;
        }
        
        if (bombDir.compare("UR") == 0){
            x1 = maxX;
            y1 = minY;
            x0 = x0 + 1;
            y0 = y0 - 1;
            maxY = y0;
            minX = x0;
        }
        
        if (bombDir.compare("DR") == 0){
            x1 = maxX;
            y1 = maxY;
            x0 = x0 + 1;
            y0 = y0 + 1;
            minY = y0;
            minX = x0;
        }
        
        if (bombDir.compare("UL") == 0){
            x1 = minX;
            y1 = minY;
            x0 = x0 - 1;
            y0 = y0 - 1;
            maxY = y0;
            maxX = x0;
        }
        
        if (bombDir.compare("DL") == 0){
            x1 = minX;
            y1 = maxY;
            x0 = x0 - 1;
            y0 = y0 + 1;
            minY = y0;
            maxX = x0;
        }
        cerr << "x1 = " << x1 << " y1 = " << y1 << endl;
        
        x0 = x0+((x1-x0)/2);
        y0 = y0+((y1-y0)/2);
        
        
        // the location of the next window Batman should jump to.
        cout << x0 << " " << y0 << endl;
    }
}
