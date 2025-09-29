#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

int n;
int LOG = 0;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;

    int akt = n;
    while(akt)
    {
        akt/=2;
        LOG++;
    }

    if(n&1 == 1) cout<<2*LOG + 1;
    else if(n == (1<<(LOG-1))) cout<<2*LOG + 1;
    else cout<<2*LOG + 3;
    return 0;
}