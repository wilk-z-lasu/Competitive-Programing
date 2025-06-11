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


constexpr int maxn = 5e5+7;

int n,k,a;

bool taken[maxn];

vector<int> p1;
vector<int> p2;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;

    for(int i=1;i<=n;++i)
    {
        cin>>a;
        if(!taken[a])
        {
            if(i>k) p2.pb(i);
            taken[a]=1;
        }
        else if(i<=k)
            p1.pb(i);
    }

    if(sz(p1) > sz(p2))
    {
        cout<<"-1";
        return 0;
    }

    reverse(p1.begin(), p1.end());
    reverse(p2.begin(), p2.end());

    int odp=0;
    while(!p1.empty())
    {
        odp += p2.back() - p1.back();
        p1.pop_back();
        p2.pop_back();
    }
    cout<<odp;
    return 0;
}