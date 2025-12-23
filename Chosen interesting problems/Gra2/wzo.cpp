#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define pi pair<int,int>
#define f first
#define s second
#define pb push_back
#define sz(A) (int)(A).size()

//esencial values
constexpr int maxm=1e5+7;
constexpr int maxn=1e7+7;
constexpr int inf=1e9+7;
int m,Q;
int p[maxm];
int what[maxn];
int dzielnik[maxn];

queue<pi>kolejka;

unordered_map<int,int>memo;
int solv(int x)
{
    if(memo.find(x)!=memo.end())
        return memo[x];
    if(x<p[m])
        return memo[x]=1;
    if(what[x]==inf)
        return memo[x]=inf;
    return memo[x]=1+solv(x-(x%what[x]));
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>m>>Q;
    for(int i=1;i<=m;++i)
        cin>>p[i];

    for(int i=1;i<=m;++i)
        for(int j=p[i];j<maxn;j+=p[i])
            dzielnik[j]=max(dzielnik[j], p[i]);

    for(int i=2;i<maxn;++i)
    {
        while(!kolejka.empty() && kolejka.front().f<i)
            kolejka.pop();
        if(!kolejka.empty())
            what[i]=kolejka.front().s;
        else 
            what[i]=inf;
        if(dzielnik[i]!=0)
        {
            int nx = i + dzielnik[i] - 1;
            kolejka.push({nx, dzielnik[i]});
        }
    }
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