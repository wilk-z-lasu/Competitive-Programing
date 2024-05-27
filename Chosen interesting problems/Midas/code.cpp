#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1000000+7;

vector<int>starts;

int n;
int l[maxn],r[maxn];
int q;
int x,y;

int layer[maxn];
int layer_nr[maxn];
int new_layer_nr[maxn];


inline void make_starts(int v=1)
{
    if(l[v]!=0)
        make_starts(l[v]);
    if(r[v]!=0)
        starts.push_back(r[v]);
}

inline void dfs(vector<int>&v, int depth=1)
{
    vector<int>left;
    vector<int>right;
    ++new_layer_nr[depth];
    for(auto &u: v)
    {
        layer[u]=depth;
        layer_nr[u]=new_layer_nr[depth];
        if(l[u]!=0)
            left.push_back(l[u]);
        if(r[u]!=0)
            right.push_back(r[u]);
    }
    if(!left.empty())
        dfs(left,depth+1);
    if(!right.empty())
        dfs(right,depth+1);
}

inline void solv()
{
    cin>>x>>y;
    if(layer[x]>layer[y] || (layer[x]==layer[y] && layer_nr[x]>=layer_nr[y]))
        cout<<"TAK\n";
    else
        cout<<"NIE\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>l[i]>>r[i];

    make_starts();

    dfs(starts);

    cin>>q;
    while(q--)
        solv();
    
    return 0;
}