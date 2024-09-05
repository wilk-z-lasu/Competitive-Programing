#include <bits/stdc++.h>
using namespace std;
// #define f first
// #define s second
#define int long long

constexpr int maxn=2e5+7;

int n,q;
int t;
int zap;
int a,b;

constexpr int M=(1<<18);
int tree[2*M];

int s_push[2*M];
int k_push[2*M];

void Push(int v, int len)
{
    int l=2*v;
    int r=2*v+1;

    if(s_push[v]==0) return;

    int s_left = s_push[v];
    s_push[l] += s_left;
    k_push[l] += k_push[v];
    tree[l] += (s_left + s_left+k_push[v]*(len/2 - 1))*len/2 /2;

    int s_right = s_push[v] + len/2 * k_push[v];
    s_push[r] += s_right;
    k_push[r] += k_push[v];
    tree[r] += (s_right + s_right+k_push[v]*(len/2 - 1))*len/2 /2;

    s_push[v]=0;
    k_push[v]=0;
}

void add_tree(int a, int b, int s=1, int k=1, int v=1, int l=1, int r=M)
{
    // cout<<"add_tree("<<l<<" <-> "<<r<<" s: "<<s<<" k: "<<k<<endl;
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        s_push[v] += s + (l-a)*k;
        k_push[v] += k;
        tree[v]+=(s + (l-a)*k + s + (r-a)*k)*(r-l+1)/2;
        return;
    }
    Push(v, r-l+1);
    int mid=(l+r)/2;
    add_tree(a,b, s, k, 2*v, l,mid);
    add_tree(a,b, s, k, 2*v+1, mid+1,r);
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
        add_tree(i,i, t);
    }

    while(q--)
    {
        cin>>zap;
        if(zap==1)
        {
            cin>>a>>b;
            add_tree(a,b);
        }
        else if(zap==2)
        {
            cin>>a>>b;
            cout<<sum_tree(a,b)<<'\n';
        }
    }
    return 0;
}