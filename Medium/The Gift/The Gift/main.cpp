#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
	//fstream infile("input");
	int N;
	cin >> N; cin.ignore();
    int C;
	cin >> C; cin.ignore();
	
	vector<int> budgets(N);
	vector<int> contributions;
    for (int i = 0; i < N; i++) {
        int B;
		cin >> B; cin.ignore();
		budgets[i] = B;
    }
	sort(budgets.begin(),budgets.end());
	vector<int>::iterator it = budgets.begin();
	
	int remainingAmnt = C;
	int remainingOods = N;
	do {
		int avgContribution = remainingAmnt / remainingOods;
		if (*it < avgContribution) {
			contributions.push_back(*it);
			remainingAmnt -= *it;
		} else {
			contributions.push_back(avgContribution);
			remainingAmnt -= avgContribution;
		}
		remainingOods--;
		it++;
	} while (it != budgets.end() && remainingAmnt > 0);
	
	if (remainingAmnt > 0)
		cout << "IMPOSSIBLE" << endl;
	else {
		for (auto & c:contributions)
			cout << c << endl;
	}
}
