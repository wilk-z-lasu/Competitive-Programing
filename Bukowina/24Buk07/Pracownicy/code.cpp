#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

constexpr int maxn=500000+7;

int n;
int b;
ll f[maxn];
vector<int>vec[maxn];

// multiset<ll>X[maxn];
// inline multiset<ll>& dfs(int v)
// {
//     // cout<<"----"<<v<<"----"<<endl;
//     if(vec[v].empty())
//     {
//         X[v]={f[v]};
//         return X[v];
//     }

//     multiset<ll> &x=dfs(vec[v][0]);

//     for(int i=1;i<vec[v].size();++i)
//     {
//         multiset<ll> &x2=dfs(vec[v][i]);
//         if(x.size()>=x2.size())
//             x.insert(x2.begin(),x2.end());
//         else
//         {
//             x2.insert(x.begin(),x.end());
//             x=x2;
//         }
//     }
//     x.insert(f[v]);
//     ll cost=2;
//     auto it=x.end(); --it;
//     while( f[v]*(cost*cost-(cost-1)*(cost-1)) < *it )
//     {
//         x.erase(it);
//         x.insert(f[v]*(cost*cost-(cost-1)*(cost-1)));
//         ++cost;
//         it=x.end(); --it;
//     }
//     return x;
// }

multiset<ll>solv;
void dfs(int v, multiset<ll>& x)
{
    if(vec[v].empty())
    {
        x.insert(f[v]);
        return;
    }

    for(int i=0;i<vec[v].size();++i)
    {
        multiset<ll> x2={};
        dfs(vec[v][i], x2);

        if(x2.size()>x.size())
            swap(x,x2);
        x.insert(x2.begin(),x2.end());
    }
    
    x.insert(f[v]);
    ll cost=2;
    auto it=x.end(); --it;
    while( f[v]*(cost*cost-(cost-1)*(cost-1)) < *it )
    {
        x.erase(it);
        x.insert(f[v]*(cost*cost-(cost-1)*(cost-1)));
        ++cost;
        it=x.end(); --it;
    }
    return;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;

    for(int i=2;i<=n;++i)
    {
        cin>>b;
        vec[b].push_back(i);
    }

    for(int i=1;i<=n;++i)
        cin>>f[i];

    dfs(1,solv);

    ll odp=0;
    for(auto it=solv.begin();it!=solv.end();++it)
        odp+=*it;
    cout<<odp;

    return 0;
}