#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
 
constexpr int maxn=1000000+7;
constexpr int inf=1e18+7;

int n;
int people[maxn];
int escape[maxn];
int a,b,c;
int holes;

vector<pair<int,int>>vec[maxn];

void dfs(int v, int parent=0)
{
    int max_escape=0;
    int sum_up=0;
    for(auto &u: vec[v])
    {
        if(u.f==parent) continue;
        dfs(u.f,v);
        if(people[u.f]<=u.s)
            sum_up+=people[u.f];
        else
        {
            holes++;
            escape[u.f]=inf;
        }
        max_escape=max(max_escape,min(escape[u.f],u.s));
    }

    if(max_escape == 0)
    {
        escape[v]=0;
        people[v]+=sum_up;
    }
    else if(people[v] + sum_up <= max_escape)
    {
        escape[v]=max_escape-(people[v] + sum_up);
        people[v]=0;
    }
    else
    {
        escape[v]=0;
        people[v]+=sum_up;
    }

    for(auto &u: vec[v])
    {
        if(u.f==parent) continue;
        people[u.f]=0;
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>people[i];


    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b>>c;
        vec[a].push_back({b,c});
        vec[b].push_back({a,c});
    }

    dfs(1);

    if(people[1]>0) holes++;
    cout<<holes;

    return 0;
}