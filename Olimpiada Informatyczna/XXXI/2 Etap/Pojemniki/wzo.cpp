// Mateusz Woloszyk

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
multiset<int>S;
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;++i)
    {
        int a;
        cin>>a;
        S.insert(a);
    }

}