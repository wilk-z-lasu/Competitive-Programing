#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int unsigned long long

int n;
int x;

map<int,int>was;//ile operacji potrzeba aby uzyskac was[i]

int sum(int p)
{
    int solv=0;
    while(p>0)
    {
        solv+=p%10;
        p/=10;
    }
    return solv;
}

int32_t main()
{
    ios_base::sync_with_stdio;
    cin.tie(0);
    cout.tie(0);

    cin>>n>>x;
    n--;

    for(int i=0;true;i++)
    {
        if(i==n)
        {
            cout<<x;
            return 0;
        }
        if(was.find(x)!=was.end())
        {
            n-=was[x];
            n%=(i-was[x]);
            break;
        }
        was[x]=i;
        x=2*sum(x);
    }

    for(int i=1;i<=n;i++)
        x=2*sum(x);
    cout<<x;
    return 0;
}