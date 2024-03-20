#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxi=100000;

int n;
int a;
int w;

vector<int>vec;

int dp[maxi+7];
int last[maxi+7];

map<int,queue<int>>odz;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    dp[0]=100000;
    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>a;
        odz[a].push(i);
        w+=a;
        vec.push_back(a);
    }

    sort(vec.begin(),vec.end(),greater<int>());

    w=w/2;

    for(int i=0;i<vec.size();++i)
    {
        for(int j=maxi;j>=vec[i];--j)
        {
            if(min(dp[j-vec[i]],vec[i])>dp[j] && min(dp[j-vec[i]],vec[i])+w>=j)
            {
                //lacze dp[j-vec[i]] z dp[j]
                dp[j]=min(dp[j-vec[i]],vec[i]);
                last[j]=vec[i];
            }
        }
    }

    int v;
    for(int i=maxi;i>=0;i--)
    {
        if(dp[i]>0)
        {
            v=i;
            break;
        }
    }

    queue<int>solv;
    while(v!=0)
    {
        solv.push(odz[last[v]].front());
        odz[last[v]].pop();
        // cout<<v<<" -> "<<v-last[v]<<endl;
        v=v-last[v];
    }

    cout<<solv.size()<<'\n';
    while(!solv.empty())
    {
        cout<<solv.front()<<' ';
        solv.pop();
    }

    return 0;
}