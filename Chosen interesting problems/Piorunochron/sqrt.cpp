#include<bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)A.size()

constexpr int maxn = 5e5+7;
constexpr int SQRT = 710;


int N;
int H[maxn];
int SQ[maxn];

unordered_map<int,int> First;
unordered_map<int,int> Last;

vector<int>vec;
vector<int>val;

constexpr int M = (1<<19);
int tree[2*M];
inline void max_tree(int a, int b, int val, int v=1, int l = 1, int r = M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v] = max(tree[v], val);
        return;
    }
    int mid = (l+r)/2;
    max_tree(a,b,val, 2*v, l, mid);
    max_tree(a,b,val, 2*v+1, mid+1, r);
}

inline int get(int poz)
{
    poz = poz + M - 1;
    int odp = 0;
    while(poz)
    {
        odp = max(odp, tree[poz]);
        poz/=2;
    }
    return odp;
}

void W(int &x)
{
    x = 0;
    char c = getchar_unlocked();
    while(c < '0' || '9' < c)
        c = getchar_unlocked();
    while('0' <= c && c <= '9')
    {
        x = x*10 + c-'0';
        c = getchar_unlocked();
    }
}
int32_t main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie();
    // cout.tie();

    for(int i=1;i<maxn;++i)
    {
        int x = sqrt(i);
        if(x*x != i) ++x;
        SQ[i] = x;
    }

    // cin >> N;
    W(N);
    for(int i = 1; i <= N; ++i)
    {
        // cin>>H[i];
        W(H[i]);
        vec.pb(H[i]);

        if(First.find(H[i]) == First.end())
            First[H[i]] = i;
        else
            First[H[i]] = min(First[H[i]], i);
        
        if(Last.find(H[i]) == Last.end())
            Last[H[i]] = i;
        else
            Last[H[i]] = max(Last[H[i]], i);
    }

    sort(vec.begin(), vec.end(), greater<int>());
    vec.pb(-1);
    for(int i=0;i+1<sz(vec);++i)
        if(vec[i]!=vec[i+1])
            val.pb(vec[i]);

    vector<int> todo;
    for(int i=0; i < sz(val) && i <= SQ[maxn-1]; ++i)
    {
        todo.pb(First[val[i]]);
        todo.pb(Last[val[i]]);
    }
        
    for(auto &v: todo)
    {
        pi range = {0, 0};
        for(int i = 1; v + range.s+1 <= N; ++i)
        {
            range.f = range.s+1;
            range.s = i*i;
            max_tree(v + range.f, min(N, v + range.s), H[v] + i);
        }
        range = {0, 0};
        for(int i = 1; v - (range.s+1) >= 1; ++i)
        {
            range.f = range.s+1;
            range.s = i*i;
            max_tree(max((int)1, v - range.s), v - range.f, H[v] + i);
        }
    }

    for(int i=1;i<=N;++i)
        cout<<max((int)0, get(i)-H[i])<<'\n';
    return 0;
}