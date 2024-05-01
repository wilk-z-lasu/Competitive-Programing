#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1e5+7;
constexpr int shift=1000+7;

int n;
int poz,val;

int tab[2*shift+maxn+7];//[shift]=indeks 0

void make_del()
{   
    queue<int>q;
    for(int i=shift;i<maxn+shift;++i)
        if(tab[i]>2)
            q.push(i);
    while(!q.empty())
    {
        int v=q.front();
        q.pop();
        if(tab[v]<3) continue;
        tab[v-2]+=tab[v]/3;
        tab[v+2]+=tab[v]/3;
        tab[v]=tab[v]%3;
        if(tab[v+2]>=3) q.push(v+2);
        if(tab[v-2]>=3) q.push(v-2);
    }
}

void solv(int x=2*shift+maxn)
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

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>poz>>val;
        poz+=shift;
        tab[poz]+=val;
    }

    make_del();
    solv();

    for(int i=0;i<2*shift+maxn;++i)
        if(tab[i])
            cout<<i-shift<<' ';

    return 0;
}