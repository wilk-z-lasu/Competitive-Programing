#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;

int n,q;
int x[maxn];
int a,b;
int solv[maxn];

vector<pair<int,int>>vec[maxn];

constexpr int M=(1<<18);
int tree[2*M];

void set_tree(int poz, int val)
{
    poz=poz+M-1;
    tree[poz]=val;
    poz/=2;
    while(poz)
    {
        tree[poz] = tree[2*poz] + tree[2*poz+1];
        poz/=2;
    }
}

int get_sum(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b) return tree[v];
    int mid=(l+r)/2;
    return get_sum(a,b, 2*v, l,mid) + get_sum(a,b, 2*v+1, mid+1,r);
}

map<int,vector<int>>pos;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>x[i];

    for(int i=n;i>=1;i--)
        pos[x[i]].push_back(i);

    for(int i=1;i<=q;i++)
    {
        cin>>a>>b;
        vec[a].push_back({b,i});
    }

    for(auto &[num, list]: pos)
        set_tree(list.back(), 1);

    for(int i=1;i<=n;i++)
    {
        for(auto &[end,id]: vec[i])
            solv[id]=get_sum(i,end);

        set_tree(pos[x[i]].back(), 0);
        pos[x[i]].pop_back();
        if(!pos[x[i]].empty())
            set_tree(pos[x[i]].back(), 1);
    }

    for(int i=1;i<=q;i++)
        cout<<solv[i]<<'\n';
    return 0;
}