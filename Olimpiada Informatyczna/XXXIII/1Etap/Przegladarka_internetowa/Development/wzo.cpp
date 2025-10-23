#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define pi pair<int,int>
#define sz(A) (int)A.size()

constexpr int maxn = 1e6+7;
constexpr int inf = 1e9+7;

int n;
string w[maxn];
int tab[maxn][26];
int Last = 0;
int depth[maxn];
vector<pair<int, char>>vec[maxn];
int id_end[maxn];

void clear()
{
    depth[0] = 0;
    for(int i=0;i<maxn;++i)
        for(int j=0;j<26;++j)
            tab[i][j] = -1;
}

void add(string &w, int id)
{
    int v = 0;
    for(int i=0;i<sz(w);++i)
    {
        int &nxt = tab[v][(w[i]-'a')];
        if(nxt == -1)
            nxt = ++Last;
        depth[nxt] = depth[v]+1;
        v = nxt;
    }
    id_end[v] = id;
}

int Sort_graph(int v = 0)
{
    vector<pair<int,pi>> children;
    int odp = depth[v];
    for(int c=0;c<26;++c)
    {
        int nxt = tab[v][c];
        if(nxt != -1)
        {
            int mx_child_depth = Sort_graph(nxt);
            odp = max(odp, mx_child_depth);
            children.pb({mx_child_depth, {nxt, c}});
        }
    }
    sort(children.begin(), children.end());
    // cout<<" ------ "<<v<<" ------ "<<endl;
    // for(auto &[val, nxt]: children)
    //     cout<<val<<" <-> "<<nxt.f<<" "<<nxt.s<<endl;

    for(auto &u: children)
    {
        int nxt = u.s.f;
        char c = u.s.s+'a';
        vec[v].pb({nxt, c});
    }
    return odp;
}

vector<char>solv;
inline void wypisz(char c)
{
    solv.pb(c);
}

vector<char> cur;
void dfs(int v = 0)
{
    if(id_end[v])
    {
        if(1+sz(cur) <= depth[v])
        {
            wypisz('T');
            for(auto c: cur)
                wypisz(c);
        }
        else
        {
            for(auto &u: w[id_end[v]])
                wypisz(u);
        }
        wypisz('E');
        cur.clear();
    }
    for(auto &[nxt, c]: vec[v])
    {
        cur.pb(c);
        dfs(nxt);
    }
    cur.pb('B');
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    clear();
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>w[i];
        add(w[i], i);
    }

    Sort_graph();

    dfs();

    cout<<sz(solv)<<"\n";
    for(auto &u: solv)
        cout<<u;
    return 0;
}