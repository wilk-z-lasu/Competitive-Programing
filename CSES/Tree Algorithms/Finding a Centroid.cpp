#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;

int n;
int a,b;
vector<int>vec[maxn];

int siz[maxn];
void find_siz(int v=1, int parent=1)
{
    siz[v]=1;
    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        find_siz(u,v);
        siz[v]+=siz[u];
    }
}
int find_centroid(int v=1, int parent=1)
{
    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        if(siz[u]>siz[1]/2)
            return find_centroid(u,v);
    }
    return v;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    find_siz();
    cout<<find_centroid();

    return 0;
}