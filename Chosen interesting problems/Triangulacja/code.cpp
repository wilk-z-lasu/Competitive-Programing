#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=100007;
constexpr int LOG = 18; //2^17=131072

int n;

vector<int> kolory[maxn];
vector<int>vec[maxn];

int up[maxn][LOG];
int depth[maxn];

int solv[maxn];

void dfs(int a, int ojciec)
{
    for(int b: vec[a]) 
    {
        if(b==ojciec) continue;
        depth[b] = depth[a] + 1;
        up[b][0] = a;
        for(int j = 1; j < LOG; j++) 
            up[b][j] = up[up[b][j-1]][j-1];
        dfs(b,a);
    }
}

int get_lca(int a, int b) 
{
    if(depth[a] < depth[b]) swap(a, b);

    int k = depth[a] - depth[b];
    for(int j = LOG - 1; j >= 0; j--) 
        if(k & (1 << j)) 
            a = up[a][j]; // parent of a

    if(a == b)
        return a;
    
    for(int j = LOG - 1; j >= 0; j--) 
    {
        if(up[a][j] != up[b][j]) 
        {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

int wyn;
bool vis[maxn];
int DFS(int v)
{
    int suma=0;
    vis[v]=1;
    for(auto u: vec[v])
        if(!vis[u]) 
            suma+=DFS(u);
    // cout<<v<<" <- "<<suma<<endl;
    solv[v]+=suma;
    return solv[v];
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    if(n==3)
    {
        cout<<0;
        return 0;
    }

    map<pair<int,int>,int> mapa;

    for(int i=1;i<=n-2;i++)
    {
        int trojkat[3]; int d; cin>>trojkat[0]>>trojkat[1]>>trojkat[2]>>d;
        kolory[d].push_back(i);
        sort(trojkat,trojkat+3);

        for(int j=0;j<=2;j++)
        {
            if(trojkat[j]>trojkat[(j+1)%3]) swap(trojkat[j],trojkat[(j+1)%3]);
            if(mapa.find({trojkat[j],trojkat[(j+1)%3]})!=mapa.end())
            {
                int a=i;
                pair<pair<int,int>,int> c= *mapa.find({trojkat[j],trojkat[(j+1)%3]});
                int b=c.s;
                // cout<<a<<"->"<<b<<endl;
                // cout<<b<<"->"<<a<<endl;
                vec[a].push_back(b);
                vec[b].push_back(a);
                // if(a>b) swap(a,b);//makes a<=b
                // con[{a,b}]=1;
            }
            mapa[{trojkat[j],trojkat[(j+1)%3]}]=i;
        }
    }

    dfs(1,1);//ukorzeniam w 1

    for (int i = 0; i <= n; ++i)
    {
        if (kolory[i].size() > 1)
        {
            int akt_lca=kolory[i][0];
            for (int j = 1; j < kolory[i].size(); ++j)
            {
                --solv[akt_lca];
                --solv[kolory[i][j]];
                akt_lca = get_lca(akt_lca, kolory[i][j]);
                solv[akt_lca] += 2;
            }
        }
    }
    DFS(1);

    for (int i=1;i<=n-2;i++)
    {
        if(solv[i]==0) wyn++;
    }
    cout << wyn - 1;
    return 0;
}