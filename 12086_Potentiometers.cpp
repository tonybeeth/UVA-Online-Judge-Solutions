#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>

using namespace std;

#define endl '\n'

int main()
{
    //freopen("data.dat", "r", stdin);
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, a, b, val, sum1, sum2; char ch;
    vector<int> V, FT;
    V.resize(200001);
    FT.resize(200001); //Fenwick tree vector
        
    for(int casen = 1; cin >> N; ++casen)
    {
        if(!N){
            break;
        }
        if(casen > 1){
            cout << endl;
        }

        std::fill(FT.begin(), FT.end(), 0);
        //read in values and build fenwick tree (nlogn)
        for(int i = 1; i <= N; ++i){
            cin >> V[i];
            
            for(int k = i; k <= N; k += (k&-k)){
                FT[k] += V[i];
            }
        }

        cout << "Case " << casen << ":" << endl;
        while(cin >> ch)
        {
            if(ch == 'E'){ //end processing of this case
                cin.ignore(1000, '\n');
                break;
            }

            cin >> a >> b;
            if(ch == 'M'){
                //measure between a and b            
                sum1 = sum2 = 0;
                
                //calculate total in [1, a-1]
                for(int i = a-1; i >= 1; i-=(i&-i)){
                    sum1+=FT[i];
                }
                //calculate total in [1, b]
                for(; b >= 1; b-=(b&-b)){
                    sum2 += FT[b];
                }

                cout << sum2 - sum1 << endl;
            }
            else if(ch == 'S'){
                //update new resistance in fenwick tree
                val = V[a];
                V[a] = b;
                for(;a<=N;a+=(a&-a)){
                    FT[a]+=(b-val);
                }
            }
        }

    }
    return 0;
}