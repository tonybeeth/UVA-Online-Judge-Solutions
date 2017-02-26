#include<iostream>
#include<vector>
#include<stdio.h>
#include<sstream>
#include<string>

using namespace std;

#define endl '\n'

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    //freopen("data.dat", "r", stdin);

    int N, P;
    vector<int> numNeighbors(1000), places;
    int n, min = 100000;
    string line;
    cin >> N;

    for(int j = 0; j < N; j++)
    {
        cin >> P;
        cin.ignore(1000, '\n');
        min = 100000;

        fill(numNeighbors.begin(), numNeighbors.end(), 0);
        for(int i = 0; i < P; i++){
            
            getline(cin, line);
            stringstream ss(line);
            while(ss >> n){
                numNeighbors[i]++;
            }
            if(numNeighbors[i] < min){
                min = numNeighbors[i];
            }
        }

        places.clear();

        for(int i = 0; i < P; i++){
            if(min == numNeighbors[i]){
                places.push_back(i+1);
            }
        }
        for(int i = 0; i < places.size();i++){
            cout << places[i];
            if(i < places.size()-1){
                cout << " ";
            }
            else{
                cout << endl;
            }
        }
    }

    return 0;
}