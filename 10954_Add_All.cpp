#include<iostream>
#include<vector>
#include<utility>
#include<stdio.h>
#include<queue>
#include<functional>

using namespace std;

#define endl '\n'
#define ull unsigned long long int

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("data.dat", "r", stdin);
	//freopen("out.dat", "w", stdout);

	priority_queue<int, vector<int>, greater<int>> numbers;
	
	int n, num, sum, weight;

	while (cin >> n && n != 0)
	{
		for (int i = 0; i < n; i++) {
			cin >> num;
			numbers.push(num);
		}

		weight = 0;
		//Add numbers until the size gets to 1
		while (numbers.size() != 1) {
			//add the two least numbers
			num = numbers.top();
			numbers.pop();
			sum = num + numbers.top();
			numbers.pop();
			weight += sum; //add weight

			//push the new sum
			numbers.push(sum);
		}
		cout << weight << endl;
		numbers.pop();
	}

}