//O(n*sqrt(n))
#include <bits/stdc++.h>
using namespace std;
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn=5e5+7;

int n,m;
int tab[maxn];
int A[maxn],B[maxn];


vector<pi>vec;
int kan[maxn];
int ile[maxn];
vector<int>Open[maxn];
vector<int>Close[maxn];
int solv[maxn];

constexpr int M=(1<<19);
pi tree[2*M];

pi combine(pi x1, pi x2)
{
    if(x1.f==x2.f)
        return {x1.f, x1.s+x2.s};
    else if(x1.s <= x2.s)
        return {x2.f, x2.s-x1.s};
    else
        return {x1.f, x1.s-x2.s};
}

pi get_tree(int a, int b, int v=1, int l=1, int r=M)
{
    if(b<l || r<a) return {0,0};
    if(a<=l &&  r<=b)
        return tree[v];
    int mid=(l+r)/2;
    return combine(
        get_tree(a,b,2*v,l,mid),
        get_tree(a,b,2*v+1,mid+1,r));
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++)
        cin>>tab[i];

    for(int i=1;i<=n;i++)
        tree[i+M-1]={tab[i],1};
    for(int i=M-1;i>=1;i--)
        tree[i] = combine(tree[2*i], tree[2*i+1]);

    for(int i=1;i<=m;i++)
    {
        cin>>A[i]>>B[i];
        vec.push_back({A[i],i});
        vec.push_back({B[i],i});
        kan[i] = get_tree(A[i],B[i]).f;
        Open[A[i]].push_back(i);
        Close[B[i]].push_back(i);

    }

    sort(vec.begin(), vec.end());

    for(int i=1;i<=n;i++)
    {
        for(auto &u: Open[i])
            solv[u] = ile[kan[u]];
        ile[tab[i]]++;
        for(auto &u: Close[i])
        {
            solv[u] = ile[kan[u]] - solv[u];
            if(solv[u] > (B[u]-A[u]+1)/2)
                solv[u]=kan[u];
            else
                solv[u]=0;
        }
    }
    for(int i=1;i<=m;i++)
        cout<<solv[i]<<'\n';
    return 0;
}