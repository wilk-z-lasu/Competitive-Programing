#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;
constexpr int inf=1e9+7;

int n,q;
int a,b;
int x;

constexpr int M=(1<<18);
int tree[2*M];

void set_tree(int poz, int val)
{
    poz=poz+M-1;
    tree[poz]=val;
    poz/=2;
    while(poz)
    {
        tree[poz]=min(tree[2*poz],tree[2*poz+1]);
        poz/=2;
    }
}

int get_min(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return inf;
    if(a<=l && r<=b) return tree[v];
    int mid=(l+r)/2;
    return min(get_min(a,b,2*v,l,mid), get_min(a,b,2*v+1,mid+1,r));
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        set_tree(i,x);
    }
    while(q--)
    {
        cin>>a>>b;
        cout<<get_min(a,b)<<'\n';
    }
    return 0;
}