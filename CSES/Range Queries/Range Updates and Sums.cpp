#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2e5+7;

int n,q;
int t;
int zap;
int a,b,x;

constexpr int M=(1<<18);
int tree[2*M];
int push_add[2*M];
int push_set[2*M];

void Push(int v, int len)
{
    int l=2*v;
    int r=2*v+1;

    if(push_set[v] != 0)
    {
        push_set[l] = push_set[v];
        push_add[l] = 0;
        tree[l] = push_set[l]*len/2;

        push_set[r] = push_set[v];
        push_add[r] = 0;
        tree[r] = push_set[r]*len/2;

        push_set[v]=0;
    }
    if(push_add[v] != 0)
    {
        push_add[l] += push_add[v];
        tree[l] += push_add[v]*len/2;

        push_add[r] += push_add[v];
        tree[r] += push_add[v]*len/2;

        push_add[v] = 0;
    }
}

void set_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v] = val*(r-l+1);
        push_set[v] = val;
        push_add[v] = 0;
        return;
    }
    Push(v, r-l+1);
    int mid=(l+r)/2;
    set_tree(a,b,val, 2*v, l,mid);
    set_tree(a,b,val, 2*v+1, mid+1,r);
    tree[v] = tree[2*v] + tree[2*v+1];
}

void add_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v] += val*(r-l+1);
        push_add[v] += val;
        return;
    }
    Push(v, r-l+1);
    int mid=(l+r)/2;
    add_tree(a,b,val, 2*v, l,mid);
    add_tree(a,b,val, 2*v+1, mid+1,r);
    tree[v] = tree[2*v] + tree[2*v+1];
}

int sum_tree(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b)
        return tree[v];
    Push(v, r-l+1);
    int mid=(l+r)/2;
    int odp = sum_tree(a,b, 2*v, l,mid) + sum_tree(a,b, 2*v+1, mid+1,r);
    tree[v] = tree[2*v] + tree[2*v+1];
    return odp;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;

    for(int i=1;i<=n;i++)
    {
        cin>>t;
        set_tree(i,i,t);
    }
    while(q--)
    {
        cin>>zap;
        if(zap==1)
        {
            cin>>a>>b>>x;
            add_tree(a,b,x);
        }
        else if(zap==2)
        {
            cin>>a>>b>>x;
            set_tree(a,b,x);
        }
        else if(zap==3)
        {
            cin>>a>>b;
            cout<<sum_tree(a,b)<<'\n';
        }
    }
    return 0;
}