#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const unsigned int NUM_NUMERALS = 20;
const long int BASE = 20;

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
void printGrid(char** g, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cerr << g[j][i];
        }
        cerr << '\n';
    }
}

void printNumeral(char** g, int rows, int cols, long int n){
    vector<long int> result;
    double power = 9;
    long int r1, r2, r3;
    r1 = n;
    
    do {
        r3 = (long int)pow(BASE,power);
        r2 = r1 % r3;
        if (r2 != r1 && power > 0) {
            if (r1 < BASE)
                result.push_back(r1);
            else {
                r1 = r1 / r3;
                result.push_back(r1);
                r1 = r2;
            }
        } else {
            if (power == 0)
                result.push_back(r1);
            else {
                if (result.size() > 0)
                    result.push_back(0);
            }
        }
        power--;
    } while (power >= 0);
    
    for (vector<long int>::iterator r = result.begin(); r != result.end(); ++r) {
        long int nn = *r;
        for (int i = 0; i < rows; i++) {
            for (long int j = nn*cols; j < nn*cols + cols; j++) {
                cout << g[j][i];
            }
            cout << '\n';
        }
    }
}

long int performOperation(long int op1, long int op2, string operand){
    if (operand == "+") return op1 + op2;
    if (operand == "-") return op1 - op2;
    if (operand == "*") return op1 * op2;
    if (operand == "/") return op1 / op2;
    
    return 0;
}

long int getOperand(char** g, char ** n, int gRows, int gCols, int oRows){
    long int operand1 = 0;
    int power = oRows/gRows - 1;
    
    for (int l = 0; l < oRows/gRows; l++){
        int i = 0;
        bool foundNumeral = true;
        bool operandFound = false;
        while (!operandFound && i < NUM_NUMERALS){
            int j = 0;
            while (foundNumeral && j < gCols){
                int k = 0;
                while (foundNumeral && k < gRows){
                    if (g[i*gCols + j][k] != n[j][l*gRows + k]){
                        foundNumeral = false;
                    }
                    k++;
                }
                j++;
            }
            if (foundNumeral){
                operand1 += i * pow(BASE,power);
                operandFound = true;
            }
            i++;
            foundNumeral = true;
        }
        power--;
    }
    
    return operand1;
}

int main()
{
    int L;
    int H;
    
    cin >> L >> H; cin.ignore();
    
    // main grid
    char** grid = new char*[L*NUM_NUMERALS];
    for (int i = 0; i < L*NUM_NUMERALS; i++)
        grid[i] = new char[H];

    // populate grid
    for (int i = 0; i < H; i++) {
        string numeral;
        cin >> numeral; cin.ignore();
        for (int j = 0; j < NUM_NUMERALS; j++){
            for (int k = 0; k < L; k++) {
                grid[j*L + k][i] = numeral[j*L + k];
            }
        }
    }
    //printGrid(grid, H, L*NUM_NUMERALS);
    
    // populate numeral 1
    int S1;
    cin >> S1; cin.ignore();
    
    // numeral 1
    char** numeral1 = new char*[L];
    for (int i = 0; i < L; i++)
        numeral1[i] = new char[S1];
    
    for (int i = 0; i < S1; i++) {
        string num1Line;
        cin >> num1Line; cin.ignore();
        for (int j = 0; j < L; j++){
            numeral1[j][i] =  num1Line[j];
        }
    }
    
    // populate numeral 2
    int S2;
    cin >> S2; cin.ignore();
    
    // numeral 2
    char** numeral2 = new char*[L];
    for (int i = 0; i < L; i++)
        numeral2[i] = new char[S2];

    for (int i = 0; i < S2; i++) {
        string num2Line;
        cin >> num2Line; cin.ignore();
        for (int j = 0; j < L; j++){
            numeral2[j][i] = num2Line[j];
        }
    }
    string operation;
    cin >> operation; cin.ignore();
    
    long int operand1 = getOperand(grid, numeral1, H, L, S1);
    long int operand2 = getOperand(grid, numeral2, H, L, S2);
    
    long int result = performOperation(operand1, operand2, operation);
    
    printNumeral(grid, H, L, result);
}
