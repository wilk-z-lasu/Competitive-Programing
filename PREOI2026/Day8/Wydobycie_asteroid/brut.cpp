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

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>N>>M;
    for(int i=1;i<=N;++i)
        cin>>v[i]>>m[i];

    int solv = 0;
    for(int mask = 0; mask<(1<<N);++mask)
    {
        int sum_v = 0, sum_m = 0;
        for(int i=0;i<N;++i)
            if(mask & (1<<i))
                sum_v+=v[i+1], sum_m+=m[i+1];
        if(sum_m <= M)
            solv = max(solv, sum_v);
    }
    cout<<solv;
    return 0;
}