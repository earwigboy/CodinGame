#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <list>
#include <cmath>
#include <fstream>

using namespace std;

struct Point {
    int x;
    int y;
    
    bool operator<(const Point &p)  const {
        return x < p.x || (x == p.x && y < p.y);
    }
    
    bool operator==(const Point &p) {
        bool r = x == p.x && y == p.y;
        return r;
    }
};
/*
 function bfs(node start_position)
     add start_position to the queue
     while the queue is not empty
         pop a node off the queue, call it "item"
         color item on the graph // make sure we don't search it again
         generate the 8 successors to item
         set the parent of each successor to "item" // this is so we can backtrack our final solution
         for each successor
             if the successor is the goal node, end the search
             else, push it to the back of the queue // So we can search this node
         end
     end
     
     if we have a goal node, look at its ancestry to find the path (node->parent->parent->parent..., etc)
     if not, the queue was empty and we didn't find a path :^\
 end
 **/

struct Node {
    Point position;
    Node* parent;
    float f, g, h;
};

class Node1 {
public:
    Node1();
    Node1(Point pos, float f1, float g1, float h1);
    Node1(const Node1 &n);
    ~Node1();
private:
    Point position;
    float f, g, h;
    Node1* parent;
};
Node1::Node1(){
    position = {-1,-1};
    f = 0.0;
    g = 0.0;
    h = 0.0;
    
}
Node1::Node1(Point pos, float f1, float g1, float h1){
    position = pos;
    f = f1;
    g = g1;
    h = h1;
}

Node1::Node1(const Node1 &n) {
    f = n.f;
    g = n.g;
    h = n.h;
    parent = new Node1;
    *parent = *n.parent;
}
bool minf(Node a, Node b) { return a.f < b.f; }
bool minfSamePosition(Node a, Node b) { return a.position == b.position && a.f < b.f; }

enum KirkState{
    EXPLORING,
    GOING_TO_CONTROL_ROOM,
    GOING_TO_TELEPORTER
};

bool isValidPosition(Point p , char** g, int gRows, int gCols){
    
    if (p.x >= 0 && p.x < gCols
        && p.y >= 0 && p.y < gRows
        && g[p.x][p.y] != '#') {
        //cerr << "char = " << g[p.x][p.y] << endl;
        return true;
    } else {
        return false;
    }
}

bool isGoal(Point p, Point goal, char** g){
    if (p == goal || g[p.x][p.y] == g[goal.x][goal.y])
        return true;
    else
        return false;
}

Point findControlRoom(char** g, int gRows, int gCols) {
    for (int i = 0; i < gCols; i++){
        for (int j = 0; j < gRows; j++){
            if (g[i][j] == 'C') {
                return {i,j};
            }
        }
    }
    return {-1,-1};
}
/**
Node bfs(Node startPosition, char** g, bool** visited, int gRows, int gCols){
    deque<Node> dq;
    dq.push_back(startPosition);
    while(!dq.empty()){
        Node item = dq.front();
        if (!visited[item.position.x][item.position.y]){
            visited[item.position.x][item.position.y] = true;
            for (int i = -1; i <= 1; i++){
                for (int j = 1; j > 1; j--){
                    Point ip = {item.position.x + i, item.position.y + j};
                    if (isValidPosition(ip, g, gRows, gCols)) {
                        Node n;
                        n.position = ip;
                        n.parent = &item;
                        if (isGoal(n.position, g,'C')) {
                            return n;
                        } else {
                            dq.push_back(n);
                        }
                    }
                    
                }
            }
        }
    }
    return startPosition;
}
*/


float getDistance(Point a, Point b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

Point findNearest(char** g, int gRows, int gCols, char target, Point position){
    float nearest = 999.0f;
    Point nearestPoint = {-1, -1};
    for (int i = 0; i < gCols; i++){
        for (int j = 0; j < gRows; j++){
            if (g[i][j] == target) {
                float f = getDistance({i,j}, position);
                if (nearest > f ){
                    nearest = f;
                    nearestPoint.x = i;
                    nearestPoint.y = j;
                }
            }
        }
    }
    return nearestPoint;
}

Point findNextPosition(Node p, Point a){
    if (p.parent->parent == nullptr) {
        return p.position;
    } else {
        findNextPosition(*p.parent, a);
    }
    return {-1,-1};
}

/*
 // A*
 initialize the open list
 initialize the closed list
 put the starting node on the open list (you can leave its f at zero)
 
 while the open list is not empty
     find the node with the least f on the open list, call it "q"
     pop q off the open list
     generate q's 8 successors and set their parents to q
     for each successor
         if successor is the goal, stop the search
         successor.g = q.g + distance between successor and q
         successor.h = distance from goal to successor
         successor.f = successor.g + successor.h
         
         if a node with the same position as successor is in the OPEN list \
             which has a lower f than successor, skip this successor
         if a node with the same position as successor is in the CLOSED list \
             which has a lower f than successor, skip this successor
         otherwise, add the node to the open list
     end
     push q on the closed list
 end
 */

Node aStar(char** g, int gRows, int gCols, Point sp, Point goalPos) {
    list<Node> openList;
    list<Node> closedList;
    list<Node>::iterator it;
    Node sn;
    sn.position = sp;
    sn.f = 0.0;
    openList.push_back(sn);
    
    while (!openList.empty()){
        it = min_element(openList.begin(), openList.end(), minf);
        Node q = Node();
        
        openList.erase(it);
        
        for (int i = -1; i <= 1; i++){
            for (int j = 1; j >= -1; j--){
                if (i==0 && j==0)
                    break;
                Node successor = Node();
                successor.parent = &q;
                successor.position.x = q.position.x + i;
                successor.position.y = q.position.y + j;
                if (isValidPosition(successor.position, g, gRows, gCols)) {
                    if (isGoal(successor.position, goalPos, g)){
                        return successor;
                    } else {
                        float distance_s_q = getDistance(q.position,successor.position);
                        float distance_s_g = getDistance(goalPos,successor.position);
                        successor.g = q.g + distance_s_q;
                        successor.h = distance_s_g;
                        successor.f = successor.g + successor.h;
                        
                        bool addNodeToList = true;
                        list<Node>::iterator openIt = find_if(openList.begin(), openList.end(),[successor](Node n){return n.position == successor.position;});
                        if (openIt != openList.end()){
                            if (openIt->f < successor.f) {
                                addNodeToList = false;
                            }
                        }
                        
                        
                        list<Node>::iterator closedIt = find_if(closedList.begin(), closedList.end(),[successor](Node n){return n.position == successor.position;});
                        if (closedIt != closedList.end() && closedIt->f < successor.f)
                            addNodeToList = false;
                        
                        if (addNodeToList)
                            openList.push_back(successor);
                        
                    }
                }

            }
        }
        closedList.push_back(q);
    }
    return {-1,-1};
}


void printGrid(char** g, int rows, int cols, Point kirk){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (kirk.x == j && kirk.y == i)
                cerr << 'K';
            else
                cerr << g[j][i];
        }
        cerr << '\n';
    }
}

int main()
{
    fstream infile("input");
    
    int R; // number of rows.
    int C; // number of columns.
    int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    infile >> R >> C >> A; infile.ignore();
    
    // main grid
    char** grid = new char*[C];
    for (int i = 0; i < C; i++)
        grid[i] = new char[R];
    
    // visited grid
    bool** visited = new bool*[C];
    for (int i = 0; i < C; i++)
        visited[i] = new bool[R];
    
    Point controlRoom;
    bool controlRoomFound = false;
    Point target;
    int kirkState = EXPLORING;
    
    // game loop
    while (1) {
        int KR; // row where Kirk is located.
        int KC; // column where Kirk is located.
        infile >> KR >> KC; infile.ignore();
        Point kirk = {KC,KR};
        for (int i = 0; i < R; i++) {
            string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            infile >> ROW; infile.ignore();
            for (int j = 0; j < C; j++){
                grid[j][i] = ROW[j];
            }
        }
        
        printGrid(grid, R, C, kirk);
        
        // Find control room if we can
        if (!controlRoomFound){
            controlRoom = findNearest(grid, R, C, 'C', kirk);
            
            if (controlRoom.x != -1 && controlRoom.y != -1) {
                controlRoomFound = true;
                target = controlRoom;
            }
        }
        
        
        
        if (controlRoomFound && kirkState == EXPLORING){
            cerr << "GOING TO CONTROL ROOM." << endl;
            kirkState = GOING_TO_CONTROL_ROOM;
        }
        
        if (kirkState == GOING_TO_CONTROL_ROOM && grid[kirk.x][kirk.y] == 'C') {
            cerr << "GOING TO TELEPORTER." << endl;
            kirkState = GOING_TO_TELEPORTER;
        }
        
        switch (kirkState) {
            case EXPLORING:
                target = findNearest(grid, R, C, '?', kirk);
                break;
            case GOING_TO_CONTROL_ROOM:
                target = findNearest(grid, R, C, 'C', kirk);
                break;
            case GOING_TO_TELEPORTER:
                target = findNearest(grid, R, C, 'T', kirk);
                break;
            default:
                break;
        }
        
        Node nextNode = aStar(grid, R, C, kirk, target);
        Point nextPosition = findNextPosition(nextNode, kirk);
        // Should have a target by now, move towards it.
        // priority is right, left, up, down
        string moveDirection = "NA";
        
        if (nextPosition.x > kirk.x) {
            moveDirection = "RIGHT";
        } else if (nextPosition.x < kirk.x) {
            moveDirection = "LEFT";
        } else if (nextPosition.y > kirk.y) {
            moveDirection = "UP";
        } else if (nextPosition.y < kirk.y) {
            moveDirection = "DOWN";
        }
        
        cout << moveDirection << endl; // Kirk's next move (UP DOWN LEFT or RIGHT).
    }
}
