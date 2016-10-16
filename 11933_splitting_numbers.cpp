#include<iostream>
#include<algorithm>
#include<bitset>
#include<vector>

using namespace std;

int main()
{
    unsigned long int n, a, b;
    int count;
    bitset<32> bs, bsa, bsb;
    while(cin >> n)
    {
        if(!n) break;
        count = 0;
        bs = n;
        bsa = bsb = 0;
        for(int i=0;i<32;i++){
            if(bs[i]){
                count++;
                count&1?bsa[i]=1:bsb[i]=1;
            }
        }
        a = bsa;
        b=bsb;
        cout << a << " " <<b << endl;
    }
}