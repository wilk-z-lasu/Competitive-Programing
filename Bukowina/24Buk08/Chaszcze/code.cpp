#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=1e6+7;

int n,m;
int q;
bool x;

int licz[maxn];

vector<vector<bool>>blocked;

void dfs1(int y, int x)//lewo gora
{
    // cout<<x<<" "<<y<<endl;
    if(!blocked[y][x] && blocked[y][x+1] && blocked[y+1][x])
    {
        licz[x+y]--;
        blocked[y][x]=1;
        dfs1(y-1,x);
        dfs1(y,x-1);
    }
}

void dfs2(int y, int x)
{
    // cout<<x<<" "<<y<<endl;
    if(!blocked[y][x] && blocked[y][x-1] && blocked[y-1][x])
    {
        licz[x+y]--;
        blocked[y][x]=1;
        dfs2(y+1,x);
        dfs2(y,x+1);
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;

    blocked.resize(n+2);
    for(int i=0;i<blocked.size();i++)
        blocked[i].resize(m+2);

    for(int i=0;i<=n+1;i++)
    {
        blocked[i][0]=1;
        blocked[i][m+1]=1;
    }
    for(int j=0;j<=m+1;j++)
    {
        blocked[0][j]=1;
        blocked[n+1][j]=1;
    }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            licz[i+j]++;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>x;
            if(x)
            {
                blocked[i][j]=1;
                licz[i+j]--;
            }
            else
                blocked[i][j]=0;
        }
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(blocked[i][j])
            {
                dfs1(i-1,j);
                dfs1(i,j-1);

                dfs2(i+1,j);
                dfs2(i,j+1);
            }
        }
    }

    cin>>q;
    while(q--)
    {
        int a,b;
        cin>>a>>b;

        // for(int i=1;i<=n;i++)
        // {
        //     for(int j=1;j<=m;j++)
        //         cout<<blocked[j][i]<<' ';
        //     cout<<endl;
        // }

        if(blocked[a][b])//nic sie nie zmnienia
        {
            if(licz[a+b]>=1)
                cout<<1<<'\n';
            else
                cout<<0<<'\n';
        }
        else
        {
            // cout<<"puste"<<endl;
            if(licz[a+b]<=1)
                cout<<0<<'\n';
            else
            {
                cout<<1<<'\n';
                blocked[a][b]=1;
                licz[a+b]--;
                dfs1(a-1,b);
                dfs1(a,b-1);

                dfs2(a+1,b);
                dfs2(a,b+1);
            }
        }
    }
    return 0;
}