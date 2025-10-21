#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,m;
int P = 1;
int D = 1;
int nwd;
int New;

bool check()//returns 1 if such x < n*m/nwd exists, that x%m == 0 && (x*New)%n == 0
{
    for(int x = m; x < n*m/nwd; x+=m)
        if((x*New)%n == 0)
            return 1;
    return 0;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    P = 1;
    D = 1;
    nwd = __gcd(n,m);
    New = max((int)1, nwd-1);
    if(check())
        P = New;
    else
        D = New;

    cout<<P+D<<'\n';
    for(int i=1;i<=P;++i)
        cout<<'P';
    for(int i=1;i<=D;++i)
        cout<<'D';
    return 0;
}