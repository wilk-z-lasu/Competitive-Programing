#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define f first
#define s second

constexpr int inf=1e9+7;

int n;
int a;
int l,r;
int solv;
set<pair<int,int>>v;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    v.insert({0,-1});
    v.insert({inf,-1});

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>a;
        v.insert({a,0});
        auto wzk=v.find({a,0});
        l=(*prev(wzk)).s;
        r=(*next(wzk)).s;
        // cout<<l<<" "<<r<<endl;
        v.erase({a,0});
        v.insert({a,max(l,r)+1});
    }
    for(auto &u: v)
        solv=max(solv,u.s);

    cout<<solv;
    
    return 0;
}