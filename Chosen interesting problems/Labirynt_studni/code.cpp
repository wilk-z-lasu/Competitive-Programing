#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

constexpr int maxn=6000+7;

int n;
vector<int> vec[maxn];
vector<int> vec_odw[maxn];

char kolor;
int a,b,c;

int k[maxn];

vector<int>warstwa[maxn];
int vis[maxn];

void bfs()
{
    priority_queue<pair<int,int>>q;
    q.push({0,n});
    vis[n]=0;
    while(!q.empty())
    {
        auto top=q.top();
        q.pop();

        for(auto &u: vec_odw[top.s])
            if(top.f+1>vis[u])
            {
                vis[u]=top.f+1;
                q.push({top.f+1,u});
            }
    }
    for(int i=1;i<=n;i++)
        warstwa[vis[i]].push_back(i);
}

int rep[maxn];
void set_rep()
{
    for(int i=0;i<maxn;++i)
        rep[i]=i;
}
int Find(int x)
{
    if(rep[x]==x) return x;
    else return rep[x]=Find(rep[x]);
}
void Union(int a, int b)
{
    rep[Find(a)]=rep[Find(b)];
}

map<ll,int>m;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;i++)
    {
        cin>>kolor>>a>>b>>c;
        if(kolor=='C')
            k[i]=1;
        else if(kolor=='Z')
            k[i]=2;
        else if(kolor=='N')
            k[i]=3;
        vec[i].push_back(a);
        vec[i].push_back(b);
        vec[i].push_back(c);

        vec_odw[a].push_back(i);
        vec_odw[b].push_back(i);
        vec_odw[c].push_back(i);
    }
    k[n]=4;
    vec[n].push_back(0);
    vec[n].push_back(0);
    vec[n].push_back(0);

    bfs();

    int solv;
    set_rep();
    for(int i=0;i<=n;i++)
    {
        // cout<<i<<": ";
        if(!warstwa[i].empty())
        {
            for(auto &u: warstwa[i])
            {
                // cout<<u<<' ';
                ll my_hash=(ll)216108018001*k[u]+(ll)36012001*Find(vec[u][0])+(ll)6001*Find(vec[u][1])+(ll)Find(vec[u][2]);
                if(m.find(my_hash)!=m.end())
                {
                    // cout<<m[my_hash]<<" = "<<u<<endl;
                    Union(m[my_hash],u);
                }
                m[my_hash]=u;
            }
            solv+=m.size();
            m.clear();
        }
        // cout<<endl;
    }
    cout<<solv;
    return 0;
}