#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=1e5+7;

int n;
int x,y;
vector<int>X,Y;
map<int,int>have;
int solv;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>x>>y;
        if(x==0)
            X.pb(y);
        else if(y==0)
            Y.pb(x);
    }
    for(int i=0;i<sz(X);++i)
        for(int j=0;j<i;++j)
            ++have[X[i]*X[j]];

    for(int i=0;i<sz(Y);++i)
    {
        for(int j=0;j<i;++j)
        {
            solv+=have[Y[i]*Y[j]];
        }
    }
    cout<<solv;
    return 0;
}