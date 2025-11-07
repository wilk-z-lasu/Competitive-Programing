#include <bits/stdc++.h>
using namespace std;

#define sz(A) (int)A.size()
#define f first
#define s second
#define pb push_back
#define pi pair<int,int>

constexpr int maxn = 200+7;
constexpr int inf = 1e9+7;

int N,K;
int TAB[maxn][maxn];

struct King {
    int real_x, real_y;
    int x, y;
    int id;
    bool is_real;
    void real_move_left()//moves king in range of his big tile
    {
        real_x--;
        if(is_real)
        {

        }
    }
};

void make_move()
{
    // implementacja ruchu
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N>>K;
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            cin>>TAB[i][j];

    return 0;
}