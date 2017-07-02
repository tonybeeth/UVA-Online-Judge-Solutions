#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

#define endl '\n'

//Union-Find Disjoint set
class UFDS {
private:
	vector<int> parent, rank;

	int findSetRep(int arg) {
		//IMPORTANT!! PATH COMPRESSION HAPPENS HERE
		return arg == parent[arg] ? arg : (parent[arg] = findSetRep(parent[arg]));
	}

public:
	UFDS(int N) {
		parent.resize(N);
		rank.resize(N);
		for (int i = 0; i < N; ++i) {
			parent[i] = i;
			rank[i] = 0;
		}
	}

	bool inSameSet(int arg1, int arg2) {
		return findSetRep(arg1) == findSetRep(arg2);
	}

	void unionSets(int arg1, int arg2) {
		if (!inSameSet(arg1, arg2)) {
			int pArg1 = findSetRep(arg1), pArg2 = findSetRep(arg2);

			if (rank[pArg1] > rank[pArg2]) {
				parent[pArg2] = pArg1;
			}
			else {
				parent[pArg1] = pArg2;
				if (rank[pArg1] == rank[pArg2])
					rank[pArg2]++;
			}
		}

	}

	~UFDS() {
		parent.clear();
		rank.clear();
	}
	
};

class Edge {

public:
	int vertex1, vertex2, weight;

	bool operator<(const Edge& b) const {
		return weight > b.weight;
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("data.dat", "r", stdin);
	//freopen("out.dat", "w", stdout);

	Edge edge;

	priority_queue<Edge> pq;

	int m, n, totalWeight, minWeight;
	while (cin >> m >> n) {
		totalWeight = minWeight = 0;

		if (m == 0 && n == 0)
			break;

		for (int i = 0; i < n; i++) {
			cin >> edge.vertex1 >> edge.vertex2 >> edge.weight;

			pq.push(edge);
			totalWeight += edge.weight;
		}

		//Kruskal's algorithm
		UFDS ufds(m);
		while (!pq.empty()) {
			edge = pq.top();
			pq.pop();
			if (!ufds.inSameSet(edge.vertex1, edge.vertex2)) {
				minWeight += edge.weight;
				ufds.unionSets(edge.vertex1, edge.vertex2);
			}
		}
		cout << totalWeight - minWeight << endl;

	}

	return 0;
}