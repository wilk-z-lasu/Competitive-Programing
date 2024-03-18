#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=300000+7;

int n;
char x;
bool tab[maxn];
queue<int>poz;

int solv[maxn];

void add(int a, int b, int var)
{
    solv[a]+=var;
    solv[b+1]-=var;
}
void push()
{
    for(int i=1;i<maxn;i++)
        solv[i]+=solv[i-1];
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>x;
        if(x=='P')
            tab[i]=1;
        else
        {
            tab[i]=0;
            poz.push(i);
        }
    }

    for(int i=1;i<=n;i++)
    {
        if(tab[i]==1 && !poz.empty())
        {
            // cout<<i<<' '<<poz.front()<<endl;
            swap(tab[i], tab[poz.front()]);
            add(i,i,1);
            add(poz.front(),poz.front(),1);
            if(i+1<=poz.front()-1)
                add(i+1,poz.front()-1,2);
            poz.pop();
        }
        else if(tab[i]==0 && poz.front()==i)
            poz.pop();
    }
    push();
    for(int i=1;i<=n;i++)
        cout<<solv[i]<<' ';
    return 0;
}