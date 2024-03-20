#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1e6+2137;
constexpr int s=1e6;


bool x;
int n1,n2;

int tab[maxn];

void check(int x)
{
    while(true)
    {
        if(tab[x]>=2 && !tab[x-2])
        {
            // cout<<"dwa\n";
            tab[x+1]++;
            tab[x-2]++;
            tab[x]-=2;
            x=x-2;
        }
        else if(tab[x]>=1 && tab[x-1]>=1)
        {
            // cout<<"redukcja\n";
            tab[x+1]++;
            tab[x]--;
            tab[x-1]--;
            x=x+1;
        }
        else if(x<=max(n1,n2)+10)//1000
        {
            // cout<<"skip\n";
            x=x+1;
        }
        else
            break;
    }
}

void make(int x)
{
    while(x>=2)
    {
        if(tab[x] && tab[x-1])
        {
            tab[x]--;
            tab[x-1]--;
            tab[x+1]++;
        }
        if(tab[x]>=2)
        {
            // cout<<"dwa\n";
            tab[x+1]++;
            tab[x-2]++;
            tab[x]-=2;
        }
        x--;
    }
}

void unupo(int x)
{
    while(x<=max(n1,n2)+10)
    {
        if(tab[x])
        {
            int l=1;
            while(x+1<=max(n1,n2)+10 && tab[x+1])
            {
                l++;
                x++;
            }
            for(int i=x+1;i>=x-l+1;i-=2)
            {
                if(tab[i-1] && tab[i-2])
                {
                    tab[i-1]=tab[i-2]=0;
                    tab[i]=1;
                }
            }
        }
        x++;
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

    // for(int i=1;i<=10;i++)
    //     cout<<tab[i]<<' ';
    // cout<<endl;
    check(2);

    // // nie wyswietla 13
    // for(int i=1;i<max(n1,n2)+10;i++)
    //     if(tab[i]>=1 && (tab[i-1]>=1 || tab[i+1]>=1))
    //         return 13;
    make(max(n1,n2)+10);

    // if(tab[0])
    // {
    //     tab[1]++;
    //     tab[0]--;
    // }
    // if(tab[1]==2)
    // {
    //     tab[1]-=2;
    //     tab[2]++;
    // }

    unupo(2);


    int n;
    for(int i=1;i<=max(n1,n2)+10;i++)
        if(tab[i])
            n=i;

    cout<<n<<' ';
    for(int i=1;i<=n;i++)
        cout<<tab[i]<<' ';

    return 0;
}