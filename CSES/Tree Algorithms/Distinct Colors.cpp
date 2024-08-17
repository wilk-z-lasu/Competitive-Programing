#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;

int n;
int c[maxn];
int a,b;
vector<int>vec[maxn];
int solv[maxn];

set<int>s;
void dfs(int v = 1, int parent = 1, set<int>&x1 = s)
{
    x1.insert(c[v]);
    for(auto &u: vec[v])
    {
        set<int>x2;
        if(u==parent) continue;
        dfs(u,v,x2);

        if(x2.size()>x1.size()) swap(x1,x2);
        x1.insert(x2.begin(),x2.end());
    }
    solv[v]=x1.size();
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>c[i];
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    dfs();
    for(int i=1;i<=n;i++)
        cout<<solv[i]<<' ';
    return 0;
}