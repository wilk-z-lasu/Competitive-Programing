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
int x,y;

void move_blank(char c)
{
    if(c=='U')
    {
        swap(TAB[y][x], TAB[y-1][x]);
        --y;
    }
    else if(c=='D')
    {
        swap(TAB[y][x], TAB[y+1][x]);
        ++y;
    }
    else if(c=='L')
    {
        swap(TAB[y][x], TAB[y][x-1]);
        --x;
    }
    else if(c=='R')
    {
        swap(TAB[y][x], TAB[y][x+1]);
        ++x;
    }
}

void Print()
{
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
            if(TAB[i][j]==0)
            {
                y = i;
                x = j;
            }
        }

    string w;
    cin>>w;
    for(auto &u: w)
    {
        move_blank(u);
    }
    Print();
    return 0;
}