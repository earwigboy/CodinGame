#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> conwayString(vector<int> a){
    
    if (a.size() == 1)
        return vector<int>{1,a[0]};
    
    vector<int> result, nextResult;
    vector<int>::iterator head = a.begin();
    vector<int>::iterator tail = a.begin()++;
    
    // find the first element that is not the same as the head.
    vector<int>::iterator tailsplit = find_if_not(tail, a.end(), [head](int i){return i == *head;});
    
    if (tailsplit != a.end()){
        // Not everything is the same as head.
        // Split the vector at the point values stop being the same as head.
        vector<int> remainder(tailsplit,a.end());
        // Calculate the distance between head and the split, this will be the count.
        size_t index = distance(head,tailsplit);
        // create a new vector with the two values, count of head and head.
        result = vector<int>{(int)index, *head};
        // Pass the remainder vector to the routine again to repeat the whole process.
        nextResult = conwayString(remainder);
        // Join the results of the next function call to the first result and return.
        result.insert(result.end(),nextResult.begin(), nextResult.end());
        return result;
    } else {
        // everything in the vector is the same
        size_t index = distance(tail,a.end());
        return vector<int>{(int)index, *head};
    }
    
}

int main()
{
    int R;
    cin >> R; cin.ignore();
    int L;
    cin >> L; cin.ignore();
    
    string c = to_string(R);
    vector<int> cc = {R};
    for (int i = 0; i < L-1; i++)
        cc = conwayString(cc);
    
    for (vector<int>::iterator it = cc.begin(); it != cc.end(); it++) {
        if (it+1 == cc.end())
            cout << *it << endl; // don't print a space character after the last element
        else
            cout << *it << " ";
    }
}
