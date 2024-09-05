#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=300+7;
constexpr int inf=1e9+7;

int t;
 
int n;
char x;
bool blocked[maxn][maxn];
int min_path;
 
int Y_a, X_a;
int Y_b, X_b;
 
struct point
{
    int y, x;
};
 
int odl_B[maxn][maxn];
 
vector<int>vec[maxn*maxn];
vector<int>vec_odw[maxn*maxn];
int create(point p)
{
    return (p.y-1)*n+p.x;
}
 
int vis[maxn][maxn];
void prepere_vis()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            vis[i][j]=0;
    for(int i=0;i<=n+1;i++)
    {
        vis[0][i]=1;
        vis[n+1][i]=1;
        vis[i][0]=1;
        vis[i][n+1]=1;
    }
}
void odl_from_B()
{
    prepere_vis();
 
    queue<point>q;
    vis[Y_b][X_b]=1;
    odl_B[Y_b][X_b]=0;
    q.push({Y_b, X_b});
    while(!q.empty())
    {
        point obc = q.front();
        q.pop();
        for(int add_y: {-1,0,1})
            for(int add_x: {-1,0,1})
                if(abs(add_x) != abs(add_y) && !vis[obc.y+add_y][obc.x+add_x] && !blocked[obc.y+add_y][obc.x+add_x])
                {
                    vis[obc.y+add_y][obc.x+add_x]=1;
                    odl_B[obc.y+add_y][obc.x+add_x] = odl_B[obc.y][obc.x] + 1;
                    q.push({obc.y+add_y,obc.x+add_x});
                }
    }
}
 
vector<int>layers[maxn*maxn];//0=A min_path=B
 
void dfs(point v, int czas=0)
{
    layers[czas].push_back(create(v));
    vis[v.y][v.x]=1;
    if(v.y+1<=n && odl_B[v.y+1][v.x] == odl_B[v.y][v.x]-1) 
    {
        if(!vis[v.y+1][v.x])
            dfs({v.y+1, v.x}, czas+1);
        vec[create({v.y, v.x})].push_back(create({v.y+1, v.x}));
        vec_odw[create({v.y+1, v.x})].push_back(create({v.y, v.x}));
 
    }
    if(v.y-1>=1 && odl_B[v.y-1][v.x] == odl_B[v.y][v.x]-1) 
    {
        if(!vis[v.y-1][v.x])
            dfs({v.y-1, v.x}, czas+1);
        vec[create({v.y, v.x})].push_back(create({v.y-1, v.x}));
        vec_odw[create({v.y-1, v.x})].push_back(create({v.y, v.x}));
 
    }
    if(v.x+1<=n && odl_B[v.y][v.x+1] == odl_B[v.y][v.x]-1) 
    {
        if(!vis[v.y][v.x+1])
            dfs({v.y, v.x+1}, czas+1);
        vec[create({v.y, v.x})].push_back(create({v.y, v.x+1}));
        vec_odw[create({v.y, v.x+1})].push_back(create({v.y, v.x}));
 
    }
    if(v.x-1>=1 && odl_B[v.y][v.x-1] == odl_B[v.y][v.x]-1) 
    {
        if(!vis[v.y][v.x-1])
            dfs({v.y, v.x-1}, czas+1);
        vec[create({v.y, v.x})].push_back(create({v.y, v.x-1}));
        vec_odw[create({v.y, v.x-1})].push_back(create({v.y, v.x}));
 
    }
}
 
int added[maxn*maxn];

int lewo[maxn*maxn];
int prawo[maxn*maxn];
void wypisz()
{
    int numer=0;
    for(auto &v: layers[min_path/2])
        lewo[v]=prawo[v]=++numer;
 
    int layer2 = min_path/2 + 1;
    for(int layer = min_path/2 - 1; layer >= 0; layer--)
    {
        for(auto &v: layers[layer])
        {
            lewo[v]=inf;
            prawo[v]=-inf;
            for(auto &u: vec[v])
            {
                lewo[v]=min(lewo[v], lewo[u]);
                prawo[v]=max(prawo[v], prawo[u]);
            }
        }
        for(auto &v: layers[layer2])
        {
            lewo[v]=inf;
            prawo[v]=-inf;
            for(auto &u: vec_odw[v])
            {
                lewo[v]=min(lewo[v], lewo[u]);
                prawo[v]=max(prawo[v], prawo[u]);
            }
        }
        for(auto &v1: layers[layer])
        {
            bool flag=1;
            for(auto &v2: layers[layer2])
            {
                if(lewo[v1]>=lewo[v2] && prawo[v2]>=prawo[v1])
                {
                    flag=0;
                    break;
                }
            }
            if(flag)
            {
                cout<<"A\n";
                return;
            }
        }

        layer2++;
    }
 
    cout<<"B\n";
    return;
}
 
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    cin>>t;
 
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                cin>>x;
                blocked[i][j]=0;
                if(x=='A')
                    Y_a=i, X_a=j;
                else if(x=='B')
                    Y_b=i, X_b=j;
                else if(x=='#')
                    blocked[i][j]=1;
            }
        }
        odl_from_B();
 
        min_path = odl_B[Y_a][X_a];
        if(min_path%2==1)
            cout<<"A\n";
        else
        {
            prepere_vis();
            dfs({Y_a, X_a});
            
            wypisz();
        }
        for(int i=0;i<=n*n;i++)
        {
            vec[i].clear();
            vec_odw[i].clear();
            layers[i].clear();
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                odl_B[i][j]=0;
    }
    return 0;
}