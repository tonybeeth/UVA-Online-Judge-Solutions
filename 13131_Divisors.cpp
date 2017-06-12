#include<iostream>
#include<math.h>
#include<vector>
#include<stdio.h>

using namespace std;

#define endl '\n'

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("data.dat", "r", stdin);
	//freopen("out.dat", "w", stdout);
	register int t, n, k, sqt, fact, i, sum;

	cin >> t;

	while (t--) {
		cin >> n >> k;

		sum = 0;
		sqt = sqrt(n);
		for (i = 1; i <= sqt; ++i) {
			if (n%i == 0){

				fact = n / i;
				if (i%k != 0) {
					sum += i;
				}

				if (n%fact == 0 && fact%k != 0 && fact != i) {
					sum += fact;
				}
			}
		}
		cout << sum << endl;
	}
}