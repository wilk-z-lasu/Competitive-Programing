#include <bits/stdc++.h>
using namespace std;

int n;
int x;
int s;

bitset<1800007>mb;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    mb[0]=1;

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        s+=x;
        mb|=(mb<<x);
    }

    // for(int i=0;i<=12;i++)
    //     cout<<i<<": "<<mb[i]<<endl;

    for(int i=s/2 + s%2; i < 1800007;i++)
        if(mb[i])
        {
            cout<<i;
            return 0;
        }
}