#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

const int maxn = 5e5+5;

int N,M;
int v[maxn],m[maxn];
map<int,vector<int>> vec;

int get_sum(int k, vector<int>& x)
{
    int sum = 0;
    for(int i=max(0ll, sz(x)-k); i<sz(x);++i)
        sum+=x[i];
    return sum;
}

void get_pop(int k, vector<int>& x)
{
    while(k-- && !x.empty())
        x.pop_back();
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>N>>M;
    for(int i=1;i<=N;++i)
    {
        cin>>v[i]>>m[i];
        vec[-m[i]].pb(v[i]);
    }

    // if(N<=20)
    // {
    //     int solv = 0;
    //     for(int mask = 0; mask<(1<<N);++mask)
    //     {
    //         int sum_v = 0, sum_m = 0;
    //         for(int i=0;i<N;++i)
    //             if(mask & (1<<i))
    //                 sum_v+=v[i+1], sum_m+=m[i+1];
    //         if(sum_m <= M)
    //             solv = max(solv, sum_v);
    //     }
    //     cout<<solv;
    //     return 0;
    // }

    for(auto &u: vec)
        sort(u.s.begin(),u.s.end());

    int solv = 0;
    for(auto &u: vec)
    {
        int cost = -u.f;
        cout<<"cost: "<<cost<<"\n";
        while(cost <= M)
        {
            pair<int, pi> best = {0, {0, 0}};
            for(auto &v: vec)
            {
                if(-v.f > cost) continue;
                int d = u.f/v.f;
                d = min(d, sz(v.s));
                int sum = get_sum(d, v.s);
                best = max(best, {sum, {d, -v.f}});
            }
            if(best.f == 0) break;

            cout<<"best: "<<best.f<<" "<<best.s.f<<" "<<best.s.s<<"\n";
            solv += best.f;
            M -= best.s.f*(best.s.s);
            get_pop(best.s.f, vec[-best.s.s]);
        }
    }
    cout<<solv;
    return 0;
}