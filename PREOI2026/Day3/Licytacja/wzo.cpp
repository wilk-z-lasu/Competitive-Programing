#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e5+7;
constexpr int mod=1e9+7;

int n;
int a[maxn];
int b[maxn];


int New_start[maxn];
int New_end[maxn];
// int siz[maxn];

vector<int> vec;
vector<pi> przedzial; //przedzialy po kompresji
vector<int> val;
vector<int> pref_val;

vector<int> p[maxn];//p[i] -> list of intervals contained in [a[i],b[i]]

int numeruj=0;

int f(int x)
{
    x--;
    return (x*(x+1)/2)%mod;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;++i)
    {
        cin>>a[i]>>b[i];
        vec.pb(a[i]); //start
        vec.pb(b[i]+1); //end
    }

    sort(vec.begin(),vec.end());
    for(int i=0;i+1<sz(vec);++i)
    {
        while(i+1 < sz(vec) && vec[i]==vec[i+1])
            ++i;
        if(i+1 == sz(vec))
            break;
        przedzial.pb({vec[i], vec[i+1]-1});
    }

    // for(auto &u: przedzial)
    // {
    //     cout<<u.f<<" "<<u.s<<"\n";
    // }

    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<sz(przedzial);++j)
        {
            if(przedzial[j].f == a[i])
                New_start[i] = j;
            if(przedzial[j].s == b[i])
                New_end[i] = j;
        }
    }

    // for(int i=1;i<=n;++i)
    //     cout<<New_start[i]<<" "<<New_end[i]<<"\n";

    val.resize(sz(przedzial));
    pref_val.resize(sz(przedzial));
    for(int j=0;j<sz(przedzial);++j)
        val[j] = pref_val[j] = 0;

    for(int i=1;i<=n;++i)
    {
        for(int j=New_start[i];j<=New_end[i];++j)
        {
            int pref = 1;
            if(j>0)
                pref = (pref + pref_val[j-1])%mod;

            val[j] = (val[j] + pref) % mod;
        }

        for(int j=0;j<sz(przedzial);++j)
            cout<<j<<": "<<val[j]<<endl;
        cout<<"------"<<endl;
        for(int j=0;j<sz(przedzial);++j)
        {
            int Prev = 0;
            if(j>0) Prev = pref_val[j-1];
            pref_val[j] = (Prev + val[j] +f(przedzial[j].s-przedzial[j].f+1)) % mod;
        }
    }

    // cout<<pref_val[sz(przedzial)-1]<<"\n";

    int solv = 0; 
    for(int j=0;j<sz(przedzial);++j)
        solv = (solv + val[j]*(przedzial[j].s-przedzial[j].f+1) + f(przedzial[j].s-przedzial[j].f+1)) % mod;
    cout<<solv<<"\n";
    return 0;
}