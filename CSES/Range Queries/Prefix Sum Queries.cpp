#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
 
constexpr int maxn=2e5+7;
constexpr int inf=1e16+7;
 
int n,q;
int x[maxn];
int zapytanie;

constexpr int M=(1<<18);
int tree[2*M];
int push[2*M];

void Push(int v)
{
    int l=2*v;
    int r=2*v+1;
    tree[l]+=push[v];
    push[l]+=push[v];
    tree[r]+=push[v];
    push[r]+=push[v];
    push[v]=0;
}
void add_tree(int a, int b, int val, int v=1, int l=0, int r=M-1)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v]+=val;
        push[v]+=val;
        return;
    }
    // cout<<"push v="<<v<<endl;
    if(push[v]!=0)
        Push(v);

    int mid=(l+r)/2;
    add_tree(a,b,val, 2*v,l,mid);
    add_tree(a,b,val, 2*v+1,mid+1,r);
    tree[v]=max(tree[2*v],tree[2*v+1]);
}

int get_max(int a, int b, int v=1, int l=0, int r=M-1)
{
    if(r<a || b<l) return -inf;
    if(a<=l && r<=b) return tree[v];
    if(push[v]!=0)
        Push(v);
    int mid=(l+r)/2;
    tree[v]=max(tree[2*v],tree[2*v+1]);
    return max(get_max(a,b, 2*v,l,mid),get_max(a,b, 2*v+1,mid+1,r));
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i];
        add_tree(i,n,x[i]);
    }

    while(q--)
    {
        cin>>zapytanie;
        if(zapytanie==1)
        {
            int k,u;
            cin>>k>>u;
            add_tree(k,n,-x[k]);
            x[k]=u;
            add_tree(k,n,x[k]);
        }
        else
        {
            int a,b;
            cin>>a>>b;
            cout<<max((int)0,get_max(a,b)-get_max(a-1,a-1))<<'\n';
        }
    }
    
    return 0;
}