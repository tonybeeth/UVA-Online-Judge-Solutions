#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<climits>
#include<unordered_map>
#include<queue>
 
using namespace std;
#define endl '\n'
 
struct cell{
    unordered_map<string, cell*> V;
    int dist = INT_MAX;
};
 
int main()
{
    //freopen("data.dat", "r", stdin);
    //freopen("out.dat", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
 
    vector<string> names;
    unordered_map<string, cell> M;
 
    int t, p, n, pos, test = 0;
 
    string line, name;
    queue<cell*> q;
    cin >> t;
     
    while (t--)
    {
        cin >> p >> n;
 
        M.clear();
        cin.ignore();
        for (int i = 0; i < p; ++i)
        {
            getline(cin, line, ':');
            cin.ignore(INT_MAX, endl);
            pos = 0;
            while (line.length() > 0)
            {
                pos = line.find(".,");
                if (pos == line.npos){
                    name = line;
                    line = "";
                }
                else{
                    name = line.substr(0, pos + 1);
                    line = line.substr(pos + 3);
                }
                names.push_back(name);
            }
 
            for (const auto& n : names)
            {
                for (const auto& oth : names)
                {
                    if (oth != n){
                        M[n].V[oth] = &M[oth];
                    }
                }
            }
            names.clear();
        }
 
        //do bfs
        cell* c = &M["Erdos, P."];
        c->dist = 0;
        q.push(c);
        int dist;
 
        while (!q.empty())
        {
            c = q.front();
            q.pop();
            for (auto const& n : c->V){
                dist = c->dist + 1;
                if (dist < n.second->dist){
                    n.second->dist = dist;
                    q.push(n.second);
                }
            }
 
        }
 
        //print result
        cout << "Scenario " << ++test << endl;
        for (int i = 0; i < n; ++i){
            getline(cin, name);
            cout << name << " ";
            if (M[name].dist == INT_MAX)
                cout << "infinity";
            else
                cout << M[name].dist;
            cout << endl;
        }
    }
 
 
    return 0;
}