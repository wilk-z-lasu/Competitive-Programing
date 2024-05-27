#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=3007;

int n;
int a,b;
bool pole_Juli[maxn];
bool zielone[maxn];
vector<int> vec[maxn];
vector<int> vec_odw[maxn];
int win[maxn];
bool vis[maxn];

void bfs()
{
    queue<int>q;

    for(int i=1;i<=n;i++)
    {
        vis[i]=0;
        win[i]=0;
        if(zielone[i])
        {
            vis[i]=1;
            q.push(i);
        }
    }
    while(!q.empty())
    {
        int v=q.front();
        q.pop();

        for(auto &u: vec_odw[v])
            if(!vis[u])
            {
                win[u]++;
                if(pole_Juli[u] || (!pole_Juli[u] && win[u]==vec[u].size()))
                {
                    vis[u]=1;
                    q.push(u);
                }
            }
    }
}

bool check(int v)
{
    int l=0;
    for(auto &u: vec[v])
        if(vis[u])
            l++;
    if((pole_Juli[v] && l>0) || (!pole_Juli[v] && l==vec[v].size()))
        return 1;
    else
        return 0;
}


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>a>>b;
    n=a+b;

    for(int i=1;i<=a;i++)
        pole_Juli[i]=1;

    for(int i=1;i<=n;i++)
    {
        int z,k; cin>>z>>k;
        if(z==1)
            zielone[i]=1;
        for(int j=0;j<k;j++)
        {
            int x; cin>>x;
            vec[i].push_back(x);
            vec_odw[x].push_back(i);
        }
    }

    bool flag=1;
    while(flag)
    {
        flag=0;
        
        bfs();
        for(int j=1;j<=n;j++)
            if(vis[j] && !check(j))
            {
                flag=1;
                zielone[j]=0;
                break;
            }
    }

    vector<int>solv;
    for(int i=1;i<=n;i++)
        if(vis[i])
            solv.push_back(i);

    cout<<solv.size()<<'\n';
    for(auto &u: solv)
        cout<<u<<'\n';

    return 0;
}