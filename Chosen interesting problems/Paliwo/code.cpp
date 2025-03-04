#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

queue<pair<int,int>>punkt;

int akt_poz;
int p,n;
int c,d;
int odp;

deque<pair<int,int>>mono;

void add(int val, int poz)
{
    while(!mono.empty() && mono.back().f>=val)
        mono.pop_back();
    mono.push_back({val,poz});
}
void del(int poz)
{
    if(mono.front().s<=poz)
        mono.pop_front();
}
int mini()
{
    return mono.front().f;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>p>>n;

    akt_poz=1;
    for(int i=1;i<=n;i++)
    {
        cin>>c>>d;
        punkt.push({c,akt_poz});
        akt_poz+=d;
    }

    for(int i=1;i<=akt_poz-1;i++)
    {
        if(punkt.front().s==i)
        {
            add(punkt.front().f, punkt.front().s);
            punkt.pop();
        }
        del(i-p);//jesli jest ujemne to nie usunie nic z kolejki

        odp+=mini();
    }
    cout<<odp;

    return 0;
}