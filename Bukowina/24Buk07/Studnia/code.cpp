#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e6+7;

int n,m;
int wys[maxn];

int l=0, r=1e9+7;//moze 0
int mid;

int m_tmp;
int wys_tmp[maxn];
int prefix_tmp[maxn];

int suma_ciagu(int ile, int k)
{
    return ile*(ile+1)/2*k;
}

int possible(int k)
{
    m_tmp=m;
    for(int i=1;i<=n;i++)
        wys_tmp[i]=wys[i];

    for(int i=1;i<n;i++)
    {
        if(wys_tmp[i+1]>wys_tmp[i]+k)
        {
            m_tmp-=(wys_tmp[i+1]-(wys_tmp[i]+k));
            wys_tmp[i+1]=wys_tmp[i]+k;
        }
    }
    for(int i=n;i>1;i--)
    {
        if(wys_tmp[i-1]>wys_tmp[i]+k)
        {
            m_tmp-=(wys_tmp[i-1]-(wys_tmp[i]+k));
            wys_tmp[i-1]=wys_tmp[i]+k;
        }
    }

    if(m_tmp<0) return -1;

    prefix_tmp[0]=0;
    for(int i=1;i<=n;i++)
        prefix_tmp[i]=prefix_tmp[i-1]+wys_tmp[i];

    int l=1,r=1;
    for(int i=1;i<=n;i++)
    {
        //rozszerzamy r
        while(r+1<=n && (r+1-i)*k < wys_tmp[r+1])
            r++;
        while(l+1<=n && (i-l)*k >= wys_tmp[l])
            l++;

        // prefix_tmp[i]

        int obszar_lewo=suma_ciagu(i-l,k);
        int obszar_prawo=suma_ciagu(r-i,k);
        int suma_pref=prefix_tmp[r]-prefix_tmp[l-1];

        int koszt=suma_pref-obszar_lewo-obszar_prawo;

        if(m_tmp-koszt>=0) return i;
    }
    return -1;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++)
        cin>>wys[i];

    while(l<r)
    {
        mid=(l+r)/2;

        int solv=possible(mid);
        if(solv!=-1)
            r=mid;
        else
            l=mid+1;
    }

    cout<<possible(l)<<' '<<l;

    return 0;
}