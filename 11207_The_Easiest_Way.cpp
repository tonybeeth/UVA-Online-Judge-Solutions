#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cmath>

using namespace std;

#define endl '\n'

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    //freopen("data.dat", "r", stdin);
    int N, idx;
    double a, b, c, d, max_pd, pd;
    while(cin >> N)
    {
        if(!N){
            break;
        }
        max_pd = 0;
        for(int i = 1; i <= N; ++i){
            cin >> c >> d;
            a = max(c,d);
            b = min(c,d);
            c = min(a/4, b);
            d = min(a/2, b/2);
            
            pd = pow(max(c,d), 2);

            //cout << a << " " << b << " " << c << " " << d << " " << pd << endl;
            if(pd > max_pd){
                idx = i;
                max_pd=pd;
            }
        }
        cout << idx << endl;
    }

    return 0;
}