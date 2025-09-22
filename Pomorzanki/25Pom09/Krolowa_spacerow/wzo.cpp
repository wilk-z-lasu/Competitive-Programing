#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pi pair<int,int>
#define f first
#define s second
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 1e6+7;
constexpr int inf = 1e18+7;

int n;
int w[maxn],d[maxn];

int In[maxn];
int akt[maxn];

int best[maxn];
int S[maxn];

void BFS()
{
    queue<int>q;
    for(int i=1;i<=n;++i)
        if(In[i]==0)
            q.push(i);

    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        --In[w[v]];
        
        S[w[v]] = max(S[w[v]], S[v]);
        S[w[v]] = max(S[w[v]], best[w[v]]+best[v]+d[v]);
        best[w[v]] = max(best[w[v]], best[v]+d[v]);
        if(In[w[v]] == 0)
            q.push(w[v]);
    }
}

bool vis[maxn];
vector<int>cycle;
void dfs(int v)
{
    while(!vis[v])
    {
        // cout<<v<<" -> "<<w[v]<<endl;
        vis[v] = 1;
        cycle.pb(v);
        v = w[v];
    }
}

deque<pi>dq;
void Del(int v)
{
    if(!dq.empty() && dq.front().f == v) dq.pop_front();
}
void Add(int v, int val)
{
    while(!dq.empty() && dq.back().s <= val) dq.pop_back();
    dq.push_back({v,val});
}
int Get()
{
    if(dq.empty()) return -inf;
    else return dq.front().s;
}

void W(int &x)
{
    x = 0;
    char c = getchar();
    while(c < '0' || '9' < c)
        c = getchar();
    while('0' <= c && c <= '9')
    {
        x = x*10 + c-'0';
        c = getchar();
    }
}
int32_t main()
{
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);

    // cin>>n;
    W(n);
    for(int i=1;i<=n;++i)
    {
        // cin>>w[i]>>d[i];
        W(w[i]); W(d[i]);
        ++In[w[i]];
    }
    BFS();

    int solv = 0;
    for(int i=1; i<=n; ++i)
    {
        if(In[i] != 0 && !vis[i])
        {
            int odp = 0;
            cycle.clear();
            dfs(i);
            int W = sz(cycle);
            for(int i=0;i<W;++i)
                cycle.pb(cycle[i]);

                int pref = 0;
            dq.clear();
            for(int i=0;i<2*W;++i)
            {
                int v = cycle[i];
                Del(v);
                odp = max(odp, Get()+best[v]+pref);
                Add(v, best[v] - pref);
                pref += d[v];
            }

            for(auto &v: cycle)
                odp = max(odp, S[v]);

            solv += odp;
        }
    }
    cout<<solv;
    return 0;
}