#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2e5+7;
constexpr int inf=1e9+7;

int n,q;
int x;
int zapytanie;
int a,b,u;
int k;

constexpr int M=(1<<18);
int tree[2*M];

int get_idx(int poz)
{
    int odp=0;
    poz=poz+M-1;
    while(poz)
    {
        odp+=tree[poz];
        poz/=2;
    }
    return odp;
}

void add_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) 
        return;
    if(a<=l && r<=b)
    {
        tree[v]+=val;
        return;
    }
    int mid=(l+r)/2;
    add_tree(a,b,val, 2*v, l, mid);
    add_tree(a,b,val, 2*v+1, mid+1, r);
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        add_tree(i,i,x);
    }
    while(q--)
    {
        cin>>zapytanie;
        if(zapytanie==1)
        {
            cin>>a>>b>>u;
            add_tree(a,b,u);
        }
        else
        {
            cin>>k;
            cout<<get_idx(k)<<'\n';
        }
    }
    return 0;
}