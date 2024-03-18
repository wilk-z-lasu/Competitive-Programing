// Solution for 6/10 pkt //

#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

#pragma GCC optimize("O3","unroll-loops")

constexpr int maxn=500+2;
constexpr int add=10000000;

int n, num;
int a[maxn], pref[maxn];
int ciag[maxn*(maxn+1)/2];

int get(int a,int b)
{
    if(b<a) swap(a,b);
    return pref[b]-pref[a-1];
}

ll ile[2*add+7];
ll solv;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        pref[i]=pref[i-1]+a[i];
    }

    //generating sequence
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j<=n;++j)
        {
            num++;
            ciag[num]=get(i,j);
        }
    }

    //solving typical 3SUM problem
    for(int i=1;i<=num;++i)
    {
        for(int j=i+1;j<=num;++j)
            solv+=ile[-(ciag[i]+ciag[j])+add];
        ile[ciag[i]+add]++;
    }
    cout<<solv;
    return 0;
}