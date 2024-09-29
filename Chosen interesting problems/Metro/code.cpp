#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1000007;

int odp;
int n,l;
vector<int> vec[maxn];
int depth[maxn];
bool taken[maxn];
int from;
int to;


void DFS(int v, int ojciec=0)
{
    depth[v]=depth[ojciec]+1;

    for(auto u: vec[v])
    {
        if(u==ojciec) continue;
        DFS(u,v);
    }
}

queue<int>to_talk;
void mark_path(int v, int cel, int ojciec=0)
{
    if(taken[v]) return;
    if(v==cel)
    {
        to_talk.push(v);
        taken[v]=1;
    }
    for(auto u: vec[v])
    {
        if(u==ojciec) continue;
        mark_path(u,cel,v);
        if(taken[u] && !taken[v]) 
        {
            to_talk.push(v);
            taken[v]=1;
        }
    }
}

int start;
pair<int,int> szukaj(int v, int ojciec)
{
    int maxi=0;
    int maxi_v=v;
    for(auto u: vec[v])
    {
        if(u==ojciec) continue;
        pair<int,int> look = szukaj(u,v);
        if(look.f>maxi)
        {
            maxi=look.f;
            maxi_v=look.s;
        }
    }
    return {maxi+1, maxi_v};
}

priority_queue< pair<int, pair<int,int> > >pq;//.f=dodatkowe stacje .s.f=poczatek .s.s=koniec

void to_talk_to_do()
{
    while(!to_talk.empty())
    {
        for(auto u: vec[to_talk.front()])
        {
            if(!taken[u]) 
            {
                pair<int,int> mam = szukaj(u,to_talk.front());
                pq.push({mam.f,{mam.s,u}});
            }
        }
        to_talk.pop();
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>l;
    if(l==0)
    {
        cout<<0;
        return 0;
    }

    for(int i=1;i<=n-1;i++)
    {
        int a,b; cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    DFS(1);

    int maxi=0;
    int maxi_v=0;
    for(int i=1;i<=n;i++)
        if(depth[i]>maxi)
        {
            maxi=depth[i];
            maxi_v=i;
        }

    from = maxi_v;

    DFS(maxi_v);

    maxi=0;
    maxi_v=0;
    for(int i=1;i<=n;i++)
        if(depth[i]>maxi)
        {
            maxi=depth[i];
            maxi_v=i;
        }
    to = maxi_v;

    // cout<<from<<" -> "<<to<<endl;
    mark_path(from, to);
    
    //ZNALAZLEM I ZAZNACZYLEM MAKSYMALNA SCIEZKE

    to_talk_to_do();

    int leafs=2;
    while(!pq.empty() && leafs<2*l)
    {
        pair<int, pair<int,int>> top=pq.top();
        pq.pop();

        mark_path(top.s.f,top.s.s);
        
        to_talk_to_do();

        leafs++;
    }

    for(int i=1;i<=n;i++)
    {
        odp+=taken[i];
    }
    cout<<odp;
    return 0;
}