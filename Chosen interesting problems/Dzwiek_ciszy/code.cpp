#include<bits/stdc++.h>
using namespace std;
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn=1e6+7;

int n,m,c;
int x[maxn];

deque<pi> maxi;
deque<pi> mini;

inline void Add(deque<pi>& dq, pi add) {
    while(!dq.empty() && dq.front().f <= add.f)
        dq.pop_front();
    dq.push_front(add);
}
inline void Del(deque<pi>& dq, int idx) {
    if(!dq.empty() && dq.back().s==idx)
        dq.pop_back();
}
inline int Get(deque<pi>& dq) {
    return abs(dq.back().f);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n>>m>>c;
    for(int i=1;i<=n;i++)
        cin>>x[i];
    
    bool print_none=1;
    for(int i=1;i<=n;i++)
    {
        Add(mini, {-x[i],i});
        Add(maxi, {x[i],i});
        if(i>=m && Get(maxi) - Get(mini) <= c)
        {
            cout<<i-m+1<<'\n';
            print_none=0;
        }
        Del(mini, i-m+1);
        Del(maxi, i-m+1);
    }
    if(print_none)
        cout<<"NONE";
}