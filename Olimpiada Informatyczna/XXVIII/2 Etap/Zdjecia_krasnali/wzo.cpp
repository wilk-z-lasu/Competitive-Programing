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
vector<pi>vec[maxn];

void NIE()
{
    cout<<"NIE\n";
    exit(0);
}

int In[maxn];
bool taken[maxn];
vector<int>preorder;
void BFS()
{
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int v=q.front();
        q.pop();
        if(v==2) continue;
        preorder.pb(v);
        for(auto &u: vec[v])
        {
            if(taken[u.s]) continue;
            taken[u.s] = 1;
            if(++In[u.f] == sz(vec[u.f])/2)
                q.push(u.f);
            else if(u.f > 2 && In[u.f] > sz(vec[u.f])/2)
                NIE();
        }
    }
}

int num;
int solv[maxn];

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b;
        vec[a].pb({b,i});
        vec[b].pb({a,i});
    }
    if(m==0)
    {
        cout<<"TAK\n";
        for(int i=1;i<=n;++i)
            cout<<i<<' ';
        return 0;
    }
    if(sz(vec[1]) == 0 || sz(vec[2]) == 0)
        NIE();

    BFS();
    for(int i=3;i<=n;++i)
        if(In[i] != sz(vec[i])/2)
            NIE();
    
    for(auto &u: preorder)
        solv[u] = ++num;
    solv[2] = ++num;

    for(int i=1;i<=n;++i)
        if(solv[i]==0)
            solv[i] = ++num;
            
    cout<<"TAK\n";
    for(int i=1;i<=n;++i)
        cout<<solv[i]<<" ";
}