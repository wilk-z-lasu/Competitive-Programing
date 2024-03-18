#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin>>n;

    int t=n/10;

    string w;
    cin>>w;

    int odp=0;
    bool spr;
    for(int i = 0;i<10;i++)
    {
        spr=0;
        for(int j =0;j<t;j++)
        {
            if(w[(i*t)+j]=='N') spr=1;
        }
        if(spr==1) odp++;
    }
    cout<<10-odp;
    return 0;
}