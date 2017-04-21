#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

using namespace std;

#define endl '\n'

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

    //freopen("data.dat", "r", stdin);    
    register int t;
    register unsigned long long int s, x;
    cin >> t;
    for(register int i = 0; i < t;++i){
        cin >> s;
        x = s*s + (s<<1);
        cout << x << endl;
    }

}