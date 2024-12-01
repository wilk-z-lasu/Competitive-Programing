#include <bits/stdc++.h>
using namespace std;
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=5000+7;

int n,k;
int x;
vector<int>vec[maxn];
int in[maxn];

int solv;

vector<int>up;
int it;
vector<int>down[maxn];

vector<int>graf[3*maxn];

int was[maxn];
void dfs(int v)
{
    was[v]=it;
    for(auto &u: down[v])
        graf[it].push_back(u);
    for(auto &u: vec[v])
        if(was[u]!=it)
            dfs(u);
}

int partner[3*maxn];
int timer=0;
int vis[3*maxn];
bool connect(int v)
{
    vis[v]=timer;
    for(auto &u: graf[v])
    {
        if(partner[u]==0)
        {
            partner[u]=v;
            return true;
        }
    }
    for(auto &u: graf[v])
    {
        if(vis[partner[u]]!=timer && connect(partner[u]))
        {
            partner[u]=v;
            return true;
        }
    }
    return false;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;i++)
    {
        cin>>k;
        while(k--)
        {
            cin>>x;
            vec[i].push_back(x);
            in[x]++;
        }
    }
    for(int v=1;v<=n;v++)
    {
        int edges = sz(vec[v]) - in[v];
        if(edges < 0)
        {
            while(edges++)
                up.push_back(v);
        }
        else if(edges > 0)
        {
            solv += edges;
            while(edges--)
                down[v].push_back(++it);
        }
    }

    it=0;
    for(auto &v: up)
    {
        ++it;
        dfs(v);
    }

    for(int v=1;v<=it;v++)
    {
        timer++;
        connect(v);
    }

    for(int i=1;i<=n;i++)
    {
        for(auto &u: down[i])
        {
            if(partner[u]!=0)
                solv--;
        }
    }
    cout<<solv;
    return 0;
}