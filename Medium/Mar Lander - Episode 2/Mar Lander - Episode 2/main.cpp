#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
typedef struct {int x; int y;} Coord;
const float GRAVITY = 3.711;
const float DEGREES_PER_RADIAN = 57.2958f;
const Coord MAX_LANDING_SPEED {20,-30};
const int RIGHT = -1;
const int LEFT = 1;
const int TARGET_SPEED_TOLERANCE = 10;
const int TARGET_X_TOLERANCE = 10;
int main()
{
    int surfaceN; // the number of points used to draw the surface of Mars.
    cin >> surfaceN; cin.ignore();
    Coord surface[surfaceN], landingSpot, maxPoint;
    
    for (int i = 0; i < surfaceN; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
        surface[i].x = landX; surface[i].y = landY;
        
        // Find the landing spot
        if (i > 0 && surface[i].y == surface[i-1].y){
            landingSpot.x = (surface[i].x + surface[i-1].x)/2;
            landingSpot.y = landY;
        }
        // Find the max point
        if (landY > maxPoint.y)
            maxPoint.y = landY; maxPoint.x = landX;
        
    }
    
    bool landing = false;
    bool initiate = true;
    
    // game loop
    while (1) {
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();
        
        double r;
        if (landing){
            r = 0;
            if (vSpeed < MAX_LANDING_SPEED.y)
                power = 4;
            else
                power = 0;
        } else {
            double dx = landingSpot.x - X;
            
            if (initiate && abs(hSpeed) <= 40){
                if (dx == 0)
                    r = 0;
                else {
                    r = (dx < 0)? 45 : -45;
                }
            } else {
                initiate = false;
                if (dx == 0) dx = 1;
                
                double xa = -(hSpeed*hSpeed) / (2 * dx);
                
                r = round(atan(power/xa) * 180.0f / M_PI);
                
                if (xa < 0) r += 180;
                
                // going too fast
                if (signbit(dx) != signbit(hSpeed)) r = 90 - r;
                
                r -= 90;
            }
            
            // keep the height right
            if (vSpeed > 0 && Y > landingSpot.y)
                power = 0;
            else
                power = 4;
            
            if (abs(hSpeed) <= TARGET_SPEED_TOLERANCE && abs(dx) < TARGET_X_TOLERANCE) landing = true;
        }
        if (r > 45) r = 45;
        if (r < -45) r = -45;
        
        cout << round(r) << " " << power << endl;
    }
}
