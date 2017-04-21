#include<iostream>
#include<vector>
#include<queue>
#include<stdio.h>
#include<string>
#include<climits>

using namespace std;

#define endl '\n'

//time it takes each car to arrive on the other side
vector<int> desTimes;

//Function to make journey from ferryPos
//q1 are cars with the same position as the ferry. q2 are cars on the other side
//FerryPos is the current boolean value for the ferry position
//curTime: current ferry time. 
//n: max cars on ferry per river crossing 
//t: time on ferry per river crossing

void makeJourney(queue<pair<int, int>>& q1, queue<pair<int, int>>& q2, bool& ferryPos, int& curTime, int& n, int &t)
{
	int ncars = 0; //keep track of the number of cars moved

	//Ferry is currently at the same position as cars in q1
	//check cars in q1 first
	while (!q1.empty() && ncars < n && q1.front().first <= curTime) {
		++ncars;
		desTimes[q1.front().second] = curTime + t; //time this car gets to the other side
		q1.pop();
	}

	//move to the other position
	curTime += t;
	ferryPos = !ferryPos;

	ncars = 0; //reset number of cars moved
	//check cars in q2
	while (!q2.empty() && ncars < n && q2.front().first <= curTime) {
		++ncars;
		desTimes[q2.front().second] = curTime + t;
		q2.pop();
	}
	if (ncars > 0) { //if cars are moved from q2 position, then move the ferry. Else remain here
		curTime += t;
		ferryPos = !ferryPos;
	}
}

int main()
{
	//freopen("data.dat", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(0);

	//Two queues for both sides of the river
	queue<pair<int, int>> qleft;
	queue<pair<int, int>> qright;

	int c, t, m, n;
	int arr;
	string pos;
	bool ferryPos;
	int curTime;
	int a, b;

	cin >> c;

	for(int i = 0; i < c; i++)
	{
		cin >> n >> t >> m;
		curTime = 0; //start time is always 0
		ferryPos = true; //start position of ferry is always left
		desTimes.resize(m);

		//Read cars info into appropriate queue (cars on the left go to qleft . . .)
		for(int j = 0; j < m; j++)
		{
			cin >> arr >> pos;

			if (pos[0] == 'l') {
				qleft.push(make_pair(arr, j)); //keep track of arrival order and time of cars
			}
			else {
				qright.push(make_pair(arr, j));
			}
		}

		//Repeat loop until all cars have been moved
		while (!qleft.empty() || !qright.empty()) {
			//get arrival times for the next car on each side
			a = qleft.empty() ? INT_MAX : qleft.front().first;
			b = qright.empty() ? INT_MAX : qright.front().first;

			//skip waiting time if needed
			if (a > curTime && b > curTime) {
				curTime = min(a,b);
			}

			if (ferryPos) { //ferry is on the left. Make journey from left
				makeJourney(qleft, qright, ferryPos, curTime, n, t);
			}
			else {//Make journey from right
				makeJourney(qright, qleft, ferryPos, curTime, n, t);
			}

		}

        //print arrival at destination times
		if (i != 0) {
			cout << endl;
		}
		for (int& val: desTimes) {
			cout <<val << endl;
		}

		desTimes.clear();

	}
}
