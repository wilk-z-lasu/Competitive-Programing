#include <bits/stdc++.h>
using namespace std;
// #define int short
// #define f first
// #define s second

constexpr int inf=1e9;
constexpr int maxn=3000;
int n;
int p;
int r;
int cena[maxn+7];//koszt przekupienia agenta
vector<int> vec[maxn+7];
vector<int> vec_odwrocone[maxn+7];
bool vis[maxn+7];
stack<int> toposort;

void DFS(int v)
{
    vis[v]=1;
    for(auto u: vec[v])
    {
        if(!vis[u]) DFS(u);
    }
    toposort.push(v);
}

int SSS[maxn+7];
int SSS_koszt[maxn+7];
int SS_liczba;

void make_SSS(int v)
{
    SSS[v]=SS_liczba;
    for(auto u: vec_odwrocone[v])
    {
        if(SSS[u]==0) make_SSS(u);
    }
}

int plan_graf[maxn+7][maxn+7];
vector<int> graf[maxn+7];

bool odwiedzone[maxn+7];

void DFS_graf(int v)
{
    odwiedzone[v]=1;
    for(auto u: graf[v])
    {
        if(!odwiedzone[u]) DFS_graf(u);
    }
    toposort.push(v);
}

bool mam[maxn+7];
void zbierz(int v)
{
    mam[v]=1;
    for(auto u: graf[v])
    {
        if(!mam[u]) zbierz(u);
    }
}

bool niet[maxn+7];
queue<int> przekupni;

void BFS_niet()
{
    while(!przekupni.empty())
    {
        int top=przekupni.front();
        przekupni.pop();

        for(auto u: vec[top])
        {
            if(!niet[u])
            {
                przekupni.push(u);
                niet[u]=1;
            }
        }
        
    }
}


int32_t main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    for(int i=0;i<maxn+7;i++)
    {
        cena[i]=inf;
        SSS_koszt[i]=inf;
    }

    cin>>n;
    cin>>p;

    for(int i=0;i<p;i++)
    {
        int a,k;
        cin>>a>>k;
        cena[a]=k;
        przekupni.push(a);
        niet[a]=1;
    }

    cin>>r;

    for(int i=0;i<r;i++)
    {
        int a,b;
        cin>>a>>b;

        vec[a].push_back(b);
        vec_odwrocone[b].push_back(a);
    }

    for(int i=1;i<=n;i++)
    {
        if(!vis[i]) DFS(i);
    }

    while(!toposort.empty())
    {
        int top=toposort.top();
        toposort.pop();
        if(SSS[top]==0) 
        {
            SS_liczba++;
            make_SSS(top);
        }  
    }

    for(int i=1;i<=n;i++)
    {
        SSS_koszt[SSS[i]]=min(SSS_koszt[SSS[i]], cena[i]);
    }

    // for(int i=1;i<=n;i++) cout<<i<<": "<<SSS[i]<<" "<<SSS_koszt[i]<<endl;


    for(int i=1;i<=n;i++)
    {
        for(auto u: vec[i])
        {
            plan_graf[SSS[i]][SSS[u]]=1;
        }
    }

    for(int i=1;i<=SS_liczba;i++)
    {
        for(int j=1;j<=SS_liczba;j++)
        {
            if(plan_graf[i][j]) 
            {
                graf[i].push_back(j);
                // cout<<i<<"->"<<j<<endl;
            }
        }
    }

    for(int i=1;i<=SS_liczba;i++)
    {
        if(!odwiedzone[i]) DFS_graf(i);
    }

    int odp=0;
    while(!toposort.empty())
    {
        int top=toposort.top();
        toposort.pop();
        // cout<<"top: "<<top<<endl;
        if(!mam[top] && SSS_koszt[top]!=inf) 
        {
            zbierz(top);
            odp+=SSS_koszt[top];
        }
    }

    for(int i=1;i<=SS_liczba;i++)
    {
        if(!mam[i])
        {
            cout<<"NIE \n";
            
            BFS_niet();
            for(int i=1;i<=n;i++)
            {
                if(!niet[i])
                {
                    cout<<i;
                    return 0;
                }
            }
            return 0;
        }
    }

    cout<<"TAK \n";
    cout<<odp;
    return 0;
}