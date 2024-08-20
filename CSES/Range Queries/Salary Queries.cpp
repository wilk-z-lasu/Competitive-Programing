#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long
 
constexpr int maxn=2e5+7;
constexpr int inf=1e9+7;
 
int n,q;
int p[maxn];
char zapytanie;

constexpr int M=(1<<30);

struct node
{
    int val, l, r, parent;
};
vector<node> tree;

void create_node()
{
    tree.push_back({0,-1,-1,-1});
}
void add_tree(int poz, int val, int v=0, int l=1, int r=M)
{
    tree[v].val+=val;
    if(l==r) return;
    int mid=(l+r)/2;
    if(poz<=mid)
    {
        if(tree[v].l == -1)
        {
            create_node();
            tree[v].l=tree.size()-1;
            tree[tree.size()-1].parent=v;
        }
        add_tree(poz,val,tree[v].l,l,mid);
    }
    else
    {
        if(tree[v].r == -1)
        {
            create_node();
            tree[v].r=tree.size()-1;
            tree[tree.size()-1].parent=v;
        }
        add_tree(poz,val,tree[v].r,mid+1,r);
    }
}

int get_sum(int a, int b, int v=0, int l=1, int r=M)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b) return tree[v].val;
    int mid=(l+r)/2;
    int odp=0;
    if(tree[v].l != -1)
        odp+=get_sum(a,b,tree[v].l,l,mid);
    if(tree[v].r != -1)
        odp+=get_sum(a,b,tree[v].r,mid+1,r);
    return odp;
}
 
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    create_node();

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>p[i];
        add_tree(p[i],1);
    }

    while(q--)
    {
        cin>>zapytanie;
        if(zapytanie=='!')
        {
            int k,x;
            cin>>k>>x;
            add_tree(p[k],-1);
            p[k]=x;
            add_tree(p[k],1);
        }
        else
        {
            int a,b;
            cin>>a>>b;
            cout<<get_sum(a,b)<<'\n';
        }
    }
    return 0;
}