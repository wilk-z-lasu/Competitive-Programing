#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 107;
int t;

int n;//doesn't need cleaning
string s;//doesn't need cleaning
int Next[maxn];//doesn't need cleaning
int Start[maxn];//doesn't need cleaning
int Czas[maxn];//doesn't need cleaning

bool vis[maxn];//needs clearing
vector<int>postorder;//needs clearing

void dfs(int v) {
    vis[v]=1;
    int u = Next[v];
    if(!vis[u])//if I don't have a child Next[v]=v, so !vis[u]=false
        dfs(u);
    postorder.push_back(v);
}

int dp[maxn];//doesn't need cleaning

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=0;i<=n-1;i++)
        {
            cin>>s>>Start[i]>>Czas[i];
            if(s=="-")
                Next[i]=i;
            else if(s.size()==1)
                Next[i]=(s[0]-'0');
            else if(s.size()==2)
                Next[i]=(s[0]-'0')*10 + (s[1]-'0');
            //n-1<=99 => s.size()<=2, provided in a task 

            // cout<<Next[i]<<' '<<Start[i]<<' '<<Czas[i]<<endl; //debug inputu
        }

        //clearing
        for(int i=0;i<=n-1;i++)
            vis[i]=0;
        postorder.clear();

        //toposort
        for(int i=0;i<=n-1;i++)
            if(!vis[i])
                dfs(i);

        //count dp
        for(int v: postorder)
        {
            dp[v] = Start[v];
            dp[v] = max(dp[v], dp[Next[v]]);//if I don't have a child Next[v]=v

            dp[v] += Czas[v];
        }

        //get solution
        int solv=0;
        for(int i=0;i<=n-1;i++)
            solv=max(solv, dp[i]);
        cout<<solv<<'\n';
    }
    return 0;
}