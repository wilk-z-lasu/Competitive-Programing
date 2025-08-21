//some brute force solution which gets 46 I wrote a long time ago
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int inf=500000000000007;//5*1e13+7

int n;
int a;

priority_queue<pair<int,pair<int,int32_t>>>pq;//.f=odleglosc .s.f=lewy bok .s.s=ile moge wrzucic
queue<pair<int,pair<int,int32_t>>>q;

int solv[500007];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for(int i=0;i<500007;++i)
        solv[i]=inf;

    pq.push({inf-0,{0,0}});

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        // cout<<"--------"<<i<<endl;
        cin>>a;
        while(!pq.empty() && pq.top().f>a)
        {
            auto top=pq.top();
            pq.pop();
            if(solv[top.s.s+1]>top.s.f+a)
            {
                q.push({a,{top.s.f,top.s.s}});
                q.push({top.f-a,{top.s.f+a,top.s.s+1}});
            }
        }
        while(!q.empty())
        {
            pq.push(q.front());
            // cout<<q.front().f<<" "<<q.front().s.f<<" "<<q.front().s.s<<endl;
            solv[q.front().s.s]=min(solv[q.front().s.s],q.front().s.f);
            q.pop();
        }
    }
    for(int i=1;i<=n;++i)
        cout<<solv[i]<<" ";

    return 0;
}