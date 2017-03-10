#include <iostream>
#include <list>
#include <cmath>
#include <fstream>
#include <deque>
#include <algorithm>

class Point {
    
public:
    Point();
    
    Point(int x, int y) : x_val(x), y_val(y) {}
    
    virtual ~Point() {
        
    }
    
    Point(const Point &p);
    
    bool operator<(const Point &p) const;
    
    bool operator==(const Point &p);
    
    int x();
    
    int y();
    
    void setX(int x);
    
    void setY(int y);
    
private:
    int x_val, y_val;
};

Point::Point() {
    x_val = -1;
    y_val = -1;
}

Point::Point(const Point &p) {
    x_val = p.x_val;
    y_val = p.y_val;
}


bool Point::operator<(const Point &p) const {
    return x_val < p.x_val || (x_val == p.x_val && y_val < p.y_val);
}

bool Point::operator==(const Point &p) {
    return x_val == p.x_val && y_val == p.y_val;
}

int Point::x() {
    return x_val;
}

int Point::y() {
    return y_val;
}

void Point::setX(int x) {
    x_val = x;
}

void Point::setY(int y) {
    y_val = y;
}

class Node {
public:
    virtual ~Node();
    
    Node();
    
    Node(float f, float g, float h, Node *parent, Point position);
    
    Node(const Node &n);
    
    Node(Node* n);
    
    friend std::ostream &operator<<(std::ostream &os, const Node &node);
    
    Node &operator=(const Node &n);
    
    float getF();
    
    void setF(float f);
    
    float getG();
    
    void setG(float g);
    
    float getH();
    
    void setH(float h);
    
    Point getPosition();
    
    void setPosition(Point p);
    
    Point findNextPosition();
    
    int getNumberOfSteps();
    
    std::deque<Point> getRoute();
    
private:
    float f, g, h;
    Point position;
    Node *parent;
};

Node::Node(float f, float g, float h, Node *parent, Point point) : f(f), g(g), h(h), parent(parent), position(point) {}

Node::Node() {
    f = 0.0f;
    g = 0.0f;
    h = 0.0f;
    position = {-1, -1};
    parent = nullptr;
}

Node::~Node() {
    if (parent != nullptr)
        delete parent;
}

Node::Node(const Node &n) {
    f = n.f;
    g = n.g;
    h = n.h;
    position = n.position;
    if (n.parent != nullptr)
        parent = new Node(*n.parent);
    else
        parent = nullptr;
}

Node::Node(Node* n){
    f = n->getF();
    g = n->getG();
    h = n->getH();
    position = n->getPosition();
    
    if (n->parent != nullptr)
        parent = new Node(*n->parent);
    else
        parent = nullptr;
}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "f: " << node.f << " parent: " << node.parent->f;
    return os;
}

Node &Node::operator=(const Node &n) {
    if (this == &n) {
        return *this;
    }
    
    f = n.f;
    g = n.g;
    h = n.h;
    
    position = n.position;
    
    //*parent = *n.parent;
    if (n.parent != nullptr)
        parent = new Node(*n.parent);
    else
        parent = nullptr;
    
    return *this;
}

float Node::getF() {
    return this->f;
}

void Node::setF(float v) {
    this->f = v;
}

float Node::getG() {
    return this->g;
}

void Node::setG(float g) {
    this->g = g;
}

float Node::getH() {
    return this->h;
}

void Node::setH(float h) {
    this->h = h;
}

void Node::setPosition(Point p) {
    this->position = p;
}

Point Node::getPosition() {
    return this->position;
}

Point Node::findNextPosition() {
    
    Node *pnode = parent;
    if (pnode->parent == nullptr){
        return position;
    }
    while (pnode->parent->parent != nullptr) {
        pnode = pnode->parent;
        
    }
    return pnode->position;
}

int Node::getNumberOfSteps(){
    Node *pnode = parent;
    if (pnode == nullptr)
        return 0;
    
    int r = 0;
    while (pnode->parent != nullptr){
        r++;
        pnode = pnode->parent;
    }
    return r;
    
}

std::deque<Point> Node::getRoute(){
    std::deque<Point> route;
    Node *n = parent;
    route.push_back(position);
    while (n != nullptr && n->parent != nullptr){
        route.push_back(n->getPosition());
        n = n->parent;
    }
    return route;
}


enum KirkState {
    EXPLORING,
    GOING_TO_CONTROL_ROOM,
    GOING_TO_TELEPORTER
};

bool isValidPosition(Point p, char **g, int rows, int cols, char goalChar) {
    //std::cerr << "Is point " << p.x() << ", " << p.y() << " valid?";
    bool r =  p.x() >= 0 && p.x() < cols
    && p.y() >= 0 && p.y() < rows
    && g[p.x()][p.y()] != '#';
    //&& g[p.x()][p.y()] != '?';
    //std::cerr << (r ? "Yes" : "No") << std::endl;
    if (r && goalChar != '?' && g[p.x()][p.y()] == '?') {
        r = false;
    }
    return r;
};

bool isGoal(Point p, Point goal, char **g) {
    return p == goal || g[p.x()][p.y()] == g[goal.x()][goal.y()];
}

float getDistance(Point a, Point b) {
    float dx = a.x() - b.x();
    float dy = a.y() - b.y();
    return (float) sqrt(dx * dx + dy * dy);
}

void printGrid(char **g, int rows, int cols, Point kirk, Point searchPoint) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (kirk.x() == j && kirk.y() == i){
                std::cerr << 'K';
            } else if (searchPoint.x() == j && searchPoint.y() == i){
                std::cerr << 'S';
            } else {
                std::cerr << g[j][i];
            }
        }
        std::cerr << '\n';
    }
}

void printGrid(char **g, int rows, int cols, Point kirk, Point searchPoint, std::deque<Point> route) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (kirk.x() == j && kirk.y() == i){
                std::cerr << 'K';
            } else if (searchPoint.x() == j && searchPoint.y() == i){
                std::cerr << 'S';
            } else if (find(route.begin(),route.end(), Point(j,i)) != route.end()){
                std::cerr << 'R';
            }
            else {
                std::cerr << g[j][i];
            }
        }
        std::cerr << '\n';
    }
}


Point findNearest(char **g, int gRows, int gCols, char target, Point position) {
    float nearest = 999.0f;
    Point nearestPoint = {-1, -1};
    for (int i = 0; i < gCols; i++) {
        for (int j = 0; j < gRows; j++) {
            if (g[i][j] == target) {
                float f = getDistance({i, j}, position);
                if (nearest > f) {
                    nearest = f;
                    nearestPoint.setX(i);
                    nearestPoint.setY(j);
                }
            }
        }
    }
    return nearestPoint;
}

bool findLocation(char **g, int gRows, int gCols, char location){
    for (int i = 1; i < gCols - 1; i++){
        for (int j = 1; j < gRows - 1; j++){
            if (g[i][j] == location){
                return true;
            }
        }
    }
    return false;
}

bool minf(Node a, Node b) {
    return a.getF() < b.getF();
}


Node aStar(char **g, int gRows, int gCols, Point sp, Point goalPos, char goalChar) {
    std::list<Node*> openList;
    std::list<Node*> closedList;
    std::list<Node*>::iterator it;
    std::list<Point> successors;
    successors.push_back({0,-1});
    successors.push_back({0,1});
    successors.push_back({1,0});
    successors.push_back({-1,0});
    
    Node *sn = new Node(0.0, 0.0, 0.0, nullptr, sp);
    openList.push_back(sn);
    
    while (!openList.empty()) {
        it = min_element(openList.begin(), openList.end(), minf);
        Node *q = new Node(*it);
        
        openList.erase(it);
        
        for(auto & s:successors){
            
            Node *successor = new Node(
                                       0.0f,
                                       0.0f,
                                       0.0f,
                                       q,
                                       {q->getPosition().x() + s.x(), q->getPosition().y() + s.y()}
                                       );
            //printGrid(g, gRows, gCols, sp, successor->getPosition());
            if (isValidPosition(successor->getPosition(), g, gRows, gCols, goalChar)) {
                if (isGoal(successor->getPosition(), goalPos, g)) {
                    return *successor;
                } else {
                    float distance_s_q = getDistance(q->getPosition(), successor->getPosition());
                    float distance_s_g = getDistance(goalPos, successor->getPosition());
                    successor->setG(q->getG() + distance_s_q);
                    successor->setH(distance_s_g);
                    successor->setF(successor->getG() + successor->getH());
                    
                    bool addNodeToList = true;
                    std::list<Node*>::iterator openIt = find_if(openList.begin(), openList.end(),
                                                               [successor](Node* n) {
                                                                   return n->getPosition() ==
                                                                   successor->getPosition();
                                                               });
                    if (openIt != openList.end()) {
                        if ((*openIt)->getF() < successor->getF()) {
                            addNodeToList = false;
                        }
                        
                    }
                    
                    
                    std::list<Node*>::iterator closedIt = find_if(closedList.begin(), closedList.end(),
                                                                 [successor](Node* n) {
                                                                     return n->getPosition() ==
                                                                     successor->getPosition();
                                                                 });
                    if (closedIt != closedList.end() && (*closedIt)->getF() < successor->getF())
                        addNodeToList = false;
                    
                    if (addNodeToList){
                        //std::cerr << "Point: " << successor->getPosition().x() << ", " << successor->getPosition().y()  << " added to open list." << std::endl;
                        openList.push_back(successor);
                        if (openIt != openList.end()) {
                            openList.erase(openIt);
                        }
                    }
                    
                }
            }
        }
        
        //std::cerr << "Point: " << q->getPosition().x() << ", " << q->getPosition().y()  << " added to closed list." << std::endl;
        closedList.push_back(q);
    }
    return *sn;
}

int main() {
    //std::fstream infile("input");
    
    int R; // number of rows.
    int C; // number of columns.
    int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    std::cin >> R >> C >> A;
    std::cin.ignore();
    
    // main grid
    char **grid = new char *[C];
    for (int i = 0; i < C; i++)
        grid[i] = new char[R];
    
    // visited grid
    //bool **visited = new bool *[C];
    //for (int i = 0; i < C; i++)
    //    visited[i] = new bool[R];
    
    Point controlRoom;
    bool controlRoomFound = false;
    Point target;
    Point teleporter;
    int kirkState = EXPLORING;
    Node nextNode;
    Node routeNode;
    std::deque<Point> route;
    std::deque<Point> controlToTeleportRoute;
    
    // game loop
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (1) {
        int KR; // row where Kirk is located.
        int KC; // column where Kirk is located.
        std::cin >> KR >> KC;
        std::cin.ignore();
        Point kirk = {KC, KR};
        for (int i = 0; i < R; i++) {
            std::string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            std::cin >> ROW;
            std::cin.ignore();
            for (int j = 0; j < C; j++) {
                grid[j][i] = ROW[j];
            }
        }
        
        //printGrid(grid, R, C, kirk, {-1,-1});
        if (!controlRoomFound && findLocation(grid, R, C, 'C')) {
            controlRoomFound = true;
            controlRoom = findNearest(grid, R, C, 'C', kirk);
            teleporter  = findNearest(grid, R, C, 'T', kirk);
            routeNode = aStar(grid, R, C, controlRoom, teleporter, 'T');
            controlToTeleportRoute = nextNode.getRoute();
            if (find(controlToTeleportRoute.begin(), controlToTeleportRoute.end(), teleporter) == controlToTeleportRoute.end()){
                // route does not contain control room, so we should keep exploring
                controlRoomFound = false;
                std::cerr << "route does not contain control room, so we should keep exploring" << std::endl;
            }
        }
        //printGrid(grid, R, C, kirk, {-1,-1},controlToTeleportRoute);
        std::cerr << "Route length to teleporter: " << controlToTeleportRoute.size() << std::endl;
        
        // If there are any unknown areas, explore them until we find the control room...
        if ((findLocation(grid, R, C, '?') && !controlRoomFound) || controlToTeleportRoute.size() > A){
            std::cerr << "EXPLORING." << std::endl;
            kirkState = EXPLORING;
            
            // find the next point to explore
            target = findNearest(grid, R, C, '?', kirk);
            nextNode = aStar(grid, R, C, kirk, target, '?');
            route = nextNode.getRoute();
            
            // calculate new route home
            routeNode = aStar(grid, R, C, controlRoom, teleporter, 'T');
            controlToTeleportRoute = nextNode.getRoute();
        } else {
            // No unexplored areas
            if (kirkState == EXPLORING) {
                // Head to control room...
                target = findNearest(grid, R, C, 'C', kirk);
                kirkState = GOING_TO_CONTROL_ROOM;
                nextNode = aStar(grid, R, C, kirk, target, 'C');
                route = nextNode.getRoute();
            } else if (kirkState == GOING_TO_CONTROL_ROOM) {
                // Have we got to the control room?
                if (grid[kirk.x()][kirk.y()] == 'C') {
                    target = findNearest(grid, R, C, 'T', kirk);
                    kirkState = GOING_TO_TELEPORTER;
                    nextNode = aStar(grid, R, C, kirk, target, 'T');
                    route = nextNode.getRoute();
                }
            }
        }
        switch (kirkState) {
        case EXPLORING:
            std::cerr << "EXPLORING." << std::endl;
            break;
        case GOING_TO_TELEPORTER:
            std::cerr << "GOING TO TELEPORTER." << std::endl;
            break;
        case GOING_TO_CONTROL_ROOM:
            std::cerr << "GOING TO CONTROL ROOM." << std::endl;
            break;
        }
        
        /*
        // Find control room if we can
        if (!controlRoomFound) {
            controlRoom = findNearest(grid, R, C, 'C', kirk);
            
            if (controlRoom.x() != -1 && controlRoom.y() != -1) {
                controlRoomFound = true;
                target = controlRoom;
            }
        }
        
        
        if (controlRoomFound && kirkState == EXPLORING) {
            std::cerr << "GOING TO CONTROL ROOM." << std::endl;
            kirkState = GOING_TO_CONTROL_ROOM;
            target = findNearest(grid, R, C, 'C', kirk);
            nextNode = aStar(grid, R, C, kirk, target);
            route = nextNode.getRoute();
        }
        
        if (kirkState == GOING_TO_CONTROL_ROOM && grid[kirk.x()][kirk.y()] == 'C') {
            std::cerr << "GOING TO TELEPORTER." << std::endl;
            kirkState = GOING_TO_TELEPORTER;
            target = findNearest(grid, R, C, 'T', kirk);
            nextNode = aStar(grid, R, C, kirk, target);
            route = nextNode.getRoute();
        }
        
        if (kirkState == EXPLORING) {
            target = findNearest(grid, R, C, '?', kirk);
            nextNode = aStar(grid, R, C, kirk, target);
            route = nextNode.getRoute();
        }
         */
        
        Point nextPosition;
        if (!route.empty()){
            nextPosition = route.back();
        }
        // Find the next position
        //Point nextPosition = nextNode.findNextPosition();
        //int steps = nextNode.getNumberOfSteps();
        
        
        // Should have a target by now, move towards it.
        // priority is right, left, up, down
        std::string moveDirection = "NA";
        if (nextPosition.x() > kirk.x()) {
            moveDirection = "RIGHT";
        } else if (nextPosition.x() < kirk.x()) {
            moveDirection = "LEFT";
        } else if (nextPosition.y() > kirk.y()) {
            moveDirection = "DOWN";
        } else if (nextPosition.y() < kirk.y()) {
            moveDirection = "UP";
        }
        
        route.pop_back();
        std::cout << moveDirection << std::endl; // Kirk's next move (UP DOWN LEFT or RIGHT).
    }
#pragma clang diagnostic pop
}
