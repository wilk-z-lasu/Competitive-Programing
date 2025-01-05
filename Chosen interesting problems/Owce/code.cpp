#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define int long long
#define pi pair<int,int>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

constexpr int maxn=600+7;
constexpr int maxk=20000+7;
constexpr int maxi=15000+7;

int n,k,m;

pi tab[maxn];
pi pkt[maxk];

bool ban[maxn][maxn];

int nr(int x)
{
    return 1+(x-1)%n;
}

int f(pi X, pi a, pi b)
{
    if((X.x-a.x) * (X.y-b.y) == (X.x-b.x) * (X.y-a.y))
        return 1;
    if((X.x-a.x) * (X.y-b.y) < (X.x-b.x) * (X.y-a.y))
        return 2;
    else
        return 3;
}

int pref[maxn][maxn];

bool allowed[maxn][maxn];

int dp[maxn][maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k>>m;

    for(int i=1;i<=n;i++)
        cin>>tab[i].x>>tab[i].y;
    for(int i=1;i<=k;i++)
        cin>>pkt[i].x>>pkt[i].y;

    for(int i=1;i<=k;i++)
    {
        // cout<<"-------"<<i<<"-------"<<endl;
        int poczatek=2;
        for(int koniec=1;koniec<=n;koniec++)
        {
            while(nr(poczatek+1) != koniec)
            {
                int opt = f(tab[koniec], tab[nr(poczatek+1)], pkt[i]);

                if(opt==1)
                {
                    ban[koniec][nr(poczatek+1)]=1;
                    break;
                }
                else if(opt==2)
                    ++poczatek;
                else if(opt==3)
                    break;
            }

            pref[koniec][koniec]++;
            pref[koniec][nr(poczatek+1)]--;
            // cout<<koniec<<" -> "<<nr(poczatek)<<endl;
        }
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=i+1; nr(j)!=(i); j++)
            pref[i][nr(j)] += pref[i][nr(j-1)];
        for(int j=i+2; nr(j+1)!=(i); j++)
            if(!ban[i][nr(j)] && pref[i][nr(j)]%2==0)
                allowed[i][nr(j)]=1;
        allowed[i][nr(i+1)]=1;
        allowed[nr(i+1)][i]=1;
    }

    // for(int i=1;i<=n;i++)
    //     for(int j=1;j<=n;j++)
    //         if(!allowed[i][j] && abs(i-j)>1)
    //             cout<<i<<" "<<j<<endl;

    for(int i=1;i<=n;i++)
        dp[i][nr(i+1)]=1;

    for(int dis=2;dis<=n;++dis)
    {
        for(int i=1;i<=n;++i)
        {
            int e=nr(i+dis);
            for(int z = i+1; nr(z) != e; ++z)
            {
                if(allowed[i][nr(z)] && allowed[nr(z)][e]  && allowed[i][e])
                    dp[i][e] = (dp[i][e] + dp[i][nr(z)] * dp[nr(z)][e])%m;
            }
        }
    }
    cout<<dp[1][n];
}