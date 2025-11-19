#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+7;

int Z;
int N;
int X[maxn];
int odp[maxn];

constexpr int M = 1<<17;
int tree[2*M];

int Get(int k, int v = 1)
{
    --tree[v];
    if(v>=M) return v - M + 1;
    if(tree[2*v] < k)
        return Get(k-tree[2*v], 2*v+1);
    else
        return Get(k, 2*v);
}
void Set(int id, int k)
{
    odp[id] = Get(k);
}
void Wypisz()
{
    for(int i = 1; i <= N; ++i)
        cout<<odp[i]<<' ';
    cout<<'\n';
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> Z;
    while(Z--)
    {
        cin>>N;
        for(int i = 1; i <= N; ++i)
            cin>>X[i];
        for(int i = 1; i <= N; ++i)
                tree[M+i-1] = 1;
        for(int i=M-1;i;--i)
            tree[i] = tree[2*i] + tree[2*i+1];
        for(int i = N; i >= 1; --i)
            Set(i, X[i]+1);
        Wypisz();
    }
    return 0;
}