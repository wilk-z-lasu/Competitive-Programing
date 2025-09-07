#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

int n;
int tab[100007];

bool check(int x)
{
    int p1=x;
    for(int p2=n;p2>=n-x+1;p2--)
    {
        if(tab[p1]*2>tab[p2])
            return false;
        p1--;
    }
    return true; //jesli mozna zapakowac x pierwszyech kangorow
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>tab[i];


    sort(&tab[1],&tab[n+1]);

    int l=0,r=n/2,mid;
    while(l<r)
    {
        mid=(l+r+1)/2;
        if(check(mid))
            l=mid;
        else
            r=mid-1;
    }
    cout<<l;
    return 0;
}