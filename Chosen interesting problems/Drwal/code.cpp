#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

int drzewo;
pair<int,int>wys[10007];//.f=ile kopniec //.s=ostatnia pozycja
pair<int,int>update[10007];//.f=ile kopniec //.s=ostatnia pozycja


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>drzewo;
        update[drzewo]={1,i};

        for(int j=1;j<=10000-drzewo;j++)
        {
            if(wys[j].f==0) continue;

            if(wys[j].s==i-1)
            {
                update[j+drzewo]={wys[j].f,i};
            }
            else
            {
                update[j+drzewo]={wys[j].f+1,i};
            }
        }
        for(int j=1;j<=10000;j++)
        {
            if(update[j].f<=wys[j].f || wys[j]==make_pair(0,0))
            {
                wys[j]=update[j];
            }
        }
    }
    int p;cin>>p;
    for(int i=0;i<p;i++)
    {
        int t;cin>>t;
        if(wys[t]==make_pair(0,0)) cout<<-1<<'\n';
        else cout<<wys[t].f<<'\n';
    }
}