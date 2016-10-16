#include<iostream>
#include<vector>
#include<bitset>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
    bitset<1025> checker; //bitset of 2^10 + 1
    
    int t, n, m, last_p, val, walk_o;
    cin >> t;

    while(t--)
    {
        checker = 0;
        cin >> n >> m;
        last_p = pow(2, n);
        walk_o = 0;
        for(int i = 0; i < m; i++){
            cin >> val;
            checker[val]=1;
            val&1?(checker[val+1]?0:++walk_o):(checker[val-1]?0:++walk_o);
        }
        cout << walk_o << endl;
    }
    return 0;
}