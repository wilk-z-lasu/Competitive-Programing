#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 1e6+7;

int n,p;
int silnia[maxn];
int a[maxn];
int b[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>p;
    if(n==1)
    {
        cout<<((int)1%p);
        return 0;
    }
    else if(n==2)
    {
        cout<<((int)4%p);
        return 0;
    }

    silnia[0] = 1;
    for(int i = 1; i <= n; ++i)
        silnia[i] = (silnia[i-1] * i) % p;

    a[0]=1;
    a[1]=0;
    for(int i = 2; i <= n; ++i)
        a[i] = (((i-1)%p)*((a[i-1] + a[i-2])%p))%p;

    b[1]=0;
    b[2]=0;
    b[3]=0;
    b[4]=4;
    for(int i = 5; i <= n; ++i)
    {
        int d,e;
        if(i % 2 == 0)
        {
            d=2;
            e=4;
        }
        else
        {
            d=1;
            e=2;
        }
        b[i] = (((i-1)*b[i-1])%p + ((int)2*(i-d)*b[i-e])%p) % p;
    }
    cout<<(silnia[n] - 2*a[n] + b[n] + p + p)%p;
}