#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<string>

using namespace std;
#define endl '\n'

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("data.dat", "r", stdin);
	string a, b, result;
	map<char, int> freqA, freqB;
	int num_occ;

	while (getline(cin, a) && getline(cin, b))
	{
		result = "";
		freqA.clear();
		freqB.clear();

		for (int i = 0; i < a.length(); ++i) {
			++freqA[a[i]];
		}
		for (int i = 0; i < b.length(); ++i) {
			++freqB[b[i]];
		}

		for (const auto& val : freqA) {
			if (freqB[val.first] > 0) {
				num_occ = val.second < freqB[val.first] ? val.second : freqB[val.first]; 
				result.append(num_occ, val.first);
			}
		}
		cout << result << endl;
	}

	return 0;
}