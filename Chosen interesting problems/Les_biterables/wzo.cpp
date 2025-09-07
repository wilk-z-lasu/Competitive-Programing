#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn = 5e5+7;
int inf = 0;

int n,d;
int s,p;

vector<int>last;//last vector with 0 at the begining and d at the end
vector<int>akt;//current vector with 0 at the begining and d at the end

constexpr int M = (1<<20);
int tree[2*M];
int lazy[2*M];

inline void Push(int v)
{
    if(lazy[v]==0) return;
    tree[v*2] += lazy[v];
    lazy[v*2] += lazy[v];
    tree[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}

inline void add_tree(int a, int b, int val, int v=1, int l = 0, int r = M-1)//O(logn)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v] += val;
        lazy[v] += val;
        return;
    }
    int mid = (l+r)/2;
    Push(v);
    add_tree(a,b,val, 2*v, l, mid);
    add_tree(a,b,val, 2*v+1, mid+1, r);
    tree[v] = min(tree[2*v], tree[2*v+1]);
}
inline int get_tree(int a, int b, int v=1, int l = 0, int r = M-1)//O(logn)
{
    if(r<a || b<l) return 1e18;
    if(a<=l && r<=b)
        return tree[v];

    int mid = (l+r)/2;
    Push(v);
    int left = get_tree(a,b, 2*v, l, mid);
    int right = get_tree(a,b, 2*v+1, mid+1, r);
    return min(left,right);
}
void clear_tree(int a, int b) //O((b-a) * logn)
{
    for(int i = a; i <= b; ++i)
    {
        int poz = i + M;
        while(poz)
        {
            lazy[poz] = 0;
            tree[poz] = 0;
            poz /= 2;
        }
    }
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    cin>>n>>d;
    for(int iter=1;iter<=n;++iter)
    {
        cin>>s;
        akt.pb(0);
        for(int i=1;i<=s;++i)
        {
            cin>>p;
            akt.pb(p);
        }
        akt.pb(d);

        if(iter==1) 
        {
            last = akt;
            akt.clear();
            continue;
        }

        inf = max(sz(last), sz(akt));

        int it = 0;
        for(int i=0;i<sz(last);++i)
        {
            while(it+1 < sz(akt) && akt[it+1] <= last[i])
                ++it;

            add_tree(-inf+inf, it-i+inf, +last[i]);
            add_tree(it-i+1+inf, +inf+inf, -last[i]);
        }

        it = 0;
        for(int i=0;i<sz(akt);++i)
        {
            while(it+1 < sz(last) && last[it+1] < akt[i])
                ++it;
            
            
            add_tree(i-it+inf, +inf+inf, +akt[i]);
            add_tree(-inf+inf, i-it-1+inf, -akt[i]);
        }

        for(int i=-inf;i<=inf;++i)
            add_tree(i+inf,i+inf, abs(sz(akt) - sz(last) - i) * d);

        cout<<get_tree(-inf+inf, inf+inf)<<'\n';
        clear_tree(-inf+inf, inf+inf);

        last = akt;
        akt.clear();
    }
}