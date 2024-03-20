#include <bits/stdc++.h>
using namespace std;
#define int short
#define f first
#define s second

int n;
int odp=0;

// int test_pamieci[207][207][207];
vector<int>vec[207];
// set<int> mapa[207];//<- graf dwudzielny <- do przepisania na graf
vector<int> graf[207];//<- graf dwudzielny <- ten prawdziwy

bool gorne[207];
bool dolne[207];

void BFS(int p)
{
    queue<int>q;
    bool was[207];
    memset(was,0,sizeof(was));

    q.push(p);
    was[p]=1;

    while(!q.empty())
    {
        int top=q.front();
        q.pop();
        
        if(dolne[top]) graf[p].push_back(top);
            // graf[p][top]=1;
            // mapa[p].insert(top);
            // mapa[p][top]=1;
        for(auto u: vec[top])
        {
           //if (q.size() < 2000)
            if(!was[u]) 
            {
                q.push(u);
                was[u]=1;
            }
        }

    }
}

int timer=0;
int partner[207];
int vis[207];

bool polaczenie(int v)
{
    vis[v]=timer;
    //po dobroci
    for(auto u: graf[v])
    {
        if(partner[u]==0)
        {
            partner[u]=v;
            return true;
        }
    }
    //na sile
    for(auto u: graf[v])
    {
        if(vis[partner[u]]!=timer && polaczenie(partner[u]))
        {
            partner[u]=v;
            return true;
        }
    }
    return false;
} 

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<n;i++)
    {
        int m;cin>>m;
        for(int j=0;j<m;j++)
        {
            int x;cin>>x;
            vec[i].push_back(x);
            if(i==1 && x==n) odp=1;
            else if(x==n) dolne[i]=1;
            else if(i==1) gorne[x]=1;
        }
    }

    for(int i=1;i<=n;i++)
    {
        if(gorne[i]) BFS(i);
    }


    for(int i=1;i<=n;i++)
    {
        if(gorne[i])
        {
            polaczenie(i);
            timer++;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(dolne[i] && partner[i]!=0) 
        {
            // cout<<i<<" ma partnera: "<<partner[i]<<endl;
            odp++;
        }
    }
    cout<<odp;

    return 0;
}