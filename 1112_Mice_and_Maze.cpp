#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
#include<climits>
#include<queue>

using namespace std;

#define endl '\n'
#define SZ 101

struct Edge {
	int from, time;
};

int main()
{
	//freopen("data.dat", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(0);
	vector<Edge> V[SZ];
	vector<int> timeToExit;
	vector<bool> visited;
	int E, N, C, T, a, t, exitMice, Time, pos;
	cin >> T;
	//cout << "T " << T << endl;
	Edge e;
	timeToExit.resize(SZ);
	visited.resize(SZ);
	queue<int> Q;

	while (T--)
	{
		for (int i = 0; i < SZ; i++) {
			V[i].clear();
		}
		while (!Q.empty()) {
			Q.pop();
		}
		exitMice = 0;
		std::fill(timeToExit.begin(), timeToExit.end(), INT_MAX);
		std::fill(visited.begin(), visited.end(), false);
		
		if (!(cin >> N >> E >> Time >> C))
			break;
		
		//cout << "N " << N << ", E " << E << ", T " << T << ", C " << C << endl;
		for (int i = 0; i < C; ++i) {
			cin >> e.from >> a >> e.time;
		//	cout << "i: " << i << ", C: " << C << endl;
			V[a].push_back(e);
		//	cout << a << " " << V[a].back().from << " " << V[a].back().time << endl;
		}

        //Bottom-up-like build of the time to exit position from all position
		Q.push(E);
		timeToExit[E] = 0;
		while (!Q.empty()) {
			pos = Q.front();
			Q.pop();
			for (Edge& e : V[pos]) {
				if (timeToExit[e.from] > timeToExit[pos] + e.time) {
					timeToExit[e.from] = timeToExit[pos] + e.time;
					Q.push(e.from);
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			if (timeToExit[i] <= Time) {
				exitMice++;
			}
		}

		cout << exitMice << endl;
		if (T) {
			cout << endl;
		}
	}
	
	return 0;
}