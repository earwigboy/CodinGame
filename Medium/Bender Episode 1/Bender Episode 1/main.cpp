#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


struct Point {
    int x;
    int y;
    
    bool operator<(const Point &p)  const {
        return x < p.x || (x == p.x && y < p.y);
    }
    
    bool operator==(const Point &p) {
        return x == p.x && y == p.y;
    }
};

enum benderStates {
    south,
    east,
    north,
    west,
    stop
};

struct Bender {
    Point position;
    Point nextPosition;
    bool breakerMode;
    bool inverted;
    bool blocked;
    unsigned int direction = south;
    unsigned int defaultDirection = south;
    unsigned int inverseDefaultDirection = west;
    
    bool operator==(const Bender &b) {
        //return x == p.x && y == p.y;
        return nextPosition == b.nextPosition
        && breakerMode == b.breakerMode
        && inverted    == b.inverted
        && direction   == b.direction;
    }
};

struct TableEntry {
    unsigned int  current_state_id;
    unsigned char transition_letter;
    unsigned int  next_state_id;
};

vector<TableEntry> obstacleTable = {
    {south, '#', east},
    {east,  '#', north},
    {north, '#', west},
    {west,  '#', south},
    {south, 'X', east},
    {east,  'X', north},
    {north, 'X', west},
    {west,  'X', south},
    {south, 'N', north},
    {east,  'N', north},
    {north, 'N', north},
    {west,  'N', north},
    {south, 'S', south},
    {east,  'S', south},
    {north, 'S', south},
    {west,  'S', south},
    {south, 'E', east},
    {east,  'E', east},
    {north, 'E', east},
    {west,  'E', east},
    {south, 'W', west},
    {east,  'W', west},
    {north, 'W', west},
    {west,  'W', west},
    {south, ' ', south},
    {east,  ' ', east},
    {north, ' ', north},
    {west,  ' ', west}
};



vector<TableEntry> inverseObstacleTable = {
    {west,  '#', north},
    {north, '#', east},
    {east,  '#', south},
    {south, '#', west},
    {west,  'X', north},
    {north, 'X', east},
    {east,  'X', south},
    {south, 'X', west},
    {south, 'N', north},
    {east,  'N', north},
    {north, 'N', north},
    {west,  'N', north},
    {south, 'S', south},
    {east,  'S', south},
    {north, 'S', south},
    {west,  'S', south},
    {south, 'E', east},
    {east,  'E', east},
    {north, 'E', east},
    {west,  'E', east},
    {south, 'W', west},
    {east,  'W', west},
    {north, 'W', west},
    {west,  'W', west},
    {south, ' ', south},
    {east,  ' ', east},
    {north, ' ', north},
    {west,  ' ', west}
};

struct directionEntry {
    unsigned int direction_state;
    Point transition;
};

static const vector<directionEntry> movement {
    {south, {0, 1}},
    {east,  {1, 0}},
    {north, {0, -1}},
    {west,  {-1, 0}}
};


bool blocked(char c){
    if (c == 'X' || c == '#')
        return true;
    else
        return false;
}

void printGrid(char** g, int rows, int cols, Point bender) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            if (j == bender.x && i == bender.y)
                cerr << "b";
            else
                cerr << g[j][i];
        }
        cerr << '\n';
    }
}

string getDirectionString(unsigned int const& s){
    if (s == south)     return "SOUTH";
    if (s == east)      return "EAST";
    if (s == north)     return "NORTH";
    if (s == west)      return "WEST";
    return "UNKNOWN";
}

unsigned int getNextDirection(unsigned int direction, char tile, bool inverted){
    if (inverted) {
        for (auto & d : inverseObstacleTable){
            if (d.current_state_id == direction && d.transition_letter == tile)
                return d.next_state_id;
        }
    } else {
        for (auto & d : obstacleTable){
            if (d.current_state_id == direction && d.transition_letter == tile)
                return d.next_state_id;
        }
    }
    
    return direction;
}

Point getMovement(unsigned int direction){
    for (auto & d : movement){
        if (d.direction_state == direction)
            return d.transition;
    }
    
    return {0,0};
}

int main()
{
    int L = 1; // lines
    int C = 1; // columns
    
    Bender bender = {};
    cin >> L >> C; cin.ignore();
    
    // main grid
    char** grid = new char*[C];
    for (int i = 0; i < C; i++)
        grid[i] = new char[L];
    
    vector<Point> teleports;    // holds teleport positions.
    vector<string> moves;       // holds moves to be output at then.
    map<Point,Bender> gridHistory;
    
    // initialise the grid
    for (int i = 0; i < L; i++) {
        string row;
        getline(cin, row);
        for(int j = 0; j < row.length(); j++){
            grid[j][i] = row[j];
            if (grid[j][i] == '@'){
                bender.position.x = j; bender.position.y = i;
            }
            if (grid[j][i] == 'T'){
                teleports.push_back({j,i});
            }
            
        }
    }
    
    bender.nextPosition.x = bender.position.x;
    bender.nextPosition.y = bender.position.y;
    bool suicide = false;
    bool loop    = false;
    
    char tile;
    
    while (!suicide && !loop) {
        printGrid(grid,L,C,bender.position);
        
        Point movement = getMovement(bender.direction);
        bender.nextPosition.x = bender.position.x + movement.x;
        bender.nextPosition.y = bender.position.y + movement.y;
        
        tile = grid[bender.nextPosition.x][bender.nextPosition.y];
        if (tile == 'X' && bender.breakerMode){
            tile = ' ';
            grid[bender.nextPosition.x][bender.nextPosition.y] = tile;
            gridHistory.clear();
        }
        if (blocked(tile)){
            if (!bender.blocked){
                bender.direction = bender.inverted ? bender.inverseDefaultDirection : bender.defaultDirection;
                bender.blocked = true;
            } else {
                bender.direction = getNextDirection(bender.direction, tile, bender.inverted);
            }
        } else {
            bender.position.x = bender.nextPosition.x;
            bender.position.y = bender.nextPosition.y;
            bender.blocked = false;
            Point p = {bender.position.x,bender.position.y};
            Bender b = {};
            if (gridHistory[p] == bender)
                loop = true;
            else {
                gridHistory[p].direction    = bender.direction;
                gridHistory[p].breakerMode  = bender.breakerMode;
                gridHistory[p].inverted     = bender.inverted;
                gridHistory[p].nextPosition = bender.nextPosition;
            }
            moves.push_back(getDirectionString(bender.direction));
            
            bender.direction = getNextDirection(bender.direction, tile, bender.inverted);
        }
        
        if (tile == '$')
            suicide = true;
        if (tile == 'I')
            bender.inverted = !bender.inverted;
        if (tile == 'B')
            bender.breakerMode = !bender.breakerMode;
        if (tile == 'T'){
            for(auto & t:teleports){
                if (t.x != bender.nextPosition.x || t.y != bender.nextPosition.y){
                    bender.position.x = t.x;
                    bender.position.y = t.y;
                    break;
                }
            }
        }
    }
    
    if (!loop){
        for (auto & m : moves)
            cout << m << endl;
    } else {
        cout << "LOOP" << endl;
    }
    
    //printGrid(grid,L,C);
    //cerr << "starting point = " << bender.x << ", " << bender.y << endl;
    
    
    
    //cout << "answer" << endl;
}
