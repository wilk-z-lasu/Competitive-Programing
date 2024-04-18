//wersja nie dzialajaca
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1e5+7;

int solv;
int n,m;
int a,b;
int stopien[maxn];
int ile;

vector<int>vec[maxn];

bool vis[maxn];

set<int> odp;

void dfs(int v)
{
    if(stopien[v]!=2)
    {
        odp.insert(v);
        return;
    }
    vis[v]=true;

    if(!vis[vec[v][1]])
        //ide vec[v][1]
        dfs(vec[v][1]);
    if(!vis[vec[v][0]])
        //ide vec[v][0]
        dfs(vec[v][0]);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
        stopien[a]++;
        stopien[b]++;
    }
    for(int i=1;i<=n;i++)
        if(stopien[i]%2==1)
            ile++;

    for(int i=1;i<=n;i++)
    {
        if(!vis[i] && stopien[i]==2)
        {
            odp.clear();
            dfs(i);
            if(odp.size()<2)
                ile+=2;
        }
    }
    cout<<ile/2;
    
    return 0;
}