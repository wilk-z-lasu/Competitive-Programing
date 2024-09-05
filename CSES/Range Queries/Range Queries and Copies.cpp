#include <bits/stdc++.h>
using namespace std;
// #define f first
// #define s second
#define int long long

constexpr int maxn=2e5+7;

int n,q;
int t;
int zap;
int a,b,k,x;


constexpr int M=(1<<18);
struct node
{
    int l, r, val;
};

int num;
int head[maxn];
vector<node>vec;

void prepere_tree()
{
    vec.push_back({0,0,0});
    head[++num]=vec.size();//1
    for(int i=1;i<2*M;i++)
        vec.push_back({2*i,2*i+1,0});
}
void set_start(int poz, int val)
{
    poz=poz+M-1;
    while(poz)
    {
        vec[poz].val+=val;
        poz/=2;
    }
}
void copy(int orginal)
{
    head[++num]=vec.size();
    vec.push_back(vec[head[orginal]]);
}

int sum_tree(int a, int b, int v, int l=1, int r=M)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b) return vec[v].val;
    int mid=(l+r)/2;
    return sum_tree(a,b, vec[v].l, l,mid) + sum_tree(a,b, vec[v].r, mid+1,r);
}

void update_tree(int poz, int val, int v, int l=1, int r=M)
{
    if(r<poz || poz<l) return;
    int mid=(l+r)/2;

    int copy_node;
    if(poz<=mid)//tworze lewe poddrzewo
    {
        copy_node=vec[v].l;
        vec[v].l=vec.size();
    }
    else//tworze prawe poddrzewo
    {
        copy_node=vec[v].r;
        vec[v].r=vec.size();
    }
    vec.push_back(vec[copy_node]);
    if(l==r)
    {
        vec[v].val=val;
        return;
    }
    update_tree(poz, val, vec[v].l, l,mid);
    update_tree(poz, val, vec[v].r, mid+1,r);
    vec[v].val = vec[vec[v].l].val + vec[vec[v].r].val;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    prepere_tree();

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>t;
        set_start(i,t);
    }

    while(q--)
    {
        cin>>zap;
        if(zap==1)
        {
            cin>>k>>a>>x;
            update_tree(a,x,head[k]);
        }
        else if(zap==2)
        {
            cin>>k>>a>>b;
            cout<<sum_tree(a,b, head[k])<<'\n';
        }
        else if(zap==3)
        {
            cin>>k;
            copy(k);
        }
    }
    return 0;
}