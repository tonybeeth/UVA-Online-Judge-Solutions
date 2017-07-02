#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<algorithm>

using namespace std;

#define endl '\n'

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("data.dat", "r", stdin);
	//freopen("out.dat", "w", stdout);

	string str;

	int distintCopiesFound, distinctStrEndIndex;
	while (cin >> str) {
		if (str == ".") {
			break;
		}

		//At least a = a^1
		distintCopiesFound = 1;
		distinctStrEndIndex = 0;

		if (str.length() > 1) {
			for (int i = 1; i < str.length(); ++i) {

				if (str[i] == str[0]) {

					//Check if this forms a new duplicate
					bool foundDuplicate = true;
					for (int j = 0; j <= distinctStrEndIndex; ++j) {
						if (str[j] != str[i + j]) {
							foundDuplicate = false;
							break;
						}
					}
					
					if (foundDuplicate) {
						i += distinctStrEndIndex;
						++distintCopiesFound;
					}
					else {//if no duplicates found, reset number of copies and expand the end of the base string
						distintCopiesFound = 1;
						distinctStrEndIndex = i;
					}
				}
				else {
					//If we can't find a character the same as the first, we haven't found a duplicate
					distinctStrEndIndex = i;
					distintCopiesFound = 1;
				}
			}
		}
		cout << distintCopiesFound << endl;
		
	}
}