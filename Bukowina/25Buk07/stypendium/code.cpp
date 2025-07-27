#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>

#define pb push_back
#define sz(A) (int)A.size()

constexpr int inf = 1e18+7;
constexpr int maxn = 2e5+7;

int n;
int skok[maxn][4];
int dp[3*maxn];

set<pi> positiv[4];
set<pi> negativ[4];
int stan[maxn];

void Set(int it)
{
    for(int i=1+stan[it];i<=3;++i)
        positiv[i-stan[it]].insert({skok[it][i] - skok[it][stan[it]], it});
    // for(int i=0;i<stan[it];++i)
    //     negativ[i].insert({skok[it][stan[it]] - skok[it][i], it});
    for(int i=stan[it];i>0;--i)
        negativ[i].insert({skok[it][stan[it]] - skok[it][stan[it]-i], it});
}

void Del(int it)
{
    for(int i=1+stan[it];i<=3;++i)
        positiv[i-stan[it]].erase({skok[it][i] - skok[it][stan[it]], it});
    // for(int i=0;i<stan[it];++i)
    //     negativ[i].erase({skok[it][stan[it]] - skok[it][i], it});
    for(int i=stan[it];i>0;--i)
        negativ[i].erase({skok[it][stan[it]] - skok[it][stan[it]-i], it});
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=3;++j)
            cin>>skok[i][j];

    for(int i=1;i<=n;++i)
        Set(i);

    dp[0]=0;
    for(int i=0;i<3*n;++i)
    {
        pi Best={inf,0};
        if(!positiv[1].empty())
            Best = min(Best, {(*positiv[1].begin()).f, 1});
        if(!negativ[2].empty() && !positiv[3].empty())
            Best = min(Best, {(*positiv[3].begin()).f - (*(--negativ[2].end())).f, 2});
        if(sz(negativ[1]) >= 2 && !positiv[3].empty())
            Best = min(Best, {(*positiv[3].begin()).f - (*(--negativ[1].end())).f - (*(--(--negativ[1].end()))).f, 3});
        if(sz(positiv[2]) >= 2 && !negativ[3].empty())
            Best = min(Best, {(*positiv[2].begin()).f + (*(++positiv[2].begin())).f - (*(--negativ[3].end())).f, 4});
        if(!positiv[2].empty() && !negativ[1].empty())
        {
            if((*(positiv[2].begin())).s != (*(--negativ[1].end())).s)
            {
                // cout<<"Best = "<<(*positiv[2].begin()).f<<" - "<<(*(--negativ[1].end())).f<<endl;

                Best = min(Best, {(*positiv[2].begin()).f - (*(--negativ[1].end())).f, 5});
            }
            if(sz(positiv[2]) >= 2)
                Best = min(Best, {(*(++positiv[2].begin())).f - (*(--negativ[1].end())).f, 6});
            if(sz(negativ[1]) >= 2)
                Best = min(Best, {(*positiv[2].begin()).f - (*(--(--negativ[1].end()))).f, 7});
        }
        if(Best.s == 1)
        {
            int idx = (*positiv[1].begin()).s;
            Del(idx);
            stan[idx]+=1;
            Set(idx);
        }
        else if(Best.s == 2)
        {
            int idx1 = (*positiv[3].begin()).s;
            int idx2 = (*(--negativ[2].end())).s;

            Del(idx1);
            stan[idx1]+=3;
            Set(idx1);

            Del(idx2);
            stan[idx2]-=2;
            Set(idx2);
        }
        else if(Best.s == 3)
        {
            int idx1 = (*positiv[3].begin()).s;
            int idx2 = (*(--negativ[1].end())).s;
            int idx3 = (*(--(--negativ[1].end()))).s;

            Del(idx1);
            stan[idx1]+=3;
            Set(idx1);

            Del(idx2);
            stan[idx2]-=1;
            Set(idx2);

            Del(idx3);
            stan[idx3]-=1;
            Set(idx3);
        }
        else if(Best.s == 4)
        {
            int idx1 = (*positiv[2].begin()).s;
            int idx2 = (*(++positiv[2].begin())).s;
            int idx3 = (*(--negativ[3].end())).s;

            Del(idx1);
            stan[idx1]+=2;
            Set(idx1);

            Del(idx2);
            stan[idx2]+=2;
            Set(idx2);

            Del(idx3);
            stan[idx3]-=3;
            Set(idx3);
        }
        else if(Best.s == 5)
        {
            int idx1 = (*positiv[2].begin()).s;
            int idx2 = (*(--negativ[1].end())).s;

            Del(idx1);
            stan[idx1]+=2;
            Set(idx1);

            Del(idx2);
            stan[idx2]-=1;
            Set(idx2);
        }
        else if(Best.s == 6)
        {
            int idx1 = (*(++positiv[2].begin())).s;
            int idx2 = (*(--negativ[1].end())).s;

            Del(idx1);
            stan[idx1]+=2;
            Set(idx1);

            Del(idx2);
            stan[idx2]-=1;
            Set(idx2);
        }
        else if(Best.s == 7)
        {
            int idx1 = (*positiv[2].begin()).s;
            int idx2 = (*(--(--negativ[1].end()))).s;

            Del(idx1);
            stan[idx1]+=2;
            Set(idx1);

            Del(idx2);
            stan[idx2]-=1;
            Set(idx2);
        }
        dp[i+1] = dp[i] + Best.f;
        // cout<<i<<": "<<Best.f<<" "<<Best.s<<endl;
    }
    for(int i=1;i<=3*n;++i)
        cout<<dp[i]<<' ';
    return 0;
}
