#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;

int q;
int n;
int a,b;

vector<int>vec[maxn];
int l[maxn];
int r[maxn];
stack<int>S;
int dp[maxn];

void bfs()
{
    queue<pair<int,int>>q;//.f- wierzcholek .s- parent
    q.push({1,1});
    while(!q.empty())
    {
        pair<int,int> top = q.front();
        q.pop();

        S.push(top.f);

        for(auto &u: vec[top.f])
        {
            if(u==top.s) continue;
            if(l[top.f]==0) l[top.f]=u;
            else r[top.f]=u;

            q.push({u,top.f});
        }
    }
}

int solv_minus;
void dfs(int v, int flow)
{
    flow=min(flow,dp[v]-1);
    solv_minus++;
    // cout<<"v: "<<v<<endl;
    if(flow==0) return;
    if(l[v]!=0) dfs(l[v],flow-1);
    if(r[v]!=0) dfs(r[v],flow-1);
}

void clear()
{
    for(int i=1;i<=n;i++)
    {
        l[i]=0;
        r[i]=0;
        dp[i]=0;
        vec[i].clear();
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>q;

    while(q--)
    {
        cin>>n;
        for(int i=1;i<=n-1;i++)
        {
            cin>>a>>b;
            vec[a].push_back(b);
            vec[b].push_back(a);
        }

        // cout<<"wczytalem dane"<<endl;
        bfs();
        // cout<<"bfs dziala"<<endl;


        while(!S.empty())
        {
            int v = S.top();
            S.pop();

            // cout<<"v: "<<v<<" dp[l[v]]: "<<dp[l[v]]<<" dp[r[v]]: "<<dp[r[v]]<<endl;
            if(dp[l[v]]==dp[r[v]])
                dp[v]=dp[l[v]]+1;
            else
                dp[v]=min(dp[l[v]],dp[r[v]])+2;
        }
        // cout<<"stack i dp dziala"<<endl;

        // for(int i=1;i<=n;i++)
            // cout<<i<<": dp[i]= "<<dp[i]<<" l:"<<l[i]<<" r:"<<r[i]<<endl;

        solv_minus=0;
        dfs(1,dp[1]-1);
        cout<<n-solv_minus<<'\n';
        clear();
    }
    return 0;
}