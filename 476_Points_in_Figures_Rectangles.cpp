#include<iostream>
#include<vector>
#include<utility>
#include<stdio.h>

using namespace std;

#define endl '\n'
#define SENTINEL 9999.9

struct Rectangle {
	pair<double, double> upperLeft, lowerRight;
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("data.dat", "r", stdin);
	//freopen("out.dat", "w", stdout);

	vector<Rectangle> rectangles;
	pair<double, double> point;
	char figType;
	Rectangle rect;
	int pointId = 1, rectId = 1;
	bool notContained;

	while (cin >> figType && figType == 'r') {
		cin >> rect.upperLeft.first >> rect.upperLeft.second >> rect.lowerRight.first >> rect.lowerRight.second;
		
		rectangles.push_back(rect);
	}

	while (cin >> point.first >> point.second && (point.first != SENTINEL && point.second != SENTINEL)) {
		rectId = 1;
		notContained = true;
		for (const Rectangle& rect : rectangles) {
			if (!(rect.lowerRight.first <= point.first || rect.lowerRight.second >= point.second ||
				rect.upperLeft.first >= point.first || rect.upperLeft.second <= point.second)) {
				cout << "Point " << pointId << " is contained in figure " << rectId << endl;
				notContained = false;
			}
			++rectId;
		}

		if (notContained) {
			cout << "Point " << pointId << " is not contained in any figure" << endl;
		}

		++pointId;
	}
}