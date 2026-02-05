#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back


int n,w,m;
vector<pair<int,pi>>vec;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>w>>m;
        vec.pb({w+m,{m,w}});
    }
    sort(vec.begin(), vec.end());

    int solv = 0;

    priority_queue<int>Weight;
    int sum_weight=0;
    for(int i=0;i<n;++i)
    {
        m = vec[i].s.f;
        w = vec[i].s.s;

        Weight.push(m);
        sum_weight += m;
        if(sum_weight > w+m)
        {
            sum_weight -= Weight.top();
            Weight.pop();
        }
        solv = max(solv, (int)Weight.size());
    }
    cout<<solv;
    return 0;
}