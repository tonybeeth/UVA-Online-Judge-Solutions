#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
#include<numeric>

using namespace std;

#define endl '\n'

vector<int> knapsack(vector<int>& data, int remW, int idx) {
	vector<int> v;
	if (idx < data.size()) {

		vector<int> v1;
		if (remW >= data[idx]) {
			v1 = knapsack(data, remW - data[idx], idx + 1); //consider this value
			v1.insert(v1.begin(), data[idx]);
		}
		vector<int> v2 = knapsack(data, remW, idx + 1); //don't consider this value
		int sum1 = accumulate(v1.begin(), v1.end(), 0);
		int sum2 = accumulate(v2.begin(), v2.end(), 0);
		 if (sum1 >= sum2) { //makes sure the first result has priority
			v = std::move(v1);
		}
		else {
			v = std::move(v2);
		}
	}

	return v;
}

int main() {

	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("data.dat", "r", stdin);
	//freopen("out.dat", "w", stdout);

	int N, tracks;
	vector<int> durations;

	while (cin >> N >> tracks) {
		durations.resize(tracks);
		for (int i = 0; i < tracks; i++) {
			cin >> durations[i];
		}

		vector<int> result = knapsack(durations, N, 0);

		for (int& a : result) {
			cout << a << " ";
		}
		cout << "sum:" << accumulate(result.begin(), result.end(), 0) << endl;

	}
	return 0;
}
