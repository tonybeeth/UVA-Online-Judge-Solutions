#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

#define endl '\n'

int main()
{
	/*
	Solution: Since the fire only starts on the first row, maximize the defended houses by
	defending safe houses that are below houses currently on fire. As the fire spreads,
	a pyramid of the safe houses will be formed. With a few simulations by hand for even and odd
	values of N, a formula to the solution can be derived.
	*/
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("data.dat", "r", stdin);
	//freopen("out.dat", "w", stdout);

	unsigned long long N, C, maxHousesSaved;

	while (cin >> N >> C) {
		if (N == 1) {
			cout << 1 << endl;
			continue;
		}
		/*cout << ((N*(N - 1)) / 2) << endl;
		cout << (((N - C)*(N - C + 1)) / 2) << endl;
		cout << (((N*(N - 1)) / 2) - (((N - C)*(N - C + 1)) / 2)) << endl;
		cout << (((N*(N - 1)) / 2) - (((N - C)*(N - C + 1)) / 2)) * 2 << endl;
		cout << (N - C)*(N - 2 * (C - 1)) << endl;*/
		maxHousesSaved = (((N*(N-1))/2) - (((N-C)*(N-C+1))/2))*2 + (N-C)*(N-2*(C-1));
		cout << maxHousesSaved << endl;
	}
}