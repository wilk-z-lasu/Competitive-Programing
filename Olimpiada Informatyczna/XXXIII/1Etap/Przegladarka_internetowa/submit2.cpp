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
pair<int, char>vec[maxn][26];
int it[maxn];
int id_end[maxn];
int mx_depth[maxn];

void add(string &w, int id)
{
    int v = 0;
    for(int i=0;i<sz(w);++i)
    {
        int &nxt = tab[v][(w[i]-'a')];
        if(nxt == 0)
        {
            nxt = ++Last;
            vec[v][it[v]] = {nxt,w[i]};
            ++it[v];
        }
        depth[nxt] = depth[v]+1;
        v = nxt;
    }
    id_end[v] = id;
}

bool cmp(pair<int, char>& x1, pair<int, char>& x2)
{
    if(mx_depth[x1.f]==mx_depth[x2.f])
        return x1.s < x2.s;
    else
        return mx_depth[x1.f] < mx_depth[x2.f];
}

void Sort_graph(int v = 0)
{
    mx_depth[v] = depth[v];
    for(int i=0;i<it[v];++i)
    {
        int nxt = vec[v][i].f;
        Sort_graph(nxt);
        mx_depth[v] = max(mx_depth[v], mx_depth[nxt]);
    }
    sort(&vec[v][0], &vec[v][it[v]], cmp);
}

vector<char>solv;
void wypisz(char c)
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
    for(int i=0;i<it[v];++i)
    {
        int nxt = vec[v][i].f;
        char c = vec[v][i].s;
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