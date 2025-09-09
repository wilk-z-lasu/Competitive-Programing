#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) ((int)(A).size())

constexpr int maxn = 1e5 + 7;

int n;
int h,k;
pi p[maxn];

constexpr int M = (1<<17);
int tree[2*M];//.f = max .s = idx
int lazy[2*M];

inline void Push(int v)
{
    if(lazy[v] == 0) return;
    tree[2*v] += lazy[v];
    tree[2*v+1] += lazy[v];
    lazy[2*v] += lazy[v];
    lazy[2*v+1] += lazy[v];
    lazy[v] = 0;
}
inline int last_tree(int val, int v = 1)//returns last element that is >= val
{
    while(v < M)
    {
        Push(v);
        v<<=1;
        if(tree[v+1] >= val)
            ++v;
    }
    return v - M + 1;
}

inline int get_tree(int poz, int v = 1, int l = 1, int r = M)
{
    if(r<poz || poz<l) return 0;
    if(l == r) return tree[v];
    Push(v);
    int mid = (l+r)>>1;
    if(poz <= mid)
        return get_tree(poz, v<<1, l, mid);
    else
        return get_tree(poz, (v<<1)+1, mid+1, r);
}

inline void add_tree(int a, int b, int v = 1, int l = 1, int r = M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        ++tree[v];
        ++lazy[v];
        return;
    }
    Push(v);
    int mid = (l+r)>>1;
    add_tree(a,b, v<<1, l, mid);
    add_tree(a,b, (v<<1)+1, mid+1, r);
    tree[v] = max(tree[v<<1], tree[(v<<1)+1]);
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>h>>k;
        p[i] = {h,k};
    }
    sort(p+1, p+n+1);

    for(int i=1;i<=n;++i)
    {
        h = p[i].f;
        k = p[i].s;

        int b = h-k+1, e = h;
        int S = get_tree(b);

        int L = 1;
        if(S != get_tree(1))
            L = (last_tree(S+1)+1);
        int R = min(last_tree(S), e);

        int S_odl = R - b + 1;

        add_tree(L, L + S_odl - 1);

        k-=S_odl;
        if(R+1 <= e)
            add_tree(R+1, e);
    }

    for(int i=1;i<M;++i)
        Push(i);
    int solv = 0;
    for(int i=1;i<=p[n].f;++i)
        solv += (tree[i+M-1]*(tree[i+M-1]-1))/2;
    cout<<solv;
	return 0;
}