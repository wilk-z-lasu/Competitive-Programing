#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1e6+2137;
constexpr int s=1e6;

bool x;
int n1,n2;

int tab[maxn];

void solv(int x)
{
    while(x>=1)
    {
        if(tab[x]>0 && tab[x+1]>0)
        {
            int replace=min(tab[x],tab[x+1]);
            tab[x]-=replace;
            tab[x+1]-=replace;
            tab[x+2]+=replace;
            x=x+2;
        }
        else if(tab[x-1]==0 && tab[x]==2)
        {
            tab[x]=0;
            tab[x+1]++;
            tab[x-2]++;
            x++;
        }
        else if(tab[x]==3)
        {
            tab[x]=0;
            tab[x-2]++;
            tab[x+2]++;
            x=x+2;
        }
        else
            x--;
    }
}


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n1;
    for(int i=1;i<=n1;i++)
    {
        cin>>x;
        if(x)
            tab[i]++;
    }
    cin>>n2;
    for(int i=1;i<=n2;i++)
    {
        cin>>x;
        if(x)
            tab[i]++;
    }

    if(tab[1]==2)
    {
        tab[1]=0;
        tab[2]++;
    }
    if(tab[2]==2)
    {
        tab[2]=0;
        tab[3]++;
        tab[1]++;
    }

    solv(max(n1,n2)+10);

    int n;
    for(int i=1;i<=max(n1,n2)+10;i++)
        if(tab[i])
            n=i;

    cout<<n<<' ';
    for(int i=1;i<=n;i++)
        cout<<tab[i]<<' ';

    return 0;
}