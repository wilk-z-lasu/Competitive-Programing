#include <bits/stdc++.h>
using namespace std;
// #define int long long
constexpr int maxn=30007;

int n;
int X1,Y1,X2,Y2;

vector<pair<int,int>>Open[maxn];
vector<pair<int,int>>Close[maxn];

constexpr int M=(1<<15);

struct node
{
    int val, ile, lazy;
} tree[2*M];

void Push(int v)
{
    if(tree[v].lazy==0) return;
    int l=2*v;
    int r=2*v+1;

    tree[l].val+=tree[v].lazy;
    tree[l].lazy+=tree[v].lazy;

    tree[r].val+=tree[v].lazy;
    tree[r].lazy+=tree[v].lazy;

    tree[v].lazy=0;
}

void add_tree(int a, int b, int add, int v=1, int l=0, int r=M-1)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v].val+=add;
        tree[v].lazy+=add;
        return;
    }
    Push(v);
    int mid=(l+r)/2;
    add_tree(a,b,add, 2*v, l,mid);
    add_tree(a,b,add, 2*v+1, mid+1,r);

    if(tree[2*v].val == tree[2*v+1].val)
    {
        tree[v].val=tree[2*v].val;
        tree[v].ile=tree[2*v].ile+tree[2*v+1].ile;
    }
    else if(tree[2*v].val < tree[2*v+1].val)
    {
        tree[v].val=tree[2*v].val;
        tree[v].ile=tree[2*v].ile;
    }
    else
    {
        tree[v].val=tree[2*v+1].val;
        tree[v].ile=tree[2*v+1].ile;
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>X1>>Y1>>X2>>Y2;
        Open[X1].push_back({Y1,Y2-1});
        Close[X2].push_back({Y1,Y2-1});
    }

    for(int i=2*M-1;i>=1;i--)
    {
        if(i>=M)
            tree[i].ile=1;
        else
            tree[i].ile = tree[2*i].ile + tree[2*i+1].ile;
    }
    int solv=0;
    for(int i=0;i<maxn;i++)
    {
        for(auto &[a,b]: Open[i])
            add_tree(a,b,1);

        for(auto &[a,b]: Close[i])
            add_tree(a,b,-1);

        solv+=(M-tree[1].ile);
    }
    cout<<solv;
}