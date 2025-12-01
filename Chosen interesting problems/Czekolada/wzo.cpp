#include <bits/stdc++.h>
using namespace std;
#define int long long 

int q;
int n,m;
int dp[31][2][2];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>q;
    while(q--)
    {
        cin>>n>>m;
        int S1 = n-1;
        int S2 = m-1;

        for(int i=0;i<=30;++i)
            for(int j=0;j<=1;++j)
                for(int k=0;k<=1;++k)
                    dp[i][j][k]=0;
        dp[0][0][0]=1;
        for(int i=0;i<30;++i)
        {
            // cout<<"----"<<i<<"----\n";
            for(int w1=0;w1<=1;++w1)
            {
                for(int w2=0;w2<=1;++w2)
                {
                    if(dp[i][w1][w2]==0) continue;
                    // cout<<w1<<" "<<w2<<" "<<dp[i][w1][w2]<<'\n';
                    for(int add1=0;add1<=1;++add1)
                    for(int add2=0;add2<=1;++add2)
                    for(int add3=0;add3<=1;++add3)
                    for(int add4=0;add4<=1;++add4)
                    {
                        if((add1 ^ add2 ^ add3 ^ add4) != 0) continue;
                        int e1 = w1+add1+add2;
                        int e2 = w2+add3+add4;

                        int bit1 = ((S1>>i)&1);
                        int bit2 = ((S2>>i)&1);
                        
                        if(((e1%2) == bit1) && ((e2%2) == bit2))
                            dp[i+1][e1/2][e2/2] += dp[i][w1][w2];
                    }
                }
            }
        }
        cout<<dp[30][0][0]<<'\n';
    }
    return 0;
}