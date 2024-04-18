#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr int inf=1e18+7;

int n, m;
int m_prim, dwa, f_prim;
int k;

int pot(int x, int p, int mod)
{
    int solv=1;
    while(p)
    {
        if(p&1) solv=(solv*x)%mod;
        x=(x*x)%mod;
        p=p/2;
    }
    return solv;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    m_prim=m;
    while(m_prim%2==0)
    {
        m_prim/=2;
        ++dwa;
    }

    int dziel=3;
    f_prim=1;
    while(m_prim>1 && dziel*dziel<=m)
    {
        k=0;
        while(m_prim%dziel==0)
        {
            m_prim/=dziel;
            k++;
        }
        if(k>0)
            f_prim*=((dziel-1)*pot(dziel,k-1,inf));
        ++dziel;
    }
    if(m_prim!=1)
        f_prim*=(m_prim-1);

    int wyk=((pot(2, n, f_prim) - dwa)%f_prim + f_prim)%f_prim;
    int i1=pot(2, wyk, m);
    int i2=pot(2, dwa, m);
    int i12=(i1 * i2)%m;

    cout<<(i12 + 1)%m;
    return 0;
}