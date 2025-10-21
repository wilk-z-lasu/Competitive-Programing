#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define pi pair<int,int>
#define sz(A) (int)A.size()

constexpr int maxn = 1e6+7;
constexpr int inf = 1e9+7;

int n,m;
int k,v;
vector<int> vec[maxn];
int where[maxn];
int empty_stack = 0;

pi prefix[maxn];
pi sufix[maxn];

bool check(vector<int> &x)
{
    for(int i=0;i<sz(x);++i)
        if(x[i]!=i+1)
            return false;
    return true;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        cin>>k;
        if(k==0) empty_stack = i;
        for(int j=1;j<=k;++j)
        {
            cin>>v;
            vec[i].pb(v);
            where[v] = i;
        }
    }

    if(check(vec[where[1]]))//case 1
    {
        int w = sz(vec[where[1]]);
        cout<<n-w<<"\n";
        for(int i = w + 1; i <= n; ++i)
            cout<<where[i]<<" "<<where[1]<<"\n";
    }
    else if(empty_stack != 0)//case 2
    {
        cout<<n<<'\n';
        for(int i = 1; i <= n; ++i)
            cout<<where[i]<<" "<<empty_stack<<"\n";
    }
    else//case 3
    {
        prefix[0] = {inf, 0};
        sufix[m+1] = {inf, 0};
        for(int i=1;i<=m;++i)
        {
            prefix[i] = {vec[i].back(),i};
            prefix[i] = min(prefix[i], prefix[i-1]);
        }
        for(int i=m;i>=1;--i)
        {
            sufix[i] = {vec[i].back(),i};
            sufix[i] = min(sufix[i], sufix[i+1]);
        }
        pair<int,pi> del = {inf, {0, 0}};//{value, stack}
        for(int i=1;i<=m;++i)
        {
            pi opt = min(prefix[i-1], sufix[i+1]);
            if(opt.f < vec[i][0])
                del = min(del, {sz(vec[i]), {i, opt.s}});
        }
        if(del.f == inf)
        {
            cout<<-1<<"\n";
            return 0;
        }
        for(auto &u: vec[del.s.f])
            where[u] = del.s.s;
        cout<<n + del.f<<"\n";
        for(int i=1;i<=del.f;++i)
            cout<<del.s.f<<" "<<del.s.s<<"\n";
        for(int i=1;i<=n;++i)
            cout<<where[i]<<" "<<del.s.f<<"\n";
    }
    return 0;
}