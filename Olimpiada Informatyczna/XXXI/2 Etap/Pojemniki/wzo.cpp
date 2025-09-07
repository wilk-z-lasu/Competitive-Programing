// Mateusz Woloszyk
//Solution for 100/100 points in O(n log n)

#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=1e6+7;
constexpr int inf=1e18+7;

int n,k;
int a, a_sum;
set<pi>S;
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;++i)
    {
        cin>>a;
        a_sum += a;
        S.insert({a,i});
    }
    if(a_sum > n*k)
    {
        cout<<"NIE";
        return 0;
    }
    cout<<"TAK\n";
    while(!S.empty())
    {
        int amount = (*S.begin()).f;
        int idx = (*S.begin()).s;
        S.erase(S.begin());

        auto fill = S.upper_bound({k-amount,inf});
        if(fill == S.end())
            cout<<1<<' '<<idx<<' '<<amount<<'\n';
        else
        {
            pi add = *fill;
            S.erase(fill);
            cout<<2<<' '<<idx<<' '<<amount<<' '<<add.s<<' '<<k-amount<<'\n';
            add.f -= k-amount;
            S.insert(add);
        }
    }
    return 0;
}