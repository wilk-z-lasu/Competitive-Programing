#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int inf=1e18+7;
constexpr int maxn=1e5+7;
constexpr int LOG=18;

//INPUT DATA
int n,r;
int x;
int a,b,c;
vector<int>restaurants[maxn];
vector<pi>graf[maxn];
int Q;
int p,q,s;
vector<pair<pi,int>>query[maxn];
int solv[maxn];

//IMPORTANT PREPROCES VARIABLES
int pref[maxn];
int preorder_cnt;
int preorder[maxn];
int depth[maxn];
int up[maxn][LOG];

//VARIABLES IN NEED OF CLEARING
vector<pi>G[maxn];
bool vis[maxn];
int depth_tmp[maxn];
int up_tmp[maxn][LOG];
int mini[maxn][LOG];

void input_data() {
    cin>>n>>r;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        restaurants[x].push_back(i);
    }
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b>>c;
        graf[a].push_back({b,c});
        graf[b].push_back({a,c});
    }
    cin>>Q;
    for(int i=1;i<=Q;i++)
    {
        cin>>p>>q>>s;
        query[s].push_back({{p,q},i});
    }
}

void dfs_preproces(int v=1, int ojciec=1) {
    up[v][0]=ojciec;
    preorder[v]=++preorder_cnt;
    for(auto &u: graf[v])
    {
        if(u.f==ojciec) continue;
        pref[u.f] = pref[v] + u.s;
        depth[u.f] = depth[v] + 1;
        dfs_preproces(u.f,v);
    }
}

void bin_lifting() {
    for(int jump=1;jump<LOG;jump++)
        for(int i=1;i<=n;i++)
            up[i][jump] = up[up[i][jump-1]][jump-1];
}

int get_lca(int a, int b){
    if(depth[a] < depth[b]) swap(a,b);

    int k = depth[a]-depth[b];
    for(int jump=LOG-1;jump>=0;jump--)
        if(k & (1<<jump))
            a = up[a][jump];

    if(a==b) return a;

    for(int i=LOG-1;i>=0;i--)
        if(up[a][i] != up[b][i])
        {
            a=up[a][i];
            b=up[b][i];
        }
    return up[a][0];
}

void make_preproces() {
    dfs_preproces();
    bin_lifting();
}

bool cmp(int &x1, int &x2) {
    return preorder[x1]<preorder[x2];
}

void create_graph_G(vector<int>& vec, int type) {
    map<int,bool>was;

    was[1]=1;
    for(auto &u: restaurants[type])
        was[u]=1;
    for(auto &u: query[type])
    {
        was[u.f.f]=1;
        was[u.f.s]=1;
    }

    for(auto &u: was)
        vec.push_back(u.f);

    sort(vec.begin(), vec.end(), cmp);

    for(int i=0;i+1<vec.size();i++)
        was[get_lca(vec[i], vec[i+1])]=1;

    vec.clear();
    for(auto &u: was)
        vec.push_back(u.f);

    sort(vec.begin(), vec.end(), cmp);

    up_tmp[1][0]=1;
    for(int i=0;i+1<vec.size();i++)
    {
        int lca=get_lca(vec[i], vec[i+1]);
        up_tmp[vec[i+1]][0]=lca;
        depth_tmp[vec[i+1]] = depth_tmp[lca] + 1;
        G[lca].push_back({vec[i+1], pref[vec[i+1]]-pref[lca]}); // lca -> i+1
        G[vec[i+1]].push_back({lca, pref[vec[i+1]]-pref[lca]}); // lca <- i+1
    }
}

void Dijkstra(vector<int> &start) {
    priority_queue<pi>pq;
    for(auto &u: start)
        pq.push({0,u});
    while(!pq.empty())
    {
        int cost = -pq.top().f;
        int v = pq.top().s;
        pq.pop();

        if(vis[v]) continue;

        vis[v]=1;
        mini[v][0]=cost;

        for(auto &u: G[v])
            if(!vis[u.f])
                pq.push({-(cost+u.s), u.f});
    }
}

void bin_lifting_tmp(vector<int>& vec) {
    for(int jump=1;jump<LOG;jump++)
    {
        for(auto &i: vec)
        {
            up_tmp[i][jump] = up_tmp[up_tmp[i][jump-1]][jump-1];
            mini[i][jump] = min(mini[i][jump-1], mini[up_tmp[i][jump-1]][jump-1]);
        }
    }
}

int min_cost(int v, int goal) {
    int odp = min(mini[v][0], mini[goal][0]);
    int k = depth_tmp[v]-depth_tmp[goal];
    for(int jump=LOG-1;jump>=0;jump--)
    {
        if(k & (1<<jump))
        {
            odp = min(odp, mini[v][jump]);
            v = up_tmp[v][jump];
            odp = min(odp, mini[v][0]);
        }
    }
    return odp;
}

void make_clearing(vector<int>&vec) {
    for(auto &i: vec)
    {
        G[i].clear();
        vis[i]=0;
        depth_tmp[i]=0;
        for(int j=0;j<LOG;j++)
        {
            up_tmp[i][j]=0;
            mini[i][j]=0;
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    input_data();//GETTING INPUT DATA 
    make_preproces();//DOING NECESSARY PREPROCESING

    for(int type=1;type<=r;type++)
    {
        if(query[type].empty()) continue;
        if(restaurants[type].empty())//CASE WHEN ANSWER DOESNT EXIST
        {
            for(auto &u: query[type])
                solv[u.s]=-1;
            continue;
        }

        vector<int>vec;//contains all active vertexes of graph G

        create_graph_G(vec, type);//CREATE GRAPH G
        Dijkstra(restaurants[type]);//counts mini[i: vec][0]
        bin_lifting_tmp(vec);

        for(auto &u: query[type])
        {
            p=u.f.f; q=u.f.s;
            int lca = get_lca(p,q);

            int odp = (int)2*min(min_cost(p,lca), min_cost(q,lca)) + pref[p] + pref[q] - 2*pref[lca];
            solv[u.s] = odp;
        }
        make_clearing(vec);    
    }

    for(int i=1;i<=Q;i++)
        cout<<solv[i]<<'\n';
    return 0;
}