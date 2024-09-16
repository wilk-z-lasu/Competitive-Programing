#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=10000+7;
int n, s;

int akt;
int solv[maxn];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n; 
    cin>>s;

    akt = -n*(n-1)/2;
    for(int i=2;i<=n;i++)
    {
        int add = 2*(n-i+1);
        if(akt + add <= s)
        {
            solv[i]=solv[i-1]+1;
            akt += add;
        }
        else
            solv[i]=solv[i-1]-1;
    }
    if(akt!=s)
        cout<<"NIE\n";
    else
        for(int i=1;i<=n;i++)
            cout<<solv[i]<<'\n';
    return 0;
}