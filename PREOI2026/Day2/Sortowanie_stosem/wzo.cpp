#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e6+7;
int n;
int tab;

vector<int>odp,stos;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    int solv=0;
    for(int i=1;i<=n;++i)
    {
        cin>>tab;
        if(!odp.empty() && tab<odp.back())
        {
            stos.clear();
            odp.clear();
            ++solv;
        }
        while(!stos.empty() && tab>stos.back())
        {
            odp.pb(stos.back());
            stos.pop_back();
        }
        stos.pb(tab);
    }
    if(!stos.empty() || !odp.empty())
        ++solv;
    cout<<solv<<"\n";
    return 0;
}