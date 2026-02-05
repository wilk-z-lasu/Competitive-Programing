#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back

constexpr int maxn=2e5+7;
constexpr int mod=1e9+7;

int n,m;
priority_queue<int>Free;
priority_queue<int>Used;
char tab[maxn];

bool used[maxn];

int i[7];
int check()
{
    for(int j=1;j<=n;++j)
        used[j]=0;

    int solv = 0;
    for(int j=1;j<=m;++j)
    {
        if(i[j]==0) continue;
        if(tab[j]=='C')
        {
            if(used[i[j]]) return -1;
            used[i[j]]=1;
        }
        else
        {
            if(!used[i[j]]) return -1;
            used[i[j]]=0;
            solv += i[j];
        }
    }
    for(int j=1;j<=n;++j)
        if(used[j])
            return -1;
    return solv;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //works for m=6;
    cin>>n>>m;
    for(int i=1;i<=m;++i)
        cin>>tab[i];
    for(int i=1;i<=n;++i)
        Free.push(i);
    
    // i[1]=2;
    // i[2]=3;
    // i[3]=0;
    // i[4]=2;
    // i[5]=3;
    // i[6]=0;
    // cout<<check()<<"\n";
    pi odp = {0,0};
    for(i[1]=0;i[1]<=n;++i[1])
    {
        for(i[2]=0;i[2]<=n;++i[2])
        {
            for(i[3]=0;i[3]<=n;++i[3])
            {
                for(i[4]=0;i[4]<=n;++i[4])
                {
                    for(i[5]=0;i[5]<=n;++i[5])
                    {
                        for(i[6]=0;i[6]<=n;++i[6])
                        {
                            int x = check();
                            // if(i[1]==2 && i[2]==3 && i[3]==0 && i[4]==2 && i[5]==3 && i[6]==0) cout<<"x= "<<x<<endl;
                            if(x==-1) continue;
                            if(odp.f<x) odp={x,1};
                            else if(odp.f==x) odp.s = (odp.s+1)%mod;
                        }
                    }
                }
            }
        }
    }
    cout<<odp.f<<" "<<odp.s<<"\n";
    return 0;
}