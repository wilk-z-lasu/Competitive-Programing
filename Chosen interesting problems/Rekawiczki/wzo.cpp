#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 27;
constexpr int inf = 1e18;

int n;
int L[maxn], R[maxn];

int addL = 0, addR = 0;
int sumL = 0, sumR = 0;

vector<pi> vec;

vector<pi>S;
void add(pi p)
{
    while(!S.empty() && S.back().f <= p.f && S.back().s <= p.s)
        S.pop_back();
    S.pb(p);
}
void get_odp()
{
    pair<int, pi> solv = {inf, {0, 0}};
    sort(vec.begin(), vec.end());
    for(auto &u: vec)
        add(u);
    for(int i=0;i+1<sz(S);++i)
    {
        int x = min(S[i].f, S[i+1].f)+1;
        int y = min(S[i].s, S[i+1].s)+1;
        solv = min(solv, {x+y, {x,y}});
    }
    cout<<solv.s.f + addL<<"\n"<<solv.s.s + addR<<"\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=0;i<n;++i)
        cin>>L[i];
    for(int i=0;i<n;++i)
        cin>>R[i];
    
    
    for(int i = 0; i < n; ++i)
    {
        while(i < n && (L[i] == 0 || R[i] == 0))
        {
            addL += L[i];
            addR += R[i];
            swap(L[i], L[n-1]);
            swap(R[i], R[n-1]);
            --n;
        }
    }

    for(int mask = 0; mask < (1<<n); ++mask)
    {
        sumL = 0, sumR = 0;
        for(int i = 0; i < n; ++i)
        {
            if(mask&(1<<i))
                sumL += L[i];
            else
                sumR += R[i];
        }
        vec.pb({sumL, sumR});
    }
    get_odp();
    return 0;
}