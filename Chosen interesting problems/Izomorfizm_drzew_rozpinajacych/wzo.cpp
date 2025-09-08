#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) ((int)(A).size())

constexpr int maxn = 2e5 + 7;

int n,m;
vector<int> vec[maxn];
bool vis[maxn];
vector<int> preorder;
bool is_cycle[maxn];

void find_cycle(int v=1, int ojciec = -1)
{
    vis[v]=1;
    preorder.pb(v);
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        if(!vis[u])
            find_cycle(u, v);
        else
        {
            while(preorder.back()!=u)
            {
                is_cycle[preorder.back()]=1;
                preorder.pop_back();
            }
            is_cycle[preorder.back()]=1;
            return;
        }
    }
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m;

    if(m==n-1)
    {
        cout<<"TAK\n";
        return 0;
    }
    if(m>n)
    {
        cout<<"NIE\n";
        return 0;
    }

    find_cycle();
    for(int i=1;i<=n;++i)
        cout<<i<<": "<<is_cycle[i]<<"\n";
	return 0;
}