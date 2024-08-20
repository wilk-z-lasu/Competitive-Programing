#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
 
constexpr int maxn=2e5+7;
constexpr int inf=1e18+7;
 
int n,q;
int k, x;

constexpr int M=(1<<18);

struct node
{
    int prefix, sufix, whole, part; 
} tree[2*M];

void update(int v)
{
    int l=2*v;
    int r=2*v+1;

    tree[v].prefix=max(tree[l].prefix, tree[l].whole+tree[r].prefix);
    tree[v].sufix=max(tree[r].sufix, tree[r].whole+tree[l].sufix);
    tree[v].whole=tree[l].whole+tree[r].whole;
    tree[v].part=max({tree[v].prefix, tree[v].sufix, tree[v].whole, tree[l].part, tree[r].part, tree[l].sufix+tree[r].prefix});
}

void set_tree(int poz, int val)
{
    poz=poz+M-1;
    tree[poz]={val,val,val,val};
    poz/=2;
    while(poz)
    {
        update(poz);
        poz/=2;
    }
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
        cin>>k>>x;
        set_tree(k,x);
        cout<<tree[1].part<<'\n';
    }
    
    return 0;
}

/*
10 1
-10 6 -1 7 3 3 -6 -8 -9 9
2 -2
*/