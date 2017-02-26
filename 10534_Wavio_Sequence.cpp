#include<iostream>
#include<algorithm>
#include<vector>
#include<stdio.h>

using namespace std;
#define endl '\n'

struct Node {
	int count, LIS_end;
};

int findMin(vector<int>& E, int start, int end, int val) throw()
{
	register int mid = 0;

	while (start < end)
	{
		mid = (start + end) >> 1;
		if (E[mid] == val) {
			return -1;
		}
		else if (E[mid] < val) {
			if (mid == end || E[mid + 1] > val) {
				return mid;
			}
			start = mid + 1;
		}
		else {
			if (E[mid - 1] < val) {
				return mid - 1;
			}
			end = mid - 1;
		}
	}
	return -1;
}

int LIS(vector<int>& V, vector<int>& E, int& n, vector<Node>& LIS_count) throw()
{
	fill(E.begin(), E.begin()+n, 0);

	register int LIS_LENGTH = 1, index;
	E[1] = V[0];
	LIS_count[0].count = 1;
	LIS_count[0].LIS_end = 0;

	for (int i = 1; i < n; ++i) {
		LIS_count[i] = LIS_count[i - 1];
		if (V[i] < E[1]) {
			//create new LIS
			E[1] = V[i];
		}
		else if (V[i] > E[LIS_LENGTH]) {
			//extend last LIS
			E[++LIS_LENGTH] = V[i];
			++(LIS_count[i].count);
			LIS_count[i].LIS_end = V[i];
		}
		else if(V[i] > E[1] && V[i] < E[LIS_LENGTH]){
			//somewhere between
			index = findMin(E, 1, LIS_LENGTH, V[i]);
			if (index != -1) {
				E[index + 1] = V[i];
			}
		}
	}

	return LIS_LENGTH;
}

int main()
{
	//freopen("data.dat", "r", stdin);
	ios_base::sync_with_stdio(false); 
	cin.tie(0);

	vector<int> V(10001), Eforward(10001), Eback(10001);
	vector<Node> countForward(10001), countBack(10001);

	int n, forwardLength, backLength;
	while (cin >> n)
	{
		for (int i = 0; i < n; i++) {
			cin >> V[i];
		}

		//forward LIS
		forwardLength = LIS(V, Eforward, n, countForward);
		reverse(V.begin(), V.begin()+n);

		backLength = LIS(V, Eback, n, countBack);
		reverse(V.begin(), V.begin() + n);

		int minV, wavio_length = 1;
		for (int i = 1, j = n - 2; i < n - 1; ++i, --j) {
			if (V[i] == countForward[i].LIS_end && V[i] == countBack[j].LIS_end) {
				minV = min(countForward[i].count, countBack[j].count);
				--minV;
				wavio_length = max(wavio_length, (minV << 1) + 1);
			}
		}

		cout << wavio_length << endl;
		
	}

	return 0;
}