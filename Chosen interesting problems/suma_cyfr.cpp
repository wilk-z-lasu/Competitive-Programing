#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll a,b;
int s;

ll dp[16][136][2];//[digits][sum][flag] flag=1 already smaller then x

int digit(ll x, int l)// O(log10(x))
{
    if(l==0) return 0;//problem specific if, because I start counting with 1
    vector<int>solv;

    while(x>0)
    {
        solv.push_back(x%10);
        x/=10;
    }
    reverse(solv.begin(),solv.end());
    return solv[l-1];
}
int digits(ll x)// O(log10(x))
{
    int solv=0;
    while(x)
    {
        x/=10;
        solv++;
    }
    return solv;
}

ll f(ll x)//counts number of numbers<=x with digit sum<=s
{
    for(int i1=0;i1<16;i1++)
    for(int i2=0;i2<136;i2++)
    for(int i3=0;i3<2;i3++)
    dp[i1][i2][i3]=0;
    dp[0][0][0]=1;

    for(int i=0;i<digits(x);++i)//position
    {
        // cout<<"i: "<<i<<endl; 
        for(int j=0;j<=s;++j)//sum
        {
            // cout<<"-j: "<<j<<endl;
            for(int flag=0;flag<=1;++flag)
            {
                // cout<<"--flag: "<<flag<<endl;
                if(flag)
                {
                    for(int add=0;add<=9;++add)
                        if(j+add<=s)
                            dp[i+1][j+add][1]+=dp[i][j][flag];
                }
                else
                {
                    // cout<<1<<" --> "<<digit(x,i+1)<<endl;
                    for(int add=0;add<digit(x,i+1);++add)
                        if(j+add<=s)
                            dp[i+1][j+add][1]+=dp[i][j][flag];
                    if(j+digit(x,i+1)<=s)
                        dp[i+1][j+digit(x,i+1)][0]+=dp[i][j][flag];
                }
            }
        }
    }
    return dp[digits(x)][s][0]+dp[digits(x)][s][1];
}

vector<int>vec;
int sum;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>a>>b>>s;

    cout<<f(b)-f(a-1)<<'\n';

    while(a)
    {
        sum+=a%10;
        vec.push_back(a%10);
        a/=10;
    }

    int it=0;
    while(sum<s)
    {
        if(it>=vec.size())
        {
            for(int i=9;i>0;i--)
            {
                if(sum+i<=s)
                {
                    vec.push_back(i);
                    sum+=i;
                    break;
                }
            }
            
        }
        else
        {
            for(int i=9;i>vec[it];i--)
            {
                if(sum+(i-vec[it])<=s)
                {
                    sum+=(i-vec[it]);
                    vec[it]+=(i-vec[it]);
                    break;
                }
            }
        }
        it++;
    }

    reverse(vec.begin(),vec.end());
    for(auto &u: vec)
        cout<<u;

    return 0;
}