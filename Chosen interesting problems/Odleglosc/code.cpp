// #include <bits/stdc++.h>
#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
// #define int int32_t

constexpr int maxn=1e5;
constexpr int maxa=1e6;
int n;

inline void writeInt (int & n)
{
    int N = n, rev, count = 0;
    rev = N;
    while ((rev % 10) == 0) { count++; rev /= 10;} //obtain the count of the number of 0s
    rev = 0;
    while (N != 0) { rev = (rev<<3) + (rev<<1) + N % 10; N /= 10;}  //store reverse of N in rev
    while (rev != 0) { putchar_unlocked(rev % 10 + '0'); rev /= 10;}
    while (count--) putchar_unlocked('0');
    putchar_unlocked('\n');
}
inline int ri() 
{
    int result = 0;
    char ch;
    ch = getchar_unlocked();
    while (true) {
        if (ch >= '0' && ch <= '9') break;
        ch = getchar_unlocked();
    }
    result = ch-'0';
    while (true) {
        ch = getchar_unlocked();
        if (ch < '0' || ch > '9') break;
        result = result*10 + (ch - '0');
    }
    return result;
}
int dys[maxa+1];

int a[maxn];
vector<int> o[maxa+1];

vector<int> poww[maxa+1];
pair<int,int> solv[maxn+1];


bool prime[maxa+1];
inline void sito()
{
    for(int i=2; i*i<=maxa; ++i)
        if(!prime[i])//jestesmy w pierwszej
            for (int j = i*i ; j<=maxa; j+=i)
                prime[j]=1;
}

int32_t main() 
{
    for(int i=0;i<=maxn;i++)
        solv[i].first=1e9;

    sito();

    n=ri();

    for(int i=0;i<n;++i)
    {
        a[i]=ri();
        o[a[i]].emplace_back(i);
    }

    fill(&dys[2], &dys[maxa+1], 1e9);

    for(int i=1;i<=maxa;++i)
        for(int j=i;j<=maxa;j+=i)
        {
            if(!prime[j/i]) dys[j]=min(dys[j],dys[i]+1);
            for(int &u: o[j])
            {
                poww[i].emplace_back(u);
            }
        }

    int maxi;
    int maxi_indeks;
    for(int i=1;i<=maxa;++i)
    {
        maxi=1e9;
        sort(poww[i].begin(),poww[i].end());
        
        for(int &u: poww[i])
            if(dys[a[u]] < maxi)
            {
                maxi=dys[a[u]];
                maxi_indeks=u;
            }
        for(int &u: poww[i])
        {
            if(u!=maxi_indeks)
            {
                solv[u]=min(solv[u],make_pair(dys[a[u]]+dys[a[maxi_indeks]]-2*dys[i], maxi_indeks+1));
                solv[maxi_indeks]=min(solv[maxi_indeks], make_pair(dys[a[u]]+dys[a[maxi_indeks]]-2*dys[i],u+1));
            }
        }
    }

    for(int i=0;i<n;++i)
        writeInt(solv[i].second);
        // cout<<(solv[i].s+1)<<'\n';
    return 0;
}