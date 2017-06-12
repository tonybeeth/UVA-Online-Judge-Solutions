#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<algorithm>
#include<vector>

using namespace std;

#define endl '\n'
#define N 1000

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("data.dat", "r", stdin);
	//freopen("out.dat", "w", stdout);

	vector<int> table[N];
	for (int i = 0; i < N; ++i) {
		table[i].resize(N);
		table[i][i] = 1; //make diagonals 1
	}

	string line;
	int t;
	cin >> t;
	cin.ignore();

	for (int i = 0; i < t; i++) {
		getline(cin, line);

		//Empty string has palindrome length of 0
		if (line.length() == 0) {
			cout << 0 << endl;
			continue;
		}

		//Build table from bottom up
		for (int j = line.length() - 1; j >= 0; --j) {
			for (int k = j + 1; k < line.length(); ++k) {
				//LLP = length of largest palindrome
				//LLP from j to k (inclusive) = LLP(j, k) = 
					//LLP(j+1, k-1) + 2. if string[j] == string[k] . . . Just take the palindrome between and add the ending chars
					//max(LLP(j+1, k), LLP(j, k-1)). Use previous palindrome formed
				table[j][k] = line[j] == line[k] ? table[j + 1][k - 1] + 2 : max(table[j][k - 1], table[j + 1][k]);
			}
		}

		cout << table[0][line.length() - 1] << endl;
	}
}