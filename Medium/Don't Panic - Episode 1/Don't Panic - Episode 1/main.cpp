#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string BLOCK  = "BLOCK";
const string WAIT   = "WAIT";
const string LEFT   = "LEFT";
const string RIGHT  = "RIGHT";

int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    
    struct elevator {int fl; int position; bool blocked;} elevators[nbElevators];
    
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        
        elevators[i].fl = elevatorFloor;
        elevators[i].position = elevatorPos;
    }
    
    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();
        
        string action = WAIT;
        for (int i = 0; i < nbElevators; i++) {
            if (cloneFloor == elevators[i].fl){
                if ((clonePos > elevators[i].position && direction.find(RIGHT) != string::npos)
                    || (clonePos < elevators[i].position && direction.find(LEFT) != string::npos)){
                    action = BLOCK;
                    elevators[cloneFloor].blocked = true;
                    break;
                }
            }
        }
        
        if (clonePos == width - 1 || clonePos == 1) action = BLOCK;
        if (cloneFloor == exitFloor && exitPos < clonePos && direction.find(RIGHT) != string::npos) action = BLOCK;
        if (cloneFloor == exitFloor && exitPos > clonePos && direction.find(LEFT) != string::npos) action = BLOCK;
        cout << action << endl; // action: WAIT or BLOCK
    }
}
