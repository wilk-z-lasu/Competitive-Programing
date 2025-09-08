#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) ((int)(A).size())

constexpr int maxn = 2e5 + 7;

int n,m;
vector<int> vec[maxn];
bool vis[maxn];
vector<int> preorder;
bool is_cycle[maxn];
vector<int> cycle;
bool found_cycle = 0;
void find_cycle(int v=1, int ojciec = -1)
{
    if(found_cycle) return;
    vis[v]=1;
    preorder.pb(v);
    for(auto &u: vec[v])
    {
        if(found_cycle) return;
        if(u==ojciec) continue;
        if(!vis[u])
            find_cycle(u, v);
        else
        {
            // cout<<"found cycle at "<<u<<endl;
            found_cycle = 1;
            while(preorder.back()!=u)
            {
                cycle.pb(preorder.back());
                is_cycle[preorder.back()]=1;
                preorder.pop_back();
            }
            cycle.pb(preorder.back());
            is_cycle[preorder.back()]=1;
            return;
        }
    }
    preorder.pop_back();
}

map<vector<int>, int>id;
int new_id=0;
int rep[maxn];
int dfs(int v, int ojciec=-1)
{
    vector<int>sons;
    for(auto &u: vec[v])
    {
        if(is_cycle[u] || u==ojciec) continue;
        sons.pb(dfs(u,v));
    }
    sort(sons.begin(), sons.end());
    if(id.find(sons) == id.end())
        id[sons] = ++new_id;
    return id[sons];
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m;

    if(m==n-1)
    {
        cout<<"TAK\n";
        return 0;
    }
    if(m>n)
    {
        cout<<"NIE\n";
        return 0;
    }

    for(int i=1;i<=m;++i)
    {
        int a,b;
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }

    find_cycle();

    // for(int i=1;i<=n;++i)
    //     cout<<i<<": "<<is_cycle[i]<<"\n";

    vector<int>hashes;
    for(auto &v: cycle)
        hashes.pb(dfs(v));
    if(sz(hashes)%2 == 1)
    {
        for(int i=1;i<sz(hashes);++i)
        {
            if(hashes[i]!=hashes[i-1])
            {
                cout<<"NIE";
                return 0;
            }
        }
        cout<<"TAK";
    }
    else
    {
        for(int i=2;i<sz(hashes);++i)
        {
            if(hashes[i]!=hashes[i-2])
            {
                cout<<"NIE";
                return 0;
            }
        }
        cout<<"TAK";
    }
	return 0;
}