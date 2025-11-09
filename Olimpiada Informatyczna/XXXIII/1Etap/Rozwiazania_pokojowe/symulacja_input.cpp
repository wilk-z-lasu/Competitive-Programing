#include <bits/stdc++.h>
using namespace std;

#define sz(A) (int)A.size()
#define f first
#define s second
#define pb push_back
#define pi pair<int,int>

constexpr int maxn = 200+7;

int N;

int TAB[maxn][maxn];
pi where[maxn*maxn];

void Print()
{
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            TAB[i][j] = 0;
    for(int i=1;i<=N*N;++i)
        TAB[where[i].f][where[i].s] = i;
    for(int i=1;i<=N;++i)
    {
        for(int j=1;j<=N;++j)
            cout<<TAB[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N;
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
        {
            cin>>TAB[i][j];
            if(TAB[i][j]!=0)
            {
                where[TAB[i][j]] = {i,j};
            }
        }

    string w;
    cin>>w;
    int t;
    cin>>t;
    while(t--)
    {
        int id, y, x;
        cin>>id>>y>>x;
        where[id] = {y,x};
    }
    Print();
    return 0;
}