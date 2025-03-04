#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long
#define pi pair<int,int>

constexpr int inf=1e9+7;
constexpr int maxn=2e5+7;

int n,k;
int a,b;
vector<int>vec[maxn];

bool blocked[maxn];
int siz[maxn];
int odl[maxn];
ll solv;

void cnt_siz(int v, int ojciec=-1)
{
    siz[v] = 1;
    for(auto &u: vec[v])
    {
        if(u==ojciec || blocked[u]) continue;
        cnt_siz(u,v);
        siz[v] += siz[u];
    }
}

int find_centroid(int v, int N, int ojciec=-1)
{
    for(auto &u: vec[v])
    {
        if(u==ojciec || blocked[u]) continue;
        if(siz[u] > N/2)
            return find_centroid(u,N,v);
    }
    return v;
}

void add_solv(int v, int ojciec=-1, int len=1)
{
    if(k-len>=0) solv += odl[k-len];
    for(auto &u: vec[v])
    {
        if(u==ojciec || blocked[u]) continue;
        add_solv(u,v, len+1);
    }
}
void recnt_odl(int v, int ojciec=-1, int len=1)
{
    odl[len]++;
    for(auto &u: vec[v])
    {
        if(u==ojciec || blocked[u]) continue;
        recnt_odl(u,v, len+1);
    }
}
void start_centroid(int v)
{
    cnt_siz(v);
    int N = siz[v];
    int C = find_centroid(v, N);

    // cout<<"centroid: "<<C<<" siz: "<<N<<endl;

    blocked[C]=1;
    odl[0]=1;

    for(auto &u: vec[C])
    {
        if(blocked[u]) continue;
        add_solv(u);
        recnt_odl(u);

        // cout<<"-----"<<solv<<"-----"<<endl;
        // for(int i=0;i<=N;i++)
        //     cout<<i<<": "<<odl[i]<<endl;
    }
    for(int i=0;i<=N;i++)
        odl[i]=0;

    for(auto &u: vec[C])
    {
        if(blocked[u]) continue;
        start_centroid(u);
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    if(k==1)
    {
        cout<<n-1;
        return 0;
    }
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    start_centroid(1);
    cout<<solv;
    return 0;
}