#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=2007;
constexpr int inf=1e9+7;

int K,N;
int tab[maxn][maxn];

void Solv(int x1, int x2, int y1, int y2)
{
    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
    exit(0);
}

vector<int> blocks[maxn];
int left_block[maxn];
int right_block[maxn];

int get_sum(int x1, int x2, int y1, int y2)
{
    return tab[y2][x2]-tab[y1-1][x2]-tab[y2][x1-1]+tab[y1-1][x1-1];
}

void make_solv(int x1, int x2, int y1, int y2)
{
    if(get_sum(x1, x2, y1, y2)<K)
        return;
    if(get_sum(x1, x2, y1, y2)>=K && get_sum(x1, x2, y1, y2)<=2*K)
        Solv(x1, x2, y1, y2);
    
    if(x1==x2)
    {
        int mid_y=(y1+y2)/2;
        make_solv(x1, x2, y1, mid_y);
        make_solv(x1, x2, mid_y+1, y2);
    }
    else
    {
        int mid_x=(x1+x2)/2;
        make_solv(x1, mid_x, y1, y2);
        make_solv(mid_x+1, x2, y1, y2);
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>K>>N;

    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            cin>>tab[i][j];
    
    for(int i=1;i<=N;++i)
        blocks[i].pb(0);
    
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            if(tab[i][j]>2*K)
                blocks[j].pb(i);

    for(int i=1;i<=N;++i)
    {
        for(int j=1;j<=N;++j)
        {
            tab[i][j]+=tab[i-1][j];
            tab[i][j]+=tab[i][j-1];
            tab[i][j]-=tab[i-1][j-1];
        }
    }
    for(int i=N;i>=1;--i)
    {
        vector<int>wys={0};
        for(int j=1;j<=N;++j)
            wys.pb(i-blocks[j].back());

        vector<pi> last;
        last.pb({-1,0});
        for(int j=1;j<=N;++j)
        {
            while(last.back().f>=wys[j])
                last.pop_back();
            left_block[j]=last.back().s+1;
            last.pb({wys[j],j});
        }
        last.clear();
        last.pb({-1,N+1});
        for(int j=N;j>=1;--j)
        {
            while(last.back().f>=wys[j])
                last.pop_back();
            right_block[j]=last.back().s-1;

            last.pb({wys[j],j});
        }

        for(int j=1;j<=N;++j)
        {
            if(get_sum(left_block[j], right_block[j], i-wys[j]+1,i) >= K)
                make_solv(left_block[j], right_block[j], i-wys[j]+1,i);
        }

        for(int j=1;j<=N;++j)
            if(blocks[j].back()==i)
                blocks[j].pop_back();
    }
    cout<<"NIE";
    return 0;
}