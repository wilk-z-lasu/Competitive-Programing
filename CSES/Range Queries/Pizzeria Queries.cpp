#include <bits/stdc++.h>
using namespace std;
#define l first
#define r second
// #define int long long
 
constexpr int maxn=2e5+7;
constexpr int inf=2e9+7;

int n,q;
int p;
int zapytanie;

constexpr int M=(1<<18);

pair<int,int> tree[2*M];

void set_tree(int poz, int val)
{
    int v=poz+M-1;
    tree[v]={val-poz, val+poz};
    v/=2;
    while(v)
    {
        tree[v].l=min(tree[2*v].l, tree[2*v+1].l);
        tree[v].r=min(tree[2*v].r, tree[2*v+1].r);
        v/=2;
    }
}

int get_min_left(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return inf;
    if(a<=l && r<=b)
        return tree[v].l;
    int mid=(l+r)/2;
    return min(get_min_left(a,b,2*v,l,mid),get_min_left(a,b,2*v+1,mid+1,r));
}
int get_min_right(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return inf;
    if(a<=l && r<=b)
        return tree[v].r;
    int mid=(l+r)/2;
    return min(get_min_right(a,b,2*v,l,mid),get_min_right(a,b,2*v+1,mid+1,r));
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>p;
        set_tree(i, p);
    }

    while(q--)
    {
        cin>>zapytanie;
        if(zapytanie==1)
        {
            int k,x;
            cin>>k>>x;
            set_tree(k,x);
        }
        else
        {
            int k;
            cin>>k;
            cout<<min(get_min_left(1,k)+k, get_min_right(k,n)-k)<<'\n';
        }
    }
    
    return 0;
}