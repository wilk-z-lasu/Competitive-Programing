#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 1007;
constexpr int inf = 1e9+7;

int n;
vector<vector<char>> tab(maxn, vector<char>(maxn));

int px, py, kx, ky;
vector<vector<int>> P(maxn, vector<int>(maxn));
vector<vector<int>> K(maxn, vector<int>(maxn));
vector<vector<int>> vP(maxn, vector<int>(maxn));
vector<vector<int>> hP(maxn, vector<int>(maxn));
vector<vector<int>> vK(maxn, vector<int>(maxn));
vector<vector<int>> hK(maxn, vector<int>(maxn));

void BFS(int x, int y, vector<vector<int>>& wyn)
{
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            wyn[i][j] = inf;

    queue<pi>q;
    q.push({x,y});
    wyn[x][y] = 0;
    while(!q.empty())
    {
        int aktx = q.front().f;
        int akty = q.front().s;
        q.pop();

        for(pi add: {make_pair(-1,0), make_pair(0, -1), make_pair(+1,0), make_pair(0,+1)})
        {
            if(aktx + add.f < 1 || aktx + add.f > n || akty + add.s < 1 || akty + add.s > n || tab[aktx + add.f][akty + add.s] == 'X') continue;
            if(tab[aktx + add.f][akty + add.s] == '#')
                wyn[aktx + add.f][akty + add.s] = min(wyn[aktx + add.f][akty + add.s], wyn[aktx][akty] + 1);
            else if(wyn[aktx + add.f][akty + add.s] > (wyn[aktx][akty] + 1))
            {
                wyn[aktx + add.f][akty + add.s] = wyn[aktx][akty] + 1;
                q.push({aktx + add.f, akty + add.s});
            }
        }
    }
}
void Push_vertical(vector<vector<int>>& wyn, vector<vector<int>>& push)
{
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            push[i][j] = wyn[i][j];

    for(int i=1;i<=n-1;++i)
        for(int j=1;j<=n;++j)
            if(tab[j][i+1] != 'X')
                push[j][i+1] = min(push[j][i+1], push[j][i]+1);
    for(int i=n;i>=2;--i)
        for(int j=1;j<=n;++j)
            if(tab[j][i-1] != 'X')
                push[j][i-1] = min(push[j][i-1], push[j][i]+1);
}
void Push_horizontal(vector<vector<int>>& wyn, vector<vector<int>>& push)
{
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            push[i][j] = wyn[i][j];

    for(int j=1;j<=n-1;++j)
        for(int i=1;i<=n;++i)
            if(tab[j+1][i] != 'X')
                push[j+1][i] = min(push[j+1][i], push[j][i]+1);
    for(int j=n;j>=2;--j)
        for(int i=1;i<=n;++i)
            if(tab[j-1][i] != 'X')
                push[j-1][i] = min(push[j-1][i], push[j][i]+1);
}
void bomb(int x, int y)
{
    for(int i=0;y+i<=n;++i)
    {
        if(tab[x][y+i] == 'X')
            break;
        if(tab[x][y+i] == '#')
            tab[x][y+i] = '.';
    }
    for(int i=0;y-i>=1;++i)
    {
        if(tab[x][y-i] == 'X')
            break;
        if(tab[x][y-i] == '#')
            tab[x][y-i] = '.';
    }
    for(int i=0;x+i<=n;++i)
    {
        if(tab[x+i][y] == 'X')
            break;
        if(tab[x+i][y] == '#')
            tab[x+i][y] = '.';
    }
    for(int i=0;x-i>=1;++i)
    {
        if(tab[x-i][y] == 'X')
            break;
        if(tab[x-i][y] == '#')
            tab[x-i][y] = '.';
    }
}
void Print(vector<vector<char>>& wyn)
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(wyn[j][i] == inf)
                cout<<"% ";
            else
                cout<<wyn[j][i]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}

void print_path(int x, int y, int X, int Y)
{
    vector<vector<int>> wyn(maxn, vector<int>(maxn));
    vector<vector<int>> last(maxn, vector<int>(maxn));

    pi m[4] = {{-1,0}, {0,-1}, {+1,0}, {0,+1}};
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            wyn[i][j] = inf;

    queue<pi>q;
    q.push({x,y});
    wyn[x][y] = 0;
    while(!q.empty())
    {
        int aktx = q.front().f;
        int akty = q.front().s;
        q.pop();

        for(int i=0;i<4;++i)
        {
            if(aktx + m[i].f < 1 || aktx + m[i].f > n || akty + m[i].s < 1 || akty + m[i].s > n || tab[aktx + m[i].f][akty + m[i].s] == 'X' || tab[aktx + m[i].f][akty + m[i].s] == '#') continue;
            else if(wyn[aktx + m[i].f][akty + m[i].s] > (wyn[aktx][akty] + 1))
            {
                wyn[aktx + m[i].f][akty + m[i].s] = wyn[aktx][akty] + 1;
                last[aktx + m[i].f][akty + m[i].s] = i;
                q.push({aktx + m[i].f, akty + m[i].s});
            }
        }
    }
    vector<char>odp;
    while(X != x || Y != y)
    {
        int rep = last[X][Y];
        if(rep == 0)
            odp.pb('L');
        if(rep == 1)
            odp.pb('G');
        if(rep == 2)
            odp.pb('P');
        if(rep == 3)
            odp.pb('D');
        
        X -= m[rep].f;
        Y -= m[rep].s;
    }
    reverse(odp.begin(), odp.end());
    for(auto &u: odp)
        cout<<u;
}
int32_t main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin>>tab[j][i];

    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(tab[i][j] == 'P')
                px = i, py = j;
            if(tab[i][j] == 'K')
                kx = i, ky = j;
        }
    }

    BFS(px, py, P);
    Push_vertical(P, vP);
    Push_horizontal(P, hP);

    BFS(kx, ky, K);
    Push_vertical(K, vK);
    Push_horizontal(K, hK);

    pair<int,pi> solv = {inf,{1,1}};
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            solv = min(solv, {vP[i][j] + hK[i][j],{i,j}});
            solv = min(solv, {hP[i][j] + vK[i][j],{i,j}});
        }
    }
    if(solv.f==inf)
    {
        cout<<"NIE";
        return 0;
    }

    
    cout << solv.f << '\n';
    cout << solv.s.s << ' ' << solv.s.f << '\n';
    bomb(solv.s.f, solv.s.s);
    print_path(px, py, kx, ky);
    return 0;
}