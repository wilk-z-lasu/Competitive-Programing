#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=500+7;
constexpr int inf=1e9+7;

int n,q;
char slowo[maxn];
char valid[maxn];

char solv[maxn];

int ile_min[30];
int ile_max[30];


int ile_min_tmp[30];
int ile_max_tmp[30];

set<char>blocked[maxn];

int greens[maxn];
bool green_in_place[maxn];

void clear()
{
    for(int i=0;i<30;i++)
    {
        ile_min[i]=0;
        ile_max[i]=inf;
    }
}

void clear_tmp()
{
    for(int i=0;i<30;i++)
    {
        ile_min_tmp[i]=0;
        ile_max_tmp[i]=inf;
    }
}

constexpr int maxi=2*maxn;//wielkosc grafu

constexpr int s=maxi-1;//zrodlo
constexpr int t=maxi-2;//ujscie
constexpr int helper=maxi-3;//ujscie prim

struct edge
{
    int start, end, capacity;
};
vector<edge> edges;
vector<int>con[maxi];

string out(int v)
{
    if(v==s)
        return "s";
    else if(v==t)
        return "t";
    else if(v==helper)
        return "helper";
    else
        return to_string(v);
}

int it=0;
void make_edge(int a, int b, int c)
{
    // cout<<out(a)<<" <-> "<<out(b)<<" koszt: "<<c<<endl; 
    edges.push_back({a,b,c});
    edges.push_back({b,a,0});
    con[a].push_back(it);
    con[b].push_back(it+1);
    it+=2;
}

int numer_v(int v)
{
    return v + 30;
}

bool vis[maxi];
pair<int,int> parent[maxi];
int new_flow;

bool dfs(int v, int koniec, int flow=inf)
{
    // out(v);
    if(v==koniec)
    {
        new_flow=flow;
        return 1;
    }
    vis[v]=1;
    for(auto &u: con[v])
    {
        if(vis[edges[u].end] || edges[u].capacity<=0) continue;

        parent[edges[u].end]={v,u};
        if(dfs(edges[u].end, koniec, min(flow,edges[u].capacity)))
            return 1;
    }
    return 0;
}

void maxflow(int S, int T) 
{
    while(dfs(S,T))
    {
        int cur = T;
        while (cur != S) 
        {
            int prev = parent[cur].f;
            edges[parent[cur].s].capacity -= new_flow;
            edges[parent[cur].s^1].capacity += new_flow;
            cur = prev;
        }
        for(int i=0;i<maxi;i++)
            vis[i]=0;
    }
    return;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>q>>n;
    q--;

    for(int i=1;i<=n;i++)
        solv[i]='#';

    clear();
    while(q--)
    {
        clear_tmp();

        for(int i=1;i<=n;i++)
            cin>>slowo[i];
        for(int i=1;i<=n;i++)
            cin>>valid[i];

        for(int i=1;i<=n;i++)
            if(valid[i]=='G')
            {
                ile_min_tmp[slowo[i]-'a']++;
                solv[i]=slowo[i];
                if(!green_in_place[i])
                {
                    green_in_place[i]=1;
                    greens[slowo[i]-'a']++;
                }
            }

        for(int i=1;i<=n;i++)
            if(valid[i]=='Y')
            {
                ile_min_tmp[slowo[i]-'a']++;
                blocked[i].insert(slowo[i]);
            }

        for(int i=1;i<=n;i++)
            if(valid[i]=='B')
            {
                ile_max_tmp[slowo[i]-'a']=ile_min_tmp[slowo[i]-'a'];
                blocked[i].insert(slowo[i]);
            }

        for(int i=0;i<30;i++)
        {
            ile_max[i]=min(ile_max[i],ile_max_tmp[i]);
            ile_min[i]=max(ile_min[i],ile_min_tmp[i]);
        }
    }

    // for(int i=0;i<30;i++)
    // {
    //     cout<<char(i+'a')<<" "<<ile_min[i]<<endl;
    // }

    int suma_min=0;
    for(int i=0;i<26;i++)
    {
        // cout<<i<<": "<<max(0,ile_min[i]-greens[i])<<endl;
        suma_min+=max(0,ile_min[i]-greens[i]);
    }
    
    for(int i=1;i<=n;i++)
        if(solv[i]!='#')
            suma_min++;

    // cout<<"zolte: "<<suma_min<<endl;

    for(int i=1;i<=n;i++)
    {
        if(solv[i]!='#')
        {
            ile_min[solv[i]-'a']--;
            if(ile_max[solv[i]-'a'] != inf)
                ile_max[solv[i]-'a']--;
        }
    }

    make_edge(s, helper, n-suma_min);//n-zolte-zielone

    for(int i=0;i<26;i++)//pierwsza warstwa polaczen
    {
        if(ile_min[i] > 0) make_edge(s, i+1, ile_min[i]);
        if(ile_max[i]!=ile_min[i]) make_edge(helper, i+1, inf);
    }

    for(int j=1;j<=n;j++)//druga i trzecia warstwa polaczen
    {
        for(int i=0;i<26;i++)
            if(solv[j]=='#' && blocked[j].find(char(i+'a')) == blocked[j].end())
                make_edge(i+1, numer_v(j), 1);
        make_edge(numer_v(j), t, 1);
    }

    //dziala
 
    // dfs(s, t);
    maxflow(s,t);

    for(int j=1;j<=n;j++)
    {
        if(solv[j]!='#') continue;
        for(auto &u: con[numer_v(j)])
            if(edges[u].capacity==1)
                solv[j]=char(edges[u].end-1+'a');
    }

    for(int i=1;i<=n;i++)
        cout<<solv[i];
    return 0;
}