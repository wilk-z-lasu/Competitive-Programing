#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr int maxn = 507;

int n,m;
int E[maxn], F[maxn], G[maxn];

int pot(int x, int k)
{
    int odp = 1;
    while(k)
    {
        if(k&1)
            odp = (odp*x)%m;
        x = (x*x)%m;
        k/=2;
    }
    return odp;
}

int silnia[maxn];
int Newton[maxn][maxn];
int Dwumian(int N, int K)
{
    if(!Newton[N][K])
        Newton[N][K] = (silnia[N] * pot((silnia[K]*silnia[N-K])%m, m-2))%m;
    return Newton[N][K];
}

int dp[2][maxn][maxn];//[dlugosc][# maksimow prefixowych][akcenty]
int t[maxn][maxn];//[dlugosc][Akcenty]
int t_prim[maxn][maxn];//[dlugosc][Akcenty]
int P[maxn][maxn];//[][] it means sth I am sure

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;++i)
        cin>>E[i];
    for(int i=1;i<=n;++i)
        cin>>F[i];
    for(int i=0;i<=n-1;++i)
        cin>>G[i];
    
    silnia[0] = 1;
    for(int i=1;i<=n;++i)
        silnia[i] = (silnia[i-1]*i)%m;

    dp[1][1][0] = 1;
    t[0][0] = E[1];
    t_prim[0][0] = F[1];

    for(int a=1; a<=n; ++a)
    {
        for(int MXp=1; MXp<=a; ++MXp)
        {
            for(int A=0; A<=a; ++A)
            {
                dp[(a+1)%2][MXp+1][A+1] += dp[a%2][MXp][A];
                dp[(a+1)%2][MXp][A] += (A * dp[a%2][MXp][A])%m;
                dp[(a+1)%2][MXp][A+1] += ((a-1-A) * dp[a%2][MXp][A])%m;
                dp[(a+1)%2][MXp][A] += dp[a%2][MXp][A];

                dp[(a+1)%2][MXp+1][A+1] %= m;
                dp[(a+1)%2][MXp][A] %= m;
                dp[(a+1)%2][MXp][A+1] %= m;

                t[a][A] += (E[MXp+1] * dp[a%2][MXp][A])%m;
                t[a][A] %= m;
                t_prim[a][A] += (F[MXp+1] * dp[a%2][MXp][a-(a!=0)-A])%m;
                t_prim[a][A] %= m;
            }
        }
        for(int MXp=1; MXp<=a; ++MXp)
            for(int A=0; A<=a; ++A)
                dp[a%2][MXp][A] = 0;
    }
    for(int a = 0; a <= n; ++a)   
    {
        for(int A = 0; A <= n; ++A)
        {
            for(int B = 0; A+B+1 <= n; ++B)
            {
                if(a==0)
                    P[a][B] += (t[a][A] * G[A+B])%m;
                else
                    P[a][B] += (t[a][A] * G[A+B+1])%m;

                P[a][B] %= m;
            }
        }
    }
    for(int k=1;k<=n;++k)
    {
        int solv = 0;
        for(int a=0; a <= k-1; ++a)
        {
            int b = k - a - 1;
            for(int B = 0; B <= b; ++B)
                solv = (solv + (Dwumian(a+b, a) * ((P[a][B] * t_prim[b][B])%m))%m)%m;
        }
        cout<<solv<<' ';
    }
    return 0;
}