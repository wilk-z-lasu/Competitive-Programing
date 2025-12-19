#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define f first
#define s second

int tab[100002];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m;cin>>m;

    for(int iter=0;iter<m;iter++)
    {
        int n;cin>>n;
        for(int i=1;i<=n;i++) cin>>tab[i];
        tab[n+1]=tab[n];
        tab[0]=tab[1];

        int dis=0;

        int ostatni=n;
        while(tab[ostatni-1]==tab[ostatni] && ostatni>=1) ostatni--;
        if(ostatni==0)
        {
            cout<<"BRAK \n";
            continue;
        }
        ostatni--;

        for(int i=1;i<=n;i++)
        {
            if(tab[i]==tab[n]) dis=max(dis, ostatni-i);
            else 
            {
                dis=max(dis, n-i);
                break;
            }
        }
        cout<<dis<<"\n";
    }
    
    return 0;
}