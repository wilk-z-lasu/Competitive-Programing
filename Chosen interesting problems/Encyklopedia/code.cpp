#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back

constexpr int maxn = 2e6+7;

int n;
int x[maxn];

bool patern[2][maxn];

vector<int>poz[2][2];

int solv[2];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n; n*=2;
    for(int i=1;i<=n;++i)
    {
        cin>>x[i];
        if(x[i]>0)
            x[i]=1;
    }

    for(int i=1;i<=n;i++)
    {
        patern[0][i] = i&1;
        patern[1][i] = !(i&1);
    }

    for(int i=1;i<=n;i++)
        for(int p=0;p<=1;++p)
            if(x[i]!=patern[p][i])
                poz[p][x[i]].pb(i);

    for(int p=0;p<=1;++p)
    {
        while(!poz[p][0].empty())
        {
            solv[p] += abs(poz[p][0].back() - poz[p][1].back());
            poz[p][0].pop_back();
            poz[p][1].pop_back();
        }
    }

    cout<<min(solv[0],solv[1]);
    return 0;
}