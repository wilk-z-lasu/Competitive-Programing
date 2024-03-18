#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=20;
constexpr int n=18;

int a[maxn];
int b[maxn];
int suma;
int sumb;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        suma+=a[i];
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
        sumb+=b[i];
    }

    if(suma>sumb)
    {
        cout<<"Algosia";
        return 0;
    }
    if(sumb>suma)
    {
        cout<<"Bajtek";
        return 0;
    }

    sort(&a[1],&a[n+1],greater<int>());
    sort(&b[1],&b[n+1],greater<int>());

    for(int i=1;i<=n;i++)
    {
        if(a[i]>b[i])
        {
            cout<<"Algosia";
            return 0;
        }
        if(a[i]<b[i])
        {
            cout<<"Bajtek";
            return 0;
        }
    }
    cout<<"remis";
    return 0;
}