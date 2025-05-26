#include<bits/stdc++.h>
using namespace std;

#define int long long

constexpr int maxn = 300+7;

int n,m;

int x[maxn];

int odp=0;
void dfs(int v, int time, int vis1, int vis2, int solv=0, int k=0)
{
    odp=max(odp, solv);

    if(k>=0)
    {
        int new_solv=solv;
        for(int i=vis2+1; i<=n; ++i)
        {
            int new_time = time+abs(x[i]-x[v]);
            if(new_time>m) break;
            new_solv += (m-new_time);
            dfs(i, new_time, vis1, i, new_solv, -1);
        }
    }
    if(k<=0)
    {
        int new_solv=solv;
        for(int i=vis1-1; i>=1; --i)
        {
            int new_time = time+abs(x[i]-x[v]);
            if(new_time>m) break;
            new_solv += (m-new_time);
            dfs(i, new_time, i, vis2, new_solv, +1);
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n>>m;

    bool have_zero=0;
    for(int i=1;i<=n;++i)
    {
        cin>>x[i];
        if(x[i]==0)
            have_zero=1;
    }
    if(!have_zero)
    {
        n++; 
        x[n+1] = 0;
    }

    sort(&x[1], &x[n+1]);

    int start=1;
    while(x[start]!=0)
        ++start;

    dfs(start, 0, start, start);

    if(have_zero) odp+=m;

    cout<<odp;
    return 0;
}