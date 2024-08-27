#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=150+2;
int p_input,q_input,r_input;
int x, y, z;
int L,R,mid;
char wczyt;

int input[maxn][maxn][maxn];
int dp[maxn][maxn][maxn];

void prepere_dp(int p, int q, int r)
{
    for(x=1;x<=p;++x)
        for(y=1;y<=q;++y)
            for(z=1;z<=r;++z)
                dp[x][y][z]+=dp[x-1][y][z];
    for(x=1;x<=p;++x)
        for(y=1;y<=q;++y)
            for(z=1;z<=r;++z)
                dp[x][y][z]+=dp[x][y-1][z];
    for(x=1;x<=p;++x)
        for(y=1;y<=q;++y)
            for(z=1;z<=r;++z)
                dp[x][y][z]+=dp[x][y][z-1];
}

inline int sum(int X, int Y, int Z, int a, int wys=1)
{
    return 
    dp[X][Y][Z]
    -dp[X-a][Y][Z]
    -dp[X][Y-a][Z]
    -dp[X][Y][Z-wys]
    +dp[X-a][Y-a][Z]
    +dp[X-a][Y][Z-wys]
    +dp[X][Y-a][Z-wys]
    -dp[X-a][Y-a][Z-wys];
}

int solv;

inline void find_solution(int p, int q, int r)
{
    prepere_dp(p,q,r);

    for(x=p;x>=1;--x)
    {
        for(y=q;y>=1;--y)
        {
            for(z=r;z>=1;--z)
            {
                if(sum(x,y,z,1)==1) continue;

                L=0; R=min(x,y);
                while(L<R)
                {
                    mid=(L+R+1)/2;
                    if(sum(x,y,z, mid) > 0)
                        R=mid-1;
                    else
                        L=mid;
                }
                int a=L;

                L=0; R=z;
                while(L<R)
                {
                    mid=(L+R+1)/2;
                    if(sum(x,y,z, a, mid) > 0)
                        R=mid-1;
                    else
                        L=mid;
                }
                int wys1=L;

                L=0; R=r-z+1;
                while(L<R)
                {
                    mid=(L+R+1)/2;
                    if(sum(x,y,z+mid-1, a, mid) > 0)
                        R=mid-1;
                    else
                        L=mid;
                }

                solv=max(solv, 4*(wys1+L-1)*a);
            }
        }
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>p_input>>q_input>>r_input;
    for(int i=1;i<=p_input*q_input;++i)
    {
        x = 1+(i-1)%p_input;
        y = 1+(i-1)/p_input;
        for(z=1;z<=r_input;++z)
        {
            cin>>wczyt;
            if(wczyt=='P')
                input[x][y][z]=1;
        }
    }

    for(x=1;x<=p_input;++x)
        for(y=1;y<=q_input;++y)
            for(z=1;z<=r_input;++z)
                dp[x][y][z]=input[x][y][z];
    find_solution(p_input, q_input, r_input);

    for(x=1;x<=p_input;++x)
        for(y=1;y<=q_input;++y)
            for(z=1;z<=r_input;++z)
                dp[x][z][y]=input[x][y][z];
    find_solution(p_input, r_input, q_input);

    for(x=1;x<=p_input;++x)
        for(y=1;y<=q_input;++y)
            for(z=1;z<=r_input;++z)
                dp[z][y][x]=input[x][y][z];
    find_solution(r_input, q_input, p_input);

    cout<<solv;
    return 0;
}