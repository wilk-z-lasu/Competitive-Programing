#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define pi pair<int,int>
#define f first
#define s second
#define pb push_back
#define sz(A) (int)(A).size()

//esencial values
constexpr int maxn=1e5+7;
int m,Q;
int p[maxn];
map<int,int>memo;
int solv(int x)
{
    if(memo.find(x)!=memo.end())
        return memo[x];
    if(x<p[m])
        return memo[x]=1;
    int res=1e9;
    for(int i=m;i>=1;--i)
        if(x%p[i]!=0)
            res=min(res,1+solv(x-(x%p[i])));
    return memo[x]=res;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>m>>Q;
    for(int i=1;i<=m;++i)
        cin>>p[i];
    for(int i=1;i<=Q;++i)
    {
        int x;
        cin>>x;
        int odp = solv(x);
        if(odp>=1e9)
            cout<<"oo\n";
        else
            cout<<odp<<"\n";
    }
    return 0;
}