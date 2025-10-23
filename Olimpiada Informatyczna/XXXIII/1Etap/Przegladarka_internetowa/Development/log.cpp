//version running O(n*logn)
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second
#define pi pair<int,int>
#define sz(A) (int)A.size()

constexpr int maxn = 1e6+7;
constexpr int inf = 1e9+7;
constexpr int LOG = 21;


int n;
string w;
int vec[maxn][26];
int Last = 0;
int depth[maxn];
int up[maxn][LOG];
void clear()
{
    depth[0] = 0;
    up[0][0] = 0;
    for(int i=0;i<maxn;++i)
        for(int j=0;j<26;++j)
            vec[i][j] = -1;
}

void add(string &w)
{
    int v = 0;
    for(int i=0;i<sz(w);++i)
    {
        int &nxt = vec[v][(w[i]-'a')];
        if(nxt == -1)
            nxt = ++Last;
        depth[nxt] = depth[v]+1;
        up[nxt][0] = v;
        v = nxt;
    }
}

void bin_lifting()
{
    for(int j=1;j<LOG;++j)
        for(int i=0;i<=Last;++i)
            up[i][j] = up[up[i][j-1]][j-1];
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
        cin>>w;
        add(w);
    }
    return 0;
}