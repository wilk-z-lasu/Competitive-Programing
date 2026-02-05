#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=2e5+7;
constexpr int mod=1e9+7;

int n,m;
char tab[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    vector<pair<bool,int>>vec;

    cin>>n>>m;
    for(int i=1;i<=m;++i)
        cin>>tab[i];

    int akt=0;
    tab[0]=tab[1];
    for(int i=1;i<=m+1;++i)
    {
        if(tab[i]==tab[i-1]) ++akt;
        else
        {
            if(tab[i-1]=='C')
                vec.pb({0,akt});
            else
                vec.pb({1,akt});
            akt = 1;
        }
    }

    int solv1=0; int solv2=1;
    for(int val=n;val>=1;--val)
    {
        for(int i=0;i+1<sz(vec);++i)
        {
            if(vec[i].f==0 && vec[i+1].f==1)
            {
                solv1 += val;
                solv2 = (solv2 * ((vec[i].s * vec[i+1].s)%mod)) % mod;
                vec[i].s--;
                vec[i+1].s--;
                i++;
            }
        }
        vector<pair<bool,int>>tmp = {};
        for(int i=0;i<sz(vec);++i)
        {
            if(vec[i].s==0) continue;
            if(!tmp.empty() && tmp.back().f==vec[i].f)
                tmp.back().s += vec[i].s;
            else
                tmp.pb(vec[i]);
        }
        vec = tmp;
    }
    cout<<solv1<<" "<<solv2;
    return 0;
}