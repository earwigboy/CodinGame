#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
const int LEFT = 0;
const int RIGHT = 1;
const int TOP = 2;
const int BLOCKED = 4;
 */

int roomTypes[14][3];
enum direction {
    LEFT,
    RIGHT,
    TOP,
    BLOCKED
};

vector<string> split(const char *str, char c = ' '){
    vector<string> result;
    do {
        const char *begin = str;
        while(*str != c && *str)
            str++;
        result.push_back(string(begin, str));
    } while (0 != *str++);
    
    return result;
}

direction getDirection(string const& s){
    if (s == "LEFT") return LEFT;
    if (s == "RIGHT") return RIGHT;
    if (s == "TOP") return TOP;
    return BLOCKED;
}

void initRoomTypes(){
    // Room types indexed by their entrance and store the next entrance
    // Type 0
    roomTypes[0][LEFT] = BLOCKED;
    roomTypes[0][RIGHT] = BLOCKED;
    roomTypes[0][TOP] = BLOCKED;
    
    // Type 1
    roomTypes[1][LEFT] = TOP;
    roomTypes[1][RIGHT] = TOP;
    roomTypes[1][TOP] = TOP;
    
    // Type 2
    roomTypes[2][LEFT] = LEFT;
    roomTypes[2][RIGHT] = RIGHT;
    roomTypes[2][TOP] = BLOCKED;
    
    // Type 3
    roomTypes[3][LEFT] = BLOCKED;
    roomTypes[3][RIGHT] = BLOCKED;
    roomTypes[3][TOP] = TOP;
    
    // Type 4
    roomTypes[4][LEFT] = BLOCKED;
    roomTypes[4][RIGHT] = TOP;
    roomTypes[4][TOP] = RIGHT;
    
    // Type 5
    roomTypes[5][LEFT] = TOP;
    roomTypes[5][RIGHT] = BLOCKED;
    roomTypes[5][TOP] = LEFT;
    
    // Type 6
    roomTypes[6][LEFT] = LEFT;
    roomTypes[6][RIGHT] = RIGHT;
    roomTypes[6][TOP] = BLOCKED;
    
    // Type 7
    roomTypes[7][LEFT] = BLOCKED;
    roomTypes[7][RIGHT] = TOP;
    roomTypes[7][TOP] = TOP;
    
    // Type 8
    roomTypes[8][LEFT] = TOP;
    roomTypes[8][RIGHT] = TOP;
    roomTypes[8][TOP] = BLOCKED;
    
    // Type 9
    roomTypes[9][LEFT] = TOP;
    roomTypes[9][RIGHT] = BLOCKED;
    roomTypes[9][TOP] = TOP;
    
    // Type 10
    roomTypes[10][LEFT] = BLOCKED;
    roomTypes[10][RIGHT] = BLOCKED;
    roomTypes[10][TOP] = RIGHT;
    
    // Type 11
    roomTypes[11][LEFT] = BLOCKED;
    roomTypes[11][RIGHT] = BLOCKED;
    roomTypes[11][TOP] = LEFT;
    
    // Type 12
    roomTypes[12][LEFT] = BLOCKED;
    roomTypes[12][RIGHT] = TOP;
    roomTypes[12][TOP] = BLOCKED;
    
    // Type 13
    roomTypes[13][LEFT] = TOP;
    roomTypes[13][RIGHT] = BLOCKED;
    roomTypes[13][TOP] = BLOCKED;
}

int main()
{
    initRoomTypes();
    
    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();
    int grid[W][H];
    for (int i = 0; i < H; i++) {
        string LINE; // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
        getline(cin, LINE);
        cerr << LINE << endl;
        
        vector<string> rooms = split(LINE.c_str());
        for (int j = 0; j < W; j++)
            grid[j][i] = stoi(rooms[j]);
        
    }
    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    cin >> EX; cin.ignore();
    
    // game loop
    while (1) {
        int XI;
        int YI;
        string POS;
        cin >> XI >> YI >> POS; cin.ignore();
        
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        int type = grid[XI][YI];
        cerr << "type = " << type << endl;
        if (roomTypes[type][getDirection(POS)] == LEFT)
            XI++;
        if (roomTypes[type][getDirection(POS)] == RIGHT)
            XI--;
        if (roomTypes[type][getDirection(POS)] == TOP)
            YI++;
        
        // One line containing the X Y coordinates of the room in which you believe Indy will be on the next turn.
        cout << XI << " " << YI << endl;
    }
}
