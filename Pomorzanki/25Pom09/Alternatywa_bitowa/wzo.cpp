#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long

#define pi pair<int,int>
#define f first
#define s second
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 1007;

int n;
int solv[maxn];

int Ask(vector<int> &x)
{
    cout<<"? ";
    cout<<sz(x)<<' ';
    for(auto &u: x)
        cout<<u<<' ';
    cout<<'\n';
    cout<< flush;
    int odp;
    cin>>odp;
    return odp;
}
constexpr int M = (1<<13);
vector<int>Pyt[20];
int odp[20];
int Mask[maxn];

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n;
    vector<int> ask;
    for(int mask=0; mask<M; ++mask)
        if(__builtin_popcount(mask)==6)
            ask.pb(mask);

    for(int i=1;i<=n;++i)
    {
        Mask[i] = ask.back();
        ask.pop_back();
        for(int j=0;j<13;++j)
        {
            if(Mask[i] & (1<<j))
                Pyt[j].pb(i);
        }
    }
    for(int j=0;j<13;++j)
        sort(Pyt[j].begin(), Pyt[j].end());

    for(int j=0;j<13;++j)
        odp[j] = Ask(Pyt[j]);
    
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<13;++j)
            if(!(Mask[i] & (1<<j)))
                solv[i] |= odp[j];
    }
    cout<<"! ";
    for(int i=1;i<=n;++i)
        cout<<solv[i]<<' ';
    cout<<'\n';
    cout<<flush;
    return 0;
}