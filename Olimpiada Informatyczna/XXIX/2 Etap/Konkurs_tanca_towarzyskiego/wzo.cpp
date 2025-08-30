//clean version of experyment.cpp 
//gets 100 points
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxq = 1e6+7;
constexpr int inf = 1e9+7;

int q;
char c[maxq];
int x[maxq];
int it[2] = {2, 2};

int state[2][maxq];
pi range[2][maxq];
int up[2][maxq];

vector<int>vec[2][maxq];

void change_tree(int i, int opt)
{
    if(c[i] != '?') ++it[opt];
    if(c[i] == 'Z')
    {
        if(state[opt][x[i]] == 0)
        {
            range[opt][it[opt]] = range[opt][x[i]];
            state[opt][it[opt]] = 0; 
        }
        else
        {
            up[opt][it[opt]] = up[opt][range[opt][x[i]].s];
            up[opt][range[opt][x[i]].s] = it[opt];
            state[opt][it[opt]] = 1;
            range[opt][it[opt]] = {up[opt][it[opt]],it[opt]};
            range[opt][x[i]] = {up[opt][range[opt][x[i]].s],range[opt][x[i]].s};
        }
    }
    if(c[i] == 'W')
    {
        if(state[opt][x[i]] == 0)
        {
            up[opt][it[opt]] = range[opt][x[i]].s;
            state[opt][it[opt]] = 1;
            range[opt][it[opt]] = {up[opt][it[opt]],it[opt]};
            range[opt][x[i]].s = it[opt];
        }
        else
        {
            range[opt][it[opt]] = range[opt][x[i]];
            state[opt][it[opt]] = 0;
        }
    }
}

int tin[2][maxq];
int tout[2][maxq];
int Time[2] = {0, 0};
void rename(int v, int opt)
{
    tin[opt][v] = ++Time[opt];
    for(auto &u: vec[opt][v])
        rename(u, opt);
    tout[opt][v] = ++Time[opt];
}

constexpr int M = 1<<21;
struct T1{
    int tree[2*M];
    T1() {
        for(int i=0;i<2*M;++i)
            tree[i] = 0;
    }

    void add(int pos, int val)
    {
        pos = pos + M - 1;
        while(pos)
        {
            tree[pos] += val;
            pos /= 2;
        }
    }
    int get_tree(int a, int b, int v=1, int l=1, int r=M)
    {
        if(r < a || b < l) return 0;
        if(a <= l && r <= b) return tree[v];
        int mid = (l + r) / 2;
        return get_tree(a, b, v*2, l, mid) + get_tree(a, b, v*2+1, mid+1, r);
    }
}graf[2];

int32_t main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>q;
    for(int i=1;i<=q;++i)
        cin>>c[i]>>x[i];

    state[0][1] = 0;
    up[0][1] = 0;
    range[0][1] = {1,2};
    state[0][2] = 1;
    up[0][2] = 1;
    range[0][2] = {1,2};

    state[1][1] = 1;
    up[1][1] = 0;
    range[1][1] = {1,2};
    state[1][2] = 0;
    up[1][2] = 1;
    range[1][2] = {1,2};

    for(int i = 1; i <= q; ++i)
    {
        change_tree(i, 0);
        change_tree(i, 1);
    }

    for(int i=2;i<=max(it[0],it[1]);++i)
    {
        if(up[0][i] != 0)
            vec[0][up[0][i]].pb(i);
        if(up[1][i] != 0)
            vec[1][up[1][i]].pb(i);
    }
    rename(1, 0);
    rename(1, 1);

    it[0] = 2;
    it[1] = 2;
    graf[0].add(tin[0][range[0][2].s], +1);
    graf[0].add(tout[0][range[0][2].s], -1);

    graf[1].add(tin[1][range[1][1].s], +1);
    graf[1].add(tout[1][range[1][1].s], -1);
    for(int i = 1; i <= q; ++i)
    {
        if(c[i] != '?')
        {
            ++it[0];
            ++it[1];
        }
        if(c[i] == '?')
        {
            if(state[0][x[i]] == 0)
                cout<<graf[0].get_tree(tin[0][range[0][x[i]].f]+1, tin[0][range[0][x[i]].s])<<'\n';
            else
                cout<<graf[1].get_tree(tin[1][range[1][x[i]].f]+1, tin[1][range[1][x[i]].s])<<'\n';
        }
        if(c[i] == 'Z' || c[i] == 'W')
        {
            if(state[0][it[0]] != 0)
            {
                graf[0].add(tin[0][range[0][it[0]].s], +1);
                graf[0].add(tout[0][range[0][it[0]].s], -1);
            }
            if(state[1][it[1]] != 0)
            {
                graf[1].add(tin[1][range[1][it[1]].s], +1);
                graf[1].add(tout[1][range[1][it[1]].s], -1);
            }
        }
    }
    
    return 0;
}