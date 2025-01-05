#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long
#define pi pair<int,int>

constexpr int inf=1e9+7;
constexpr int maxn = 40007;
constexpr int maxm = 1e6+7;

int n,m;
int a,b;
vector<int>vec[maxn];

int odl[3][maxn];
void prepere()
{
    for(int i=0;i<3;++i)
        for(int j=0;j<maxn;++j)
            odl[i][j]=-1;
}
void bfs(int opt)
{
    queue<pi>q;
    q.push({opt,0});

    while(!q.empty() && q.front().s<=2)
    {
        int v = q.front().f;
        int len = q.front().s;
        q.pop();

        if(odl[opt][v]==-1)
            odl[opt][v]=len;
        else
            continue;

        for(auto &u: vec[v])
            if(odl[opt][u]==-1)
                q.push({u,len+1});
    }
}

int layer[6];
int freelacers;


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;

    for(int i=1;i<=m;++i)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }
    
    prepere();
    bfs(1);
    bfs(2);

    layer[0]=layer[5]=1;

    for(int i=3;i<=n;++i)
    {
        if(odl[1][i] == 1)
            ++layer[1];
        else if(odl[1][i] == 2)
            ++layer[2];
        else if(odl[2][i] == 1)
            ++layer[4];
        else if(odl[2][i] == 2)
            ++layer[3];
        else
            ++freelacers;
    }

    // for(int i=0;i<=5;i++)
    //     cout<<i<<": "<<layer[i]<<endl;

    if(layer[1]>=layer[4])
        layer[2]+=freelacers;
    else
        layer[3]+=freelacers;

    ll solv = 0;
    solv += layer[1];// za layer 0
    for(int i=1;i<=4;i++)// za layers 1-4
        solv += (ll)layer[i] *  (layer[i-1] + layer[i] + layer[i+1] - 1);
    solv += layer[4];// za layer 5

    solv/=2;
    solv-=m;
    cout<<solv;
    return 0;
}