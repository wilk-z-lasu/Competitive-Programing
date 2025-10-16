#include <bits/stdc++.h>
using namespace std;
#define int long long

#define sz(A) (int)A.size()
#define f first
#define s second
#define pb push_back
#define pi pair<int,int>

constexpr int maxn = 1000+7;
constexpr int inf = 1e18+7;

int n,q;
int A,B;
char tab[maxn][maxn];
int odl[maxn][maxn];
int where[maxn][maxn];

inline void BFS()
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            odl[i][j] = inf;
    odl[1][1] = 0;

    queue<pi> Q;
    Q.push({1,1});

    while(!Q.empty())
    {
        auto v = Q.front();
        Q.pop();
        int x = v.f;
        int y = v.s;
        int dist = odl[x][y];

        if(x+1 <= n && odl[x+1][y] == inf && tab[x+1][y] != '#') odl[x+1][y] = dist+1, Q.push({x+1,y});
        if(x-1 >= 1 && odl[x-1][y] == inf && tab[x-1][y] != '#') odl[x-1][y] = dist+1, Q.push({x-1,y});
        if(y+1 <= n && odl[x][y+1] == inf && tab[x][y+1] != '#') odl[x][y+1] = dist+1, Q.push({x,y+1});
        if(y-1 >= 1 && odl[x][y-1] == inf && tab[x][y-1] != '#') odl[x][y-1] = dist+1, Q.push({x,y-1});
    }
}

constexpr int M = (1<<20);
int tree[2*M];
int push[2*M];
inline void Push(int v)
{
    if(push[v] == 0) return;
    tree[2*v] += push[v];
    push[2*v] += push[v];
    tree[2*v+1] += push[v];
    push[2*v+1] += push[v];
    push[v] = 0;
}
inline void add_tree(int a, int b, int val, int v = 1, int l = 1, int r = M)
{
    if(r < a || b < l) return;
    if(a <= l && r <= b)
    {
        tree[v] += val;
        push[v] += val;
        return;
    }
    Push(v);
    int mid = (l + r) / 2;
    add_tree(a, b, val, 2*v, l, mid);
    add_tree(a, b, val, 2*v+1, mid+1, r);
    tree[v] = max(tree[2*v], tree[2*v+1]);
}
inline int get_tree()
{
    if(tree[1] < 0) return 0;
    return tree[1];
}
inline void add(int x, int y)
{
    int pos = where[x][y];
    add_tree(pos, pos, +inf);
    add_tree(pos+1, M, +1);
}
inline void remove(int x, int y)
{
    int pos = where[x][y];
    add_tree(pos, pos, -inf);
    add_tree(pos+1, M, -1);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            cin>>tab[i][j];

    BFS();
    vector<pair<int,pi>> S;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(tab[i][j] != '#')
                S.push_back({odl[i][j], {i,j}});
    
    sort(S.begin(), S.end(), greater<pair<int,pi>>());
    int id = 0;
    for(auto &u: S)
    {
        int odl = u.f;
        int x = u.s.f;
        int y = u.s.s;
        where[x][y] = ++id;
        add_tree(id, id, odl);
    }
    add_tree(1, M, -inf);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(tab[i][j] == 'F')
                add(i,j);

    cout<<get_tree()<<"\n";
    while(q--)
    {
        cin>>A>>B;
        if(tab[A][B] == 'F')
        {
            tab[A][B] = '.';
            remove(A,B);
        }
        else if(tab[A][B] == '.')
        {
            tab[A][B] = 'F';
            add(A,B);
        }
        cout<<get_tree()<<"\n";
    }
    return 0;
}