//Gets 86 points
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e6+7;

int N,S;
int Y,X;

vector<int> kol[maxn];
vector<pi> wyn[maxn];
    

map<pi, int>memoryL[maxn];
int ask_left(int p, int k, int column)
{
    if(memoryL[column].find({p,k}) != memoryL[column].end())
        return memoryL[column][{p,k}];
    
    int odp = 0;
    for(auto &u: wyn[column-1])
    {
        if(u.s<p || k<u.f) continue;
        int l = max(u.f, p);
        int r = min(u.s, k);
        odp = max(odp, ask_left(l, r, column-1));
    }
    return memoryL[column][{p,k}] = k-p+1+odp;
}

map<pi, int>memoryR[maxn];
int ask_right(int p, int k, int column)
{
    if(memoryR[column].find({p,k}) != memoryR[column].end())
        return memoryR[column][{p,k}];
    
    int odp = 0;
    for(auto &u: wyn[column+1])
    {
        if(u.s<p || k<u.f) continue;
        int l = max(u.f, p);
        int r = min(u.s, k);
        odp = max(odp, ask_right(l, r, column+1));
    }
    return memoryR[column][{p,k}] = k-p+1+odp;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>N>>S;
    for(int i=1;i<=S;++i)
    {
        cin>>Y>>X;
        kol[X].pb(Y);
    }

    for(int i=1;i<=N;++i)
    {
        if(kol[i].empty()) continue;
        sort(kol[i].begin(), kol[i].end());
        for(int s=0;s<sz(kol[i]);++s)
        {
            int k = s;
            while(k+1 < sz(kol[i]) && kol[i][k]+1 == kol[i][k+1])
                ++k;
            wyn[i].pb({kol[i][s], kol[i][k]});
            s = k;
        }
    }

    int solv = 0;
    for(int i=1;i<=N;++i)
    {
        // cout<<"---- "<<i<<" ----\n";
        for(auto x:wyn[i])
        {
            // cout<<x.f<<" "<<x.s<<"\n";
            solv = max(solv, ask_left(x.f, x.s, i) + ask_right(x.f, x.s, i) - (x.s-x.f+1));
        }
    }
    cout<<solv<<"\n";
    return 0;
}