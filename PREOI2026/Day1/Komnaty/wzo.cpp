//O(n*m + n)
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1007;

int n,m,k;

int vec[maxn];
pi nxt[maxn];
string w;

inline int dfs(int v, int idx=1)
{
    while(idx<=m)
    {
        if(w[idx]=='L')
            v=nxt[v].f;
        else
            v=nxt[v].s;
        ++idx;
    }
    return v;
}

int vis[maxn];
inline int travel(int v=1)
{
    while(k>0 && vis[v]==0)
    {
        vis[v]=k;
        --k;
        v=vec[v];
    }
    if(k==0) return v;

    int cycle = (vis[v]-k);
    k%=cycle;

    while(k--)
        v=vec[v];

    return v;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;++i)
        cin>>nxt[i].f>>nxt[i].s;

    cin>>w;
    w = '#' + w;
    for(int i=1;i<=n;++i)
        vec[i]=dfs(i);
    
    cout<<travel();
}