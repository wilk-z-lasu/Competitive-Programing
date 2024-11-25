#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=5e5+7;

int m,d,n;

int tab[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>m>>d>>n;

    for(int i=1;i<=n;i++)
        cin>>tab[i];

    sort(&tab[1], &tab[n+1]);

    int idx=0;
    for(int i=n;i>=1;i--)
    {
        if(tab[i]>=(m-d))
            idx=i;
    }
    if(idx==0)
    {
        cout<<0;
        return 0;
    }

    int poz=0;
    int odp=0;
    if(poz >= d - (tab[idx]-(m-d))/2)
    {
        cout<<odp+1;
        return 0;
    }
    for(int i=n;i>=1;i--)
    {
        if(i==idx) continue;

        int need = abs(poz-d);
        tab[i]-=need;

        if(poz<m && tab[i]>0)
        {
            odp++;
            poz+=tab[i];
        }

        if(poz >= m)
        {
            cout<<odp;
            return 0;
        }
        if(poz >= d - (tab[idx]-(m-d))/2)
        {
            cout<<odp+1;
            return 0;
        }
    }
    cout<<0;
    return 0;
}