#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 5e5+7;
constexpr int inf = 1e18;

int n;
int w[maxn];

constexpr int M = (1<<19);
int tree[2*M];
int push[2*M];

void Push(int v)
{
    tree[v*2] += push[v];
    push[v*2] += push[v];
    tree[v*2+1] += push[v];
    push[v*2+1] += push[v];
    push[v] = 0;
}

void add_tree(int a, int b, int val, int v = 1, int l = 1, int r = M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v] += val;
        push[v] += val;
        return;
    }
    Push(v);
    int mid = (l+r)/2;
    add_tree(a,b,val, v*2, l, mid);
    add_tree(a,b,val, v*2+1, mid+1, r);
    tree[v] = max(tree[v*2], tree[v*2+1]);
}
int get_tree()
{
    int v=1;
    while(v<M)
    {
        Push(v);
        if(tree[v*2] > 0)
            v = v*2;
        else
            v = v*2+1;
    }
    return v-M+1;
}

int odp[maxn];
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>w[i];

    for(int i=1;i<=n;++i)
    {
        add_tree(i, i, w[i]);
        if(1 <= i-1) add_tree(1, i-1, -w[i]);
    }

    int solv=0;
    for(int i=1;i<=n;++i)
        solv+=w[i];
    odp[n] = solv;

    for(int i=n-1;i>=1;--i)
    {
        int poz = get_tree();
        solv -= w[poz];
        odp[i] = solv;

        add_tree(poz, poz, -inf);
        if(1 <= poz-1) add_tree(1, poz-1, +w[poz]);
    }
    for(int i=1;i<=n;++i)
        cout<<odp[i]<<" ";
    return 0;
}