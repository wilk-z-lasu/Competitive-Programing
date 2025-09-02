#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) ((int)(A).size())

constexpr int maxn = (1e4 + 7);
constexpr int inf = (1e9 + 7);
constexpr int maxk = 10;
constexpr int maxmask = (1 << 10);

int n,m,d,k;
int a,b,c;

vector<pair<int,vector<int>>>vec[maxn];

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m>>d>>k;
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b;
        vector<int>costs;
        for(int j=0;j<k;++j)
        {
            cin>>c;
            costs.pb(c);
        }
        vec[a].pb({b,costs});
        vec[b].pb({a,costs});
    }

    for(int add = 0; add < k; ++add)
    {
        int maxi = 0;
        for(int v=1;v<=n;++v)
        {
            for(auto &xd : vec[v])
            {
                int u = xd.f;
                vector<int> costs = xd.s;
            }
        }
    }

	return 0;
}