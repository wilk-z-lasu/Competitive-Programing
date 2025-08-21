#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 2007;

int n;
int a,b;
char c;

vector<pair<int,char>>vec[maxn];

vector<vector<char>>kan;
vector<char>szablon;
void gen_szablony(int v, int ojciec=-1)
{
    kan.pb(szablon);
    for(auto &u: vec[v])
    {
        if(u.f == ojciec) continue;
        szablon.pb(u.s);
        gen_szablony(u.f, v);
        szablon.pop_back();
    }
}

constexpr int LOG = 11;
int up[maxn][LOG];
int depth[maxn];
void preproces(int v=1, int ojciec=1)
{
    up[v][0] = ojciec;
    for(auto &u: vec[v])
    {
        if(u.f == ojciec) continue;
        depth[u.f] = depth[v] + 1;
        preproces(u.f, v);
    }
}
void bin_lifting()
{
    for(int i=1;i<LOG;++i)
        for(int j=1;j<=n;++j)
            up[j][i] = up[up[j][i-1]][i-1];
}
int get_lca(int A, int B)
{
    if(depth[A] < depth[B]) swap(A, B);
    int k = depth[A]-depth[B];
    for(int i=0;i<LOG;++i)
        if(k&(1<<i))
            A = up[A][i];
    if(A==B) return A;
    for(int i=LOG-1;i>=0;--i)
    {
        if(up[A][i]!=up[B][i])
        {
            A = up[A][i];
            B = up[B][i];
        }
    }
    return up[A][0];
}

struct V{
    int next[26];
    bool active = false;
    vector<pi>marked;
    V() {
        fill(begin(next), end(next), -1);
    }
};
vector<V>trie(1);
void add_string(vector<char>& c)
{
    // for(auto &u: c)
    //     cout<<u<<' ';
    // cout<<endl;
    int v = 0;
    for(int i=0;i<sz(c);++i)
    {
        int x = c[i] - 'A';
        if(trie[v].next[x] == -1)
        {
            trie[v].next[x] = sz(trie);
            trie.emplace_back();
        }
        v = trie[v].next[x];
    }
    trie[v].active = true;
}

int cover[maxn];
void pref_sum(int v=1, int ojciec=-1)
{
    for(auto &u: vec[v])
    {
        if(u.f == ojciec) continue;
        pref_sum(u.f, v);
        cover[v] += cover[u.f];
    }
}
bool verify(vector<pi>& marked)
{
    for(int i=0;i<maxn;++i)
        cover[i] = 0;
    
    for(auto &u: marked)
    {
        int A = u.f;
        int B = u.s;
        int lca = get_lca(A,B);
        cover[A]++;
        cover[B]++;
        cover[lca] -= 2;
    }
    pref_sum();
    for(int i=2;i<=n;++i)
        if(cover[i] <= 0)
            return false;
    return true;
}
set<vector<char>>solv;
void DFS(int v=0)
{
    if(trie[v].active)
    {
        if(verify(trie[v].marked))
        {
            for(int i=0;i<=1;++i)
            {
                solv.insert(szablon);
                reverse(szablon.begin(), szablon.end());
            }
        }
    }
    for(int i=0;i<26;++i)
    {
        if(trie[v].next[i] == -1) continue;
        szablon.pb('A' + i);
        DFS(trie[v].next[i]);
        szablon.pop_back();
    }
}
int s;
void dfs(int v1, int ojciec=-1, int v2=0)
{
    if(v2!=-1) 
        trie[v2].marked.pb({s,v1});
    for(auto &u: vec[v1])
    {
        if(u.f == ojciec) continue;
        int next_v2 = -1;
        if(v2 != -1)
            next_v2 = trie[v2].next[u.s - 'A'];
        dfs(u.f, v1, next_v2);
    }
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;++i)
    {
        cin>>a>>b>>c;
        vec[a].pb({b, c});
        vec[b].pb({a, c});
    }

    int start;
    for(int i=1;i<=n;++i)
        if(sz(vec[i])==1)
            start=i;

    gen_szablony(start);
    for(auto &v: kan)
        add_string(v);

    preproces();
    bin_lifting();
    for(int i=1;i<=n;++i)
    {
        s = i;
        dfs(i);
    }
    DFS();

    cout<<sz(solv)<<'\n';
    for(auto &szablon: solv)
    {
        for(auto &u: szablon)
            cout<<u;
        cout<<'\n';
    }
    return 0;
}