#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 5e5+7;

int n,m;

int a,b;
vector<int>vec[maxn];

vector<int>s;
bool check()
{
    for(int i=3;i<=n;++i)
    {
        int lo=0;
        int hi=0;
        for(auto &u: vec[i])
        {
            if(s[u-1] > s[i-1])
                ++hi;
            else
                ++lo;
        }
        if(hi != lo) return 0;
    }
    return 1;
}
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }
    if(n>10) return 0;
    for(int i=1;i<=n;++i)
        s.pb(i);
    do
    {
        if(check())
        {
            cout<<"TAK\n";
            for(auto &u: s)
                cout<<u<<' ';
            return 0;
        }
    }
    while (std::next_permutation(s.begin(), s.end()));

    cout<<"NIE\n";
    return 0;
}