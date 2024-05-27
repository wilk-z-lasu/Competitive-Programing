#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

#pragma GCC target("avx,avx2,fma,tune=native")
#pragma GCC optimization("Ofast,unroll-loops")

constexpr int maxn=1e5+7;
constexpr int inf=1e9+7;

ll n;
ll m=-1;
ll l;
ll x[25];
ll add[300];

bool vis[maxn];

queue<pair<ll,ll>>q;

void bfs()
{
    q.push({0,0});
    vis[0]=1;
    for(ll i=0;i<=n;i++)
    {
        q.push({x[i],1});
        vis[x[i]]=1;
    }
    while(!q.empty())
    {
        ll v=q.front().f;
        ll cost=q.front().s;
        q.pop();

        if(v==l)
        {
            cout<<cost;
            exit(0);
        }

        cost+=2;
        for(ll i=0;i<=m;++i)
        {
            if(v+add[i]<maxn && !vis[v+add[i]])
            {
                vis[v+add[i]]=1;
                q.push({v+add[i],cost});
            }
            if(v-add[i]>=0 && !vis[v-add[i]])
            {
                vis[v-add[i]]=1;
                q.push({v-add[i],cost});
            }
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n; --n;
    for(ll i=0;i<=n;++i)
        cin>>x[i];
    cin>>l;
    for(ll i=0;i<=n;++i)
        for(ll j=i+1;j<=n;++j)
            add[++m]=x[j]-x[i];

    bfs();

    cout<<"NIE";
    return 0;
}