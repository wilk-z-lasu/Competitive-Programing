#include <bits/stdc++.h>
using namespace std;

int n;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int ile = 0; ile <= 8; ++ile)
    {
        int x = n - 3*ile;
        if(x>=0 && x%8==0)
        {
            cout<<"TAK";
            return 0;
        }
    }
    
    cout<<"NIE";
    return 0;
}