#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;

int n;
int parent[maxn];

vector<int>vec[maxn];
int solv[maxn];

void dfs(int v=1)
{
    solv[v]++;
    for(auto &u: vec[v])
    {
        if(u==parent[v]) continue;
        dfs(u);
        solv[v]+=solv[u];
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=2;i<=n;i++)
    {
        cin>>parent[i];
        vec[parent[i]].push_back(i);
    }
    dfs();
    for(int i=1;i<=n;i++)
        cout<<solv[i]-1<<' ';
    return 0;
}