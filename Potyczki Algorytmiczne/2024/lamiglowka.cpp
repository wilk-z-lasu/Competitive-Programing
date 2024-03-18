#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long;

constexpr int maxn=2000+7;

int n,m;
char x;

int k[maxn][30];
int r[maxn][30];

stack<pair<char,pair<int,char>>> solv;

int obc=1;
int val;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>x;
            k[j][x-'A']++;
            r[i][x-'A']++;
        }
    }

    while(true)
    {
        bool next=false;
        for(int i=1;i<=n;i++)
        {
            obc=0;
            for(int z=0;z<30;z++)
            {
                if(r[i][z]>0)
                {
                    val=z;
                    ++obc;
                }
            }
            if(obc==1)
            {
                r[i][val]=0;
                solv.push({'R',{i,'A'+val}});
                // cout<<'R'<<" "<<i<<" "<<char('A'+val)<<endl;
                for(int j=1;j<=m;++j)
                    --k[j][val];
                next=true;
                break;
            }
        }
        if(!next)//dla kolumn
        for(int j=1;j<=m;++j)
        {
            obc=0;
            for(int z=0;z<30;++z)
            {
                if(k[j][z]>0)
                {
                    val=z;
                    ++obc;
                }
            }
            if(obc==1)
            {
                k[j][val]=0;
                solv.push({'K',{j,'A'+val}});
                // cout<<'K'<<" "<<j<<" "<<char('A'+val)<<endl;
                for(int i=1;i<=n;++i)
                    --r[i][val];
                next=true;
                break;
            }
        }
        if(!next)
            break;
    }

    cout<<solv.size()<<'\n';
    while(!solv.empty())
    {
        cout<<solv.top().f<<' '<<solv.top().s.f<<' '<<solv.top().s.s<<'\n';
        solv.pop();
    }
    
    return 0;
}